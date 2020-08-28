#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <string.h>
#include "../incl/funciones.h"
#include "../incl/escritura.h"

//Entradas: img <tipo: Imagen*> (estructura que representa a la imagen), i <tipo: int>, jerr <tipo: struct jpeg_error_mgr*>
//(estructura definida en la libreria jpeglib)
//Funcionamiento: Lee la imagen ingresada, llama a la funcion que genera la matriz y la rellena
//Salidas: 0 cuando la escritura esta completa.
int escribirJpg(Imagen* imagen, int i, struct jpeg_error_mgr* jerr){
	char* nombreArchivo = armarNombreArchivo(i, 0);

	struct jpeg_compress_struct cinfo;

	FILE* salida;

	jpeg_create_compress(&cinfo);

	cinfo.err = jpeg_std_error(jerr);

	if ((salida = fopen(nombreArchivo, "wb")) == NULL) {
    	fprintf(stderr, "No se pudo abrir %s\n", nombreArchivo);
    	exit(1);
  	}

  	free(nombreArchivo);

	jpeg_stdio_dest(&cinfo, salida);

	cinfo.image_width = imagen->ancho;
	cinfo.image_height = imagen->alto;
	cinfo.input_components = imagen->canales;
	cinfo.in_color_space = JCS_GRAYSCALE;
	//cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);

	jpeg_start_compress(&cinfo, TRUE);

	int j;

	for(j = 0; cinfo.next_scanline < cinfo.image_height; j++) {
		jpeg_write_scanlines(&cinfo, &(imagen->matriz[j]), 1);
	}

	jpeg_finish_compress(&cinfo);

	fclose(salida);

	jpeg_destroy_compress(&cinfo);

	liberarMatrizJpg(imagen);
	return 0;
}