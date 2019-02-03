/*Sabiendo que se cuenta con el TDA cola con las primitivas bool cola_encolar(cola_t* void*), void*
cola_desencoalr(cola_t*) y bool cola_esta_vacia(cola_t*), implementar el TDA cola con prioridad.
Este TDA debe implementar las primitivas:
- cola_p_t* cola_p_crear()
- bool cola_p_encolar_comun(cola_p_t*, void*)
- bool cola_p_encolar_prioritario(cola_p_t*, void*)
- void* desencolar(cola_p_t*)
- bool cola_p_esta_vacia(cola_p_t*)
- void cola_p_destruir(cola_p_t*)
Al desencolar esta nueva coladebe prioritizar aquellos elemntos que fueron encoladdos con prioridad:
es decir, no deben salir elementos comunes de la estructura si no salieron previamente todos los
elementos con prioridad.
Todas las primitivas deben funcionar en tiempo contasnte.*/

typedef struct cola_p{
  cola_t* comun;
  cola_t* prioridad;
} cola_p_t*;

cola_p_t* cola_p_crear(){
  
  cola_p_t* cola = malloc(sizeof(cola_t));
  if (!cola) return NULL;
  
  cola->comun = cola_crear();
  if (!cola->comun){
    free(cola);
    return NULL;
  }
  
  cola->prioridad = cola_crear();
  if (!cola->prioridad){
    cola_destrir(cola->comun);
    free(cola);
    return NULL;
  }
  
  return cola;

}

bool cola_p_encolar_comun(cola_p_t* cola, void* dato){
  return cola_encolar(cola->comun, dato);
}

bool cola_p_encolar_prioridad(cola_p_t* cola, void* dato){
  return cola_prioridad(cola->prioridad, dato);
}

void* desencolar(cola_p_t* cola){
  return (!cola_esta_vacia(cola->prioridad)) ? cola_desencolar(cola->prioridad) : cola_desencolar(cola->comun);
}

bool cola_p_esta_vacia(cola_p_t* cola){
  return cola_esta_vacia(cola->prioridad) && cola_esta_vacia(cola->prioridad);
}

void cola_p_destruir(cola_p_t* cola){
  cola_destruir(cola->prioridad);
  cola_destriuir(cola->comun);
  free(cola);
}
