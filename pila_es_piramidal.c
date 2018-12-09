//EJERCICIO PILA
/*CONSIGNA:
Dada una pila de enteros, escribir una función que determine si es piramidal. Una pila de enteros es
piramidal si cada elemento es menor a su elemento inferior (en el sentido que va desde el tope de la pila hacia
el otro extremo). La pila no debe ser modificada al terminar la función.
Indicar el orden del algoritmo propuesto.*/

bool _es_piramidal(pila_t* pila, bool res){
  
  if(pila_esta_vacia(pila)) return res;
  void* dato = pila_desapilar(pila);
  
  if(pila_esta_vacia(pila)){
    pila_apilar(pila,datos);
    return res;
  }
  
  if( (*(int*)dato) < (*(int*)pila_ver_tope(pila)) ) res = false;
  
  res &= es_piramidal(pila, res)
  
  pila_apilar(pila,datos);
  
  return res;
}

bool es_piramidal(pila_t* pila){
  return _es_piramidal(pila, true)
}

//Complejidad: O(n), n=cantidad de elementos en pila
