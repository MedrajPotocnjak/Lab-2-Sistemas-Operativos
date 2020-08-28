#include "../incl/clasificacion.h"

//Entradas: imagen <tipo Imagen*> (estructura que representa la imagen) - umbral <tipo: int> (valor de umbral en porcentaje para clasificar)
//Funcionamiento: recorre la matriz imagen y cuenta la cantidad de pixeles negros, y si el porcentaje de estos es mayor o igual
//al umbral ingresado sera clasificado como nearly black
//Salidas: nb <tipo: int> (0: no es nearly black; 1: es nearly black)
int clasificar(Imagen* imagen, int umbral){
    int pix_total = imagen->ancho * imagen->alto;
    int contador = 0;
    int nb;
    int i;
    int j;

    for(i = 0; i < imagen->alto; i++){
        for(j = 0; j < imagen->ancho; j++){
            if(imagen->matriz[i][j] == 0){
                contador += 1;
            }
        }
    }

    float porcentaje = (float)contador / pix_total;
    int razon = porcentaje * 100;

    if(razon >= umbral){
        nb = 1;
    }
    else{
        nb = 0;
    }
    return nb;
}