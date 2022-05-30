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
