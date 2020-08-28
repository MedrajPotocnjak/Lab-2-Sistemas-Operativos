#include <stdio.h>
#include <stdlib.h>
#include "../incl/filtroRealce.h"
#include "../incl/funciones.h"

//Entradas: ruta <tipo: char*> (la ruta del archivo de texto que contiene el filtro a usar)
//Funcionamiento: lee el filtro desde el archivo indicado, crea y devuelve la matriz filtro
//Salidas: filtro <tipo: int**> (la matriz filtro 3x3 a utilizar)
int** abrirFiltro(char* ruta){
    FILE* archivo = fopen(ruta, "r");
    if(archivo == NULL){
        fprintf(stderr, "ERROR: no se pudo leer el archivo de filtro\n");
        return NULL;
    }

    int** filtro = (int**)malloc(sizeof(int*) * 3);
    if(filtro == NULL){
        fprintf(stderr, "ERROR: fallo al dar memoria a filtro\n");
        return NULL;
    }

    int i;
    for(i = 0; i < 3; i++){
        filtro[i] = (int*)malloc(sizeof(int) * 3);
        if(filtro[i] == NULL){
            fprintf(stderr, "ERROR: fallo al dar memoria a filtro[%d]\n", i);
            return NULL;
        }
    }

    if(fscanf(archivo, "%d%d%d%d%d%d%d%d%d",
        &filtro[0][0], &filtro[0][1], &filtro[0][2], 
        &filtro[1][0], &filtro[1][1], &filtro[1][2], 
        &filtro[2][0], &filtro[2][1], &filtro[2][2]) != 9){
        fprintf(stderr, "ERROR: fallo al leer la matriz de filtro\n");
        return NULL;
    }
    fclose(archivo);
    return filtro;
}

//Entradas: imagen <tipo: Imagen> (estructura que representa la imagen) - filtro <tipo: int**> (la matriz de filtro)
//Funcionamiento: recorre la matriz de imagen y aplica el filtro de realce
//Salidas: imgFiltro <tipo: Imagen*> (imagen nueva creada con el filtro de realce aplicado para mantener la original)
Imagen* aplicarFiltro(Imagen* imagen, int** filtro){
	Imagen* imgFiltro = (Imagen*)malloc(sizeof(Imagen));
	if(imgFiltro == NULL){
        printf("Fallo en malloc de imgFiltro\n");
        return NULL;
    }

    imgFiltro->alto = imagen->alto;
    imgFiltro->ancho = imagen->ancho;
    imgFiltro->canales = 1;

    crearMatrizJpg(imgFiltro);

    int i;
    int j;
    for(i = 0; i < imagen->alto; i++){
        for(j = 0; j < imagen->ancho; j++){
            /*
              1 2 3
            a|_|_|_|
            b|_|_|_|
            c|_|_|_|
            */
            //Las siguientes variables corresponden a los valores que se toman de la matriz imagen
            int a1;
            int a2;
            int a3;
            int b1;
            int b2;
            int b3;
            int c1;
            int c2;
            int c3;

            b2 = imagen->matriz[i][j];
            //Si estoy en 1ra fila
            if(i == 0){
                a1 = 0;
                a2 = 0;
                a3 = 0;
                //Si estoy en 1ra y última fila (matriz de una fila)
                if(i == imagen->alto - 1){
                    c1 = 0;
                    c2 = 0;
                    c3 = 0;
                    //Si estoy en 1ra columna
                    if(j == 0){
                        b1 = 0;
                    }
                    else{
                        b1 = imagen->matriz[i][j - 1];
                    }
                    //Si estoy en última columna
                    if(j == imagen->ancho - 1){
                        b3 = 0;
                    }
                    else{
                        b3 = imagen->matriz[i][j + 1];
                    }
                }
                //Si estoy en 1ra fila, y no en la última
                else{
                    c2 = imagen->matriz[i + 1][j];
                    //Si estoy en 1ra columna
                    if(j == 0){
                        b1 = 0;
                        c1 = 0;
                    }
                    else{
                        b1 = imagen->matriz[i][j - 1];
                        c1 = imagen->matriz[i + 1][j - 1];
                    }
                    //Si estoy en última columna
                    if(j == imagen->ancho - 1){
                        b3 = 0;
                        c3 = 0;
                    }
                    else{
                        b3 = imagen->matriz[i][j + 1];
                        c3 = imagen->matriz[i + 1][j + 1];
                    }
                }
            }
            //Si no estoy en 1ra fila
            else{
                a2 = imagen->matriz[i - 1][j];
                //Si no estoy en 1ra fila, y estoy en última fila
                if(i == imagen->alto - 1){
                    c1 = 0;
                    c2 = 0;
                    c3 = 0;
                    //Si estoy en 1ra columna
                    if(j == 0){
                        a1 = 0;
                        b1 = 0;
                    }
                    else{
                        a1 = imagen->matriz[i - 1][j - 1];
                        b1 = imagen->matriz[i][j - 1];
                    }
                    //Si estoy en última columna
                    if(j == imagen->ancho - 1){
                        a3 = 0;
                        b3 = 0;
                    }
                    else{
                        a3 = imagen->matriz[i - 1][j + 1];
                        b3 = imagen->matriz[i][j + 1];
                    }
                }
                //Si no estoy en 1ra fila, y no estoy en última fila
                else{
                    c2 = imagen->matriz[i + 1][j];
                    //Si estoy en 1ra columna
                    if(j == 0){
                        a1 = 0;
                        b1 = 0;
                        c1 = 0;
                    }
                    else{
                        a1 = imagen->matriz[i - 1][j - 1];
                        b1 = imagen->matriz[i][j - 1];
                        c1 = imagen->matriz[i + 1][j - 1];
                    }
                    //Si estoy en última columna
                    if(j == imagen->ancho - 1){
                        a3 = 0;
                        b3 = 0;
                        c3 = 0;
                    }
                    else{
                        a3 = imagen->matriz[i - 1][j + 1];
                        b3 = imagen->matriz[i][j + 1];
                        c3 = imagen->matriz[i + 1][j + 1];
                    }
                }
            }
            //Se calcula el valor del pixel central
            int suma_prod_1 = (a1 * filtro[0][0]) + (a2 * filtro[0][1]) + (a3 * filtro[0][2]);
            int suma_prod_2 = (b1 * filtro[1][0]) + (b2 * filtro[1][1]) + (b3 * filtro[1][2]);
            int suma_prod_3 = (c1 * filtro[2][0]) + (c2 * filtro[2][1]) + (c3 * filtro[2][2]);
            imgFiltro->matriz[i][j] =  (suma_prod_1 + suma_prod_2 + suma_prod_3);
        }
    }
    return imgFiltro;
}