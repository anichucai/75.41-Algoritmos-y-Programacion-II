//EJERCICIO RECURSIVIDAD

/*CONSIGNA: Del primer recuperatorio del parcialito del segundo cuatrimestre de 2012
Escriba una funci´on recursiva para calcular de forma eficiente la potencia de un n´umero
con exponente entero positivo.*/

int potencia(int n,int e){

  if (e==0){
    return 1;
  }else if (e==1){
    return n;
  }
  
  int m = potencia(n,e/2);
  
  if(e%2==0){
    return m*m
  }else{
    return m*m*n;
  }
  
