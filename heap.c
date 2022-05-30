#include "heap.h"
#include <stddef.h>
#define HIJO_IZQ 2*i+1
#define HIJO_DER 2*i+2
#define PADRE (i-1)/2

struct heap {
    void **datos;
    size_t tam;
    size_t cant;
    cmp_func_t cmp;
};

bool heap_esta_vacio(const heap_t *heap){
    return heap->cant == 0;
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}

void *heap_ver_max(const heap_t *heap){
    return heap->cant == 0 ? NULL : heap->datos[0];
}
