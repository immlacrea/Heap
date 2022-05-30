#include "pila.h"

#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...
bool pila_agrandar(pila_t *pila) {
    void **aux = realloc(pila->datos, sizeof(void*) * (pila->capacidad*2));

    if (aux == NULL) {
        return false;
    }
    pila->datos = aux;
    pila->capacidad = pila->capacidad*2;
    return true;
}

void pila_achicar(pila_t *pila) {
    void **aux = realloc(pila->datos, sizeof(void*) * (pila->capacidad/2));

    if (aux == NULL) {
        return;
    }
    pila->datos = aux;
    pila->capacidad = pila->capacidad/2;
    return;
}

pila_t *pila_crear() {
    pila_t *pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }
    pila->capacidad = 8;
    pila->datos = malloc(pila->capacidad * sizeof(void*));

    if (!pila->datos) {
        free(pila);
        return NULL;
    }
    pila->cantidad = 0;
    return pila;
}

void pila_destruir(pila_t *pila) {
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
    return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void *valor) {
    if (pila->cantidad == pila->capacidad) {
        if (!pila_agrandar(pila)) {
            return false;
        }     
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad ++;
    return true;
}

void *pila_ver_tope(const pila_t *pila) {
    if (pila_esta_vacia(pila)) {
        return NULL;
    }
    return pila->datos[pila->cantidad-1];
}

void *pila_desapilar(pila_t *pila) {
    if (pila_esta_vacia(pila)) {
        return NULL;
    }
    if ((pila->cantidad)*4 <= pila->capacidad) {
        pila_achicar(pila);
    }
    pila->cantidad --;
    return pila->datos[pila->cantidad];
}