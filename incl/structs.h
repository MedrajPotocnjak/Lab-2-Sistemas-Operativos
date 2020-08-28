#include <stdint.h>
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

//Estructura para guardar la imagen
//Posee:
//Alto de la imagen (Numero de filas de pixeles)
//Ancho de la imagen (Numero de columnas de pixeles)
//Canales que tiene cada pixel (Cuantos colores hay por pixel)
//Matriz (Tiene los valores numericos para cada pixel de la imagen)
typedef struct imagenJpg{
	uint32_t alto;
	uint32_t ancho;
	uint32_t canales;
	uint8_t** matriz;
}Imagen;

#endif