#include "tp0.h"

/* ******************************************************************
 *                     FUNCIONES A COMPLETAR
 * *****************************************************************/

/* swap() intercambia dos valores enteros.
 */
void swap (int* x, int* y) {
	int aux = *x;
	*x = *y;
	*y = aux;
}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[], int n) {
	if (n<=0) {
		return -1;
	}
	int pos_max = 0;
	for(int i=1; i<n; i++){
		if (vector[pos_max]<vector[i]){
			pos_max = i;
			}
	}
	return pos_max;
}

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2) {
	for (int i =0; n1>i && n2>i;i++){
		if (vector1[i]<vector2[i]){
			return -1;
		} else if (vector1[i]>vector2[i]){
			return 1;
		}
	}
	if (n1<n2){
		return -1;
	} else if (n1>n2){
		return 1;
	}
	return 0;
}

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(int vector[], int n) {
	for (int i = 0; i<n; i++){
		int pos = maximo(vector, n-i);
		swap(&vector[pos], &vector[n-1-i]);
	}
}


//funcion para saber si tiene solo un hijo unico
bool tiene_hijo_unico(abb_nodo_t* nodo){
	
	abb_nodo_t* hijo1=nodo->izq;
	abb_nodo_t* hijo2=nodo->der;

	if(!hijo1) return es_hoja(hijo2);
	if(!hijo2) return es_hoja(hijo1);
	return false;

}


//función para buscar al prox inorder de un nodo padre
abb_nodo_t* siguiente_inorder(abb_nodo_t* nodo){
	abb_nodo_t* sig=nodo->der;

	if(!sig) return NULL;

	while(sig->izq){
		sig=sig->izq;
	}
	return sig;	
}


//función para buscar al anterior inorder de un nodo padre
abb_nodo_t* anterior_inorder(abb_nodo_t* nodo){

	abb_nodo_t* ant=nodo->izq;

	if(!ant) return NULL;

	while(ant->der){
		ant=ant->der;
	}
	return ant;
}

bool tiene_hijo_mayor(abb_nodo_t* nodo){
	return nodo->der;
}