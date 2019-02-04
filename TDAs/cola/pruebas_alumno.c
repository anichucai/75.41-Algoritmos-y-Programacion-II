#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_casos_borde(){

	printf("---PRUEBAS DE CASOS BORDE---\n");

	cola_t * cola = cola_crear();
	void* vect[2];

	print_test("Una cola recien creada esta vacia.", cola_esta_vacia(cola));
	print_test("Se trato de desencolar y devolvio NULL.", cola_desencolar(cola)==NULL);
	print_test("Se trato de ver el primer dato y devolvio NULL.", cola_ver_primero(cola)==NULL);

	print_test("Se encolo un valor x1.", cola_encolar(cola, &vect[0]) && cola_ver_primero(cola)== &vect[0]);
	print_test("Se encolo un valor x2.", cola_encolar(cola, &vect[1])  && cola_ver_primero(cola)== &vect[0]);
	print_test("Se encolo un valor NULL.", cola_encolar(cola, NULL) && cola_ver_primero(cola)== &vect[0]);
	print_test("Se desencolo un valor x1.", cola_desencolar(cola)  && cola_ver_primero(cola)== &vect[1]);
	print_test("Se desencolo un valor x2.", cola_desencolar(cola)  && cola_ver_primero(cola)== NULL);
	print_test("Se desencolo un valor NULL.", cola_desencolar(cola)==NULL);

	print_test("La cola esta vacia.", cola_esta_vacia(cola));
	print_test("Se trato de desencolar y se devolvio NULL.", cola_desencolar(cola)==NULL);
	print_test("Se trato de ver el primer dato y se devolvio NULL.", cola_ver_primero(cola)==NULL);
	
	cola_destruir(cola, NULL);
}

void pruebas_invariantes(){

	printf("---PRUEBAS DE INVARIANTES---\n");

	cola_t * cola = cola_crear();
	void* vect[4];
	bool 	tope_correcto= true;
	print_test("Se encolo un valor v0.", cola_encolar(cola, &vect[0]));
	print_test("Se encolo un valor v1.", cola_encolar(cola, &vect[1]));
	print_test("Se encolo un valor v2.", cola_encolar(cola, &vect[2]));
	print_test("Se encolo un valor v3.", cola_encolar(cola, &vect[3]));
	print_test("La cola no esta vacia.", !cola_esta_vacia(cola));
	print_test("El tope es el v0.", cola_ver_primero(cola)==&vect[0]);

	print_test("Se desencolo un valor v0.", cola_desencolar(cola)==&vect[0]);
	tope_correcto &= cola_ver_primero(cola)==&vect[1];
	print_test("Se desencolo un valor v1.", cola_desencolar(cola)==&vect[1]);
	tope_correcto &= cola_ver_primero(cola)==&vect[2];
	print_test("Se desencolo un valor v2.", cola_desencolar(cola)==&vect[2]);
	tope_correcto &= cola_ver_primero(cola)==&vect[3];
	print_test("Se desencolo un valor v3.", cola_desencolar(cola)==&vect[3]);
	tope_correcto &= cola_ver_primero(cola)==NULL;
	print_test("Al desencolar, su valor primero es el esperado", tope_correcto);
	print_test("LA cola esta vacia", cola_esta_vacia(cola));

	cola_destruir(cola, NULL);
}

void pruebas_crear_y_destruir(){
	printf("---PRUEBAS DE CREAR Y DESTRUIR COLA---\n");
	void* vect[4];
	cola_t * cola_1 = cola_crear();
	print_test("Cola 1 fue creada", cola_1!=NULL);
	print_test("Se encolo un entero a la Cola 1",cola_encolar(cola_1, &vect[0]));
	print_test("Se encolo un entero a la Cola 1",cola_encolar(cola_1, &vect[1]));
	print_test("Se encolo un entero a la Cola 1",cola_encolar(cola_1, &vect[2]));
	cola_destruir(cola_1, NULL);
	print_test("Cola nueva fue destruida con el parametro NULL", true);
	
	cola_t * cola_2 = cola_crear();
	print_test("Cola 2 fue creada", cola_2!=NULL);
	void** p1= malloc(sizeof(void*));
	void** p2= malloc(sizeof(void*));
	print_test("Se encolo con memoria dinamica a la Cola 2",cola_encolar(cola_2,p1));
	print_test("Se encolo con memoria dinamica a la Cola 2",cola_encolar(cola_2,p2));
	cola_destruir(cola_2, free);
	print_test("Cola nueva fue destruida con el parametro free",true);

}

void pruebas_volumen(int cant_elemetos){

	printf("---PRUEBAS DE VOLUMEN---\n");


	cola_t * cola = cola_crear();
	void* vector[cant_elemetos];

	bool esta_encolado = true;
	bool coincide_primero_encolar = true;
	bool coincide_primero_desencolar = true;

	for(int i=0; i<cant_elemetos; i++){
		esta_encolado &= cola_encolar(cola, &vector[i]);
		coincide_primero_encolar &= (&vector[0]== cola_ver_primero(cola));
	}

	for(int j=0; j<cant_elemetos; j++){
		coincide_primero_desencolar &= (cola_ver_primero(cola)== &vector[j]);
		cola_desencolar(cola);
	}

	print_test("Se logro encolar una gran volumen de elementos.", esta_encolado);
	print_test("Cada vez que se encola, el primer elemento es el correspondiente.", coincide_primero_encolar);
	print_test("Se logro desencolar una gran volumen de elementos.", coincide_primero_desencolar);
	
	cola_destruir(cola, NULL);
}

void pruebas_cola_alumno(void) {
	pruebas_invariantes();
	pruebas_casos_borde();
	pruebas_volumen(1000);
	pruebas_crear_y_destruir();


}