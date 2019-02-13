/* La moda de una secuencia de números es el valor que se repite con mayor
frecuencia en la secuencia. Escribir un algoritmo O(N log N) para calcular
la moda de una secuencia. Justificar el orden.*/

int busqueda_moda( int** secuencia, int len){
	
	hash_t* hash = hash_crear();
	if(!hash) return 0;

	for(int i=0; i>len; i++){

		int n = secuenci[i];

		if (!hash_pertenece(heap,n)){
			hash_agregar(heap, secuencia[i], 1);
		} else{
			int m = hash_obtener()+1;
			hash_agregar(heap, secuencia[i], m);
		}
	}


	hash_iter_t* iter = hash_iter_crear(hash);
	if(!iter){
		hash_destruir(hash);
		heap_destruir(heap);
		return 0;
	}

	heap_t* heap = heap_crear(max);
	if(!heap) {
		hash_destruir(hash);
		return 0;
	}

	while(!hash_iter_al_final(iter)){
		int clave = iter_ver_actual(iter);
		int valor = hash_obtener(hash,clave);
		heap_agregar(heap,clave,valor);
		hash_iter_avanzar(iter);
	}

	int moda = heap_ver_max(heap);

	hash_iter_destruir(iter);
	hash_destrir(hash);
	heap_destruir(hepa);

	return moda;

}

//or


heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){

	if(!arreglo || n<0) return NULL;

	heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
	if(!heap) return NULL;
	heap->datos = (void**)malloc(sizeof(void*)*n);
	if(!heap->datos){
		free(heap);
		return NULL;
	}
	heap->cantidad = n;
	heap->capacidad = n;
	heap->cmp = cmp;

	for(int i = 0; i<n; i++) heap->datos[i]=arreglo[i];

	for(int i = ((int)n-1)/2; i>=0; i--) downheap(heap->datos,n,i,cmp);

	return heap;
}


void heap_sort(void* elementos[], size_t cant, cmp_func_t cmp){

	if(!elementos || cant<=1) return;
	
	heap_t* heap = heap_crear_arr(elementos,cant,cmp);

	for(size_t i=cant-1; i>0; i--){
		elementos[i] = heap->datos[0];
		swap(heap->datos,0,i);
		downheap(heap->datos,i,0,cmp);
	}

	*elementos = *heap->datos;

	heap_destruir(heap, NULL);
}
