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
		int obtenerNivel(T dato);
		T obtenerAbuelo(T dato);
		void obtenerAntepasados(T dato);
		void obtenerAntepasadosComunes(T dato1, T dato2);
		void obtenerPrimos(T dato);

		int contarNodosPadre(NodoArbol<T> *inicial);
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
int ABB<T>::obtenerNivel(T dato)
{
	NodoArbol<T> *aux = raiz;
	int nivel = 0; 
	while (aux != NULL && aux->info != dato)
	{
		aux = (dato < aux->info? aux->izq : aux->der);
		nivel++;
	}
	if(!(aux == NULL))
	{
		return nivel;
	}else
	{
		return -1;
	}
}
template <class T>
T ABB<T>::obtenerAbuelo(T dato)
{
	NodoArbol<T> *aux = raiz;
	NodoArbol<T> *padre = NULL;
	NodoArbol<T> *abuelo = NULL;
	while (aux != NULL && aux->info != dato)
	{
		abuelo = padre; 
		padre = aux; 
		aux = (dato < aux->info? aux->izq : aux->der);
	}
	if(abuelo != NULL)
	{
		return abuelo->info;
	}else
	{
		return -1;
	}
}
template <class T>
void ABB<T>::obtenerAntepasados(T dato)
{
	NodoArbol<T> *aux = raiz;
	while (aux != NULL && aux->info != dato)
	{
		cout<<aux->info<<endl;
		aux = (dato < aux->info? aux->izq : aux->der);
	}
}
template <class T>
void ABB<T>::obtenerAntepasadosComunes(T dato1, T dato2)
{
	NodoArbol<T> *trayecto1 = raiz;
	NodoArbol<T> *trayecto2 = raiz;
	while (trayecto1 != NULL && trayecto2 != NULL && trayecto1->info != dato1 && trayecto2->info != dato2)
	{
		if(trayecto1==trayecto2)
			cout<<trayecto1->info<<endl;
		trayecto1 = (dato1 < trayecto1->info? trayecto1->izq : trayecto1->der);
		trayecto2 = (dato2 < trayecto2->info? trayecto2->izq : trayecto2->der);
	}
}
template <class T>
void ABB<T>::obtenerPrimos(T dato)
{
	NodoArbol<T> *aux = raiz;
	NodoArbol<T> *padre = NULL;
	NodoArbol<T> *abuelo = NULL;
	while (aux != NULL && aux->info != dato)
	{
		abuelo = padre; 
		padre = aux; 
		aux = (dato < aux->info? aux->izq : aux->der);
	}
	if(abuelo != NULL)
	{
		aux = abuelo;
		aux = (aux->izq !=  padre? aux->izq : aux->der);
		if(aux!=NULL)
		{
			if(aux->izq != NULL)
				cout<<aux->izq->info<<' ';
			if(aux->der != NULL)
				cout<<aux->der->info<<' ';
			cout<<endl;
		}
	}
}

template <class T>
int contarNodosPadre(NodoArbol<T> *inicial, int contadorNodos)
{
	if(inicial!=NULL)
	{
		if(inicial->der!=NULL)
		{
			contadorNodos = contarNodosPadre(inicial->der, contadorNodos);
		}
		if(inicial->izq!=NULL)
		{
			contadorNodos = contarNodosPadre(inicial->izq, contadorNodos);
		}
	}
	return contadorNodos;
	
}

template <class T>
T ABB<T>::obtenerValorMenor()
{
	NodoArbol<T> *actual = raiz;
	while(actual->izq == NULL)
	{
		actual=actual->izq;
	}
	if(actual==NULL)
		return NULL;
	return actual->info;
}
template <class T>
T ABB<T>::obtenerValorMayor()
{
	NodoArbol<T> *actual = raiz;
	while(actual->der == NULL)
	{
		actual=actual->der;
	}
	if(actual==NULL)
		return NULL;
	return actual->info;
}
int main()
{
	ABB<int> arbol;
	ifstream arch;
	string nomarch;
	int dato;
	cout << "Ingrese el nombre del archivo a cargar: "<<endl;
	cin >> nomarch;
	arch.open(nomarch.c_str());
	while (!arch.eof())
	{
		arch >> dato;
		arbol.inserta(dato);
	}
	arch.close();

	cout<< "Contando nodos."<<endl;
	contarNodosPadre(arbol.raiz,0);
	
}
