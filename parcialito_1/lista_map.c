/*CONSIGNA: Si se tiene una implementacion de Lista Enlazada con las siguientes estructura:

typedef struct nodo_lista{
  struct nodo_lista prox;
  void* dato;
} nodo_lista_t;

typedef struct lista{
  nodo_lista_t* prim;
} lista_t;

a) Implementar un nueva primitiva "lista_map" que reciba como parametro un puntero a una
funcion f (que tome y devuelva un numero entero), y como segundo parametro un puntero a 
lista_t. lista_map debe reemplazar cada uno de los valores  de la lista por el resultado
de aplicar la funcion f a dichos valores.
b) Muestre un ejemplo de invocacion a la primitiva lista_map con una funcion que eleve al
cuadrado.
*/

void lista_map( (int) f (int) , lista_t* lista){
  nodo_t* act = lista->prim;
  while(act){
    act->dato = f (act->dato);
    act = act->prox;
  }
}
