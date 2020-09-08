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
		int dupiao = dup2(paip2[0], STDIN_FILENO);
		if (dupiao == -1){
			fprintf(stderr, "Dup2 fallido" );
			return 1; 
		}
		close(paip5[0]);
		execv("mainClasificacion", argv);
	}

	//Padre
	close(paip5[0]);
	

	int c = atoi(argv[2]);
	int u = atoi(argv[4]);
	int n = atoi(argv[6]);
	char* m = argv[8];
	int b = atoi(argv[10]);
	
	int i;
	//imgFiltro es la que se le entrega a este main

	for(i = 1; i <= c; i++){
		//binarizar(imgFiltro, u);
	}

	wait(NULL);
	return 0;
}