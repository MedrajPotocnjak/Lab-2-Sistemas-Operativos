#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jpeglib.h>
#include "../incl/lectura.h"
#include "../incl/escalaGrises.h"
#include "../incl/filtroRealce.h"
#include "../incl/binarizacion.h"
#include "../incl/clasificacion.h"
#include "../incl/escritura.h"
#include "../incl/funciones.h"

//Entradas: argc <tipo: int> (cantidad de argumentos) - argv <tipo: array de char> (lista de argumentos)
//Funcionamiento: inicia el programa, realiza el getopt y ejecuta los procesos del pipeline para la
//modificacion de las imagenes y la clasificacion.
//Salidas: 0 si termina correctamente, 1 si termina con errores.
int main(int argc, char* argv[]){
	int c = -1;
	int u = -1;
	int n = -1;
	char* m = NULL;
	int b = 0;
	opterr = 0;
	int opt;

	while((opt = getopt(argc, argv, "c:u:n:m:b")) != -1){
		switch(opt){
			case 'c':
				c = atoi(optarg);
				if(c < 0){
					printf("ERROR: cantidad de imagenes no puede ser negativa\n");
					return 1;
				}
				if(c == 0){
					printf("Cantidad de imagenes nula/número no entero. Ejecución finalizada...");
					return 1;
				}
				break;
			case 'u':
				u = atoi(optarg);
				if(u < 0){
					printf("ERROR: umbral no puede ser negativo\n");
					return 1;
				}
				break;
			case 'n':
				n = atoi(optarg);
				if(n < 0){
					printf("ERROR: El umbral no puede ser menor a 0\n");
					return 1;
				}
				if(n > 100){
					printf("ERROR: El umbral no puede ser superior a 100\n");
				}
				break;
			case 'm':
				m = optarg;
				int len_ruta = strlen(m);
				if(len_ruta < 5){
					printf("ERROR: ruta de filtro inválida\n");
					return 1;
				}
				char dot = m[len_ruta - 4];
				char t1 = m[len_ruta - 3];
				char x = m[len_ruta - 2];
				char t2 = m[len_ruta - 1];
				if(dot != '.' || t1 != 't' || x != 'x' || t2 != 't'){
					printf("ERROR: archivo de filtro debe ser .txt\n");
					return 1;
				}
				break;
			case 'b':
				b = 1;
				break;
			case '?':
				printf("ERROR: parámetro no reconocido/valor faltante\n");
				printf("El formato de ejecución es: ./ejemplo -c valor -u valor -n valor -m ruta -b");
				return 1;
		}
	}

	int i;
	Imagen* img = (Imagen*)malloc(sizeof(Imagen));
	if(img == NULL){
		printf("Fallo en malloc de img %d\n", i);
		return 1;
	}

	int** filtro = abrirFiltro(m);
	if(filtro == NULL){
		return 1;
	}

	char salida[500] = "";
	if(b == 1){
		strcat(salida, "|     image     |  nearly black  |\n");
		strcat(salida, "|---------------|----------------|\n");
	}

	char* result;
	char* nombre;

	for(i = 1; i <= c; i++){
		int nb;
		struct jpeg_error_mgr jerr;
		//1° leer la imagen
		leerJpg(img, i, &jerr);
		//2° convertir a escala de grises
		Imagen* imgGris = converGris(img);
		//3° aplicar filtro
		Imagen* imgFiltro = aplicarFiltro(imgGris, filtro);
		//4° aplicar binarizacion
		binarizar(imgFiltro, u);
		//5° analizar propiedad
		nb = clasificar(imgFiltro, n);
		//6° escribir imagen
		escribirJpg(imgFiltro, i, &jerr);

		nombre = armarNombreArchivo(i, 2);

		if(nb == 1){
            result = "yes";
        }
        else{
            result = "no";
        }

        if(b == 1){
            char resultado[50];
    		sprintf(resultado, "|%15s|%16s|\n", nombre, result);
            strcat(salida, resultado); 
    	}
	}
	if (b == 1) {
        printf("%s\n", salida); 
    }
	free(img);
	return 0;
}