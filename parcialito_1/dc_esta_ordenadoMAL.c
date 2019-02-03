/*CONSIGNA: Escribir una funcion en C que determine si un arreglo esta ordenado aplicando division y conquista.
Indicar el orden de la funcion, utilizando el Teorema del Maestro.*/

bool _esta_ordenado(void** arr, int inicio, int fin){
    
    if (fin-inicio<2) return true;
    
    medio = (inicio+fin)/2;
    
    if(arr[medio-1]<arr[medio]) return _esta_ordenado(arr, inicio, medio-1);
    if(arr[medio+1]>arr[medio]) return _esta_ordenado(arr, medio+1, fin);
    
    return false;
    
}

bool esta_ordenado(void** arr, int n){

    return _esta_ordenado(arr, 0, n-1);
}


//Complejidad: O(n)
