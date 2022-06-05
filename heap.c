#include "heap.h"
#include <stddef.h>
#include <stdlib.h>
#define HIJO_IZQ 2*i+1
#define HIJO_DER 2*i+2
#define PADRE (i-1)/2
#define TAM_INICIAL 64
#define DOBLE 2
#define REDUCIR_TAMANIO_OK ((heap->cant*4)<=heap->tam)&&((heap->tam/DOBLE)>=TAM_INICIAL)
#define AUMENTAR_TAMANIO_OK (heap->cant >= heap->tam/2)

void downheap(void* arr[], size_t cant, size_t i, cmp_func_t cmp);
void heapify(void* arr[], size_t cant, cmp_func_t cmp);
size_t maximo(void* arr[], size_t i, size_t d, cmp_func_t cmp);
void swap(void* arreglo[], size_t a, size_t b);
bool es_heap(void* arr[], size_t p, size_t izq, size_t der, bool e_der, cmp_func_t cmp);



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
    if (comparar(arreglo[j], arreglo[i]) <0) {
        swap(arreglo, i, j);
        upheap (arreglo, j, comparar);
    }
}

bool redimensionar(heap_t* heap, size_t tam, bool achicar) {
    size_t capacidad = achicar? heap->tam / 2 : heap->tam*2;
    void** datos = realloc(heap->datos, sizeof(void*) * capacidad);

    if (datos == NULL) return false;
    heap->datos = datos;
    heap->tam = capacidad;
    return true;
}

void* heap_desencolar(heap_t* heap){
    if(heap->cant == 0 || (REDUCIR_TAMANIO_OK && !redimensionar(heap, 2, true)) ) return NULL;
    swap(heap->datos,0,heap->cant-1);
    void* dato = heap->datos[heap->cant-1];
    heap->cant--;
    downheap(heap->datos,heap->cant,0,heap->cmp);
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

bool heap_encolar(heap_t *heap, void *elem) {
    if (AUMENTAR_TAMANIO_OK && ! redimensionar(heap, 2, false)) return false;
    heap->datos[heap->cant] = elem;
    upheap(heap->datos, heap->cant, heap->cmp);
    heap->cant++;
    return true;
}
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t* heap = heap_crear(cmp);
    if(!heap) return NULL;
    for(int i=0; i<n ; i++) heap->datos[i] = arreglo[i];
    heap->cant = n;
    heapify(heap->datos, heap->cant, heap->cmp);
    return heap;
}

/*utils*/

void downheap(void* arr[], size_t cant, size_t i, cmp_func_t cmp){
    if( !(i < cant) || !(HIJO_IZQ < cant) || es_heap(arr,i,HIJO_IZQ, HIJO_DER, HIJO_DER < cant, cmp) ) return;
    size_t pos = HIJO_DER < cant ? maximo(arr, HIJO_IZQ, HIJO_DER, cmp) : HIJO_IZQ;
    swap(arr, pos, i);
    downheap(arr, cant, pos, cmp);
}

void heapify(void* arr[], size_t cant, cmp_func_t cmp){
    for(size_t i = 0; i < cant; i++) downheap(arr, cant , cant -1 -i, cmp );
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heapify(elementos, cant, cmp);

    for(int i=0; i<cant; i++){
        if(cant-1-i == 0) break;
        swap(elementos,0,cant-1-i);
        downheap(elementos,cant-1-i,0,cmp);
    }
}

size_t maximo(void* arr[], size_t i, size_t d, cmp_func_t cmp){
    return cmp(arr[i], arr[d]) >= 0 ? i : d; 
}

bool es_heap(void* arr[], size_t p, size_t izq, size_t der, bool e_der, cmp_func_t cmp){
    return cmp(arr[p], arr[izq]) > 0 && (!e_der ? true : cmp(arr[p], arr[der]) > 0); 
}

