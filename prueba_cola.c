#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cola.h"

/*
 * NOMBRE: Matias Tebele
 * PADRON: 95372
 */

/******************************************************************
 *                        PRUEBAS UNITARIAS
 ******************************************************************/

// Funciones auxiliares para imprimir si estuvo OK o no
void print_test(char* name, bool result)
{
	printf("* %s: %s\n", name, result? "OK" : "ERROR");
}

void print_test_loop(char* name, int value, bool result)
{
	printf("* %s %d: %s\n", name, value, result? "OK" : "ERROR");
}

// Clono una cadena con memoria dinámica
char *strdup(const char *s)
{
    char *n = malloc(strlen(s) + 1);
    if(n == NULL) return NULL;
    strcpy(n, s);
    return n;
}

// Pruebas para una cola de tamanio 0
void pruebas_cola_nula()
{
	printf("-- INICIO DE PRUEBAS CON COLA SIN ELEMENTOS -- \n");

	// Creo una cola
	cola_t* cola = cola_crear();
	
	// Inicio de pruebas
	print_test("Crear cola", cola != NULL);
	print_test("La cola esta vacia", cola_esta_vacia(cola));
	print_test("El primero es nulo", cola_ver_primero(cola) == NULL);
	print_test("No tengo elementos que desencolar", cola_desencolar(cola) == NULL);
		
	// Destruyo la cola
	cola_destruir(cola, NULL);
	print_test("La cola fue destruida", true);
}

// Pruebas de guardar y obtener algunos elementos
void pruebas_cola_algunos_elementos()
{
	printf("-- INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS -- \n");
	
	// Creo una cola y un vector con enteros
	cola_t* cola = cola_crear();
	int v[] = {0,5,22,-10,3,8};
	char c = 'w';
	char vc[] = {'_','z'};
	
	// Defino la cantidad de elementos del vector v
	int size = 6;
	
	// Pruebo encolar y desencolar
	print_test("Crear cola", cola != NULL);
	print_test("Encolo 22", cola_encolar(cola, &v[2]));
	print_test("Desencolo 22", cola_desencolar(cola) == &v[2]);
	print_test("Encolo 'w'", cola_encolar(cola, &c));
	print_test("Encolo vc[]", cola_encolar(cola, &vc));
	print_test("Desencolo 'w'", cola_desencolar(cola) == &c);	
	print_test("Desencolo vc[]", cola_desencolar(cola) == &vc);
	print_test("Desencolo nuevamente (null)", cola_desencolar(cola) == NULL);	
	print_test("La cola esta vacia", cola_esta_vacia(cola));
	
	for (int i = 0; i < size; i++)
		print_test_loop("Encolo", v[i], cola_encolar(cola, &v[i]));

	for (int i = 0; i < size; i++)
		print_test_loop("Desencolo", v[i], cola_desencolar(cola) == &v[i]);
	
	print_test("El primero es nulo", cola_ver_primero(cola) == NULL);
	print_test("La cola esta vacia", cola_esta_vacia(cola));
								
	// Destruyo la cola
	cola_destruir(cola, NULL);
	print_test("La cola fue destruida", true);
}

// Pruebas de guardar y obtener elementos dinamicos
void pruebas_cola_elementos_dinamicos()
{
	printf("-- INICIO DE PRUEBAS CON ELEMENTOS DINAMICOS -- \n");
	
	// Creo una cola y punteros a char
	cola_t* cola = cola_crear();
	
	char* hola = strdup("hola");
	char* mundo = strdup("mundo");
	char* hello = strdup("hello");
	char* world = strdup("world");
	
	// Pruebo encolar
	print_test("Crear cola", cola != NULL);
	print_test("Encolo hola", cola_encolar(cola, hola));
	print_test("Encolo mundo", cola_encolar(cola, mundo));
	print_test("Encolo hello", cola_encolar(cola, hello));
	print_test("Encolo world", cola_encolar(cola, world));
	
	// Destruyo la cola y los datos
	cola_destruir(cola, free);
	print_test("La cola fue destruida", true);
}

// Pruebas de la cola al trabajar con un volumen grande de elementos
void pruebas_cola_volumen()
{
	printf("-- INICIO DE PRUEBAS DE VOLUMEN -- \n");
	
	// Creo una cola
	cola_t* cola = cola_crear();
	
	// Creo la cola
	print_test("Crear cola", cola != NULL);
	
	// Defino la cantidad de elementos a encolar
	int cant = 10000;
	int i;
	bool result = true;	
	
	// Pruebo encolar y desencolar		
	for (i = 0; i < cant; i++)
		result &= cola_encolar(cola, &i);
	print_test("Se encolaron todos los elementos", result);
	
	result = true;
	for (i = 0; i < cant; i++)
		result &= (cola_desencolar(cola) == &i);
	print_test("Se desencolaron todos los elementos", result);
	
	print_test("El primero es nulo", cola_ver_primero(cola) == NULL);
	print_test("La cola esta vacia", cola_esta_vacia(cola));
								
	// Destruyo la cola
	cola_destruir(cola, NULL);
	print_test("La cola fue destruida", true);
}

// Ejecuto todas las pruebas
void pruebas_cola()
{
	pruebas_cola_nula();
	pruebas_cola_algunos_elementos();
	pruebas_cola_elementos_dinamicos();
	pruebas_cola_volumen();
}

// Programa principal
int main(int argc, char **argv)
{	
	pruebas_cola();
	return 0;
}
