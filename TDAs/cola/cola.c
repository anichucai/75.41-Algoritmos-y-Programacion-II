#include "cola.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo{
	void* dato;
	struct nodo* prox;
} nodo_t;

nodo_t* crear_nodo(void* valor){
	nodo_t* nodo= malloc(sizeof(nodo_t));
	if (!nodo) return NULL;
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
}

typedef struct cola{
	nodo_t* prim;
	nodo_t* ult;
} cola_t;

cola_t* cola_crear(void){
	cola_t* cola = malloc(sizeof(cola_t));
	if (!cola) return NULL;
	cola->prim = NULL;
	cola->ult = NULL;

	return cola;
}

typedef void (*destruir_dato_t)(void*);

void cola_destruir(cola_t *cola, void destruir_dato(void*)){

	if (destruir_dato!=NULL){
		while (!cola_esta_vacia(cola)) destruir_dato(cola_desencolar(cola));
	} else{
		while (!cola_esta_vacia(cola)) cola_desencolar(cola);
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t* cola){
	return (cola->prim == NULL);
}

void* cola_ver_primero(const cola_t* cola){
	return cola_esta_vacia(cola) ? NULL:cola->prim->dato;
}

bool cola_encolar(cola_t* cola, void* valor){
	nodo_t* nodo = crear_nodo(valor);
	if (!nodo) return false;
	if (cola_esta_vacia(cola)){
		cola->prim = nodo;
	}else{
		cola->ult->prox = nodo;
	}
	cola->ult = nodo;
	return true;
}

void* cola_desencolar(cola_t* cola){
	if (cola_esta_vacia(cola)) return NULL;
	nodo_t* desencolado = cola->prim;
	void* valor = desencolado->dato;
	if (cola->prim->prox==NULL){
		cola->prim=NULL;
		cola->ult=NULL;
	}else{
		cola->prim = cola->prim->prox;
	}
	free(desencolado);
	return valor;
}