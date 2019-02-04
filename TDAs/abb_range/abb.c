#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "abb.h"
#include "pila.h"

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);
typedef int (*cmp_func_t) (const void *a, const void *b);



//----------------------Definición de Structs------------------

typedef struct abb_nodo abb_nodo_t;
typedef struct abb_nodo{
	abb_nodo_t* izq;
	abb_nodo_t* der;
	char* clave;
	void* dato;
}abb_nodo_t;

typedef struct abb{
	abb_nodo_t* raiz;
	abb_destruir_dato_t destruir_dato;
	abb_comparar_clave_t cmp;
	size_t cantidad;	
}abb_t;

typedef struct abb_iter{
	const abb_t* arbol;
	pila_t* pila;
	
}abb_iter_t;


//--------------------Funciones Auxiliares---------------------------

//Funcion para buscar un nodo, lo retorna si lo encuentra

abb_nodo_t* _buscar_nodo(const abb_t* arbol, const char* clave, abb_nodo_t* nodo){
	
	if(!nodo) return NULL;

	int cmp = arbol->cmp(clave,nodo->clave);

	if(cmp<0) return _buscar_nodo(arbol,clave,nodo->izq);	
	if(cmp>0) return _buscar_nodo(arbol,clave,nodo->der);

	return nodo;
}

abb_nodo_t* buscar_nodo(const abb_t* arbol, const char* clave){
	if (!arbol) return NULL;
	return _buscar_nodo(arbol, clave, arbol->raiz);
}


//Función para encontrar padre de nuestro nodo, exista o no.

abb_nodo_t* _buscar_padre(const abb_t* arbol,abb_nodo_t* padre,abb_nodo_t* hijo,const char* clave){
	
	if(!hijo) return padre;

	int resultado = arbol->cmp(clave,hijo->clave); 
	if(resultado<0) return _buscar_padre(arbol,hijo,hijo->izq,clave);
	if(resultado>0) return _buscar_padre(arbol,hijo,hijo->der,clave);

	return padre;
		
}

abb_nodo_t* buscar_padre(const abb_t* arbol, const char* clave){
	return _buscar_padre(arbol, NULL, arbol->raiz, clave);
}


//Funcion para swappear nodos

void swap(abb_nodo_t* nodo1, abb_nodo_t* nodo2){
	
	void* dato_aux = nodo1->dato;
	char* clave_aux = nodo1->clave;

	nodo1->clave = nodo2->clave;
	nodo1->dato = nodo2->dato;

	nodo2->clave = clave_aux;
	nodo2->dato = dato_aux;

}

abb_nodo_t* sig_min_in_order(abb_nodo_t* nodo){
	if (!nodo) return NULL;
	abb_nodo_t* min = nodo;
	if (min->der) min = min->der;
	while(min->izq) min = min->izq;
	return min;
} 


//Funciones para determinar los distintos casos de un nodo en un abb
bool es_hoja(abb_nodo_t* nodo){
	if(!nodo) return false;
	return !nodo->der && !nodo->izq;
}
bool tiene_un_hijo(abb_nodo_t* nodo){
	if(!nodo) return false;
	return (nodo->der && !nodo->izq) || (!nodo->der && nodo->izq);
}
bool tiene_dos_hijos(abb_nodo_t* nodo){
	if(!nodo) return false;
	return nodo->der && nodo->izq;
}


/* *****************************************************************
 *                    ARBOL BINARIO NODO
 * *****************************************************************/

abb_nodo_t* crear_nodo(const char* clave, void* dato){

	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if(!nodo) return NULL;
	nodo->izq = NULL;
	nodo->der = NULL;
	nodo->clave = malloc(sizeof(char)*(strlen(clave)+1));
	if(!nodo->clave){
		free(nodo);
		return NULL;
	}
	strcpy(nodo->clave,clave);
	nodo->dato = dato;
	return nodo;
}

void destruir_nodo(abb_nodo_t* nodo){
	free(nodo->clave);
	free(nodo);
}


