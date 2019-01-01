// EJERCITACION COLA

/*CONSIGNA: Implementar la primitiva void** cola_multiprimeros(const cola_t* cola, size_t k) que dada
una cola y un número k, devuelva los primeros k elementos de la cola, en el mismo orden en el que habrían
salido de la cola. En caso que la cola tenga menos de k elementos, rellenar con NULL.
La cola debe quedar en el mismo estado que al invocarse la primitiva.
Indicar el orden de ejecución del algoritmo. Justificar.*/

//  PRIMITIVA:

void* cola_multiprimeros(const cola_t* cola, size_t k){
  
  void ** multiprimeros = malloc(sizeof(void*)*k);
  if(!multiprimeros) return NULL;
  
  nodo_t* act = cola->prim;
  
  for(int i=0; i<k; i++){
    if(act){
      multiprimeros[i] = act->dato;
      act = act->prox;
    } else {
      multiprimeros[i] = NULL;
    }
  
  return multiprimeros;
}


//FUNCION:

void* cola_multiprimeros(cola_t* cola, size_t k){

  void ** multiprimeros = malloc(sizeof(void*)*k);
  if(!multiprimeros) return NULL;
  
  cola_t* cola_aux = cola_crear();
  if(!cola){
    free(multiprimeros);
    return NULL;
  }
  
  for(int i=0; i<k; i++){
    void* dato= cola_desncolar(cola);
    multiprimeros[i] = dato;
    if (dato) cola(encolar(cola_aux, dato));
  }
  
  while(!cola_esta_vacia(cola))
    cola_encolar(cola_aux, cola_desncolar(cola));
  
  while(!cola_esta_vacia(cola_aux))
    cola_encolar(cola, cola_desncolar(cola_aux));
    
  return multiprimeros;
}


//Complejidad:
  - n>>k -> O(n)
  - k>>n -> O(k)
  siendo n = cantidad de elementos en cola y k = cantidad de multiprimeros a mostrar
