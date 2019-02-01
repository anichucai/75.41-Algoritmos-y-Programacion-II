/* CONSIGNA: Dada una pila de numeros enteros y un numero n, escribir una funcion
recursiva que saque de la pila los numeros que sean iguales a n, dejando la pila tal
como fue recibida pero sin ocurrencias de ese numero. */

void pila_sacar_recursiva(pila_t* pila, int n){
  
  if pila_esta_vacia(pila) return;
  
  void* dato = pila_desapilar(pila);
  
  pila_sacar_recursiva(pila, n);
  
  if( (*(int*))dato != n) pila_apilar(pila_dato);
  
}

//Complejidad O(n) siendo n la cantidad de elementos en la pila
