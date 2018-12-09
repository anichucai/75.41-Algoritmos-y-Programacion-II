// EJERCICIO COLA RECURSIVO

/*CONSIGNA: Del primer recuperatorio del primer parcialito, segundo cuatrimestre de 2013
Escribir una primitiva que invierta el contenido de una cola sin usar ninguna estructura
auxiliar*/

void invertir_cola_recursivo(cola_t* cola){

  if(cola_esta_vacia(cola)) return;
  
  void* dato = cola_desencolar(cola);
  invertir_cola(cola);
  
  cola_encolar(cola,dato);
  
}

//Complejidad: O(n), n=cantidad de elementos en cola
