//EJERCITACION TDA Y PILA

/*CONSIGNA: Implementar en C el TDA ComposiciónFunciones que emula la composición de funciones (i.e. f(g(h(x))).
Se debe definir la estructura del TDA, y las siguientes primitivas:
• composicion_t* composicion_crear( );
• void composicion_destruir(composicion_t*);
• bool composicion_agregar_funcion(composicion_t, double ( f)(double));
• double composicion_aplicar(composicion_t*, double);
Considerar que primero se irán agregando las funciones como se leen, pero tener en cuenta el correcto orden
de aplicación. Por ejemplo: para emular f(g(x)), se debe hacer:
composicion_agregar_funcion(composicion, f) composicion_agregar_funcion(composicion, g)
composicion_aplicar(composicion, x)
Indicar el orden de las primitivas.*/


typedef struct composicion{
  pila_t* funciones;
} composicion_t;


composicion_t* composicion_crear(void){

  composicion_t* composicion = malloc(sizeosf(composicion_t));
  if(!composicion) return NULL;
  
  composicion->funciones = crear_pila();
  if(!composicion->funciones){
    free(composicion);
    return NULL;
  }
  
  return composicion;
}

//Complejidad O(1)


void composicion_destruir(composicion_t* composicion){

  pila_destruir(composicion->pila);
  free(composicion);
}

//Complejidad O(1)


bool composicion_agregar_funcion(composicion_t composicion, double ( f)(double)){

  return pila_apilar(composicion->pila, f);
}

//Complejidad O(1)


double composicion_aplicar(composicion_t* composicion, double x){

  double res = x;
  
  while(!pila_esta_vacia(composicion->pila)){
    res = (pila_desapilar(composicion->pila)) (res);
  }
  
  return res;
}

//Complejidad O(n), n=cantidad de funciones
