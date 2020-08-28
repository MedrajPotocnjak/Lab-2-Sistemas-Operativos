#ifndef FILTROREALCE_H
#define FILTROREALCE_H
#include "structs.h"

//Cabeceras de filtroRealce.c
int** abrirFiltro(char* ruta);
Imagen* aplicarFiltro(Imagen* imagen, int** filtro);

#endif