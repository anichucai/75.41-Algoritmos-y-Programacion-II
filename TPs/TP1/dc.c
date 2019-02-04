#include "pila.h"
#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000



/*---------------------------OPERACIONES ARITMETICAS------------------------------*/

int _raiz(int n, int inicio, int fin){
    if (inicio > fin) return inicio-1;
    int medio = (inicio + fin) / 2;
    if (medio*medio < n) return _raiz(n, medio+1,fin);
    if (medio*medio > n) return _raiz(n, inicio, medio-1);
    return medio; 
}

int raiz(unsigned int n){
	if (n<2) return n;
	return _raiz(n,0,n);
}

int potencia(int n,unsigned int e){
	if (e==0) return 1;
	if (e==1) return n;
	int res = potencia(n,e/2);
	return (e%2==0) ? res*res: res*res*n;
}

int logaritmo(int n, unsigned int b){
	if (n<b) return 0;
	return 1+(int)logaritmo(n/b,b);
}


/*------------------------------FUNCIONES AUXILIARES---------------------------------*/

char** separar_datos(char* line){

	char cadena[MAX]; char* str; str=line; int anterior= -1;int actual=0; int siguiente=1; int i=0;

	while (str[actual] && str[actual]!='\n'){
		if ( (str[actual]!=' ') || ((str[actual]==' ' && actual!=0 && str[anterior]!=' '))){
			cadena[i]=str[actual];
			i++;
		}
		actual++; siguiente++; anterior++;
	}
	(actual>0 && str[actual-1]==' ') ? (cadena[i-1]='\0') : (cadena[i]='\0');


	return split(cadena,' ');

}

bool es_num(char* num){
	return !(atoi(num)==0 && strcmp(num,"0")!=0);
}



/*------------------------------CALCULADORA POLACA---------------------------------*/


bool operar(char* operador, pila_t* numeros, int* res){

	int* a; int* b; int* c;

	if(pila_esta_vacia(numeros)) return false;
	a = (int*)(pila_desapilar(numeros));

	if (strcmp(operador,"sqrt")!=0){
		if(pila_esta_vacia(numeros)){free(a);return false;}
		b = (int*)(pila_desapilar(numeros));
	}

	if (strcmp(operador,"?")==0){
		if(pila_esta_vacia(numeros)){free(a); free(b);return false;}
		c = (int*)(pila_desapilar(numeros));
	}

	if (strcmp(operador,"+")==0){
		*res = (*a)+(*b);
	}else if (strcmp(operador,"-")==0){
		*res = (*a)-(*b);
 	}else if (strcmp(operador,"*")==0){
   		*res = (*a)*(*b);
   	}else if (strcmp(operador,"/")==0 && (*b)!=0) {
   		*res = (*a)/(*b);
   	}else if (strcmp(operador,"?")==0){
   		*res =  (*a) ? (*b) : (*c);
   	}else if (strcmp(operador,"^")==0 && ((*b)>=0)){
		*res = potencia(*a,*b);
	}else if (strcmp(operador,"sqrt")==0 && (*a)>=0){
   		*res = raiz(*a);
   	}else if (strcmp(operador,"log")==0 && (*b)>1 && (*a)=>1){
   		*res = (int) logaritmo(*a,*b);
	}else{
		free(a);
		if (strcmp(operador,"sqrt")!=0)free(b);
		return false;
	}

	free(a);
	if (strcmp(operador,"sqrt")!=0)free(b);
	if (strcmp(operador,"?")==0)free(c);

	return true;
}


void calculadora_polaca(char** datos){

	if (strcmp(datos[0],"")==0){fprintf(stdout, "%s\n", "ERROR");return;}

	pila_t* numeros = pila_crear();
	if (!numeros){fprintf(stdout, "%s\n", "ERROR");return;}
	
	bool operacion_exitosa= true;

	for(int i=0; datos[i] && operacion_exitosa; i++){
		int* n; int* res;
		if (es_num(datos[i])){
			n = (int*)malloc(sizeof(int));
			*n = atoi((char*)datos[i]);
			pila_apilar(numeros, n);
		} else if (!es_num(datos[i])) {
			res = (int*)malloc(sizeof(int));
			operacion_exitosa &= operar((char*) datos[i], numeros, res);
			pila_apilar(numeros, res);
		}
	}
	if (!operacion_exitosa || pila_len(numeros)!=1){
		fprintf(stdout, "%s\n", "ERROR");
	} else{
		int* tope = (int*)pila_desapilar(numeros);
		fprintf(stdout, "%d\n", *tope);
		free(tope);
	}

	while(!pila_esta_vacia(numeros)) free(pila_desapilar(numeros));
	pila_destruir(numeros);

}



void ejecutar_calculadora(int argc, char** argv){

	char line[MAX];

	fgets(line,MAX,stdin);

	if(!*line) {fprintf(stdout, "%s\n", "ERROR");return;}

	do{
		char** datos; 
		datos = separar_datos(line);
		
		calculadora_polaca(datos);
		
		free_strv(datos);
	} while (fgets(line,MAX,stdin));
}
