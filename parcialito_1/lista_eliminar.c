/* CONSIGNA:
Dada una lista enlazada, implementar la siguiente primitiva:
           bool lista_eliminat(lista_t* lista, void* dato)
que elimine todas las ocurrencias del dato pasado por parametro y devuelva true
si encuentra al menos una ocurrencia, y false de caso contrario.
Las estructuras de la lista enlazada son:

typedef struct nodo_lista{
  struct nodo_lista prox;
  void* dato;
} nodo_lista_t;

typedef struct lista{
  nodo_lista_t* prim;
} lista_t;

*/

bool lista_eliminar(lista_t* lista, void* dato){

  bool hay_ocurrencia = false;
    
  nodo_t* actual = lista->prim;
  
  while(actual && actual == lista->prim && actual->dato==dato){
        lista->prim = actual->prox;
        actual = actual->prox;
        hay_ocurrencia = true;
  }
  
  nodo_t* anterior = lista->prim;
  
  while(actual){
    if (actual->dato == dato){
      anterior->prox = actual->prox;
      hay_ocurrencia = true;
    }
    anterior = actual;
    actual = actual->prox;
  }

  return hay_ocurrencia;

}

//Complejidad: O(n)
