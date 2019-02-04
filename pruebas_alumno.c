#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void pruebas_invariantes(){

	printf("\n---PRUEBAS DE LAS INVARIANTES---\n");
	
	void* vect[6];

	lista_t * lista = lista_crear();
	print_test("Se creo una lista.", true);

	print_test("Se inserto primero un valor v0.", lista_insertar_primero(lista, &vect[0]));
	print_test("Se inserto primero un valor v1.", lista_insertar_primero(lista, &vect[1]));
	print_test("Se inserto primero un valor v2.", lista_insertar_primero(lista, &vect[2]));

	print_test("Se inserto ultimo un valor v3.", lista_insertar_ultimo(lista, &vect[3]));
	print_test("Se inserto ultimo un valor v4.", lista_insertar_ultimo(lista, &vect[4]));
	print_test("Se inserto ultimo un valor v5.", lista_insertar_ultimo(lista, &vect[5]));

	print_test("El primer valor es v2.", lista_ver_primero(lista)==&vect[2]);

	print_test("El ultimo valor es v5.", lista_ver_ultimo(lista)==&vect[5]);

	print_test("El largo de la lista es 6", lista_largo(lista)==6);

	print_test("Se borro el primer valor v0.", lista_borrar_primero(lista)==&vect[2]);
	print_test("Se borro el primer valor v1.", lista_borrar_primero(lista)==&vect[1]);
	print_test("Se borro el primer valor v2.", lista_borrar_primero(lista)==&vect[0]);
	print_test("Se borro el primer valor v2.", lista_borrar_primero(lista)==&vect[3]);
	print_test("Se borro el primer valor v1.", lista_borrar_primero(lista)==&vect[4]);
	print_test("Se borro el primer valor v0.", lista_borrar_primero(lista)==&vect[5]);

	print_test("La lista esta vacia.", lista_esta_vacia(lista));

	lista_destruir(lista, NULL);
}

void pruebas_casos_borde(){

	printf("\n---PRUEBAS DE LOS CASOS BORDE---\n");

	void* vect[2];

	lista_t * lista = lista_crear();
	print_test("Se creo una lista.", true);

	print_test("La lista esta vacia.", lista_esta_vacia(lista));
	print_test("Borrar primer devuelve NULL.", lista_borrar_primero(lista)==NULL);
	print_test("Ver el primer elemento devuelve NULL.", lista_ver_primero(lista)==NULL);
	print_test("Ver el ultimo elemento devuelve NULL.", lista_ver_ultimo(lista)==NULL);

	print_test("Se inserto primero un valor NULL.", lista_insertar_primero(lista, NULL));
	print_test("Se inserto primero un valor v0.", lista_insertar_primero(lista, &vect[0]));
	print_test("Se inserto ultimo un valor NULL.", lista_insertar_ultimo(lista, NULL));
	print_test("Se inserto ultimo un valor v1.", lista_insertar_ultimo(lista, &vect[1]));

	print_test("Se borro el primer valor v0.", lista_borrar_primero(lista)==&vect[0]);
	print_test("Se borro el primer valor NULL.", lista_borrar_primero(lista)==NULL);
	print_test("Se borro el primer valor NULL.", lista_borrar_primero(lista)==NULL);
	print_test("Se borro el primer valor v1.", lista_borrar_primero(lista)==&vect[1]);

	print_test("La lista esta vacia.", lista_esta_vacia(lista));
	print_test("Borrar primer devuelve NULL.", lista_borrar_primero(lista)==NULL);
	print_test("Ver el primer elemento devuelve NULL.", lista_ver_primero(lista)==NULL);
	print_test("Ver el ultimo elemento devuelve NULL.", lista_ver_ultimo(lista)==NULL);
	
	lista_destruir(lista, NULL);
}

