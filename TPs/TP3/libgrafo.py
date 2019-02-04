from Cola import *
from heapq import heappush, heappop
from Grafo import *
import random

'''
	Biblioteca de Grafos:
			
			-Orden Topológico
			-Recorrido BFS
			-Recorrido DFS
			-Algoritmo de Dijkstra
			-Algoritmo de Prim 
			-Random Walk
			

'''

INF= 999999999999999999999999999999999999999999999999999999999999999999

#Recorrido BFS
def bfs(grafo,aeropuertos,origen,destino):

	cola=Cola()
	visitados=set()
	distancia={}
	padre={}
	
	distancia[origen]=0
	padre[origen]=None
	cola.encolar(origen)
	dist=INF
	
	while not cola.esta_vacia():
	
		v=cola.desencolar()

		if v in aeropuertos[destino]: 
			dist=distancia[v]
			break

		for ady in grafo.ver_adyacentes(v):

			if not ady in visitados:

				distancia[ady]=distancia[v]+1
				padre[ady]=v
				cola.encolar(ady)
				visitados.add(ady)

	return padre,dist




#DFS
def dfs_modificado(grafo,aeropuertos,origen,n):

	visitados=set()	
	niveles={}
	padres={}

	niveles[origen]=0
	padres[origen]=None	
	

	funciono = r_dfs(grafo,aeropuertos,origen,origen,visitados,n,niveles,padres)
	
	return padres if funciono else None


def r_dfs(grafo,aeropuertos,v,destino,visitados,n,niveles,padres):

	if v==destino and niveles[v]==n : return True

	if(no_se_puede(v,destino,niveles,n)):
		padres.pop(v)
		niveles[v] = 0
		visitados.remove(v)
		return False

	ady=grafo.ver_adyacentes(v)
	if ady==None: return False
	
	for w in ady:
		if not w in visitados:

			niveles[w]=niveles[v]+1
			padres[w]=v
			
			visitados.add(w)
			if r_dfs(grafo,aeropuertos,w,destino,visitados,n,niveles,padres):
			
				return True

	if len(ady)<n and v in visitados: visitados.remove(v)			
			
	
def no_se_puede(v,destino,niveles,n):
	return (v==destino and niveles[v]!=n and niveles[v]!=0) or (niveles[v]==n and destino!=v) or (niveles[v]>n)


		


#Dijkstra
def dijkstra_modificado(vuelos, aeropuertos, origen, destino, modo):

	total=0

	dist = {}
	padre = {}

	for v in vuelos.ver_vertices(): dist[v] = INF

	padre[origen] = None
	dist[origen] = 0
	
	heap = []
	heappush(heap, (0,origen))

	while heap:

		distv,v = heappop(heap)

		if(v in aeropuertos[destino]): return padre,total

		adyacentes = vuelos.ver_adyacentes(v)

		if (adyacentes == None): continue

		for w in adyacentes:

			peso_union =  vuelos.peso(v,w)[modo]

			if (distv + peso_union) <= dist[w]:				

				dist[w] = distv + peso_union
				
				total += dist[w]

				padre[w] = v
				
				heappush(heap,(dist[w],w))				

	return None,INF


#Prim
def prim(grafo,origen,modo):

	padres={}
	visitados=set()
	pesos = {}
	prioridades = []

	for v in grafo.ver_vertices():
		heappush(prioridades,(INF,v))
		pesos[v] = INF

	padres[origen]=None
	visitados.add(origen)
	pesos[origen]=0
	heappush(prioridades,(0,origen))
	
	while prioridades:

		distv,v=heappop(prioridades)

		adyacentes=grafo.ver_adyacentes(v)

		if not adyacentes: continue

		for w in adyacentes:

			if not w in visitados:

				peso_nuevo=int(grafo.peso(v,w)[modo])
				peso_viejo=int(pesos[w]) 

				if prioridades:
 				
					if peso_nuevo <= peso_viejo:
						padres[w]= v
						heappush(prioridades,(peso_nuevo,w))
						pesos[w]=peso_nuevo

		visitados.add(v)

	return padres

		
#Orden Topologico
def orden_topologico_dfs(grafo):

	visitados=set()
	lista=[]
	for v in grafo.ver_vertices():
		if not v in visitados:
			ot_rec(grafo,v,lista,visitados)
	return lista[::-1]

def ot_rec(grafo,v,lista,visitados):

	visitados.add(v)

	ady=grafo.ver_adyacentes(v)

	if ady!=None:

		for w in ady:

			if not w in visitados:

				ot_rec(grafo,w,lista,visitados)

	lista.append(v)


                                                                                                  
#Random Walk
def random_walk(grafo,origen,n,apariciones):

	v=origen

	for i in range(n):

		v=random.choice(list(grafo.ver_adyacentes(v)))

		apariciones[v]+=1

	

