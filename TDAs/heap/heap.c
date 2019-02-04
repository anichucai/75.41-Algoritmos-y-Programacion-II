#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM_INICIAL 10


/* *****************************************************************
 *                   		  STRUCT
 * *****************************************************************/

typedef struct heap {

    void** datos;
    size_t cantidad;  
    size_t capacidad;  
    cmp_func_t cmp;

}heap_t;


/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/


//Función para swapear elementos
void swap(void** arreglo,size_t n1,size_t n2){
	void* dato_aux = arreglo[n1];
	arreglo[n1] = arreglo[n2];
	arreglo[n2] = dato_aux;
}


//Función para redimensionar el heap
bool redimensionar(heap_t* heap,size_t capacidad){

	void** nuevos_datos = realloc(heap->datos, capacidad*sizeof(void*));
	if(!nuevos_datos) return false;

	heap->datos = nuevos_datos;
	heap->capacidad = capacidad;

	return true;
}


//DOWNHEAP
void downheap(void* datos[],size_t cant,size_t pos,cmp_func_t cmp){

	if(pos >= cant) return;

	size_t max = pos;
	size_t izq = (2*pos)+1;
	size_t der = (2*pos)+2;

	if(izq<cant && cmp(datos[izq], datos[max])>0) max = izq;
	if(der<cant && cmp(datos[der], datos[max])>0) max = der;
	
	if(max!=pos){
		swap(datos,pos,max);
		downheap(datos,cant,max,cmp);
	}
}


//UPHEAP
void upheap(void* datos[],size_t pos,cmp_func_t cmp){

	if(pos==0) return;

	size_t pos_padre = (pos-1)/2;

	if(cmp(datos[pos_padre],datos[pos])<0){
		swap(datos,pos_padre,pos);
		upheap(datos,pos_padre,cmp);
	}
}


/* *****************************************************************
 *                  	     HEAPSORT
 * *****************************************************************/

void heap_sort(void* elementos[], size_t cant, cmp_func_t cmp){

	if(!elementos || cant<=1) return;
	
	heap_t* heap = heap_crear_arr(elementos,cant,cmp);

	for(size_t i=cant-1; i>0; i--){
		elementos[i] = heap->datos[0];
		swap(heap->datos,0,i);
		downheap(heap->datos,i,0,cmp);
	}

	*elementos = *heap->datos;

	heap_destruir(heap, NULL);
}


/* *****************************************************************
 *                    PRIMITIVAS DEL HEAP
 * *****************************************************************/


void *heap_ver_max(const heap_t *heap){
	return (heap->cantidad==0) ? NULL : heap->datos[0];
}


void* heap_desencolar(heap_t *heap){

	if(heap->cantidad==0) return NULL;

	heap->cantidad--;

	swap(heap->datos, 0, heap->cantidad);

	void* dato = heap->datos[heap->cantidad];

	heap->datos[heap->cantidad] = NULL;

	downheap(heap->datos, heap->cantidad, 0, heap->cmp);

	if(heap->cantidad==(int)heap->capacidad/4 && heap->capacidad>1) {
		if(!redimensionar(heap,(int)heap->capacidad/2)) return NULL;
	}
	return dato;	
}


bool heap_encolar(heap_t* heap, void* valor){

	if(!valor) return false;

	if(heap->capacidad==heap->cantidad){
		if(!redimensionar(heap,heap->capacidad*2)) return false;
	}
	heap->datos[heap->cantidad]=valor;
	upheap(heap->datos, heap->cantidad, heap->cmp);

	heap->cantidad++;
	
	return true;
}


bool heap_esta_vacio(const heap_t* heap){
	return heap->cantidad==0;
}


heap_t* _heap_crear(cmp_func_t cmp, size_t capacidad){

	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;

	heap->datos = malloc(sizeof(void*)*capacidad);
	if(!heap->datos){
		free(heap);
		return NULL;
	}

	heap->cantidad = 0;
	heap->capacidad = capacidad;
	heap->cmp = cmp;

	return heap;
}

heap_t* heap_crear(cmp_func_t cmp){
	return _heap_crear(cmp, TAM_INICIAL);
}


size_t heap_cantidad(const heap_t* heap){
	return heap->cantidad;
}


heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){

	if(!arreglo || n<0) return NULL;

	heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
	if(!heap) return NULL;
	heap->datos = (void**)malloc(sizeof(void*)*n);
	if(!heap->datos){
		free(heap);
		return NULL;
	}
	heap->cantidad = n;
	heap->capacidad = n;
	heap->cmp = cmp;

	for(int i = 0; i<n; i++) heap->datos[i]=arreglo[i];

	for(int i = ((int)n-1)/2; i>=0; i--) downheap(heap->datos,n,i,cmp);

	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){

	if(destruir_elemento){
		while(!heap_esta_vacio(heap)) (destruir_elemento)(heap_desencolar(heap));

	}
	free(heap->datos);
	free(heap);
}