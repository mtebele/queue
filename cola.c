#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cola.h"

/*
 * NOMBRE: Matias Tebele
 * PADRON: 95372
 */

/******************************************************************
 *                IMPLEMENTACION DE LOS TIPOS DE DATOS
 ******************************************************************/

typedef struct nodo
{
	void* dato;
	struct nodo *siguiente;
} nodo_t;

struct cola
{
	nodo_t *primero;
	nodo_t *ultimo;
};

/*******************************************************************
 *                IMPLEMENTACION DE LAS PRIMITIVAS
 *******************************************************************/

// Crea una cola.
// Post: devuelve una nueva cola vacía.
cola_t* cola_crear()
{
	cola_t* cola = malloc(sizeof(cola_t));
	if (cola == NULL) return NULL;
	cola->primero = NULL;
	cola->ultimo = NULL;
	return cola;
}

// Destruye la cola. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la cola llama a destruir_dato.
// Pre: la cola fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_t *cola, void destruir_dato(void*))
{	
	while (!cola_esta_vacia(cola))
		if (destruir_dato != NULL)
			destruir_dato(cola_desencolar(cola));
		else
			cola_desencolar(cola);
	free(cola);
}

// Devuelve verdadero o falso, según si la cola tiene o no elementos encolados.
// Pre: la cola fue creada.
bool cola_esta_vacia(const cola_t *cola)
{
	return (cola->primero == NULL);
}

// Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
// Pre: la cola fue creada.
// Post: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola.
bool cola_encolar(cola_t *cola, void* valor)
{
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL) return false;
	nodo->dato = valor;
	nodo->siguiente = NULL;
	if (cola_esta_vacia(cola))
		cola->primero = nodo;
	else
		cola->ultimo->siguiente = nodo;
	cola->ultimo = nodo;
	return true;
}

// Obtiene el valor del primer elemento de la cola. Si la cola tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el primer elemento de la cola, cuando no está vacía.
void* cola_ver_primero(const cola_t *cola)
{
	return (cola_esta_vacia(cola)) ? NULL : cola->primero->dato;
}

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primero de la cola, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vacía.
void* cola_desencolar(cola_t *cola)
{
	if (cola_esta_vacia(cola)) return NULL;
	nodo_t *nodo = cola->primero;
	cola->primero = nodo->siguiente;
	void* dato = nodo->dato;
	free(nodo);
	return dato;
}
