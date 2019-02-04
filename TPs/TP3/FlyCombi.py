#!/usr/bin/env python3
from Algueiza import *
import sys


def main():

	if not parametros_correctos(): return

	vuelos=Grafo()

	ciudades,aeropuertos = leer_aeropuertos(vuelos,sys.argv[1])

	leer_vuelos(vuelos,sys.argv[2])

	consola(vuelos,ciudades,aeropuertos)


def parametros_correctos():

	if(len(sys.argv)!=3): 

		raise Exception("Error en parametros")

		return False
	
	return True

def consola(vuelos,ciudades,aeropuertos):

	while True:


		try:
			entrada=input()
			lineas=entrada.split(",")

			if len(lineas)!=1:
			
				elem=lineas[0].split(" ")
				if len(elem)>2: 

					elem[1]=" ".join(elem[1:])
					elem=elem[:2]

				lineas.pop(0)


				lineas=elem+lineas 
				

			else: lineas=lineas[0].split(" ")
							

			if lineas[0]=="camino_mas":

				if(len(lineas)==4): camino_mas(vuelos,aeropuertos,lineas[2], lineas[3], lineas[1])
				else: print("Error de comando")

			elif lineas[0]=="camino_escalas":

				if(len(lineas)==3): camino_escalas(vuelos,aeropuertos, lineas[1], lineas[2])
				else: print("Error de comando")

			elif lineas[0]=="itinerario":

				if(len(lineas)==2): itinerario(lineas[1], aeropuertos,vuelos)
				else: print("Error de comando")

			elif lineas[0]=="nueva_aerolinea":

				if(len(lineas)==2): nueva_aerolinea(vuelos, lineas[1])
				else: print("Error de comando")

			elif lineas[0]=="centralidad_aprox":


				if(len(lineas)==2): centralidad_aproximada(vuelos,int(lineas[1]))
				else: print("Error de comando")


			elif lineas[0]=="vacaciones":


				if(len(lineas)==3): vacaciones(vuelos,aeropuertos,lineas[1],int(lineas[2]))
				else: print("Error de comando")

			elif lineas[0]=="listar_operaciones":


				if(len(lineas)==1): listar_operaciones()
				else: print("Error de comando")
	

			else: print("Error de comando")

		except EOFError: break
	

#_____________________________________________________________________

main()

