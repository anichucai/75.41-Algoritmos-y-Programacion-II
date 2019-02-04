#include "strutil.h"
#include "hash.h"
#include "abb.h"
#include "heap.h"
#include "pila.h"
#include "cola.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool agregar_archivo(char* nombre_archivo, hash_t* diccionario, abb_t* tablero);

bool ver_tablero(abb_t* tablero, hash_t* diccionario, int k, char* modo, char* desde, char* hasta);

bool info_vuelo(hash_t* tablero, char* codigo);

bool prioridad_vuelos(hash_t* diccionario, int k);

bool borrar(abb_t* tablero, hash_t* diccionario, char* desde, char* hasta);

int cmp_fecha_asc(char* fecha_1, char* fecha_2);

int cmp_fecha_desc(char* fecha_1, char* fecha_2);

