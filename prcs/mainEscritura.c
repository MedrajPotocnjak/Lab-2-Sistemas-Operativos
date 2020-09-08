#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jpeglib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../incl/escritura.h"
#include "../incl/funciones.h"

//Entradas: argc <tipo: int> (cantidad de argumentos) - argv <tipo: array de char> (lista de argumentos)
//Funcionamiento: inicia el programa, realiza el getopt y ejecuta los procesos del pipeline para la
//modificacion de las imagenes y la clasificacion.
//Salidas: 0 si termina correctamente, 1 si termina con errores.
int main(int argc, char* argv[]){
	
	//Pipe
	int paip7[2];

	if (pipe(paip7) == -1){ 
        fprintf(stderr, "Pipe fallido" ); 
        return 1; 
    }

	//Fork con execv
	pid_t forky = fork();

	if(forky < 0){
		fprintf(stderr, "Fork fallido" ); 
        return 1;
	}
	if(forky == 0){
		//Hijo
		close(paip7[1]);
		//execv("nose", argv);
	}
	
	//Padre
	close(paip7[0]);

	int c = atoi(argv[2]);
	int u = atoi(argv[4]);
	int n = atoi(argv[6]);
	char* m = argv[8];
	int b = atoi(argv[10]);
	struct jpeg_error_mgr jerr;
	int i;
	int nb;
	char* result;
	char* nombre;
	//imgFiltro es la que se le entrega a este main

	char salida[500] = "";
	if(b == 1){
		strcat(salida, "|     image     |  nearly black  |\n");
		strcat(salida, "|---------------|----------------|\n");
	}



	for(i = 1; i <= c; i++){
		//escribirJpg(imgFiltro, i, &jerr);

		nombre = armarNombreArchivo(i, 2);

		if(nb == 1){
        	result = "yes";
    	}
    	else{
        	result = "no";
    	}

    	if(b == 1){
        	char resultado[50];
    		sprintf(resultado, "|%15s|%16s|\n", nombre, result);
        	strcat(salida, resultado); 
    	}
	}

	if (b == 1) {
        printf("%s\n", salida); 
    }
	//free(img);

	wait(NULL);
	return 0;
}