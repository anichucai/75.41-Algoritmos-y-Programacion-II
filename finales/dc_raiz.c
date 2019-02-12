/*CONSIGNA: Aplicar división y conquista para calcular la raíz cuadrada entera
de un número entero. Calcular el orden del algoritmo propuesto.*/

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
