#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

int _max(int n, int m){
	if(n>m) {
		return 1;
	} else if (n<m){
		return -1;
	}
	return 0;
}

int max( const void* n, const void* m){
	return _max(*(int*)n, *(int*)m);
}



/* *****************************************************************
 *                    PRUEBAS ALUMNO DEL HEAP
 * *****************************************************************/

void pruebas_heap_crear_destruir(){

	printf("\n---PRUEBAS CREAY Y DESTRUIR HEAP---\n");

	heap_t* heap_1 = heap_crear(max);
	print_test("Se creo un heap.",heap_1!=NULL);
	print_test("El heap esta vacio.", heap_esta_vacio(heap_1));
	print_test("Heap destruir sin funcion de destruccion.", true);
	heap_destruir(heap_1,NULL);

	int datos[8];
	for(int i = 0; i<8; i++) datos[i]=i;

	heap_t* heap_2 = heap_crear(max);
	print_test("Se creo un heap.",heap_2!=NULL);
	bool se_encolar_datos = true;  
	for(int i = 0; i<8; i++) se_encolar_datos &= heap_encolar(heap_2, &datos[i]);
	print_test("El heap se encolaron datos en memoria estatica.", se_encolar_datos);
	heap_destruir(heap_2,NULL);
	print_test("Heap destruir sin funcion de destruccion.", true);

	heap_t* heap_3 = heap_crear(max);
	print_test("Se creo un heap.",heap_2!=NULL);
	bool se_encolar_y_desencolaron_datos = true;  
	for(int i = 0; i<8; i++) se_encolar_y_desencolaron_datos &= heap_encolar(heap_3, &datos[i]);
	for(int i = 0; i<8; i++) se_encolar_y_desencolaron_datos &= (heap_desencolar(heap_3)!=NULL);
	print_test("El heap se encolaron y desencolaron datos.", se_encolar_y_desencolaron_datos);
	heap_destruir(heap_3,NULL);
	print_test("Heap destruir sin funcion de destruccion.", true);

	heap_t* heap_4 = heap_crear(max);
	int* datos1 = malloc(sizeof(int)); int* datos2 = malloc(sizeof(int)); int* datos3 = malloc(sizeof(int));
	*datos1=1; *datos2=2; *datos3=3;
	bool se_encolar_datos_d = heap_encolar(heap_4, datos1) && heap_encolar(heap_4, datos2) && heap_encolar(heap_4, datos3);
	print_test("Se creo un heap.",heap_4!=NULL);
	print_test("El heap se encolaron datos en memoria dinamica.", se_encolar_datos_d);
	print_test("Heap destruir con funcion de destruccion.", true);
	heap_destruir(heap_4,free);
	


}

void pruebas_heap_vacio(){

	printf("\n---PRUEBAS HEAP VACIO---\n");

	heap_t* heap = heap_crear(max);
	print_test("Se creo un heap.",heap!=NULL);
	print_test("El heap esta vacio.", heap_esta_vacio(heap) && heap_cantidad(heap)==0);
	print_test("Heap ver maximo.",heap_ver_max(heap)==NULL);
	print_test("Heap desencolar.",heap_desencolar(heap)==NULL);
	print_test("Heap destruir.", true); heap_destruir(heap,NULL);

}


void pruebas_heap_vacio_luego_de_desencolar(int n){

	printf("\n---PRUEBAS HEAP VACIO LUEGO DE DESENCOLAR---\n");

	heap_t* heap = heap_crear(max);
	int datos[n];
	for(int i = 0; i<n; i++) datos[i]=i;
	for(int i = 0; i<n; i++) heap_encolar(heap, &datos[i]);
	for(int i = 0; i<n; i++) heap_desencolar(heap);

	print_test("Se creo un heap, se encolo y desencolo hasta estar vacio.", heap!=NULL);
	print_test("El heap esta vacio.", heap_esta_vacio(heap) && heap_cantidad(heap)==0);
	print_test("Heap ver maximo.",heap_ver_max(heap)==NULL);
	print_test("Heap desencolar.",heap_desencolar(heap)==NULL);
	print_test("Heap destruir.", true); heap_destruir(heap,NULL);

}


