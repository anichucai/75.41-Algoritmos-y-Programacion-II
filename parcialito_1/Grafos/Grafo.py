DIRIGIDO=1
NO_DIRIGIDO=0

class Grafo:

	''' Implementacion del TDA Grafo diccionario de diccionarios. El siguiente es pesado y no dirigido'''

	def __init__(self,modo=NO_DIRIGIDO):
		
		self.dict = {}

		self.modo=modo


	def __len__(self):

		return len(self.dict)


	def __str__(self):

		return str(self.dict)


	def __repr__(self):

		return self.dict


	def vertice_pertenece(self, vertice):

		return vertice in self.dict.keys()


	def arista_pertenece(self, origen, destino):

		return destino in self.dict[origen].keys()


	def agregar_vertice(self, vertice):

		if self.vertice_pertenece(vertice): return
		self.dict[vertice] = {}


	def agregar_arista(self, origen, destino, peso):

		if self.vertice_pertenece(origen):
			self.dict[origen][destino] = peso
			if(self.modo==NO_DIRIGIDO):self.dict[destino][origen] = peso
			

	def sacar_vertice(self, vertice):

		if self.vertice_pertenece(vertice):
			for adj in self.dict[vertice].keys():
				self.dict[adj].pop(vertice, None)
			self.dict.pop(vertice, None)


	def sacar_arista(self, origen, destino):

		if self.arista_pertenece(origen, destino):
			self.dict[origen].pop(destino, None)
			if(self.modo==NO_DIRIGIDO):self.dict[destino].pop(origen, None)
			 


	def ver_vertices(self):

		return self.dict.keys()


	def ver_adyacentes(self, vertice):

		if self.vertice_pertenece(vertice): return self.dict[vertice].keys()
		return False


	def peso(self, origen, destino):

		if self.arista_pertenece(origen, destino): return self.dict[origen][destino]