void pruebas_crear_y_destruir(){
	
	printf("\n---PRUEBAS CREAR Y DESTRUIR LISTA---\n");
	
	lista_t * lista_A = lista_crear();
	print_test("Lisa A fue creada", lista_A!=NULL);

	void* vect[4];
	print_test("Se inserto primero un valor v0 en lista A.", lista_insertar_primero(lista_A, &vect[0]));
	print_test("Se inserto primero un valor v1 en lista A.", lista_insertar_primero(lista_A, &vect[1]));
	print_test("Se inserto primero un valor v2 en lista A.", lista_insertar_primero(lista_A, &vect[2]));

	lista_destruir(lista_A, NULL);
	print_test("Lista A fue destruida con el parametro NULL", true);
	
	lista_t * lista_B = lista_crear();
	print_test("Lisa B fue creada", lista_B!=NULL);

	void** p1= malloc(sizeof(void*));
	void** p2= malloc(sizeof(void*));
	print_test("Se inserto primero memoria dinamica en lista B",lista_insertar_primero(lista_B,p1));
	print_test("Se inserto primero memoria dinamica en lista B",lista_insertar_primero(lista_B,p2));
	
	lista_destruir(lista_B, free);
	print_test("La lista B fue destruida con el parametro free",true);

}

void pruebas_volumen(int cant_elemetos){

	printf("\n---PRUEBAS DE VOLUMEN---\n");

	lista_t * lista = lista_crear();
	print_test("Se creo una lista.", true);

	void* vector[cant_elemetos];

	bool esta_insertado = true;
	bool instertar_coincide_primero = true;
	bool insertar_coincide_ultimo = true;
	bool borrar_coincide_primero = true;
	bool borrar_coincide_ultimo = true;

	for(int i=0; i<cant_elemetos; i++){
		esta_insertado &= lista_insertar_primero(lista, &vector[i]);
		instertar_coincide_primero &= (&vector[i]== lista_ver_primero(lista));
		insertar_coincide_ultimo	&= (&vector[0]== lista_ver_ultimo(lista));
	}

	for(int i=0; i<cant_elemetos; i++){
		esta_insertado &= lista_insertar_ultimo(lista, &vector[i]);
		instertar_coincide_primero &= (&vector[cant_elemetos-1]== lista_ver_primero(lista));
		insertar_coincide_ultimo	&= (&vector[i]== lista_ver_ultimo(lista));
	}

	for(int j=0; j<cant_elemetos; j++){
		borrar_coincide_primero &= (&vector[cant_elemetos-j-1]== lista_ver_primero(lista));
		borrar_coincide_ultimo	&= (&vector[cant_elemetos-1]== lista_ver_ultimo(lista));
		lista_borrar_primero(lista);
	}

	for(int j=0; j<cant_elemetos; j++){
		borrar_coincide_primero &= (&vector[j]== lista_ver_primero(lista));
		borrar_coincide_ultimo	&= (&vector[cant_elemetos-1]== lista_ver_ultimo(lista));
		lista_borrar_primero(lista);
	}

	print_test("Se logro insertar una gran volumen de elementos.", esta_insertado);
	print_test("Cada vez que se inserta, el primer elemento es el correspondiente.", instertar_coincide_primero);
	print_test("Cada vez que se inserta, el ultimo elemento es el correspondiente.", insertar_coincide_ultimo);
	print_test("Se logro borrar primero una gran volumen de elementos.", borrar_coincide_primero && borrar_coincide_ultimo);
	
	lista_destruir(lista, NULL);
}

