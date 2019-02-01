/* CONSIGNA: Se desea implementar en C el tipo abstracto de datos PIla como una PIla Enlazzada, es deir, con nodos en lugar de un vector dinamico.
  a. Definir la o las estructuras que  componen la pila.
  b. Implementar las primitivas: pila_crear, pila_apilar y pila_desapilar usando la estructuras definidas.
*/


// ________________ Estructuras pila ______________

typedef struct nodo_pila{
  void* dato;
  struct nodo_pila* prox;
}  nodo_píla_t;

typedef struct pila{
  nodo_pila_t* prim;
} pila_t;


// _________ Funciones auxiliares nodo ____________

nodo_pila_t* nodo_pila_crear(void* dato){
  
  nodo_pila_t* nodo = malloc(sizeof(nodo_pila_t));
  if (!nodo) return NULL;
  
  nodo->dato = dato;
  nodo->prox = NULL;
  
  return nodo;
}

void* nodo_pila_destruir( nodo_pila_t* nodo){

  void* dato = nodo->dato;
  
  free(nodo);
  
  return dato;
}


//_______________ Funciones pila _________________

pila_t* pila_crear(){
  
  pila_t* pila = malloc(sizeof(pila_t));
  if(!pila) return NULL;
  
  pila->prim = NULL;
  
  return pila;
}

bool pila_apilar(pila_t* pila, void* dato){
  
  if(!pila) return false;
  
  nodo_pila_t* nodo = crear_nodo(dato);
  if (!nodo) return false;
  
  if(!pila->prim){
    pila->prim = nodo;
  } else{
    nodo->prox = pila->prim;
    pila->prim = nodo;
   }
   
   return true;
}

void* pila_desapilar(pila_t* pila){
  
  if(!pila || !pila->prim) return NULL;
  
  nodo_pila_t* nodo = pila->prim;
  
  pila->prim = pila->prim->prox;
  
  return nodo_destruir(nodo)

}

// Complejidad de todas las funciones es de O(1) =)
