from Grafo import *
from Cola import *
from libgrafo import *
from heapq import heappush, heappop
import csv
import random
import sys


RAPIDO=0
BARATO=1

COMANDOS=["camino_mas","centralidad_aprox","nueva_aerolinea","itinerario","camino_escalas","vacaciones"]


#--------------LISTAR OPERACIONES----------------------

def listar_operaciones():

	print("\n".join(COMANDOS))


#-------------------CAMINO MINIMO-----------------------

def camino_mas(vuelos, aeropuertos, origen, destino, modo):

	if modo=="rapido": modo = RAPIDO
	elif modo=="barato": modo = BARATO

	camino_mas = None

	optimo=INF
		
	for aeropuerto in aeropuertos[origen]:

		camino,costo = dijkstra_modificado(vuelos, aeropuertos, aeropuerto, destino, modo)

		if costo<optimo:
		
			optimo=costo
			camino_mas=camino	

	if (camino_mas!=None): reconstruir_camino(camino_mas,aeropuertos,origen,destino)


def camino_escalas(grafo,aeropuertos,origen,destino):

	camino_min = None

	optimo = INF #aca se pone infinito
	
	for aeropuerto in aeropuertos[origen]:

		padres,dist=bfs(grafo,aeropuertos,aeropuerto,destino)
		
		if dist < optimo:

			optimo=dist
			camino_min=padres
		
	if (camino_min != None): reconstruir_camino(camino_min,aeropuertos,origen,destino)	
	

def reconstruir_camino(padres,aeropuertos,origen,destino):

	act= None	

	for aeropuerto in aeropuertos[destino]:

		act=padres.get(aeropuerto,False)

		if act:
			act=aeropuerto
			break

	if not act: return	

	camino_inverso = []


	while not (act in aeropuertos[origen]):
		camino_inverso.append(act)
		act = padres[act]

	camino_inverso.append(act)
	camino = camino_inverso[::-1]

	print(" -> ".join(camino))

#-------------------------VACACIONES-----------------------------

def vacaciones(grafo,aeropuertos,origen,n):
	
	for aeropuerto in aeropuertos[origen]:
		padre = dfs_modificado(grafo,aeropuertos,aeropuerto,n)
		if padre!=None:
			cadena=cadena_vacaciones(padre,aeropuerto,n)
			print(cadena)
			return
	
	print("No se encontro recorrido")	

	

def cadena_vacaciones(padres,origen,n):
		
	camino=[]
	camino.append(origen)
	actual=padres[origen]

	while actual!=origen:

		camino.append(actual)
		actual=padres.get(actual,None)
		
	camino.append(actual)

	return ' -> '.join(camino[::-1])
			


#-------------------------CENTRALIDAD-----------------------------

def centralidad_aproximada(grafo,n):

	apariciones={}

	for v in grafo.ver_vertices(): apariciones[v]=0

	for v in grafo.ver_vertices(): random_walk(grafo,v,len(grafo),apariciones)

	apariciones=ordenar_vertices(apariciones)
							
	print(", ".join(apariciones[:n]))


def ordenar_vertices(distancias):

	ordenados=[]

	heap=[]

	for v in distancias:
		if(distancias[v]!=INF): heappush(heap,(distancias[v],v));

	while heap: ordenados.append(heappop(heap)[1])

	return ordenados[::-1]


#-----------------------NUEVA AEROLINEA--------------------------

def peso_MST(archivo):

	with open(archivo,"r") as file:
	
		vuelos_csv = csv.reader(file)

		peso = 0

		for aeropuertoi,aeropuertoj,tiempo,precio,vuelos in vuelos_csv:
			peso += int(precio)	

	return peso


def nueva_aerolinea(grafo,archivo):

	origen=list(grafo.ver_vertices())[0]

	padres=prim(grafo,origen,BARATO)

	with open(archivo,'w') as file:

		for v in grafo.ver_vertices():

			if v==origen: continue
			
			padre=padres.get(v,False)

			if not padre: continue
			
			peso=grafo.peso(padre,v)

			linea=[padre,v,str(peso[0]),str(peso[1]),str(peso[2])]

			file.write(','.join(linea)+'\n')

	print("OK")
		
#-------------------------ITINERARIO---------------------------

def itinerario(archivo,aeropuertos, grafo):

	lista = leer_itinerario(archivo)

	print(', '.join(lista))

	for i in range(len(lista)-1):

		camino_escalas(grafo,aeropuertos,lista[i],lista[i+1])


def poner_arista(grafo,vertice,destino):
	
	adyacentes=list(grafo.ver_adyacentes(destino))

	if vertice in adyacentes:grafo.sacar_arista(destino,vertice)

	grafo.agregar_arista(vertice,destino,None)
				

def leer_itinerario(archivo):

	grafito=Grafo(DIRIGIDO)

	with open(archivo) as file:
      
		itinerario_csv=csv.reader(file,delimiter='\n')

		for linea in itinerario_csv:

			lineas=linea[0].split(',')

			if len(lineas)==2: poner_arista(grafito,lineas[0],lineas[1])

			else:
				for elem in lineas: grafito.agregar_vertice(elem)
		
	return orden_topologico_dfs(grafito)
			

#-------------------------LECTURA DE ARCHIVOS-------------------------


def leer_aeropuertos(grafo,archivo):

	ciudades={}

	codigos={}

	with open(archivo) as file:
      
		aeropuertos_csv=csv.reader(file)

		valores=[]

		for ciudad,codigo,latitud,longitud in aeropuertos_csv:

			if not grafo.vertice_pertenece(codigo): grafo.agregar_vertice(codigo)

			codigos[codigo]=ciudad

			valores=codigos.get(ciudad,[])

			valores.append(codigo)

			codigos[ciudad]=valores

			lista = ciudades.get(ciudad,[])
			lista.append((codigo,latitud,longitud))
			ciudades[ciudad]=lista


	return ciudades,codigos


def leer_vuelos(grafo,archivo):

	with open(archivo) as file:
	
		vuelos_csv = csv.reader(file)

		for aeropuertoi,aeropuertoj,tiempo,precio,vuelos in vuelos_csv:

			grafo.agregar_arista(aeropuertoi,aeropuertoj,(int(tiempo),int(precio),int(vuelos)))

#______________________________________________________________


