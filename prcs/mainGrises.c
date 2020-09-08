#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jpeglib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../incl/escalaGrises.h"
#include "../incl/funciones.h"

//Entradas: argc <tipo: int> (cantidad de argumentos) - argv <tipo: array de char> (lista de argumentos)
//Funcionamiento: inicia el programa, realiza el getopt y ejecuta los procesos del pipeline para la
//modificacion de las imagenes y la clasificacion.
//Salidas: 0 si termina correctamente, 1 si termina con errores.
int main(int argc, char* argv[]){

	//Pipe
	int paip3[2];

	if (pipe(paip3) == -1){ 
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
		close(paip3[1]);
		int dupiao = dup2(paip3[0], STDIN_FILENO);
		if (dupiao == -1){
			fprintf(stderr, "Dup2 fallido" );
			return 1; 
		}
		close(paip3[0]);
		execv("mainFiltro", argv);
	}

	//Padre
	close(paip3[0]);
	int dupiao = dup2(paip3[1], STDOUT_FILENO);
	if (dupiao == -1){
		fprintf(stderr, "Dup2 paip3[1] fallido" );
		return 1; 
	}

	int c = atoi(argv[2]);
	int u = atoi(argv[4]);
	int n = atoi(argv[6]);
	char* m = argv[8];
	int b = atoi(argv[10]);
	Imagen* img;
	Imagen* imgGris;
	int i;

	for(i = 1; i <= c; i++){
		uint32_t alt;
		uint32_t anch;
		uint32_t canals;
		read(STDIN_FILENO, &alt, sizeof(uint32_t));
		read(STDIN_FILENO, &anch, sizeof(uint32_t));
		read(STDIN_FILENO, &canals, sizeof(uint32_t));
		img = (Imagen*)malloc(sizeof(Imagen));
		img->alto = alt;
		img->ancho = anch;
		img->canales = canals;
		int ancho = img->ancho * img->canales;
		crearMatrizJpg(img);
		int j;
		int k;
		uint8_t pxl;
		for(j = 0; j < img->alto; j++){
			for(k = 0; k < ancho; k++){
				read(STDIN_FILENO, &pxl, sizeof(uint8_t));
				img->matriz[j][k] = pxl;
			}
		}

		//2° convertir a escala de grises
		imgGris = converGris(img);

		alt = imgGris->alto;
		anch = imgGris->ancho;
		canals = imgGris->canales;

		write(STDOUT_FILENO, &alt, sizeof(uint32_t));
		write(STDOUT_FILENO, &anch, sizeof(uint32_t));
		write(STDOUT_FILENO, &canals, sizeof(uint32_t));

		for(j = 0; j < alt; j++){
			for(k = 0; k < anch*canals; k++){
				pxl = imgGris->matriz[j][k];
				write(STDOUT_FILENO, &pxl, sizeof(uint8_t));	
			}
		}
		liberarMatrizJpg(imgGris);
	}

	wait(NULL);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(paip3[1]);
	free(img);
	free(imgGris);
	return 0;
}