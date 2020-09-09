#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jpeglib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../incl/clasificacion.h"
#include "../incl/funciones.h"

//Entradas: argc <tipo: int> (cantidad de argumentos) - argv <tipo: array de char> (lista de argumentos)
//Funcionamiento: inicia el programa, realiza el getopt y ejecuta los procesos del pipeline para la
//modificacion de las imagenes y la clasificacion.
//Salidas: 0 si termina correctamente, 1 si termina con errores.
int main(int argc, char* argv[]){

	//Pipe
	int paip6[2];

	if (pipe(paip6) == -1){ 
        fprintf(stderr, "Pipe fallido \n" ); 
        return 1; 
    }

	//Fork con exec
	pid_t forky = fork();

	if(forky < 0){
		fprintf(stderr, "Fork fallido \n" ); 
        return 1;
	}
	if(forky == 0){
		//Hijo
		close(paip6[1]);
		fprintf(stderr, "Estoy en hijo mainClasificacion \n" );
		int dupiao = dup2(paip6[0], STDIN_FILENO);
		if (dupiao == -1){
			fprintf(stderr, "Dup2 fallido \n" );
			return 1; 
		}
		close(paip6[0]);
		execv("./mainEscritura", argv);
	}

	//Padre
	close(paip6[0]);
	fprintf(stderr, "Estoy en padre mainClasidicacion \n" );
	int dupiao = dup2(paip6[1], STDOUT_FILENO);
	if (dupiao == -1){
		fprintf(stderr, "Dup2 paip6[1] fallido \n" );
		return 1; 
	}
	close(paip6[1]);
	
	int c = atoi(argv[2]);
	int u = atoi(argv[4]);
	int n = atoi(argv[6]);
	char* m = argv[8];
	int nb;
	Imagen* imgFiltro = (Imagen*)malloc(sizeof(Imagen));
	int i;
	//imgFiltro es la que se le entrega a este main
	
	for(i = 1; i <= c; i++){
		uint32_t alt;
		uint32_t anch;
		uint32_t canals;
		read(STDIN_FILENO, &alt, sizeof(uint32_t));
		read(STDIN_FILENO, &anch, sizeof(uint32_t));
		read(STDIN_FILENO, &canals, sizeof(uint32_t));
		imgFiltro->alto = alt;
		imgFiltro->ancho = anch;
		imgFiltro->canales = canals;
		int ancho = imgFiltro->ancho * imgFiltro->canales;
		crearMatrizJpg(imgFiltro);
		int j;
		int k;
		uint8_t pxl;
		for(j = 0; j < imgFiltro->alto; j++){
			for(k = 0; k < ancho; k++){
				uint8_t pxl;
				read(STDIN_FILENO, &pxl, sizeof(uint8_t));
				imgFiltro->matriz[j][k] = pxl;
			}
		}

		//5° clasificacion de imagen
		nb = clasificar(imgFiltro, n);

		alt = imgFiltro->alto;
		anch = imgFiltro->ancho;
		canals = imgFiltro->canales;

		write(STDOUT_FILENO, &alt, sizeof(uint32_t));
		write(STDOUT_FILENO, &anch, sizeof(uint32_t));
		write(STDOUT_FILENO, &canals, sizeof(uint32_t));

		for(j = 0; j < alt; j++){
			for(k = 0; k < anch*canals; k++){
				pxl = imgFiltro->matriz[j][k];
				write(STDOUT_FILENO, &pxl, sizeof(uint8_t));	
			}
		}

		write(STDOUT_FILENO, &nb, sizeof(int));

		liberarMatrizJpg(imgFiltro);
	}

	wait(NULL);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free(imgFiltro);
	return 0;
}