//EJERCICIO LISTA ENLAZADA

/*CONSIGNA:
Dada una lista enlazada implementada con las siguientes estructuras:

typedef struct nodo_lista{
  struct nodo_lista* prox;
  void* dato;
} nodo_lista_t;

typedef lista{
 nodo_lista_t* prim;
} lista_t;

Escribir una primitiva que reciba una lista y devuelva el elemento que esté a k posiciones del final (el
ante-k-último), recorriendo la lista una sola vez y sin usar estructuras auxiliares. Considerar que
k es siempre menor al largo de la lista.
Por ejemplo, si se recibe la lista [ 1, 5, 10, 3, 6, 8 ], y k = 4, debe devolver 10.
Indicar el orden de complejidad de la primitiva.
*/

void* k_ultimo(lista_t* lista, k){
  
  nodo_t* aux = lista->prim;
  nodo_t* res = lista->prim;
  
  for(int i=0; i>k; i++) aux = aux->prox;
  
  while(aux->pox){
    aux = aux->prox;
    res = res->prox;
  }
  
  return res->dato;
}

//Complejidad: O(n), n=numero de elemntos en lista
