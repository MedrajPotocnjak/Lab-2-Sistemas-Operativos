#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jpeglib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../incl/filtroRealce.h"
#include "../incl/funciones.h"

//Entradas: argc <tipo: int> (cantidad de argumentos) - argv <tipo: array de char> (lista de argumentos)
//Funcionamiento: inicia el programa, realiza el getopt y ejecuta los procesos del pipeline para la
//modificacion de las imagenes y la clasificacion.
//Salidas: 0 si termina correctamente, 1 si termina con errores.
int main(int argc, char* argv[]){

	//Pipe
	int paip4[2];

	if (pipe(paip4) == -1){ 
        fprintf(stderr, "Pipe fallido \n" ); 
        return 1; 
    }

	//Fork con execv
	pid_t forky = fork();

	if(forky < 0){
		fprintf(stderr, "Fork fallido \n" ); 
        return 1;
	}
	if(forky == 0){
		//Hijo
		close(paip4[1]);
		int dupiao = dup2(paip4[0], STDIN_FILENO);
		if (dupiao == -1){
			fprintf(stderr, "Dup2 paip4[0] fallido \n" );
			return 1; 
		}
		close(paip4[0]);
		execv("./mainBinarizacion", argv);
	}
	
	//Padre
	close(paip4[0]);
	int dupiao = dup2(paip4[1], STDOUT_FILENO);
	if (dupiao == -1){
		fprintf(stderr, "Dup2 paip4[1] fallido \n" );
		return 1; 
	}
	close(paip4[1]);

	int c = atoi(argv[2]);
	int u = atoi(argv[4]);
	int n = atoi(argv[6]);
	char* m = argv[8];
	
	int** filtro = abrirFiltro(m);
	if(filtro == NULL){
		return 1;
	}

	Imagen* imgGris = (Imagen*)malloc(sizeof(Imagen));
	Imagen* imgFiltro;
	int i;

	for(i = 1; i <= c; i++){
		uint32_t alt;
		uint32_t anch;
		uint32_t canals;
		read(STDIN_FILENO, &alt, sizeof(uint32_t));
		read(STDIN_FILENO, &anch, sizeof(uint32_t));
		read(STDIN_FILENO, &canals, sizeof(uint32_t));		
		imgGris->alto = alt;
		imgGris->ancho = anch;
		imgGris->canales = canals;
		int ancho = imgGris->ancho * imgGris->canales;
		crearMatrizJpg(imgGris);
		int j;
		int k;
		uint8_t pxl;
		for(j = 0; j < imgGris->alto; j++){
			for(k = 0; k < ancho; k++){
				read(STDIN_FILENO, &pxl, sizeof(uint8_t));
				imgGris->matriz[j][k] = pxl;
			}
		}

		//3° aplicar filtro de realce
		imgFiltro = aplicarFiltro(imgGris, filtro);

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
		liberarMatrizJpg(imgGris);
		liberarMatrizJpg(imgFiltro);
		free(imgFiltro);
	}

	wait(NULL);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free(imgGris);
	return 0;
}