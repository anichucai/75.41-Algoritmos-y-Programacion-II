#include "pila.h"
#include <stdlib.h>
#include <stdbool.h>
#define TAMANIO_INICIAL 25
#define PORCENTAJE_DISMINUCION_MEMORIA 75
#define PORCENTAJE_AUMENTO_MEMORIA 200

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));
	if(!pila) return NULL;
	pila->datos = malloc(sizeof(void*)*TAMANIO_INICIAL);
	if (!pila->datos){
		free(pila);
		return NULL;
	}
	pila->cantidad = 0;
	pila->capacidad = TAMANIO_INICIAL;
	return pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	return (pila->cantidad == 0);
}

bool pila_redimensionar(pila_t *pila, int porcentaje){
	size_t nueva_capacidad = (pila->capacidad*porcentaje)/100;
	void** datos_nuevos = realloc(pila->datos, sizeof(void*)*nueva_capacidad);
	if (datos_nuevos==NULL) return false;
	pila->datos = datos_nuevos;
	pila->capacidad = nueva_capacidad;
	return true;
}

bool pila_apilar(pila_t *pila, void* valor){
	if (pila->capacidad==pila->cantidad){
		if (!pila_redimensionar(pila, PORCENTAJE_AUMENTO_MEMORIA)) return false;
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad ++;
	return true;
}


void* pila_ver_tope(const pila_t *pila){
	return (pila_esta_vacia(pila)) ? NULL : pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila){
	if (pila_esta_vacia(pila)) return NULL;
	pila->cantidad--;
	if ( pila->cantidad < (pila->capacidad*PORCENTAJE_DISMINUCION_MEMORIA)/100 && pila->capacidad > (TAMANIO_INICIAL*(100+PORCENTAJE_DISMINUCION_MEMORIA))/100){
		pila_redimensionar(pila,PORCENTAJE_DISMINUCION_MEMORIA);
	}
	return pila->datos[pila->cantidad];
}