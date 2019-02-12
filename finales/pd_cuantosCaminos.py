"""CONSIGNA:
Escribir usando programación dinámica una función cuantosCaminos(n, m) que cuenta
por cuántos caminos diferentes se puede ir del punto (n, m) al punto (0, 0) sobre
una grilla de enteros no negativos, sabiendo que sólo se pueden dar pasos hacia abajo
y hacia la izquierda. Calcular el orden."""

""" ecuacion de recurrenccia:
          si n==0 y m==0 return 0
      /
e(n,m)--  si n==0 y m!=0 return e(n,m-1)
      \
          si n!=0 y m==0 return e(n-1,m)
          
          else n!=0 y m!=0 return e(n-1,m-1)

def cuantosCaminos(n, m):
  
  return cuantosCaminos(n+1, m)+cuantosCaminos(n, m+1)

