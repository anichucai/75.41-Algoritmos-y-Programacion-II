#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                PRIMITIVAS DE LA LISTA
 * *****************************************************************/


/* La lista está planteada como una lista de punteros genéricos. */
typedef struct lista lista_t;

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al
// principio de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al
//final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se
// quita el primero de la lista, y se devuelve su valor, si está vacía, 
//devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista 
//contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene la cantidad de elementos que contiene la lista.
// Pre: la lista fue creada.
// Post: se devolvió la cantidad de elementos de la lista, cuando está vacía
// devuelve 0.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/* ******************************************************************
 *                PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* ******************************************************************
 *                PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

/* La lista iter está planteada como una lista de punteros genéricos. */
typedef struct lista_iter lista_iter_t;

// Crea una lista iter.
// Post: devuelve una nueva lista_iter vacía.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza un lugar en la lista. Devuelve falso en caso de error.
// Pre: el iter fue creado.
// Post: se mueve un lugar en la lista y si estaba en el final, vuelve al comienzo.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del elemento en el que esta parado el iter actual.
// Si el iterse encuentra al final devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el elemento de la lista en la posicion del iter si este no
// se encuentra en el final.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Verifica si el iter se encuentra en la posicion final de la lista.
// Pre: la lista fue creada.
// Post: devolvió true si el iter se encuentra en la posicion final o 
// false en caso contarrio.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iter.
// Pre: la lista fue creada.
// Post: se elimina el iter.
void lista_iter_destruir(lista_iter_t *iter);

// Agrega un nuevo elemento a la lista en la posicion que se encuentra
// el iter. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista en la posicion que se encuentra
// el iter.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Saca el elemento de la lista en la posicion del iter y lo devuelve. Si 
// la lista no tiene elementos o el iter se encuentra en el final NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del elemento en la posicion del iter, la lista 
//contiene un elemento menos, si la lista no estaba vacía o el iter no estaba
// al final.
void *lista_iter_borrar(lista_iter_t *iter);
