#ifndef ABB_H
#define ABB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"

// Structs

struct abb;
struct abb_iter;
struct abb_rango_iter;

typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;
typedef struct abb_rango_iter abb_iter_rango_t;


// Tipos de funciones para destruir dato y comparar claves

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);


abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

bool abb_pertenece(const abb_t *arbol, const char *clave);

size_t abb_cantidad(abb_t *arbol);

void abb_destruir(abb_t *arbol);


/* Iterador del abb (interno) */

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);


/* Iterador del abb (externo) */

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

bool abb_iter_in_avanzar(abb_iter_t *iter);

const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

bool abb_iter_in_al_final(const abb_iter_t *iter);

void abb_iter_in_destruir(abb_iter_t* iter);


/* *****************************************************************
                  ITERADOR EXTERNO DEL ARBOL BINARIO RANGO
 * *****************************************************************/


abb_iter_rango_t *abb_iter_rango_crear(const abb_t *arbol, char* desde, char* hasta);

bool abb_iter_rango_al_final(const abb_iter_rango_t *iter);

bool abb_iter_rango_avanzar(abb_iter_rango_t *iter);

const char *abb_iter_rango_ver_actual(const abb_iter_rango_t *iter);

void abb_iter_rango_destruir(abb_iter_rango_t* iter);

#endif // ABB_H