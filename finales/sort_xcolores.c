/*CONSIGNA: Se tiene una secuencia de n pares de la forma (número,color),
ordenada por número, y donde color pertenece al conjunto {Rojo, Verde, Azul}.
Escribir un algoritmo O(n) que deje todos los rojos, luego todos los verdes,
y luego todos los azules, pero donde los números dentro de cada color siga
ordenado: (por ejemplo (A,1),(R,2),(R,3),(A,4)→(R,2),(R,3),(A,1),(A,4)).
Codificarlo en C.*/ 

// Implementacion modificada de Bucket Sort que es O(cn) siendo c la cantidad
//de buckets o categorias en las que se va a ordenar los datos. EN este caso c=3
//ya que son tres colores.

#define AZUL A
#define ROJO R
#define VERDE V

bool ordenar_x_color(void** secuencia, size_t len){
  
  void** bucketA[len]; void** bucketR[len]; void** bucketV[len];
  
  size_t iA=0; size_t iR=0; size_t iV=0;
  
  for(size_t i=0; i<len; i++){
    
    void** actual = secuencia[i];
    char* color = (char*)actual[0];
    
    if(color==AZUL){
      bucketA[iA] = actual;
      iA++;
    } else if (color==ROJO){
      bucketR[iR] = actual;
      iR++;
    } else if (color==VERDE){
      bucketA[iV] = actual;
      iV++;
    } else {
      return false;
    }
  }
  
  size_t j=0;
  
  for(size_t jR=0; jR<=iR; iR++, j++) secuencia[j]= bucketR[jR];
  for(size_t jV=0; jV<=iV; iV++, j++) secuencia[j]= bucketR[jV];
  for(size_t jA=0; jA<=iA; iA++, j++) secuencia[j]= bucketR[jA];
  
  return true;
}     


