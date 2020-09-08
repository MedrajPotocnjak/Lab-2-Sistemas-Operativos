#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jpeglib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../incl/binarizacion.h"
#include "../incl/funciones.h"

//Entradas: argc <tipo: int> (cantidad de argumentos) - argv <tipo: array de char> (lista de argumentos)
//Funcionamiento: inicia el programa, realiza el getopt y ejecuta los procesos del pipeline para la
//modificacion de las imagenes y la clasificacion.
//Salidas: 0 si termina correctamente, 1 si termina con errores.
int main(int argc, char* argv[]){

	//Pipe
	int paip5[2];

	if (pipe(paip5) == -1){ 
        fprintf(stderr, "Pipe fallido" ); 
        return 1; 
    }

	//Fork con exec
	pid_t forky = fork();

	if(forky < 0){
		fprintf(stderr, "Fork fallido" ); 
        return 1;
	}
	if(forky == 0){
		//Hijo
		close(paip5[1]);
		fprintf(stderr, "Estoy en hijo mainBinarizacion \n" );
		int dupiao = dup2(paip5[0], STDIN_FILENO);
		if (dupiao == -1){
			fprintf(stderr, "Dup2 fallido" );
			return 1; 
		}
		close(paip5[0]);
		execv("./mainClasificacion", argv);
	}

	//Padre
	close(paip5[0]);
	fprintf(stderr, "Estoy en padre mainBinarizacion \n" );
	int dupiao = dup2(paip5[1], STDOUT_FILENO);
	if (dupiao == -1){
		fprintf(stderr, "Dup2 paip5[1] fallido" );
		return 1; 
	}
	
	int c = atoi(argv[2]);
	int u = atoi(argv[4]);
	int n = atoi(argv[6]);
	char* m = argv[8];
	int b = atoi(argv[10]);
	
	Imagen* imgFiltro;
	int i;
	//imgFiltro es la que se le entrega a este main

	for(i = 1; i <= c; i++){
		uint32_t alt;
		uint32_t anch;
		uint32_t canals;
		read(STDIN_FILENO, &alt, sizeof(uint32_t));
		read(STDIN_FILENO, &anch, sizeof(uint32_t));
		read(STDIN_FILENO, &canals, sizeof(uint32_t));
		imgFiltro = (Imagen*)malloc(sizeof(Imagen));
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

		//4° binarizacion de la imagen
		binarizar(imgFiltro, u);

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
		liberarMatrizJpg(imgFiltro);
	}

	wait(NULL);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free(imgFiltro);
	close(paip5[1]);
	return 0;
}