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
    printf("El heap se destruyo con exito\n");
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
    print_test("Tiene 5 elementos", heap_cantidad(heap)== 5);

    //Destruyo el heap
    heap_destruir(heap, NULL);
    printf("El heap se destruyo con exito\n");
}

//Pruebas de manejo de un gran volumen de datos
static void prueba_muchos_elementos() {
    printf("INICIO DE PRUEBAS DE VOLUMEN\n");

    //Creo el heap
    heap_t* heap = heap_crear(entero_mayor);
    print_test("El heap se creo con exito", heap!=NULL);

    //Defino la cantidad de elementos a agregar
    size_t tam_max = 1000;

    //Prueba de encolar todos los elementos
    size_t i;
    size_t vector[tam_max];
    bool ok = true;
    bool ok2 = true;
    for (i=0; i<tam_max; i++) {
        vector[i] = i;
        ok &= heap_encolar(heap, &vector[i]);
        ok2 &= (*(size_t*)heap_ver_max(heap) == vector[i]);
    }
    print_test("Todos los elementos se agregaron", ok);
    print_test("Se mantuvo el invariante del maximo", ok2);

    //Destruccion del heap
    heap_destruir(heap, NULL);
}

//Pruebas de destruccion de datos con funcion FREE
static void prueba_destruccion_con_free() {
    printf("INICIO DE PRUEBAS CON FUNCION DE DESTRUCCION FREE\n");

    //Creo el heap
    heap_t* heap = heap_crear(entero_mayor);

    //Inicializacion de punteros de prueba
    int* puntero1 = malloc(sizeof(int));
    int* puntero2 = malloc(sizeof(int));
    int* puntero3 = malloc(sizeof(int));

    *puntero1 = 1;
    *puntero2 = 2;
    *puntero3 = 3;

    //Agregar los datos al heap
    heap_encolar(heap, puntero1);
    heap_encolar(heap, puntero2);
    heap_encolar(heap, puntero3);
    print_test("Se agregaron los elementos", !heap_esta_vacio(heap));

    //Destruccion del heap
    heap_destruir(heap, free);
    print_test("Se destruyo el heap con exito\n", true);
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
    print_test("Se destruyo el heap con exito\n", true);
}

void pruebas_heap_desencolar(){
    printf("INICIO PRUEBAS HEAP DESENCOLAR\n");
    heap_t* heap = heap_crear(entero_mayor);
    int arr[] = {1,2,3,4,5};
    bool ok = true;
    for(int i=0; i<5; i++){
        //encolo y verifico que el maximo sea el correcto
        ok&= (heap_encolar(heap,&arr[i]) && arr[i] == *(int*)heap_ver_max(heap));
    }
    print_test("encolar todos los datos y verifico ver maximo correctos", ok);
    for(int i=0; i<4; i++){
        //desencolo y verifico maximos correctos
        ok&= (arr[5-1-i] == *(int*)heap_desencolar(heap) && *(int*)heap_ver_max(heap) == arr[4-1-i]); 
    }
    ok &= arr[0] == *(int*)heap_desencolar(heap) && !heap_ver_max(heap);
    print_test("desencolar todos los datos y verifico ver maximos correctos", ok);
    print_test("el heap esta vacio y ver maximo es falso", heap_esta_vacio(heap) && !heap_ver_max(heap));
    heap_destruir(heap,NULL);
}

void prueba_crear_arr(){
    printf("INICIO CREAR ARRAY HEAP\n");
    void* v[5];
    int arr[] = {1,2,3,4,5};
    int a = 9;
    int b = 6;
    int c = 8;
    bool ok = true;
    for(int i=0; i<5; i++) v[i] = &arr[i];
    heap_t* heap = heap_crear_arr(v,5,entero_mayor);
    print_test("se cargaron los datos en el heap", !heap_esta_vacio(heap));
    print_test("el maximo es 5", 5 == *(int*)heap_ver_max(heap));
    ok&= heap_encolar(heap,&a) && *(int*)heap_ver_max(heap) == a;
    print_test("encolo 9 y el maximo es 9", ok);
    ok&= heap_encolar(heap,&b) && *(int*)heap_ver_max(heap) != b && *(int*)heap_ver_max(heap) == a ;
    print_test("encolo 6 y el maximo es 9", ok);
    ok&= heap_encolar(heap,&c) && *(int*)heap_ver_max(heap) != c && *(int*)heap_ver_max(heap) == a ;
    print_test("encolo 8 y el maximo es 9", ok);
    heap_destruir(heap,NULL);
    print_test("se destruyo el heap", ok);
}

void prueba_heap_sort(){
    printf("PRUEBA HEAPSORT\n");
    int sufle[] =  { 2,7,1,4,3,9,8,5,6};
    int solucion[] = { 1,2,3,4,5,6,7,8,9};
    void* v[9];
    for(int i=0; i<9; i++) v[i] = &sufle[i];
    heap_sort(v,9,entero_mayor);
    bool ok=true;
    for(int i=0; i<9; i++){
        ok&= (*(int*)v[i] == solucion[i] ); 
    }
    print_test("se acomodaron los elementos correctamente", ok);
}

void pruebas_heap_estudiante() {
    //Ejecuta las pruebas
    prueba_heap_vacio();
    prueba_encolar();
    prueba_muchos_elementos();
    prueba_destruccion_con_free();
    prueba_destruccion_con_pila();
    pruebas_heap_desencolar();
    prueba_crear_arr();
    prueba_heap_sort();
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif