/*CONSIGNA: Implementar una primitiva para el TDA Lista (de numeros enteros)
int lista_borrar_menores(lista_t* lista, int valor) que eliminen todas las
ocurrencias de numeros menores a valor pasado por parametro devolviendo el
valor mas grande eliminado. En caso de no eliminar ninguno, devolver -1.
Indicar y justificar el orden de la primitiva. Aclaracion: La destruccion de
los datos en responsabilidad del usuario. y queda fuera del alcance de esta
primitiva.*/

int lista_borrar_menores(lista_t* lista, int valor){
  
  int max = valor;
  
  while(lista->prim && lista->prim->dato<valor){
      if (max<lista->prim->dato) max=lista->prim->dato;
      lista->prim = lista->prim->prox;
  }
  
  nodo_t* ant = lista->prim;
  nodo_t* act = ant->prox;
  
  while(act){
    if (act->dato<valor){
        if (max<act->dato) max=act->dato;
        ant->prox=act->prox;
        act = act->prox;
    } else {
        ant = ant->prox;
        act = act->prox;
    }
  }
  
  return (max==valor) ? -1 : max;
  
}
