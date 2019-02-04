#include "algueiza.h"

#define LEN 200

typedef enum datos {FLIGHT_NUMBER, AIRLINE, ORIGIN_AIRPORT, DESTINATION_AIRPORT, TAIL_NUMBER, PRIORITY, DATE, DEPARTURE_DELAY, AIR_TIME, CANCELLED} dato_t;


/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/


//Funcion para validar los parametros de ver_tablero
bool ver_tablero_validar_parametros(int  cant, char* modo, char* fecha1,char* fecha2){

	if( (strcmp(modo,"asc")!=0 && strcmp(modo,"desc")!=0) || cant<=0 || cmp_fecha_asc(fecha1,fecha2)>0 ) return false;
	return true;
}


//Funcion que compara dos fechas
int cmp_fecha_asc(char* fecha_1, char* fecha_2){

	for(;*fecha_1!='\0'; fecha_1++, fecha_2++){

			if(*fecha_1>*fecha_2){
				return 1;
			} else if(*fecha_1<*fecha_2){
				return -1;
			}
		
	}
	return 0;
}

//Funcion que compara dos fechas
int cmp_fecha_desc(char* fecha_1, char* fecha_2){

	for(;*fecha_1!='\0'; fecha_1++, fecha_2++){

			if(*fecha_1<*fecha_2){
				return 1;
			} else if(*fecha_1>*fecha_2){
				return -1;
			}
		
	}
	return 0;
}


//Funcion para imprimir un heap recursivamente desde el ultimo elem del heap
void imprimir_heap_al_reves(heap_t* heap){

	if(heap_cantidad(heap)==0) return;

	void * datos = heap_desencolar(heap);
	imprimir_heap_al_reves(heap);

	fprintf(stdout,"%s - %s\n",  ((char**)datos)[PRIORITY],((char**)datos)[FLIGHT_NUMBER]);

}


//Funcion que compara dos vuelos de forma maxima 
int cmp_prioridad_max(void* datos1, void* datos2){

	char** p1 = ((char**)datos1);
	char** p2 = ((char**)datos2);

	if (atoi(p1[PRIORITY])>atoi(p2[PRIORITY])){
		return 1;
	} else if(atoi(p1[PRIORITY])<atoi(p2[PRIORITY])){
		return -1;
	} else{
		return (strcmp(p1[FLIGHT_NUMBER],p2[FLIGHT_NUMBER])<0) ? 1: -1;
	}

}

//Funcion que compara las prioridades de dos vuelos de forma minima
int cmp_prioridad_min(void* datos1, void* datos2){

	char** p1 = ((char**)datos1);
	char** p2 = ((char**)datos2);

	if (atoi(p1[PRIORITY])<atoi(p2[PRIORITY])){
		return 1;
	} else if(atoi(p1[PRIORITY])>atoi(p2[PRIORITY])){
		return -1;
	}else{
		return (strcmp(p1[FLIGHT_NUMBER],p2[FLIGHT_NUMBER])>0) ? 1: -1;
	}

}


/* *****************************************************************
 *                    FUNCIONES ALGUEIZA
 * *****************************************************************/


bool agregar_archivo(char* nombre_archivo, hash_t* diccionario, abb_t* tablero){

	FILE* archivo = fopen(nombre_archivo, "r");
	if(!archivo) return false;

	char cadena[LEN];
	char** datos;
	bool operacion_exitosa = true;

	while(fgets(cadena,LEN,archivo)){

		datos = split(cadena,',');
		if(!datos) continue;

		char barra[2] = "-";
		char* aux[4] = {datos[DATE], barra, datos[FLIGHT_NUMBER]};
		char* clave_fecha = join(aux, ' ');

		if(hash_pertenece(diccionario,datos[FLIGHT_NUMBER])){
			char** datos_viejos = (char**) hash_obtener(diccionario,datos[FLIGHT_NUMBER]);
			char* aux[4] = {datos_viejos[DATE], barra, datos_viejos[FLIGHT_NUMBER], NULL};
			char* clave_fecha_vieja = join(aux, ' ');
			abb_borrar(tablero,clave_fecha_vieja);	
			free(clave_fecha_vieja);
		}

		operacion_exitosa &= hash_guardar(diccionario, datos[FLIGHT_NUMBER], datos) && abb_guardar(tablero, clave_fecha, datos);

		free(clave_fecha);
	}

	fclose(archivo);

	return operacion_exitosa;
}


