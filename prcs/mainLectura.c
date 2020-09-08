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

//Se le entregara el número de la imagen la cual se asignara a la variable i, tambien se le entregara la cantidad total de imagenes
int main(int argc, char* argv[]){

	//Pipe
	int paip2[2];

	if (pipe(paip2) == -1){ 
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
		close(paip2[1]);
		execv("mainGrises", argv);
	}
	//Padre
	close(paip2[0]);
	

	int c = atoi(argv[2]);
	int u = atoi(argv[4]);
	int n = atoi(argv[6]);
	char* m = argv[8];
	int b = atoi(argv[10]);

	struct jpeg_error_mgr jerr;
	
	int i;

	for(i = 1; i <= c; i++){
		Imagen* img = (Imagen*)malloc(sizeof(Imagen));
		if(img == NULL){
			printf("Fallo en malloc de img %d\n", i);
			return 1;
		}

		//read(int fd, void *buf, size_t count);
		//write(int fd, const void *buf, size_t count);
		
		//1° leer la imagen
		//leerJpg(img, i, &jerr);
	}

	wait(NULL);
	return 0;
}