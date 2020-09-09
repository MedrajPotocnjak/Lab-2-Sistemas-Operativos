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

	fprintf(stderr, "Estoy en primera linea escritura \n" );

	int c = atoi(argv[2]);
	int u = atoi(argv[4]);
	int n = atoi(argv[6]);
	char* m = argv[8];
	int b;
	struct jpeg_error_mgr jerr;
	Imagen* imgFiltro = (Imagen*)malloc(sizeof(Imagen));
	int i;
	int nb;
	char* result;
	char* nombre;

	if(argc == 10){
		b = 1;
	}
	else{
		b = 0;
	}

	char salida[500] = "";
	if(b == 1){
		strcat(salida, "|     image     |  nearly black  |\n");
		strcat(salida, "|---------------|----------------|\n");
	}

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
				read(STDIN_FILENO, &pxl, sizeof(uint8_t));
				imgFiltro->matriz[j][k] = pxl;
			}
		}
		
		//6° escritura de imagen
		escribirJpg(imgFiltro, i, &jerr);

		read(STDIN_FILENO, &nb, sizeof(int));

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

    	liberarMatrizJpg(imgFiltro);
	}

	if (b == 1) {
        printf("%s\n", salida); 
    }
	wait(NULL);
	close(STDIN_FILENO);
	free(imgFiltro);
	return 0;
}