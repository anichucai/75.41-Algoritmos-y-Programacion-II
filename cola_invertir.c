//EJERCICIO COLA

/*CONSIGNA: Del primer recuperatorio del parcialito del segundo cuatrimestre de 2012
a) Implementar la funcion void invertir cola(cola t* cola), que invierte el orden
de sus elementos.
b) Indicar el orden de complejidad de la funci´on implementada.
*/

void invertir_cola(cola_t* cola){

  pila_t* pila = pila_crear();
  if(!pila) return;
  
  while(!cola_esta_vacia(cola)){
    pila_apilar(pila, cola_desapilar(cola));
  }
  
  while(!pila_esta_vacia(pila)){
    cola_encolar(cola, pila_desapilar(pila));
  }
  
  destruir_pila(pila);

}

//Coplejidad: O(n), n=cantida de elementos en cola 
