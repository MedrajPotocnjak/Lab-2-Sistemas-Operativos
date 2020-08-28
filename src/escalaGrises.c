#include <stdio.h>
#include <stdlib.h>
#include "../incl/escalaGrises.h"
#include "../incl/funciones.h"

//Entradas: img <tipo: Imagen*> (estructura que representa a la imagen) 
//Funcionamiento: La imagen ingresada la pasa a escala de grises, modificando la structura ingresada
//Salidas: imgGris <tipo: Imagen*> (imagen nueva creada en escala de grises para mantener la original)
Imagen* converGris(Imagen* img){
    Imagen* imgGris = (Imagen*)malloc(sizeof(Imagen));
    if(imgGris == NULL){
        printf("Fallo en malloc de imgGris\n");
        return NULL;
    }

    imgGris->alto = img->alto;
    imgGris->ancho = img->ancho;
    imgGris->canales = 1;

    crearMatrizJpg(imgGris);

    int i;
    int j;

    int x = 0;
    int y = 0;

    uint8_t z;

    uint8_t r;
    uint8_t g;
    uint8_t b;
    int ancho = img->ancho * img->canales;

    for(i = 0; i < img->alto; i++){
        y = 0;
        for(j = 0; j < ancho; j++){
            r = img->matriz[i][j];
            j++;
            g = img->matriz[i][j];
            j++;
            b = img->matriz[i][j];
            z = (uint8_t)(r * 0.3 + g * 0.59 + b * 0.11);
            imgGris->matriz[x][y] = z;
            y++;
        }
        x++;
    }
    liberarMatrizJpg(img);
    return imgGris;
}