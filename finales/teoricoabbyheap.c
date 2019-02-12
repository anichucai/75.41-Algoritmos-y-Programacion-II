/*CONSIGNA:

a) Un arreglo en orden descendiente es siempre un heap de máx? Justificar.

Verdadero. Al encolar en el heap, se coloca el dato en la posicion len_arreglo-1 y luego se le
aplica up_heap(es decir, swapea posiciones con su padre siempre que este ultimo sea menor que el nodo actual).
Como nunca realiza este upheap ya que el arreglo esta ordenado de manera descendiente no va a haber ningun
swap y por ende el arreglo no es modificado nunca.


b) Un arbol binario de búsqueda completo es también un heap de máximo? Justificar.
Falso. 

Un arbol binario de busqueda significa que es un arbol esta ordenado de manera tal que su hijo
izquierdo siempre sea menor que el nodo actual y el nodo derecho sea mayor que el nodo actual y
que este completo significa que todos los nodos tiene dos o ningun hijo.
En cambio un heap de maximos tiene al mayor valor en la raiz, por ende si tiene hijo izquierdo, ya no es ABB.
Contraejemplos:

El siguiente es un ABB completo y no es un heap de max:

    6
  /   \
  2   17
El siguiente es un heap de max y no un ABB:
    17
  /   \
  2   6
*/
