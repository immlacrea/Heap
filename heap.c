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

void swap(void* arreglo[], size_t a, size_t b) {
    void* dato = arreglo[a];
    arreglo[a] = arreglo[b];
    arreglo[b] = dato;
}

void upheap (void* arreglo[], size_t i, cmp_func_t comparar) {
    if (!i) return;
    size_t j = PADRE;
    if (comparar(j, i) <0) {
        swap(arreglo, i, j);
        upheap (arreglo, j, comparar);
    }
}

bool redimensionar(heap_t* heap);

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

<<<<<<< HEAD
void *heap_ver_max(const heap_t *heap){
    return heap->cant == 0 ? NULL : heap->datos[0];
}

bool heap_esta_vacio(const heap_t *heap){
    return heap->cant == 0;
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
=======
bool heap_encolar(heap_t *heap, void *elem) {
    if (heap->cant >= heap->tam/2) {
        if (!redimensionar(heap)) return false;
    }
    heap->datos[heap->cant] = elem;
    upheap(heap->datos, heap->cant, heap->cmp);
    heap->cant++;
    return true;
>>>>>>> encolar
}