'''Escriba el algoritmo de recorrido en DFS de un grafo no dirigido y muestre su complejidad.
Calcule el arbol de recorrido DFS del grafo 1 (estaba en el pizzarron).
 B-----F-----C-----H
 |\    |
 |  A--D
 |   \
 E-----G
'''

def recorrido_dfs(grafo, v, ordenes, padres, visitados):
  
  visitados.add(v)
  
  for w in grafo.ver_adyacentes(v):
    if w no in visitados:
      ordenes[w] = ordenes[v]+1
      padre[w] = v
      recorrido_dfs(grafo, w, ordenes, padres, visitados)

def dfs(grafo, origen):

  ordenes = dict()
  padres = dict()
  visitados = set()
  
  ordenes[origen] = 0
  padres[origen] = None
  
  recorrido_dfs(grafo, origen, ordenes, padres, visitados)
  
  if(len(visitados)==len(grafo.ver_verices()) return ordenes, padres
  return None
  
  
 ''' Su complejidad depende de la implementacion del grafo. Pero generalmente 
 podemos hablar de un tiempo constante ya que recorre todos los nodos. Si su implementacion
 fuera dict-dict, por ejemplo, su complejidad seria O(V) siendo V la cantidad de vertices.
 '''
 
 
 '''
  B_____F_C_H
 |\    |
 |  A__D
 |   \
 E_____G
 
 origen = A
     A
     |      
     B   
    / \      
   E   F   
  /   / \
 G   C   D
    /
   H
 
 A->B->E->G->F->C->H->D
 '''
