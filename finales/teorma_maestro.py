TEOREMA MAESTRO
4) Tienen que elegir entre estos tres algoritmos para resolver el mismo problema. Justificar la elección mostrando cuáles son los órdenes de ejecución de cada uno (en notación O):

*El algoritmo A resuelve un problema de tamaño N dividiéndolo en cinco subproblemas de tamaño N/2, resolviendo cada subproblema recursivamente y luego combinando las soluciones en tiempo lineal.
a=5
b=2
c=1
[logb(a)=2,32]>[c=1]
O(n²)

*El algoritmo B resuelve un problema de tamaño N resolviendo recursivamente dos subproblemas de tamaño N-1 y luego combinando las soluciones en tiempo constante.
a=2
b=1
c=0
[log1(2)>0]
O(n*n*n...)

*El algoritmo C resuelve un problema de tamaño N dividiéndolo en nueve subproblemas de tamaño N/3, resolviendo cada subproblema recursivamente y luego combinando las soluciones en tiempo O(N^2)
a=9
b=3
c=2
[log3(9)==2] -> n²log(n)

Luego el mejor algoritmo es el primero
