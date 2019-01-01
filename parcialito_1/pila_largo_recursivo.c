//EJERCICIO PILA RECURSIVO

/*CONSIGNA: Del primer recuperatorio del primer parcialito, primer cuatrimestre de 2014
Se pide implementar una funci´on recursiva que calcule el largo de una pila sin utilizar
estructuras auxiliares ni acceder a su estructura interna (que no sabemos cu´al es). El prototipo
de la funci´on es:
size t largo pila(pila t *pila);
Se puede llamar a cualquier primitiva de la pila, incluyendo aquellas que la modifiquen,
pero siempre la pila debe quedar en su estado original al terminar la ejecuci´on de la funci´on.*/

size_t* pila_largo_recursivo(pila_t* pila){

  if (pila_esta_vacia(pila)) return 0;
  
  void* dato = pila_desapilar(pila);
  size_t* largo = largo_pila_recursivo(pila,largo)+1;
  pila_apilar(pila,dato);
  
  return largo;
  
}

//Complejidad: O(n), n=cantidad de elemntos en pila
