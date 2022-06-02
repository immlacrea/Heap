#include "testing.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int comp ( const void* a, const void* b){
    const int * n1 = a;
    const int * n2 = b;

    if (*n1 == *n2) return 0;

    return *n1 > *n2 ? 1 : -1;
}

//void pruebas_heap_catedra(void);
void pruebas_heap_estudiante(void){
    
}
//void pruebas_heap_volumen_catedra(size_t, bool);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

#ifdef CORRECTOR
int main(int argc, char *argv[]) {
    if (argc > 1) {
        // Asumimos que nos están pidiendo pruebas de volumen.
        long largo = strtol(argv[1], NULL, 10);
        pruebas_heap_volumen_catedra((size_t) largo, false);
        return 0;
    }
    printf("~~~ PRUEBAS ESTUDIANTE ~~~\n");
    pruebas_heap_estudiante();
    printf("\n~~~ PRUEBAS CÁTEDRA ~~~\n");
    //pruebas_heap_catedra();

    return failure_count() > 0;
}
#endif

int main(){
    printf("\n[TEST]\n\n");
    pruebas_heap_estudiante();
    return 0;
}
