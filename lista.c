#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
/* ******************************************************************
 *                PRIMITIVAS DE LA LISTA
 * *****************************************************************/

typedef struct nodo{
	void* dato;
	struct nodo* prox;
} nodo_t;

typedef struct lista{
	nodo_t* prim;
	nodo_t* ult;
	size_t len;
} lista_t;

nodo_t* crear_nodo(void* valor){

	nodo_t* nodo= malloc(sizeof(nodo_t));
	if (!nodo) return NULL;

	nodo->dato = valor;
	nodo->prox = NULL;

	return nodo;
}

lista_t *lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if (!lista) return NULL;
	lista->len = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista){
	return (lista->len==0);
}

bool lista_insertar_primero(lista_t *lista, void *dato){

	nodo_t* primero = crear_nodo(dato);
	if (!primero) return false;

	(lista_esta_vacia(lista)) ? (lista->ult=primero) : (primero->prox=lista->prim);
	lista->prim = primero;
	
	lista->len++;

	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){

	nodo_t* ultimo = crear_nodo(dato);
	if (!ultimo) return false;

	(lista_esta_vacia(lista)) ? (lista->prim = ultimo) : (lista->ult->prox=ultimo) ;
	lista->ult = ultimo;

	lista->len++;
	
	return true;
}

void *lista_borrar_primero(lista_t *lista){

	if (lista_esta_vacia(lista)) return NULL;

	nodo_t* borrado = lista->prim;
	void* dato = borrado->dato;

	if (lista->len == 1) lista->ult = NULL;
	lista->prim = lista->prim->prox;

	lista->len--;
	
	free(borrado);
	
	return dato;
}

void *lista_ver_primero(const lista_t *lista){
	if (lista_esta_vacia(lista)) return NULL;
	return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista)) return NULL;
	return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->len;
}

typedef void (*destruir_dato_t)(void*);

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	while (!lista_esta_vacia(lista)){
		void* dato = lista_borrar_primero(lista);
		if (destruir_dato!=NULL) destruir_dato(dato);
	}
	free(lista);
}



/* ******************************************************************
 *                PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

 void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
 	if(lista_esta_vacia(lista)) return;
 	nodo_t* actual = lista->prim;
 	while(actual && visitar(actual->dato, extra)) actual = actual->prox;
 }

 /* ******************************************************************
 *                PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

typedef struct lista_iter{

	lista_t* lista;
 	nodo_t* anterior;
 	nodo_t* actual;

 } lista_iter_t;


lista_iter_t *lista_iter_crear(lista_t *lista){

	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if(!iter) return NULL;

	iter->lista = lista;
	iter->anterior = NULL;
	(lista_esta_vacia(iter->lista))? (iter->actual = NULL) : (iter->actual = iter->lista->prim);

	return iter;
}


 bool lista_iter_avanzar(lista_iter_t *iter){

 	if(lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) return false;

 	iter->anterior = iter->actual;
 	iter->actual = iter->actual->prox;

 	return true;
 }


 void *lista_iter_ver_actual(const lista_iter_t *iter){

 	if(lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) return NULL;
 	return iter->actual->dato;
 }


bool lista_iter_al_final(const lista_iter_t *iter){
	return (!iter->actual);
}


void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}


bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	nodo_t* insertado = crear_nodo(dato);
	if (!insertado) return false;

	(iter->actual) ?  (insertado->prox = iter->actual):(iter->lista->ult = insertado);
	iter->actual = insertado;
	(iter->anterior) ? (iter->anterior->prox = insertado):(iter->lista->prim = insertado);
	
	iter->lista->len++;

	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){

	if (!iter->actual) return NULL;

	nodo_t* borrado = iter->actual;
	void *dato = iter->actual->dato;

	(!iter->anterior) ? (iter->lista->prim = iter->actual->prox) : (iter->anterior->prox = iter->actual->prox);
	if (!iter->actual->prox) iter->lista->ult = iter->anterior;

	iter->actual = iter->actual->prox;
	
	iter->lista->len--;
	
	free(borrado);
	
	return dato;
}