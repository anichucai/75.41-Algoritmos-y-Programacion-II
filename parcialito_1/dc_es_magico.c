//EJERCICIO DIVISION Y CONQUISTA

/*Implementar una función en C que reciba un arreglo de n enteros sin repetir y ordenado ascendentemente,
y determine en O(logn) si es mágico. Un arreglo es mágico si existe algún valor i (entre 0 y n - 1) tal que
arr[i] = i.
Ejemplos:
• A = [ -3, 0, 1, 3, 7, 9 ] es mágico porque A[3] = 3.
• B = [ 1, 2, 4, 6, 7, 9 ] no es mágico porque B[i] != i para todo i.
Justificar el orden del algoritmo.*/

bool es_magico(int arr[], int n){

  return _es_magico(arr,0,n-1);
}

bool _es_magico(inr arr[], int inicio, int fin){
  
  if(inicio>fin) return false;
  
  medio = (inicio+fin)/2;
  
  if(arr[medio]>medio){
    _es_magico(arr,inicio,medio-1);
  }else if(arr[medio]<medio){
    _es_magico(arr,medio+1,fin);
  } else{
    return true;
  }
  
}

// Complejidad:  teorema del maestro
// a=1; b=2; c=0 -> log2(1)=0 -> O(logn)
