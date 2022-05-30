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