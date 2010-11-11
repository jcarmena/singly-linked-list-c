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


// -----------------------------------------------------------------------------
// Para hacer más legible el código
typedef void* TElemento;

// Definición de la lista
typedef struct list
{
	TElemento    dato;
	struct list* next;
} TNodoLista;

typedef TNodoLista* TLista;

// -----------------------------------------------------------------------------
// Puntero a función utilizada para comparar dos elementos
// POST: devuelve  0 (cero)     si e1 = e2
//       devuelve >0 (positivo) si e1 > e2
//       devuelve <0 (negativo) si e1 < e2
// -----------------------------------------------------------------------------
typedef int (*FComparar) (TElemento e1, TElemento e2);

// -----------------------------------------------------------------------------
// Puntero a una función que se quiera aplicar a todos los elementos
// -----------------------------------------------------------------------------
typedef void (*FMap) (TElemento e);

// -----------------------------------------------------------------------------
// Puntero a función para destruir un elemento
// -----------------------------------------------------------------------------
typedef void (*FDestruir) (TElemento e);




// -----------------------------------------------------------------------------
// POST: Crea y devuelve una lista vacía
// crear_lista_vacia = []
// -----------------------------------------------------------------------------
TLista crear_lista_vacia (void);

// -----------------------------------------------------------------------------
//	POST: Devuelve distinto de cero si la lista no contiene elementos
//       es_lista_vacia(crear_lista_vacia) = cierto
//       es_lista_vacia(insertar_elemento(lista, e)) = falso
// -----------------------------------------------------------------------------
int es_lista_vacia (TLista lista);

// -----------------------------------------------------------------------------
// POST: Ordena la lista utilizando para ello la función pasada como parámetro
//       ordenar_lista(crear_lista_vacia) = crear_lista_vacia
//       ordenar_lista([e1, e2, e3]) = [e2, e3, e1] <=> 
//          comparar(e2, e3) < 0 Y comparar(e3, e1) < 0 Y comparar(e2, e1) < 0
// -----------------------------------------------------------------------------
void ordenar_lista (TLista* lista, FComparar comparar);

// -----------------------------------------------------------------------------
// POST: Inserta un elemento en la lista (por la cabeza)
//       insertar_elemento(crear_lista_vacia, e) = [e]
//       insertar_elemento(insertar_elemento(crear_lista_vacia, e1), e2) = 
//          [e2, e1]
// -----------------------------------------------------------------------------
void insertar_elemento (TLista* lista, TElemento e);

// -----------------------------------------------------------------------------
// POST: Busca coincidencias con e en la lista guiándose con la función comparar
//       Devuelve el número de ocurrencias encontradas
//       buscar_elemento(crear_lista_vacia, e) = 0
//       buscar_elemento(insertar_elemento(crear_lista_vacia, e1), e) = 1 <=>
//          comparar(e1, e) == 0
//       buscar_elemento(insertar_elemento(lista, e1), e) = buscar_elemento(lista, e)
//          <=> comparar(e1, e) != 0
// -----------------------------------------------------------------------------
int buscar_elemento (TLista lista, TElemento e, FComparar comparar);

// -----------------------------------------------------------------------------
// POST: Recorre la lista aplicando la función map a cada elemento
// -----------------------------------------------------------------------------
TNodoLista* recorrer (TLista lista, FMap map);

// -----------------------------------------------------------------------------
// POST: Si todos!=0 borra el primer elemento de la lista que coincida con e
//       Si todos==0 borra todas los elementos de la lista que coinciden con e
//       Analiza las coincidencias con la función apuntada por comparar
//       Libera la memoria dinámica del elemento utilizando la función apuntada
//       por destruir
//       borrar_elemento (crear_lista_vacia) = crear_lista_vacia
//       borrar_elemento (insertar_elemento(lista, e1), e) = lista <=> (comparar(e1, e) == 0) Y (todos == 0)
//       borrar_elemento (insertar_elemento(lista, e1), e) = borrar_elemento(lista, e) <=> (comparar(e1, e) == 0) Y (todos != 0)
//       borrar_elemento (insertar_elemento(lista, e1), e) = insertar_elemento(borrar_elemento(lista, e), e1) <=> comparar(e1, e) != 0
// -----------------------------------------------------------------------------
void borrar_elemento (TLista* lista, TElemento e, int todos, FComparar comparar, FDestruir destruir);

// -----------------------------------------------------------------------------
// POST: Libera la memoria dinámica utilizada por la lista, libera también la
//       de los elementos utilizando la función apuntada por destruir
//       destruir_lista(crear_lista_vacia) = crear_lista_vacia
//       destruir_lista(insertar_elemento(lista, e)) = (destruir_lista(lista) Y destruir(e))
// -----------------------------------------------------------------------------
void destruir_lista (TLista* lista, FDestruir destruir);