void pruebas_iter_externo(){

printf("\n---PRUEBAS DE ITERADOR EXTERNO---\n");

	//PRUEBA ITER 1

	void *vect[20];

    lista_t *lista_1 = lista_crear();
	lista_iter_t* iter_1 = lista_iter_crear(lista_1);
	print_test("Se creo una lista iter.", true);


	lista_iter_insertar(iter_1, &vect[1]);
	lista_iter_insertar(iter_1, &vect[2]);
	lista_iter_insertar(iter_1, &vect[3]);

	print_test("Al insertar un elemento en la posición en la que se crea el iterador,\nefectivamente se inserta al principio.",lista_iter_ver_actual(iter_1)==&vect[3]);
	
	lista_iter_borrar(iter_1);
	lista_iter_borrar(iter_1);
	print_test("Se borro un elemento.",lista_iter_ver_actual(iter_1)==&vect[1]);

	lista_iter_borrar(iter_1);


	print_test("Se borro el iter", true);
	lista_iter_destruir(iter_1);
	lista_destruir(lista_1, NULL);

	//PRUEBA ITER 2

    lista_t *lista_2 = lista_crear();
	lista_iter_t* iter_2 = lista_iter_crear(lista_2);
	print_test("Se creo una lista iter.", true);

	bool es_ultimo = true;
	for(int i=0; i<5; i++){
		print_test("Se inserto un valor",lista_iter_insertar(iter_2, &vect[i]));
		es_ultimo &= (lista_iter_ver_actual(iter_2)==&vect[i]);
	}

	print_test("Insertar un elemento cuando el iterador está al final efectivamente es equivalente a insertar al final.", es_ultimo && lista_iter_ver_actual(iter_2)==&vect[4]);
	print_test("La eliminacion de un elemento con un iterador apuntando al último elemento de la lista se comportaría como una primitiva lista_borrar_ultimo.", lista_iter_borrar(iter_2)==&vect[4]);

	print_test("Se borro el iter", true);
	lista_iter_destruir(iter_2);
	lista_destruir(lista_2, NULL);


	//PRUEBA ITER 2_bis

    lista_t *lista_2_bis = lista_crear();
    lista_iter_t* iter_2_bis = lista_iter_crear(lista_2_bis);
    	
    print_test("Se itero una lista vacia.", !lista_iter_avanzar(iter_2_bis));
	print_test("Se vio una lista_vacia.", lista_iter_ver_actual(iter_2_bis)==NULL);

	lista_destruir(lista_2_bis, NULL);
	lista_iter_destruir(iter_2_bis);


	//PRUEBA ITER 3

	lista_t *lista_3 = lista_crear();
    for( int i=0;i<9;i++ ){lista_insertar_ultimo(lista_3, &vect[i]);}
    lista_iter_t* iter_3 = lista_iter_crear(lista_3);
	
	int i = 0;
	while(!lista_iter_al_final(iter_3)){
		if (i==4){
			lista_iter_insertar(iter_3, &vect[15]);
			print_test("Se inserto un valor en el medio.",lista_iter_ver_actual(iter_3)==&vect[15]);		}
		lista_iter_avanzar(iter_3);
		i++;
	}
	lista_iter_destruir(iter_3);

	//PRUEBAS ITER 4

	lista_iter_t* iter_4 = lista_iter_crear(lista_3);
	i = 0;
	while(!lista_iter_al_final(iter_4)){
		if (i==4) print_test("Ese elemento fue insertado en la posición correcta.",lista_iter_borrar(iter_4)==&vect[15]);
		lista_iter_avanzar(iter_4);
		i++;
	}
	lista_iter_destruir(iter_4);

	bool no_esta_valor_borrado = true;
	lista_iter_t* iter_5 = lista_iter_crear(lista_3);
	while(!lista_iter_al_final(iter_5)){
		if (lista_iter_ver_actual(iter_5)==&vect[15]) (no_esta_valor_borrado=false);
		lista_iter_avanzar(iter_5);
	}
	lista_iter_destruir(iter_5);
	print_test("Ese elemento fue borrado correctamente.",no_esta_valor_borrado);
	
	lista_destruir(lista_3, NULL);
}
//suma todos los numeros que aparecen en un arreglo de ints hasta que
//aparece "0".
bool sumar_hasta_cero(void* dato, void* extra) {
	if (*(int*) dato==0) return false;
	*(int*) extra += *(int*) dato; 
	return true;
}

//suma todos los numeros que aparecen en un arreglo de ints 
bool sumar_todos(void* dato, void* extra) {
	*(int*) extra += *(int*) dato; 
	return true;
}

void pruebas_iter_interno(){

	printf("\n---PRUEBAS DE ITERADOR EXTERNO---\n");
	
	int suma = 0;
	int num[7] ={1,2,3,0,4,5} ;
	lista_t *lista = lista_crear();

	lista_iterar(lista, sumar_todos, &suma);
	print_test("Se trato de iterar internamente una lista vacia", true);

	for( int i=0;i<5;i++ ){lista_insertar_ultimo(lista, &num[i]);}

	lista_iterar(lista, sumar_todos, &suma);
	print_test("Se itero internamente una lista con utilizando el parametro extra.",suma==10);

	lista_iterar(lista, sumar_hasta_cero, &suma);
	print_test("Se itero internamente una lista con utilizando una condicion de corte.",suma==16);

	lista_destruir(lista, NULL);
}

void pruebas_lista_alumno(void) {
	pruebas_invariantes();
	pruebas_casos_borde();
	pruebas_crear_y_destruir();
	pruebas_volumen(1000);
	pruebas_iter_externo();
	pruebas_iter_interno();

}