/* *****************************************************************
 *                    PRIMITIVAS DEL ARBOL BINARIO
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb) return NULL;

	abb->raiz = NULL;
	abb->destruir_dato = destruir_dato;
	abb->cmp = cmp;
	abb->cantidad = 0;

	return abb;	
}


bool abb_pertenece(const abb_t* arbol,const char* clave){
	return buscar_nodo(arbol, clave)!=NULL;
}


void* abb_obtener(const abb_t* arbol,const char* clave){
	abb_nodo_t* nodo = buscar_nodo(arbol, clave);
	if (!nodo) return NULL;
	return nodo->dato;	
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

	if(!arbol->raiz){															

		arbol->raiz = crear_nodo(clave,dato);
		if(!arbol->raiz) return false;
		arbol->cantidad++;

	}else{

		abb_nodo_t* padre = buscar_padre(arbol,clave);

		if(!padre){ 															
			if (arbol->destruir_dato && arbol->raiz->dato) arbol->destruir_dato(arbol->raiz->dato);
			arbol->raiz->dato = dato;
		}else{

			int resultado = arbol->cmp(clave,padre->clave);

			abb_nodo_t* hijo;

			if(resultado<0) hijo=padre->izq;
							
			else  hijo=padre->der;
			
			
			if(hijo && arbol->cmp(clave,hijo->clave)==0){

				if (arbol->destruir_dato && hijo->dato) arbol->destruir_dato(hijo->dato); 
				hijo->dato=dato;

			}
			else{

				abb_nodo_t* nodo = crear_nodo(clave,dato); 
				if(!nodo) return false;
				
				if(resultado<0) padre->izq=nodo;
								
				else  padre->der=nodo;
								
				arbol->cantidad++;
			}
							
							 				
			}
		}
	

	return true;
}

void* _abb_borrar(abb_t *arbol, const char *clave, abb_nodo_t* nodo, abb_nodo_t* padre){

	if (!nodo) return NULL;

	void* dato = nodo->dato;

	if(es_hoja(nodo)){

		if(!padre){
			arbol->raiz = NULL;
		}else{
			(padre->izq && arbol->cmp(clave,padre->izq->clave)==0) ? (padre->izq = NULL) : (padre->der = NULL);
		}

	} else if (tiene_un_hijo(nodo)){

		if(!padre){
			(nodo->izq) ? (arbol->raiz = nodo->izq) : (arbol->raiz = nodo->der);
		}else{
			if (padre->izq && arbol->cmp(nodo->clave, padre->izq->clave)==0){
				padre->izq = ((nodo->izq) ? nodo->izq : nodo->der);
			}else{
				padre->der = ((nodo->izq) ? nodo->izq : nodo->der);
			}
		}

	} else if(tiene_dos_hijos(nodo)){

		abb_nodo_t* nodo_min = sig_min_in_order(nodo);
		abb_nodo_t* padre_min = buscar_padre(arbol, nodo_min->clave);
		swap(nodo, nodo_min);
		return _abb_borrar(arbol, clave,nodo_min,padre_min);

	}

	destruir_nodo(nodo);
	arbol->cantidad--;
	return dato;
}

void* abb_borrar(abb_t *arbol, const char *clave){
	if (!arbol || !arbol->raiz) return NULL;
	abb_nodo_t* nodo = buscar_nodo(arbol, clave);
	abb_nodo_t* padre = buscar_padre(arbol,clave);
	return _abb_borrar(arbol, clave, nodo, padre);
}



size_t abb_cantidad(abb_t* arbol){
	return arbol->cantidad;
}

void _abb_destruir(abb_t* arbol, abb_nodo_t* nodo){

	if(!nodo) return;

	if(nodo->izq) _abb_destruir(arbol, nodo->izq);
	if(nodo->der) _abb_destruir(arbol, nodo->der);

	if (arbol->destruir_dato && nodo->dato) arbol->destruir_dato(nodo->dato);;
	destruir_nodo(nodo);
}

void abb_destruir(abb_t* arbol){

	if(!arbol) return;
	_abb_destruir(arbol,arbol->raiz);
	free(arbol);
}



/* *****************************************************************
 *                  ITERADOR INTERNO DEL ARBOL BINARIO
 * *****************************************************************/
