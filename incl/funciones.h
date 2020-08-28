#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "structs.h"

//Cabeceras de funciones.c
void crearMatrizJpg(Imagen* img);
void liberarMatrizJpg(Imagen* img);
char* concatenar(char* str1, char* str2);
char* armarNombreArchivo(int nro, int modo);

#endif