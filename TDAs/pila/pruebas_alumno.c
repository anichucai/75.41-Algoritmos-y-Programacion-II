#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#define TAMANIO_INICIAL 25


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_casos_borde(){

	printf("---PRUEBAS DE CASOS BORDE---\n");

	pila_t * pila = pila_crear();
	void* vect[2];

	print_test("Una pila recien creada esta vacia.", pila_esta_vacia(pila));
	print_test("Se trato de desapilar una pila recien creada y se devolvio NULL.", pila_desapilar(pila)==NULL);
	print_test("Se trato de ver el tope de una pila recien creada y se devolvio NULL.", pila_ver_tope(pila)==NULL);

	print_test("Se apilo un valor NULL.", pila_apilar(pila, NULL));
	print_test("Se apilo un valor x.", pila_apilar(pila, &vect[0]));
	print_test("Se desapilo un valor x.", pila_desapilar(pila)==&vect[0]);
	print_test("Se desapilo un valor NULL.", pila_desapilar(pila)==NULL);

	print_test("La pila esta vacia.", pila_esta_vacia(pila)==true);
	print_test("Se trato de desapilar una pila vacia y se devolvio NULL.", pila_desapilar(pila)==NULL);
	print_test("Se trato de ver el tope de una pila y se devolvio NULL.", pila_ver_tope(pila)==NULL);
	
	pila_destruir(pila);
}

void pruebas_invariantes(){

	printf("---PRUEBAS DE INVARIANTES---\n");

	pila_t * pila = pila_crear();
	void* vect[4];

	print_test("Se apilo un valor v0.", pila_apilar(pila, &vect[0]) && pila_ver_tope(pila)==&vect[0] && !pila_esta_vacia(pila));
	print_test("Se apilo un valor v1.", pila_apilar(pila, &vect[1]) && pila_ver_tope(pila)==&vect[1] && !pila_esta_vacia(pila));
	print_test("Se apilo un valor v2.", pila_apilar(pila, &vect[2]) && pila_ver_tope(pila)==&vect[2] && !pila_esta_vacia(pila));
	print_test("Se apilo un valor v3.", pila_apilar(pila, &vect[3]) && pila_ver_tope(pila)==&vect[3] && !pila_esta_vacia(pila));
	print_test("Se desapilo un valor v3.", pila_desapilar(pila)==&vect[3]  && pila_ver_tope(pila)==&vect[2] && !pila_esta_vacia(pila));
	print_test("Se desapilo un valor v2.", pila_desapilar(pila)==&vect[2] && pila_ver_tope(pila)==&vect[1] && !pila_esta_vacia(pila));
	print_test("Se desapilo un valor v1.", pila_desapilar(pila)==&vect[1] && pila_ver_tope(pila)==&vect[0] && !pila_esta_vacia(pila));
	print_test("Se desapilo un valor v0.", pila_desapilar(pila)==&vect[0] && pila_ver_tope(pila)==NULL && pila_esta_vacia(pila));

	pila_destruir(pila);
}

void pruebas_crear_y_destruir_pila(){
	printf("---PRUEBAS DE CREAR Y DESTRUIR PILA---\n");
	pila_t * pila = pila_crear();
	print_test("Pila nueva fue creada", pila!=NULL);
	pila_destruir(pila);
	print_test("Pila nueva fue destruida", true);

}

void pruebas_volumen(int cant_elemtos){

	printf("---PRUEBAS DE VOLUMEN---\n");


	pila_t * pila = pila_crear();
	void* vector[cant_elemtos];

	bool esta_apilado = true;
	bool coincide_tope_apilar = true;
	bool coincide_tope_desapilar = true;

	for(int i=0; i<cant_elemtos; i++){
		esta_apilado &= pila_apilar(pila, &vector[i]);
		coincide_tope_apilar &= (&vector[i]== pila_ver_tope(pila));
	}
	for(int j=0; j<cant_elemtos; j++){
		coincide_tope_desapilar &= (pila_ver_tope(pila)== &vector[cant_elemtos-j-1]);
		pila_desapilar(pila);
	}

	print_test("Se logro apilar una gran volumen de elementos.", esta_apilado);
	print_test("Los elementos coinciden con su correspondiente tope.", coincide_tope_apilar);
	print_test("Se logro desapilar una gran volumen de elementos comprobando que su tope sea el acorde.", coincide_tope_desapilar);
	
	pila_destruir(pila);
}

void pruebas_pila_alumno() {
	pruebas_crear_y_destruir_pila();
	pruebas_invariantes();
	pruebas_casos_borde();
	pruebas_volumen(1000);

}