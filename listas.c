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


#include "listas.h"
#include <stdlib.h>


// -----------------------------------------------------------------------------
// POST: Crea un nodo nuevo a partir de el elemento e y la dirección del
//       siguiente nodo
// O(1)
// -----------------------------------------------------------------------------
TNodoLista* crear_nodo (TElemento e, TNodoLista* sig)
{
	TNodoLista* ptr;
	ptr = (TNodoLista*)malloc(sizeof(TNodoLista));
	
	ptr->dato = e;
	ptr->next = sig;
	
	return ptr;
}


// -----------------------------------------------------------------------------
// O(1)
// -----------------------------------------------------------------------------
TLista crear_lista_vacia (void)
{
	return NULL;
}


// -----------------------------------------------------------------------------
// O(1)
// -----------------------------------------------------------------------------
int es_lista_vacia (TLista lista)
{
	return lista == NULL;
}


// -----------------------------------------------------------------------------
// PRE: ptrnodo1 y ptrnodo2 no pueden ser nulos
// O(1)
// POST: Intercambia los datos de dos nodos
// -----------------------------------------------------------------------------
void intercambiar (TNodoLista* ptrnodo1, TNodoLista* ptrnodo2)
{
	TElemento aux;
	
	aux = ptrnodo1->dato;
	ptrnodo1->dato = ptrnodo2->dato;
	ptrnodo2->dato = aux;
}


// -----------------------------------------------------------------------------
// PRE: n es la longitud de la sublista a ordenar
// O(n^2)
// POST: ordena la lista por el método de burbuja
// -----------------------------------------------------------------------------
void burbuja(TLista* ptrlista, int n, FComparar comparar)
{
	int i; 	// (i comparaciones -> i+1 elementos)
	TNodoLista* ptrnodo;
	
	if (n<2)
		return;
	
	ptrnodo = *ptrlista;
	
	// Realiza n-1 veces...
	for (i=1; i<n; i++)
	{
		// Si e1 > e2 los intercambia
		if (comparar(ptrnodo->dato, ptrnodo->next->dato) > 0)
			intercambiar (ptrnodo, ptrnodo->next);
		
		ptrnodo = ptrnodo->next;
	}
	burbuja(ptrlista, n-1, comparar);
	return;
}


// -----------------------------------------------------------------------------
// O(n^2)
// -----------------------------------------------------------------------------
void ordenar_lista (TLista* ptrlista, FComparar comparar)
{
	int i;
	TNodoLista* ptrnodo;
	
	if (es_lista_vacia(*ptrlista))
		return;
	
	ptrnodo = *ptrlista;
			
	if (ptrnodo->next == NULL)
		return;
	
	i=0;
	// La primera pasada se realiza aquí (para calcular la longitud)
	while (ptrnodo->next != NULL)
	{
		i++;			
		// Si e1 > e2 los intercambia
		if (comparar(ptrnodo->dato, ptrnodo->next->dato) > 0)
			intercambiar (ptrnodo, ptrnodo->next);
			
		ptrnodo = ptrnodo->next;
	}
	// Las demás pasadas se realizan en burbuja
	burbuja(ptrlista, i, comparar);
}


// -----------------------------------------------------------------------------
// O(1)
// -----------------------------------------------------------------------------
void insertar_elemento (TLista* ptrlista, TElemento e)
{
	*ptrlista = crear_nodo (e, *ptrlista);
}


// -----------------------------------------------------------------------------
// O(n)
// -----------------------------------------------------------------------------
int buscar_elemento (TLista lista, TElemento e, FComparar comparar)
{
	TNodoLista* ptrnodo;
	int n;
	
	if (lista == NULL)
		return 0;
	
	ptrnodo = lista;
	
	n = 0;
	while (ptrnodo != NULL)
	{
		if (comparar(e, ptrnodo->dato) == 0)
			n++;
		
		ptrnodo = ptrnodo->next;
	}
	return n;
}


// -----------------------------------------------------------------------------
// POST: Devuelve un puntero al puntero que apunta al elemento
//       Devuelve NULL si no lo encontró
// inicial es un puntero al puntero que señala al predecesor del primer elemento 
// de la búsqueda
// -----------------------------------------------------------------------------
TNodoLista** localizar_elemento (TNodoLista** inicial, TElemento e, FComparar comparar)
{
	TNodoLista* ptrnodo;
	TNodoLista** res;
	TNodoLista** ptrptrnodo;
	
	res = NULL;
	ptrnodo = *inicial;
	ptrptrnodo = inicial;
	
	while ((ptrnodo != NULL) && (res == NULL))
	{
		if (comparar(e, ptrnodo->dato) == 0)
			res = ptrptrnodo;
		
		ptrptrnodo = &(ptrnodo->next);
		ptrnodo = ptrnodo->next;
	}
	
	return res;
}


// -----------------------------------------------------------------------------
// POST: Elimina el nodo de la lista y devuelve un puntero al puntero que 
//       apunta al siguiente elemento de la lista o NULL si no hay más o si
//       se pasó un puntero nulo o el puntero que señala al elemento era nulo
// -----------------------------------------------------------------------------
TNodoLista** quitar_nodo (TNodoLista** ptrptrnodo, FDestruir destruir)
{
	TNodoLista* aux;
	
	if (ptrptrnodo == NULL)
		return NULL;
	
	if (*ptrptrnodo == NULL)
		return NULL;
		
	aux = *ptrptrnodo;
	*ptrptrnodo = aux->next;
	destruir (aux->dato);
	free (aux);
	return ptrptrnodo;
}


// -----------------------------------------------------------------------------
// O(n)
// -----------------------------------------------------------------------------
void borrar_elemento (TLista* ptrlista, TElemento e, int todos, FComparar comparar, FDestruir destruir)
{
	TNodoLista** ptrptrnodo;
	
	if (es_lista_vacia(*ptrlista))
		return;
	
	ptrptrnodo = ptrlista;
	do
	{
		ptrptrnodo = localizar_elemento(ptrptrnodo, e, comparar);
		ptrptrnodo = quitar_nodo (ptrptrnodo, destruir);
	} 
	while (todos && (ptrptrnodo != NULL));
}


// -----------------------------------------------------------------------------
// O(n)
// -----------------------------------------------------------------------------
void destruir_lista (TLista* ptrlista, FDestruir destruir)
{
	while (!es_lista_vacia (*ptrlista))
	{
		quitar_nodo (ptrlista, destruir);
	}
}


// -----------------------------------------------------------------------------
// O(n)
// -----------------------------------------------------------------------------
TNodoLista* recorrer (TLista lista, FMap map)
{
	TNodoLista* ptrnodo;
	
	ptrnodo = lista;
	while (ptrnodo != NULL)
	{
		map (ptrnodo->dato);
		ptrnodo = ptrnodo->next;
	}
}
