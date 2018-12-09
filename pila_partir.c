#EJERCICIO PILA

/*CONSIGNA: */

pila_t* pila_partir(pila_t* pila_original, int n){

  pila_t* inversa = pila_crear();
  if(!pila_inversa) return NULL;
  pila_t* pila_a_devolver = pila_crear();
  if(!pila_a_devolver){
    pila_destruir(pila_inversa);
    return NULL;
  }
  
  while(!pila_esta_vacia(pila_original)){
    pila_apilar(pila_inversa,pila_desapilar(pila_original));
  }
  
  int i = n-1;
  
  for(; i>=n/2-1; i--){
    pila_apilar(pila_a_devolver,pila_desapilar(pila_inversa));
  }
  
  for(; i>=0; i--){
    pila_apilar(pila_original,pila_desapilar(pila_inversa));
  }
  
  pila_destruir(pila_inversa);
  
  return pila_a_devolver;
  
}
