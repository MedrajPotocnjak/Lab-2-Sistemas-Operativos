#include "../incl/binarizacion.h"

/*
Para cada pixel:
	si el pixel > UMBRAL
		pixel = 255
	sino
		pixel = 0
*/

//Entradas: imagen <tipo: Imagen> (estructura que representa la imagen) - umbral <tipo: int> (representa el valor del umbral)
//Funcionamiento: recorre la matriz de imagen y aplica la binarizacion de acuerdo a las condiciones del algoritmo
//Salidas: <tipo: void>
void binarizar(Imagen* imagen, int umbral){
    int i;
    int j;
    for(i = 0; i < imagen->alto; i++){
        for(j = 0; j < imagen->ancho; j++){
            if(imagen->matriz[i][j] > umbral){
                imagen->matriz[i][j] = 255;
            }
            else{
            	imagen->matriz[i][j] = 0;
            }
        }
    }
    return;
}