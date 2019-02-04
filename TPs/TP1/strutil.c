#include "strutil.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

size_t contar_apariciones (const char* str, char sep){

	size_t apariciones = 0;
	for(;*str != '\0'; str++){
		if (*str == sep) apariciones++;
	}

	return apariciones;
}


char **split(const char *str, char sep){

	if (!str) return NULL;

	size_t len_arreglo = contar_apariciones(str, sep)+1;
	char** strv = (char**) malloc( sizeof(char*) * (len_arreglo+1) );
	if (!strv) return NULL;
	strv[len_arreglo] = NULL;

	size_t inicio = 0; size_t actual = 0; size_t i = 0;

	while (i<len_arreglo){

		if (str[actual]==sep || str[actual]=='\0'){

			char* palabra = (char*) malloc(sizeof(char)*(actual-inicio+1));
			if (!palabra) {free_strv(strv); free(strv); return NULL;}
			strncpy(palabra, &str[inicio], actual-inicio);
			palabra[actual-inicio]='\0';
			strv[i] = palabra;
			inicio = actual+1;
			++i;
		}

		++actual;
	}
	
	return strv;
}

char* join(char **strv, char sep){

	size_t len_str = 1;
	for(size_t i=0;strv && strv[i]; i++) len_str += strlen(strv[i])+1;

	char* str =(char*) malloc(sizeof(char)*(len_str));
	if (!str) return NULL;

	if(!strv || !strv[0]){ str[0]='\0';return str;}

	int act=0; char* palabra; char c;

    for(int i=0; strv[i]; i++){
    	palabra = strv[i];
    	c = *palabra;
    	for(; c!='\0';){
    		str[act]=c;
    		act++;
    		palabra++;
    		c=*palabra;
    	}
    	str[act]=sep;
    	act++;

	}
	str[act-1]='\0';

	return str;
}



void free_strv(char *strv[]){
	for(size_t i=0; strv[i]!=NULL; ++i){
		free(strv[i]);
	}
	free(strv);

}
