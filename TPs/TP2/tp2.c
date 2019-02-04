#include "algueiza.h"
#include "strutil.h"
#include "hash.h"
#include "abb.h"
#include "heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LEN_COMANDO 300

int main(){

	hash_t* diccionario = hash_crear((hash_destruir_dato_t)free_strv);
	if(!diccionario) fprintf(stderr, "%s\n", "Error en comando\n");

	abb_t* tablero = abb_crear((abb_comparar_clave_t)cmp_fecha_asc, NULL);
	if(!tablero) fprintf(stderr, "%s\n", "Error en comando\n");

	char comando[LEN_COMANDO];

	while(fgets(comando,LEN_COMANDO,stdin)){

		char** aux =  split(comando,'\n');
		char** parametros = split(aux[0], ' ');
		size_t len = len_strv(parametros);

		if (strcmp(parametros[0], "agregar_archivo")==0){

			(len!=2 && agregar_archivo(parametros[1], diccionario, tablero)) ? fprintf(stdout, "OK\n") : fprintf(stderr, "Error en comando %s\n", parametros[0]);

		} else if (strcmp(parametros[0], "ver_tablero")==0){

			(len!=5 && ver_tablero(tablero, diccionario, atoi(parametros[1]), parametros[2], parametros[3], parametros[4])) ? fprintf(stdout, "OK\n") : fprintf(stderr, "Error en comando %s\n", parametros[0]);

		} else if (strcmp(parametros[0], "info_vuelo")==0){

			(len!=2 && info_vuelo(diccionario, parametros[1])) ? fprintf(stdout, "OK\n") : fprintf(stderr, "Error en comando %s\n", parametros[0]);

		} else if (strcmp(parametros[0], "prioridad_vuelos")==0){

			(len!=2 && prioridad_vuelos(diccionario, (int)atoi(parametros[1])) ? fprintf(stdout, "OK\n") : fprintf(stderr, "Error en comando %s\n", parametros[0]));

		} else if (strcmp(parametros[0], "borrar")==0){

			(len!=3 && borrar(tablero, diccionario, parametros[1], parametros[2])) ? fprintf(stdout, "OK\n") : fprintf(stderr, "Error en comando %s\n", parametros[0]);

		} else {

			fprintf(stderr, "Error en comando\n");
		}

		free_strv(aux);
		free_strv(parametros);
	}

	hash_destruir(diccionario);
	abb_destruir(tablero);

	return 0;

}