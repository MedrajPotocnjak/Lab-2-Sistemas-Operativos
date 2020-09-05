#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jpeglib.h>
#include "../incl/filtroRealce.h"
#include "../incl/funciones.h"

//Entradas: argc <tipo: int> (cantidad de argumentos) - argv <tipo: array de char> (lista de argumentos)
//Funcionamiento: inicia el programa, realiza el getopt y ejecuta los procesos del pipeline para la
//modificacion de las imagenes y la clasificacion.
//Salidas: 0 si termina correctamente, 1 si termina con errores.
int main(int argc, char* argv[]){
	
	int** filtro = abrirFiltro(m);
	if(filtro == NULL){
		return 1;
	}

	int i = numero de la imagen;
	int c = cantidad de imagenes;
	//imgGris es la que se le entrega a este main

	for(i; i <= c; i++){
		Imagen* imgFiltro = aplicarFiltro(imgGris, filtro);
	}

	return 0;
}