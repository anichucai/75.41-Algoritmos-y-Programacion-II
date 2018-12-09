//EJERCICIO DIVISION Y CONQUISTA

/*CONSIGNA: Del primer parcialito, primer cuatrimestre de 2016
Se tiene un arreglo tal que [1, 1, 1, ..., 0, 0, ...] (es decir, “unos seguidos de ceros”). Se pide:
a) una funci´on de orden O(logn) que encuentre el indice del primer 0. Si no hay ning´un 0 (solo
hay unos), debe devolver -1.
b) demostrar con el Teorema Maestro que la funci´on es, en efecto, O(log n).
Ejemplos:
[1, 1, 0, 0, 0] ->2
[0, 0, 0, 0, 0] ->0
[1, 1, 1, 1, 1] ->-1
*/

int primer_cero(int arr[],int n){

  return _primer_cero(arr[],0,n-1);

}

int _primer_cero(int arr[], int inicio, int fin){
  
  if( inicio>fin) return -1;
  
  int medio = (inicio+fin)/2;
  
  if (arr[medio]==1){
    return _primer_cero(arr,medio+1,fin);
  } else if(arr[medio]==0 && medio>0 && arr[medio-1]==0){
    return _primer_cero(arr,inicio,medio-1);
  }
  
  return medio;
  
}  
  
//Complejidad: a=1; b=2; c= 0 -> log2(1)=0 -> O(logn)
