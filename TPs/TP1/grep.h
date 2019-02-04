#ifndef GREP_H
#define GREP_H

#include <stdbool.h>
#include <stdlib.h>

int ejecutar_grep(int argc,char* argv[]){

	if (argc<3 || argc>4){
		fprintf(stderr, "%s", "Cantidad de parametros erronea");
		return 1;
	}
	
	if (strcmp(argv[2],"0")!=0 && atoi(argv[2])==0) {
		fprintf(stderr, "%s", "Tipo de parametro incorrecto");
		return 1;
	}

	if (argc==4){
		FILE* archivo = fopen(argv[3], "r");
		if (!archivo){
			fprintf(stderr, "%s", "No se puede ver el archivo indicado");
			return 1;
		}
		grep(argv[1], atoi(argv[2]), archivo);
		fclose(archivo);
	} else {
		grep(argv[1], atoi(argv[2]), stdin);
	}

	return 0;
}

#endif
