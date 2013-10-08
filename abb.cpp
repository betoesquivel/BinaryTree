#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <class T>
class NodoArbol
{ public:
	T info;
	NodoArbol<T> *izq, *der;
	NodoArbol() { izq = der = NULL; }
	NodoArbol(T dato) { info = dato; izq = der = NULL; }
};

template <class T>
class ABB
{
private:
		NodoArbol<T> *raiz;
public:
		ABB() { raiz = NULL; }
		void inserta (T dato);
		bool existe (T dato);
		T obtenerValorMenor();
		T obtenerValorMayor();
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

template <class T>
T ABB<T>::obtenerValorMenor()
{
	NodoArbol<T> *actual = raiz;
	NodoArbol<T> *anterior = NULL;
	while(actual!=NULL)
	{
		anterior=actual;
		actual=actual->izq;
	}
	return anterior->info;
}
template <class T>
T ABB<T>::obtenerValorMayor()
{
	NodoArbol<T> *actual = raiz;
	NodoArbol<T> *anterior = NULL;
	while(actual!=NULL)
	{
		anterior=actual;
		actual=actual->der;
	}
	if(anterior==NULL)
		return NULL;
	return anterior->info;
}
int main()
{
	ABB<int> arbol;
	ifstream arch;
	string nomarch;
	int dato;
	cout << "Ingrese el nombre del archivo a cargar: ";
	cin >> nomarch;
	arch.open(nomarch.c_str());
	while (!arch.eof())
	{
		arch >> dato;
		arbol.inserta(dato);
	}
	arch.close();
	
	cout << "Dato a buscar: ";
	cin >> dato;
	if (arbol.existe(dato))
		cout << "El dato si existe";
	else
		cout << "El dato no existe";
	cin>>dato;
}
