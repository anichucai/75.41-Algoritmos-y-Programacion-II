#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"
#define FACTOR_DE_CARGA 0.7
#define TAM_INICIAL 5381

typedef enum estado{VACIO,OCUPADO,BORRADO} estado_t;


//---------------Declaración de Structs------------------

typedef struct hash_campo{
	char* clave;
	void* valor;
	estado_t estado;
}hash_campo_t;

struct hash{
	size_t cant;
	size_t tam;
	hash_destruir_dato_t destruir_dato;
	hash_campo_t* tabla;
};


struct hash_iter{
	size_t pos;
	const hash_t* hash;
};

	
//-----------Funciones de tipo Auxiliar----------------


//Función que evalua si un nro es o no primo

bool _es_primo(int n,int i){

	if(i==n) return true;
	if(n%i==0) return false;

	return _es_primo(n,i+1);
}

bool es_primo(int n){
	return _es_primo(n,2);
}


//Convierte un numero en primo
int convertir_primo(int n){
	while(!es_primo(n)) n+=1;
	return n;
}


//Función para evaluar igualdad de dos cadenas
bool es_igual(const char* cadena1,const char* cadena2){
	return strcmp(cadena1,cadena2)==0;

}


//Función para guardar la copia de la clave
char* copiar_clave(const char* clave){
	size_t n = strlen(clave)+1;
	char* copia=(char*)malloc(sizeof(char)*n);
	if(!copia) return NULL;
	memmove(copia,clave,n);
	return copia;
}


//Funcion para crear un campo
hash_campo_t* campo_crear(const char* clave, void* valor,estado_t estado){

	hash_campo_t* campo=(hash_campo_t*)malloc(sizeof(hash_campo_t));

	if(!campo) return NULL;

	campo->clave=copiar_clave(clave);

	if(!campo->clave){
		free(campo);
		return NULL;
	}
	campo->valor=valor;
	campo->estado=estado;

	return campo;
}


//Función de Hash de Dan Bernstein
unsigned long hashing(const char *str){

        unsigned long hash = 5381;
        int c;

        while ((c = (*str++))){
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }

        return hash;
}


//Funciónes para retornar la posicion para guardar la clave

size_t lineal_probing_search(const hash_t *hash, const char *clave){

	size_t encript = (size_t)(hashing(clave)%hash->tam);
	size_t i = encript;

	do{
		if(hash->tabla[i].estado==OCUPADO && es_igual(hash->tabla[i].clave,clave)) return i;
		i++;
		if(i==hash->tam) i=0;
	} while(encript!=i);

	return -1;
}

size_t lineal_probing(const hash_t *hash, const char *clave){

	size_t encript = (size_t)(hashing(clave)%hash->tam);
	size_t i = encript;

	do{
		if((hash->tabla[i].estado==VACIO) || (hash->tabla[i].estado==OCUPADO && es_igual(hash->tabla[i].clave,clave))) return i;
		i= i+1;
		if(i>=hash->tam) i=0;
	} while(i!=encript);

	return -1;
}


//Función para redimensionar el hash
bool hash_redimensionar(hash_t* hash, size_t tam){

	tam = (size_t) convertir_primo((int)tam); 

	hash_campo_t* tabla_vieja = hash->tabla;

	hash_campo_t* tabla_nueva = (hash_campo_t*)malloc(tam*sizeof(hash_campo_t));
	if(!tabla_nueva) return false;

	for(int i=0;i<tam;i++) tabla_nueva[i].estado = VACIO;
	hash->tabla = tabla_nueva;
	hash->cant = 0;
	
	int tam_ant = (int)hash->tam;

	hash->tam = tam;
	
	for(int i=0; i<tam_ant; i++){
		if(tabla_vieja[i].estado==OCUPADO){
			char* clave = tabla_vieja[i].clave;
			if(!hash_guardar(hash,clave,tabla_vieja[i].valor)) return false;
			free(clave);
		}
	}

	free(tabla_vieja);

	return true;
}



/* *****************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/


hash_t* hash_crear(hash_destruir_dato_t destruir_dato){

	hash_t* hash = (hash_t*)malloc(sizeof(hash_t));
	if(!hash) return NULL;

	hash->tam = TAM_INICIAL;
	hash->cant = 0;
	hash->destruir_dato = destruir_dato;

	hash->tabla = (hash_campo_t*)malloc(sizeof(hash_campo_t)*hash->tam);
	if(!hash->tabla){
		free(hash);
		return NULL;
	}

	for(size_t i = 0; i<hash->tam; i++) hash->tabla[i].estado = VACIO;
	
	return hash;
}


bool hash_guardar(hash_t* hash, const char* clave, void* dato){
	
	if((double)hash->cant/(double)hash->tam>=FACTOR_DE_CARGA){
		if(!hash_redimensionar(hash,hash->tam*2)) return false;
	}

	size_t pos = lineal_probing(hash, clave);

	if(pos==-1) return false;

	if(hash->tabla[pos].estado==OCUPADO){
		if(hash->destruir_dato) hash->destruir_dato(hash->tabla[pos].valor);
		hash->tabla[pos].valor=dato;
	}else{
		hash_campo_t* campo = campo_crear(clave,dato,OCUPADO);
		if(!campo) return false;
		hash->tabla[pos] = *campo;
		hash->cant++;
		free(campo);
	}

	return true;
}


void *hash_borrar(hash_t *hash, const char *clave){

	if(hash_cantidad(hash)==0) return NULL;

	size_t pos = lineal_probing_search(hash,clave);
	if(pos==-1) return NULL;
	
	free(hash->tabla[pos].clave);
	hash->tabla[pos].estado = BORRADO;
	hash->cant--;

	return hash->tabla[pos].valor;
}


void* hash_obtener(const hash_t *hash, const char *clave){
	size_t pos = lineal_probing_search(hash,clave);
	if(pos==-1) return NULL;
	return hash->tabla[pos].valor;
}	


bool hash_pertenece(const hash_t *hash, const char* clave){
	return (lineal_probing_search(hash,clave) != -1) ;
}


size_t hash_cantidad(const hash_t* hash){
	return hash->cant;
}


void hash_destruir(hash_t *hash){

	for(int i=0;i<hash->tam;i++){
		if(hash->tabla[i].estado==OCUPADO){
			if(hash->destruir_dato!=NULL) hash->destruir_dato(hash->tabla[i].valor);
			free(hash->tabla[i].clave);
		}
	}
	free(hash->tabla);
	free(hash);
}



/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/


hash_iter_t *hash_iter_crear(const hash_t *hash){

	hash_iter_t* iter = (hash_iter_t*)malloc(sizeof(hash_iter_t));
	if(!iter) return NULL;

	iter->hash=hash;
	iter->pos=0;

	for(int i=0;i<iter->hash->tam;i++,iter->pos++){
		if(iter->hash->tabla[i].estado==OCUPADO) break;
	}
	return iter;
}
	
	
bool hash_iter_avanzar(hash_iter_t *iter){

	if(hash_iter_al_final(iter)) return false;

	iter->pos++;

	while(!hash_iter_al_final(iter)){
		if(iter->hash->tabla[iter->pos].estado==OCUPADO) return true;
		iter->pos++;
	}
	return false;
}


const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if(hash_iter_al_final(iter)) return NULL;
	return iter->hash->tabla[iter->pos].clave;
}


bool hash_iter_al_final(const hash_iter_t *iter){
	return iter->pos==iter->hash->tam || iter->hash->tam==1;
}


void hash_iter_destruir(hash_iter_t* iter){
	free(iter);
}	
	
