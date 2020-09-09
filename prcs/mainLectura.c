#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jpeglib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../incl/lectura.h"
#include "../incl/funciones.h"

//Entradas: argc <tipo: int> (cantidad de argumentos) - argv <tipo: array de char> (lista de argumentos)
//Funcionamiento: inicia el programa, realiza el getopt y ejecuta los procesos del pipeline para la
//modificacion de las imagenes y la clasificacion.
//Salidas: 0 si termina correctamente, 1 si termina con errores.
int main(int argc, char* argv[]){
	//Pipe
	int paip2[2];
	if (pipe(paip2) == -1){ 
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
		close(paip2[1]);
		int dupiao = dup2(paip2[0], STDIN_FILENO);
		if (dupiao == -1){
			fprintf(stderr, "Dup2 paip2[0] fallido \n" );
			return 1; 
		}
		close(paip2[0]);

		execv("./mainGrises", argv);
	}
	//Padre
	close(paip2[0]);
	int dupiao = dup2(paip2[1], STDOUT_FILENO);
	if (dupiao == -1){
		fprintf(stderr, "Dup2 paip2[1] fallido \n" );
		return 1; 
	}
	close(paip2[1]);
	
	int c = atoi(argv[2]);
	int u = atoi(argv[4]);
	int n = atoi(argv[6]);
	char* m = argv[8];

	struct jpeg_error_mgr jerr;
	Imagen* img = (Imagen*)malloc(sizeof(Imagen));
	int i;

	for(i = 1; i <= c; i++){

		if(img == NULL){
			printf("Fallo en malloc de img %d\n", i);
			return 1;
		}
		//1° leer la imagen
		leerJpg(img, i, &jerr);

		uint32_t alt = img->alto;
		uint32_t anch = img->ancho;
		uint32_t canals = img->canales;
		uint8_t pxl;

		write(STDOUT_FILENO, &alt, sizeof(uint32_t));
		write(STDOUT_FILENO, &anch, sizeof(uint32_t));
		write(STDOUT_FILENO, &canals, sizeof(uint32_t));

		int j;
		int k;
		for(j = 0; j < alt; j++){
			for(k = 0; k < anch*canals; k++){
				pxl = img->matriz[j][k];
				write(STDOUT_FILENO, &pxl, sizeof(uint8_t));	
			}
		}
		liberarMatrizJpg(img);	
	}
	wait(NULL);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free(img);
	return 0;
}