void pruebas_encolar(int n){

	printf("\n---PRUEBAS ENCOLAR---\n");

	heap_t* heap = heap_crear(max);
	int datos[n];
	for(int i = 0; i<n; i++) datos[i]=i;

	bool encolar_sin_error = true;
	bool cantidad_correcta = true;
	bool max_correcto = true;

	for(int i = 0; i<n; i++){
		cantidad_correcta &= (heap_cantidad(heap)==i);
		encolar_sin_error &= heap_encolar(heap, &datos[i]);
		max_correcto &= (*(int*)heap_ver_max(heap)==i);
	}

	heap_destruir(heap,NULL);

	print_test("Heap encolar numeros enteros.", encolar_sin_error);
	print_test("Heap cantidad correcta de elementos.", cantidad_correcta);
	print_test("Heap maximo correcto.", max_correcto);
}


void pruebas_desencolar(int n){

	printf("\n---PRUEBAS DESENCOLAR---\n");

	heap_t* heap = heap_crear(max);
	int datos[n];
	for(int i = 0; i<n; i++) datos[i]=i;
	for(int i = 0; i<n; i++) heap_encolar(heap, &datos[i]);

	bool desencolar_sin_error = true;
	bool cantidad_correcta = true;
	bool max_correcto = true;

	for(int i = n-1; i>=0; i--){
		cantidad_correcta &= (heap_cantidad(heap)==i+1);
		max_correcto &= (*(int*)heap_ver_max(heap)==i);
		desencolar_sin_error &= (*(int*)heap_desencolar(heap)==datos[i]);
	}

	heap_destruir(heap,NULL);

	print_test("Heap desencolar numeros enteros.", desencolar_sin_error);
	print_test("Heap cantidad correcta de elementos.", cantidad_correcta);
	print_test("Heap maximo correcto.", max_correcto);

}


void pruebas_invariantes(){

	printf("\n---PRUEBAS INVARIANTES---\n");

	heap_t* heap = heap_crear(max);

	int datos[10];
	for(int i = 0; i<10; i++) datos[i]=i;

	for(int i = 0; i<10; i++) if(i%2!=0) heap_encolar(heap, &datos[i]); // encolo impares
	for(int i = 0; i<10; i++) if(i%2==0) heap_encolar(heap, &datos[i]); // encolo pares

	print_test("Heap minimo correcto luego de encolar numeros mezclados.", *(int*)heap_ver_max(heap)==9);
	print_test("Heap minimo correcto luego de desencolar.", *(int*)heap_desencolar(heap)==9 &&  *(int*)heap_ver_max(heap)==8);

	heap_destruir(heap,NULL);
}


void pruebas_crear_arreglo(){

	printf("\n---PRUEBAS CREAR ARREGLO---\n");


	int datos[10]={1,4,3,2,5,6,8,9,7};
	void* arr[10];
	for(int i = 0; i<10; i++) arr[i] = &datos[i];

	heap_t* heap = heap_crear_arr(arr, 10, max);

	bool ok = true;
	for(int i=9; i>=0; i--) (ok &= (*(int*)heap_desencolar(heap)==i));
	print_test("Heap creado a travez de arreglo.",ok);

	heap_destruir(heap, NULL);

}


void pruebas_heapsort(){

	printf("\n---PRUEBAS HEAPSORT---\n");

	int datos[10]={1,0,4,3,2,5,6,8,9,7};
	void* elementos[10];
	for(int i = 0; i<10; i++) elementos[i] = &datos[i];

	heap_sort(elementos,10,max);

	bool ok = true;
	for(int i=0; i<10; i++) (ok &= (*(int*)elementos[i]==i));

	//for (int i = 0; i < 10; ++i) printf("res%d\n", *((int*)elementos[i]));
	print_test("Arreglo ordenado a travez de heapsort.",ok);

}


void pruebas_heap_alumno(void){
	pruebas_heap_crear_destruir();
	pruebas_heap_vacio();
	pruebas_heap_vacio_luego_de_desencolar(10);
	pruebas_encolar(10);
	pruebas_desencolar(10);
	pruebas_invariantes();
	pruebas_crear_arreglo();
	pruebas_heapsort();
}