bool recorrido_inorder(abb_nodo_t* nodo,bool visitar(const char* clave, void* valor, void* extra), void *extra){

	if(!nodo) return false;
	
	if(nodo->izq){
		if(!recorrido_inorder(nodo->izq,visitar,extra))return false;
	}

	if(!(visitar)(nodo->clave,nodo->dato,extra)) return false;
	
	if(nodo->der)if(!recorrido_inorder(nodo->der,visitar,extra))return false;

	return true;
}


void abb_in_order(abb_t *arbol, bool visitar(const char* clave, void* valor, void* extra), void *extra){

	if(!arbol) return;

	recorrido_inorder(arbol->raiz, visitar,extra);
}


/* *****************************************************************
 *                  ITERADOR EXTERNO DEL ARBOL BINARIO
 * *****************************************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

	abb_iter_t* iter=malloc(sizeof(abb_iter_t));
	if(!iter) return NULL;

	iter->pila = pila_crear();
	if(!iter->pila){
		free(iter);
		return NULL;
	}

	if (arbol->raiz){
		pila_apilar(iter->pila,arbol->raiz);
		while(((abb_nodo_t*)pila_ver_tope(iter->pila))->izq) pila_apilar(iter->pila,((abb_nodo_t*)pila_ver_tope(iter->pila))->izq);
	}

	return iter;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}

bool abb_iter_in_avanzar(abb_iter_t *iter){

	if(abb_iter_in_al_final(iter)) return false;
	
	abb_nodo_t* act = pila_desapilar(iter->pila);
	if(act->der){
		pila_apilar(iter->pila, act->der);
		while (((abb_nodo_t*)pila_ver_tope(iter->pila))->izq) pila_apilar(iter->pila, ((abb_nodo_t*)pila_ver_tope(iter->pila))->izq);
	}

	return true;

}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)) return NULL;
	return ((abb_nodo_t*)pila_ver_tope(iter->pila))->clave;
}

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}






/* *****************************************************************
                  ITERADOR EXTERNO DEL ARBOL BINARIO RANGO
 * *****************************************************************/

typedef struct abb_rango_iter{
	const abb_t* arbol;
	pila_t* pila;
	char* desde;
	char* hasta;
	cmp_func_t cmp;
	
}abb_iter_rango_t;

void apilar_siguiente_inorder(abb_iter_rango_t* iter, abb_nodo_t* nodo){

	if (nodo){
		pila_apilar(iter->pila,nodo);
		abb_nodo_t* actual = ((abb_nodo_t*)pila_ver_tope(iter->pila))->izq;
		while(actual && iter->cmp(actual->dato,iter->desde)>=0 && iter->cmp(actual->dato, iter->hasta)<=0){
			pila_apilar(iter->pila,((abb_nodo_t*)pila_ver_tope(iter->pila))->izq);
			actual = ((abb_nodo_t*)pila_ver_tope(iter->pila))->izq;
		}
	}
}


abb_iter_rango_t *abb_iter_rango_crear(const abb_t *arbol, char* desde, char* hasta, cmp_func_t cmp){

	abb_iter_rango_t* iter = malloc(sizeof(abb_iter_rango_t));
	if(!iter) return NULL;

	iter->pila = pila_crear();
	if(!iter->pila){
		free(iter);
		return NULL;
	}
	iter->cmp = cmp;
	iter->desde = desde;
	iter->hasta = hasta;

	apilar_siguiente_inorder(iter, arbol->raiz);

	return iter;
}

bool abb_iter_rango_al_final(const abb_iter_rango_t *iter){
	return pila_esta_vacia(iter->pila);
}

bool abb_iter_rango_avanzar(abb_iter_rango_t *iter){

	if(abb_iter_rango_al_final(iter)) return false;
	
	apilar_siguiente_inorder(iter, ((abb_nodo_t*)pila_desapilar(iter->pila))->der);

	return true;

}

const char *abb_iter_rango_ver_actual(const abb_iter_rango_t *iter){
	if(abb_iter_rango_al_final(iter)) return NULL;
	return ((abb_nodo_t*)pila_ver_tope(iter->pila))->clave;
}

void abb_iter_rango_destruir(abb_iter_rango_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}