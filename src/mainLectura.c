#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jpeglib.h>
#include "../incl/lectura.h"
#include "../incl/funciones.h"

//Entradas: argc <tipo: int> (cantidad de argumentos) - argv <tipo: array de char> (lista de argumentos)
//Funcionamiento: inicia el programa, realiza el getopt y ejecuta los procesos del pipeline para la
//modificacion de las imagenes y la clasificacion.
//Salidas: 0 si termina correctamente, 1 si termina con errores.

//Se le entregara el número de la imagen la cual se asignara a la variable i, tambien se le entregara la cantidad total de imagenes
int main(int argc, char* argv[]){

	struct jpeg_error_mgr jerr;
	
	int i;
	Imagen* img = (Imagen*)malloc(sizeof(Imagen));
	if(img == NULL){
		printf("Fallo en malloc de img %d\n", i);
		return 1;
	}

	int c = numero total de imagenes;
	for(i; i <= c; i++){
		//1° leer la imagen
		leerJpg(img, i, &jerr);
	}

	return 0;
}