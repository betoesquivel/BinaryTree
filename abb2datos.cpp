/*
 * =====================================================================================
 *
 *       Filename:  abb2datos.cpp
 *
 *    Description:  Arbol en el que le puedes meter dos datos. 
 *
 *        Version:  1.0
 *        Created:  10/16/2013 11:43:54 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Alberto Esquivel Patino, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <class T>
class NodoArbol
{ public:
	T info, info2;
	NodoArbol<T> *izq, *der;
	NodoArbol() { izq = der = NULL; }
	NodoArbol(T dato, T dato2) { info = dato; info2 = dato2; izq = der = NULL; }
};

template <class T>
class ABB
{
private:
		NodoArbol<T> *raiz;
public:
		ABB() { raiz = NULL; }
		NodoArbol<T>* getRaiz(){return raiz;}
		void inserta (T dato);
		bool existe (T dato);
		~ABB() { libera(raiz); }
};

template <class T>
void libera (NodoArbol<T>* raiz) 
{ //Observar que al ser recursive, es una función libre llamada por el método
	if (raiz != NULL)
	{ 	libera(raiz->izq);
		libera(raiz->der);
		delete(raiz);
	}
}

template <class T>
void ABB<T>::inserta (T valor)
{ //Precondición: el valor no existe en el árbol.
	NodoArbol<T> *NuevoNodo = new NodoArbol<T>(valor);
	NodoArbol<T> *actual = raiz, *anterior = NULL;
	while (actual != NULL)
	{
		anterior=actual;
		actual=(actual->info>valor? actual->izq: actual->der);
	}
	if (anterior==NULL)	raiz = NuevoNodo;
	else
		if (anterior->info > valor) anterior->izq = NuevoNodo;
		else anterior->der = NuevoNodo;
}

template <class T>
bool ABB<T>::existe(T dato)
{
	NodoArbol<T> *aux = raiz;
	while (aux != NULL && aux->info != dato)
		aux = (dato < aux->info? aux->izq : aux->der);
	return !(aux == NULL);
}

