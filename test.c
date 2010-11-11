/*
Copyright (c) 2010 Javier Carmena (git@github.com:jcarmena/listas.git)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "listas.h"


// Comandos que puede introducir el usuario
#define COMANDO_MOSTRAR "mostrar"
#define COMANDO_BORRAR "borrar"
#define COMANDO_BORRARTODOS "borrartodos"
#define COMANDO_BUSCAR "buscar"
#define COMANDO_INSERTAR "insertar"
#define COMANDO_ORDENAR "ordenar"
#define COMANDO_AYUDA "ayuda"
#define COMANDO_SALIR "fin"

// Códigos internos para trabajar con los comandos
enum COMANDOS_ENUM { BUSCAR, BORRAR, BORRARTODOS, INSERTAR, ORDENAR, MOSTRAR, AYUDA, SALIR };
typedef enum COMANDOS_ENUM TCodigoComando;

// Estructura comando con el código y el argumento que introdujo el usuario
typedef struct comando
{
	TCodigoComando codigo;
	int argumento;
} TComando;



// -----------------------------------------------------------------------------
// Función que se utilizará para llamar a las operaciones de listas
// -----------------------------------------------------------------------------
int comparar_elementos (void* a, void* b)
{	
	int e1 = *((int*)a);
	int e2 = *((int*)b);
	
	return (e1 - e2);
}



// -----------------------------------------------------------------------------
// Función para mostrar un elemento, se utilizará con FMap de listas para
// mostrar la lista por pantalla
// -----------------------------------------------------------------------------
void mostrar_elemento (TElemento e)
{
	printf ("%d ", *((int*)e));
}



// -----------------------------------------------------------------------------
// Función para liberar la memoria ocupada por un elemento, se utilizará con
// FDestruir de litas
// -----------------------------------------------------------------------------
void destruir_elemento (TElemento e)
{
	free((int*)e);
}



// -----------------------------------------------------------------------------
// Crea y devuelve un puntero al un elemento nuevo creado dinámicamente para 
// evitar que se tome la dirección de las variables auxiliares y se sobreescriban
// valores
// Debe liberarse la memoria reservada cuando deje de ser necesario el elemento
// -----------------------------------------------------------------------------
TElemento crear_elemento (int e)
{
	int* ptrint;
	ptrint = malloc (sizeof(int));
	*ptrint = e;
	return ptrint;
}



// -----------------------------------------------------------------------------
// Pide por pantalla n elementos y devuelve una lista nueva creada a partir de ellos
// -----------------------------------------------------------------------------
TLista pedir_elementos (int n)
{
	int c, valor;
	TLista lista;
	
	lista = crear_lista_vacia();
	for (c=0; c<n; c++)
	{
		printf ("Introduce el elemento número %d: ", c+1);
		scanf ("%d", &valor);
		insertar_elemento (&lista, crear_elemento(valor));
	}
	return lista;
}



// -----------------------------------------------------------------------------
// Muestra información de los comandos que reconoce el programa
// -----------------------------------------------------------------------------
void mostrar_ayuda ()
{
	printf("\nComandos:");
	printf("\n========\n");
	printf("\n %s\n\tmuestra la lista", COMANDO_MOSTRAR);
	printf("\n %s <valor>\n\tinserta un nuevo elemento en la lista", COMANDO_INSERTAR);
	printf("\n %s <valor>\n\tquita el elemento de la lista (el primero encontrado)", COMANDO_BORRAR);
	printf("\n %s <valor>\n\tquita el elemento de la lista (todos los que coinciden)", COMANDO_BORRARTODOS);
	printf("\n %s\n\tordena la lista", COMANDO_ORDENAR);
	printf("\n %s <valor>\n\tbusca un elemento en la lista e indica el número de veces que aparece", COMANDO_BUSCAR);
	printf("\n %s\n\testa ayuda", COMANDO_AYUDA);
	printf("\n %s\n\tsale del programa", COMANDO_SALIR);
	printf("\n");
}


// -----------------------------------------------------------------------------
// Pide por pantalla que se introduzca el siguiente comando
// Si introduce uno incorrecto vuelve a pedirlo
// Devuelve un puntero a la estructura TComando con la información introducida
// por el usuario
// -----------------------------------------------------------------------------
TComando* pedir_comando (void)
{
	TComando* comando;
	char txt[20];
	int arg;
	int ok;

	comando = malloc(sizeof(TComando));
	ok = 0;
	
	while (!ok)
	{
		printf ("\n> ");
		scanf ("%s", txt); 
		if (strcmp(txt, COMANDO_SALIR) == 0)	{
			comando->codigo = SALIR;
			ok = 1;
		} else if (strcmp(txt, COMANDO_MOSTRAR) == 0)	{
			comando->codigo = MOSTRAR;
			ok = 1;
		} else if (strcmp(txt, COMANDO_ORDENAR) == 0)	{
			comando->codigo = ORDENAR;
			ok = 1;
		} else if (strcmp(txt, COMANDO_AYUDA) == 0)	{
			comando->codigo = AYUDA;
			ok = 1;
		} else if (strcmp(txt, COMANDO_INSERTAR) == 0)	{
			scanf ("%d", &arg);
			comando->codigo = INSERTAR;
			comando->argumento = arg;
			ok = 1;
		} else if (strcmp(txt, COMANDO_BORRAR) == 0)	{
			scanf ("%d", &arg);
			comando->codigo = BORRAR;
			comando->argumento = arg;
			ok = 1;
		} else if (strcmp(txt, COMANDO_BUSCAR) == 0)	{
			scanf ("%d", &arg);
			comando->codigo = BUSCAR;
			comando->argumento = arg;
			ok = 1;
		} else if (strcmp(txt, COMANDO_BORRARTODOS) == 0)	{
			scanf ("%d", &arg);
			comando->codigo = BORRARTODOS;
			comando->argumento = arg;
			ok = 1;
		}
	}
		
	return comando;
}



// -----------------------------------------------------------------------------
// Muestra la lista por pantalla
// -----------------------------------------------------------------------------
void mostrar_lista (TLista lista)
{
	printf("[ ");
	recorrer (lista, mostrar_elemento);
	printf("]");
}



// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------
int main (int argc, char* argv[])
{
	int num;
	TLista lista;
	TComando* comando;
	
	if (argc != 2)
	{
		printf ("\n%s: Uso incorrecto: %s <número de elementos>\n", argv[0], argv[0]);
		return 1;
	}
	
	num = atoi(argv[1]);
	if (num < 1)
		return 0;
		
	lista = pedir_elementos (num);
	mostrar_ayuda();	
	comando = pedir_comando();
	while (comando->codigo != SALIR)
	{
		switch (comando->codigo)
		{
			case MOSTRAR:
				mostrar_lista(lista);
				break;
			case ORDENAR:
				ordenar_lista (&lista, comparar_elementos);
				mostrar_lista(lista);
				break;
			case INSERTAR:
				insertar_elemento (&lista, crear_elemento(comando->argumento));
				mostrar_lista(lista);
				break;
			case BORRAR:
				borrar_elemento (&lista, (void*)(&comando->argumento), 0, comparar_elementos, destruir_elemento);
				mostrar_lista(lista);
				break;
			case BORRARTODOS:
				borrar_elemento (&lista, (void*)(&comando->argumento), 1, comparar_elementos, destruir_elemento);
				mostrar_lista(lista);
				break;
			case BUSCAR:
				num = buscar_elemento (lista, (void*)(&comando->argumento), comparar_elementos);
				printf("%d ocurrencias", num);
				break;
			case AYUDA:
				mostrar_ayuda ();
				break;				
		}
		
		// esto abajo del todo
		free(comando);
		comando = pedir_comando();
	}
	free(comando);
	
	destruir_lista (&lista, destruir_elemento);
		
	return 0;
}
