#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incl/funciones.h"

//Entradas: img <tipo: Imagen*> (estructura que representa a la imagen)
//Funcionamiento: Crea la matriz respectiva para la imagen
//Salidas: <tipo: void>
void crearMatrizJpg(Imagen* img){
	img->matriz = (uint8_t**)malloc(sizeof(uint8_t*) * img->alto);
	if(img->matriz == NULL){
		printf("Fallo en malloc al crear matriz\n");
		return;
	}
	
	int i;
	int totalAncho = img->ancho * img->canales;

	for(i = 0; i < img->alto; i++){
		img->matriz[i] = (uint8_t*)malloc(sizeof(uint8_t) * totalAncho);
		if(img->matriz[i] == NULL){
			printf("Fallo en malloc al crear matriz[%d]\n", i);
			return;
		}
	}
	return;
}

//Entradas: img <tipo: Imagen*> (estructura que representa a la imagen)
//Funcionamiento: Libera la memoria utilizada en la matriz de la imagen
//Salidas: <tipo: void>
void liberarMatrizJpg(Imagen* img){
	int i;
	for(i = 0; i < img->alto; i++){
		free(img->matriz[i]);
	}
	free(img->matriz);
	return;
}

//Entradas: str1 <tipo: char*> (string delantero) - str2 <tipo: char*> (string trasero)
//Funcionamiento: concatena los strings str1 y str2
//Salidas: strcon <tipo: char*> (string concatenado "str1str2")
char* concatenar(char* str1, char* str2){

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char* strcon = (char*)malloc(len1 + len2 + 1);
    if(strcon == NULL){
    	printf("ERROR: <concatenar()> fallo en malloc()\n");
    	return NULL;
    }
    memcpy(strcon, str1, len1);
    memcpy(strcon + len1, str2, len2 + 1);
    return strcon;
}

//Entradas: nro <tipo: int> (número de imagen) - modo <tipo: int> (modo de nombre, 1: "imagen_"; 0: "salida_")
//Funcionamiento: crea un string de nombre para la imagen jpg del número correspondiente
//Salidas: nom_con_ext <tipo: char*> (nombre de la imagen con extensión, del tipo "imagen_nro.jpg" o "salida_nro.jpg")
char* armarNombreArchivo(int nro, int modo){
	char* ruta;
	char* extension = ".jpg";

	if(modo == 1 || modo == 2){
		ruta = "imagen_";
		int len = snprintf(NULL, 0, "%d", nro);
		char* num = malloc(len + 1);
		snprintf(num, len + 1, "%d", nro);
		char* nom = concatenar(ruta, num);
		free(num);
		if(modo == 1){
			char* nom_con_ext = concatenar(nom, extension);
			free(nom);
			return nom_con_ext;
		}
		return nom;
	}
	else{
		ruta = "salida_";
		int len = snprintf(NULL, 0, "%d", nro);
		char* num = malloc(len + 1);
		snprintf(num, len + 1, "%d", nro);
		char* nom = concatenar(ruta, num);
		char* nom_con_ext = concatenar(nom, extension);
		free(num);
		free(nom);
		return nom_con_ext;
	}
}