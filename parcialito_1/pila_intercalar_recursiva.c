/* CONSIGNA: Se pide una funcion recursiva que reciba dos pilas p1 y p2 y devuelva
una nueva pila con los elemnos de ambas pilas intercaladas. Las especificaciones son:
  - pre-condicion: se garantiza que p1 y p2 tienen el mismo numero de elementos.
  - la mezcla comienza con el tope de p1 (que sera tambien el tope de la pila devuelta)
  - las pilas originales p1 y p2 deben permanecer en su orden original.
*/

pila_t* pila_intercalar(pila_t* p1, pila_t* p2){
  
  pila_t* pila_intercalada = pila_crear();
  if(!pila_intercalada) return NULL;
  
  _pila_intercalar(pila_intercalada, p1, p2);
  
  return pila_intercalada;
}

void _pila_intercalar(pila_t* pila_intercalada, pila_t* p1, pila_t* p2){
  
    if(pila_esta_vacia(p1) && pila_esta_vacia(p2)) return;
    
    void* dato1 = pila_desapilar(p1);
    void* dato2 = pila_desapilar(p2);
    
    _pila_intercalar(pila_t* pila_intercalada, pila_t* p1, pila_t* p2);
    
    pila_apilar(p1, dato1);
    pila_apilar(p2, dato2);
    
    pila_apilar(pila_intercalada, dato2);
    pila_apilar(pila_intercalada, dato1);
 
 }
    
    
