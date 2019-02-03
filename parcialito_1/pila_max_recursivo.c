/* CONSIGNA: Implementar una funcion que determine el maximo valor de una
pila( de eteros), sin utilizar estructuras auxiliares. AL terminar la
ejecucion de la funcion, la pila debe quedar igual qye en su estado incial.
Indicar el orden de la funcion. Justificar. */

int pila_max(pila_t* pila, int max){
  
  if(pila_esta_vacia(pila)) return max;
  
  int num = *(int*) pila_desapilar(pila);
  
  if(num>max) max = num;
  
  max = pila_max(pila, max);
  
  pila_apilar(pila, num);
  
  return max

}

int pila_max(pila_t* pila){
  return _pila_max(pila, -inf);
}

//Complejidad: O(n) siendo n la cantida de elementos en la pila..
