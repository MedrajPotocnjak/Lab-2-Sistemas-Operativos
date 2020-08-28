#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <string.h>
#include "../incl/funciones.h"
#include "../incl/lectura.h"

//Entradas: img <tipo: Imagen*> (estructura que representa a la imagen), i <tipo: int>, jerr <tipo: struct jpeg_error_mgr*>
//(estructura definida en la libreria jpeglib)
//Funcionamiento: Lee la imagen ingresada, llama a la funcion que genera la matriz y la rellena
//Salidas: 0 si la lectura a la imagen esta correcta, 1 si ocurre un error. 
int leerJpg(Imagen* imagen, int i, struct jpeg_error_mgr* jerr){
	char* rutaImg = armarNombreArchivo(i, 1);

	struct jpeg_decompress_struct cinfo;
	
	FILE* entrada;

	if((entrada = fopen(rutaImg, "rb")) == NULL) {
    	fprintf(stderr, "No se pudo abrir %s\n", rutaImg);
    	return 1;
  	}

  	free(rutaImg);

	cinfo.err = jpeg_std_error(jerr);

	jpeg_create_decompress(&cinfo);

	jpeg_stdio_src(&cinfo, entrada);

	jpeg_read_header(&cinfo, TRUE);

	jpeg_start_decompress(&cinfo);

	imagen->alto = cinfo.image_height;
	imagen->ancho = cinfo.image_width;
	imagen->canales = cinfo.num_components;

	crearMatrizJpg(imagen);

	//Leer el Jpg y guardar en estructura
    for (int y = 0; y < imagen->alto; y++) {
        jpeg_read_scanlines(&cinfo, &(imagen->matriz[y]), 1);
    }

  	jpeg_finish_decompress(&cinfo);

  	jpeg_destroy_decompress(&cinfo);

  	fclose(entrada);
  	return 0;
}