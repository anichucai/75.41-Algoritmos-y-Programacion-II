/*CONSIGNA: Posicion pico*/

int posicion_pico( int** arr, int n){
    return _posicion_pico(arr, 0, n-1);
}

int _posicion_pico(int** arr, int inicio, int fin, pos pico){
    
    if(fin-inicio<2) return -1;
    
    medio = (inicio+fin)/2;
    
    if(arr[medio-1]<arr[medio] && arr[medio]<arr[medio+1]){
        return _posicion_pico(arr, medio+1, fin);
    } else if (arr[medio-1]>arr[medio] && arr[medio]>arr[medio+1]){
        return _posicion_pico(arr, 0, medio-1);
    }
    return medio;
}
    
 
