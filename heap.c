#include "heap.h"
#include <stddef.h>
#define HIJO_IZQ 2*i+1
#define HIJO_DER 2*i+2
#define PADRE (i-1)/2
#define TAM_INICIAL 64

struct heap {
    void **datos;
    size_t tam;
    size_t cant;
    cmp_func_t cmp;
};

//debug
void rellenar(heap_t* heap, int* a, size_t cant){
    for(int i=0; i<cant; i++){
        heap->datos[i] = &a[i];
    }
    heap->cant = cant;
}

bool Existe(heap_t* heap, size_t pos){
    return pos < heap->cant;
}

void mostrarARR(heap_t* heap){
    printf("\n[ ");
    int i=0;
    for(; i<heap->cant - 1; i++) printf("%d ", *(int*)heap->datos[i]);
    printf("%d ]\n\n",*(int*)heap->datos[i]);
}

void swap(void* arreglo[], size_t a, size_t b){
    void* dato = arreglo[a];
    arreglo[a] = arreglo[b];
    arreglo[b] = dato;
}

bool es_heap(heap_t* heap ,size_t p,  size_t izq, size_t der, bool e_der){
    return heap->cmp(heap->datos[p], heap->datos[izq]) > 0 && (!e_der ? true : heap->cmp(heap->datos[p], heap->datos[izq]) > 0);
}

size_t maximo(heap_t* heap, size_t i, size_t d){
    return heap->cmp(heap->datos[i], heap->datos[d]) >= 0 ? i : d; 
}

void _downheap(heap_t* heap,size_t i){
    if(!Existe(heap, i) || !Existe(heap,HIJO_IZQ) || es_heap(heap, i, HIJO_IZQ, HIJO_DER, Existe(heap, HIJO_DER) ) ) return;
    size_t pos = Existe(heap, HIJO_DER) ? maximo(heap, HIJO_IZQ, HIJO_DER) : HIJO_IZQ ;
    swap(heap,pos,i);
    return _downheap(heap, pos);
}

void* heap_desencolar(heap_t* heap){
    if(heap->cant == 0) return NULL;
    swap(heap,0,heap->cant-1);
    void* dato = heap->datos[heap->cant-1];
    heap->cant--;
    _downheap(heap,0);
    return dato;
}

heap_t *heap_crear(cmp_func_t cmp) {
    heap_t* heap = malloc(sizeof(heap_t));
    if (heap == NULL) return NULL;

    void** datos = malloc(sizeof(void*) * TAM_INICIAL);
    if (datos==NULL) {
        free(heap);
        return NULL;
    }
    heap->datos = datos;
    heap->cant = 0;
    heap->tam = TAM_INICIAL;
    heap->cmp = cmp;

    return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)) {
    if (destruir_elemento != NULL) {
        for (size_t i = 0; i<heap->cant; i++) {
            destruir_elemento(heap->datos[i]);
        }
    }
    free(heap->datos);
    free(heap);
}

void *heap_ver_max(const heap_t *heap){
    return heap->cant == 0 ? NULL : heap->datos[0];
}

bool heap_esta_vacio(const heap_t *heap){
    return heap->cant == 0;
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}