bool ver_tablero(abb_t* tablero, hash_t* diccionario, int k, char* modo, char* desde, char* hasta){

	if(!ver_tablero_validar_parametros(k,modo,desde,hasta)) return false;

	abb_iter_rango_t* iter = abb_iter_rango_crear(tablero, desde, hasta);
	if(!iter) return true;

	if(strcmp(modo,"asc")==0){
		for(int i=0; i<k && !abb_iter_rango_al_final(iter); abb_iter_rango_avanzar(iter), i++){
			const char* clave = abb_iter_rango_ver_actual(iter);
			fprintf(stdout, "%s\n", clave);
		}
	} else {
		pila_t* pila = pila_crear(); 
		while(!abb_iter_rango_al_final(iter)){
			const char* clave = abb_iter_rango_ver_actual(iter);
			pila_apilar(pila,(void*)clave);
			abb_iter_rango_avanzar(iter);
		}
		for(int i=0; !pila_esta_vacia(pila) && i<k; i++) fprintf(stdout, "%s\n", (char*)pila_desapilar(pila));
		pila_destruir(pila);
	}
	

	abb_iter_rango_destruir(iter);

	return true;
}


bool info_vuelo(hash_t* tablero, char* codigo){

	void* datos = hash_obtener(tablero,codigo);
	if(!datos) return false;
	
	char* cadena = join((char**)datos,' ');
	fprintf(stdout,"%s",cadena);

	free(cadena);

	return true;
}


bool prioridad_vuelos(hash_t* diccionario, int k){

	if(k<=0) return false;

	hash_iter_t* iter = hash_iter_crear(diccionario);
	if (!iter) return false;
	heap_t* prioridades = heap_crear((cmp_func_t)cmp_prioridad_min);
	if (!prioridades) {hash_iter_destruir(iter);return false;}

	void* datos_dic; void* datos_heap;

	for(int i=0; i<k && !hash_iter_al_final(iter); i++){
		heap_encolar(prioridades,hash_obtener(diccionario,hash_iter_ver_actual(iter)));
		hash_iter_avanzar(iter);
	}


	while(!hash_iter_al_final(iter)){
		datos_dic = hash_obtener(diccionario,hash_iter_ver_actual(iter));
		datos_heap = heap_ver_max(prioridades);
		if(cmp_prioridad_max(datos_heap,datos_dic)<0){
			heap_desencolar(prioridades);
			heap_encolar(prioridades, datos_dic);
		}
		hash_iter_avanzar(iter);
	}

	imprimir_heap_al_reves(prioridades);

	hash_iter_destruir(iter);
	heap_destruir(prioridades, NULL);
	return true;
}


bool borrar(abb_t* tablero, hash_t* diccionario, char* desde, char* hasta){
	
	if(cmp_fecha_asc(desde,hasta)>0) return false;
	cola_t* q = cola_crear();

	abb_iter_rango_t* iter = abb_iter_rango_crear(tablero, desde, hasta);
	if(!iter) return true;

	while(!abb_iter_rango_al_final(iter)){
		cola_encolar(q,(void*)abb_iter_rango_ver_actual(iter));
		abb_iter_rango_avanzar(iter);
	}
	

	while(!cola_esta_vacia(q)){
		char** datos = (char**) abb_borrar(tablero, (char*)cola_desencolar(q));
		info_vuelo(diccionario, datos[FLIGHT_NUMBER]);
		hash_borrar(diccionario,datos[FLIGHT_NUMBER]);
		free_strv(datos);
	}

	cola_destruir(q, free);
	abb_iter_rango_destruir(iter);

	return true;
}