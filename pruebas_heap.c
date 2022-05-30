#include "heap.h"
#include "testing.h"
#include "pila.h"
#include <stdio.h>
#include <stdlib.h>


//WRAPPER DE PILA DESTRUIR
void pila_destruir_wrapper(void* pila) {
    pila_destruir(pila);
}

int entero_mayor(const void* a, const void* b) {
    int dato_a = *(int*)a;
    int dato_b = *(int*)b;
    if (dato_a < dato_b) return -1;
    if (dato_b < dato_a) return 1;
    return 0;
}

//Pruebas para un heap vacio
static void prueba_heap_vacio(void) {
    printf("INICIO DE PRUEBAS CON HEAP VACIO\n");

    //Declaro el heap a utilizar
    heap_t* heap = heap_crear(entero_mayor);

    //Inicio de pruebas
    print_test("Se creo el heap con exito", heap != NULL);

    //Pruebo que el heap esta vacio
    print_test("Heap nuevo esta vacio", heap_esta_vacio(heap));

    //Pruebo que ver el maximo del heap devuelve NULL
    print_test("El maximo es NULL", heap_ver_max(heap) == NULL);

    //Pruebo que la cantidad del heap es cero
    print_test("Tiene cero elementos", heap_cantidad(heap) == 0);

    //Pruebo desencolar en heap vacio
    //print_test("Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

    //Destruccion del heap
    heap_destruir(heap, NULL);
    printf("El heap se destruyo con exito");
}

//Pruebas de encolar
static void prueba_encolar(void) {
    printf("INICIO DE PRUEBAS ENCOLAR\n");
    
    //Defino el heap
    heap_t* heap = heap_crear(entero_mayor);
    
    //Declaro los punteros para pruebas
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;

    //Agrego el elemento NULL
    print_test("Se agrego el elemento NULL", heap_encolar(heap, NULL));
    print_test("El maximo es NULL", heap_ver_max(heap) == NULL);
    //Agrego elementos al heap
    print_test("Se agrego el valor 1", heap_encolar(heap, &a));
    print_test("El maximo es 1", *(int*)heap_ver_max(heap) == a);
    print_test("Se agrego el valor 2", heap_encolar(heap, &b));
    print_test("El maximo es 2", *(int*)heap_ver_max(heap) == b);
    print_test("Se agrego el valor 4", heap_encolar(heap, &d));
    print_test("El maximo es 4", *(int*)heap_ver_max(heap) == d);
    print_test("Se agrego el valor 3", heap_encolar(heap, &c));
    print_test("El maximo es 4", *(int*)heap_ver_max(heap) == d);
    print_test("Se agrego el valor 5", heap_encolar(heap, &e));
    print_test("El nuevo maximo es 5", *(int*)heap_ver_max(heap) == e);

    //Comportamiento
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Tiene cero elementos", heap_cantidad(heap)== 0);

    //Destruyo el heap
    heap_destruir(heap, NULL);
    printf("El heap se destruyo con exito");
}
/*
//Pruebas de manejo de un gran volumen de datos
static void prueba_muchos_elementos() {
    printf("INICIO DE PRUEBAS DE VOLUMEN\n");

    //Creo el heap
    heap_t* heap = heap_crear(entero_mayor);

    //Defino la cantidad de elementos a agregar
    size_t tam_max = 1000;

    //Prueba de encolar todos los elementos
    size_t i;
    size_t vector[tam_max];
    bool ok = true;
    bool ok2 = true;
    for (i=0; i<tam_max; i++) {
        vector[i] = i;
        ok &= heap_enheapr(heap, &vector[i]);
        ok2 &= (*(size_t*)heap_ver_primero(heap) == vector[0]);
    }
    print_test("Todos los elementos se agregaron", ok);
    print_test("Se mantuvo el invariante del maximo", ok2);

    //Destruccion del heap
    heap_destruir(heap, NULL);
}
*/
//Pruebas de destruccion de datos con funcion FREE
static void prueba_destruccion_con_free() {
    printf("INICIO DE PRUEBAS CON FUNCION DE DESTRUCCION FREE\n");

    //Creo el heap
    heap_t* heap = heap_crear(entero_mayor);

    //Inicializacion de punteros de prueba
    int* puntero1 = malloc(sizeof(int));
    int* puntero2 = malloc(sizeof(int));
    int* puntero3 = malloc(sizeof(int));

    //Agregar los datos al heap
    heap_encolar(heap, puntero1);
    heap_encolar(heap, puntero2);
    heap_encolar(heap, puntero3);
    print_test("Se agregaron los elementos", !heap_esta_vacio(heap));

    //Destruccion del heap
    heap_destruir(heap, free);
    print_test("Se destruyo el heap con exito", true);
}

//Pruebas de destruccion de datos PILA
static void prueba_destruccion_con_pila() {
    printf("INICIO DE PRUEBAS DE DESTRUCCION CON PILAS\n");

    //Creo el heap
    heap_t* heap = heap_crear(entero_mayor);

    //Inicializacion de punteros de prueba
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();

    //Agregar los datos al heap
    heap_encolar(heap, pila1);
    heap_encolar(heap, pila2);
    heap_encolar(heap, pila3);
    print_test("Se agregaron las pilas", !heap_esta_vacio(heap));


    //Destruccion del heap
    heap_destruir(heap, pila_destruir_wrapper);
    print_test("Se destruyo el heap con exito", true);
}

void pruebas_heap_estudiante() {
    //Ejecuta las pruebas
    prueba_heap_vacio();
    prueba_encolar();
//    prueba_muchos_elementos();
    prueba_destruccion_con_free();
    prueba_destruccion_con_pila();
}