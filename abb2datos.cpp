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
	T info;
	int repeticiones;
	NodoArbol<T> *izq, *der;
	NodoArbol() { izq = der = NULL; }
	NodoArbol(T dato){ info = dato; repeticiones = 0; izq = der = NULL; }
};

template <class T>
class ABB
{
private:
		NodoArbol<T> *raiz;
public:
		ABB() { raiz = NULL; }
		NodoArbol<T>* getRaiz(){return raiz;}
		void insertarDatoRecursivamente(NodoArbol<T> *inicial, T dato);
		void desplegarArbol(NodoArbol<T> *inicial);
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
void ABB<T>::insertarDatoRecursivamente(NodoArbol<T> *inicial, T dato)
{
	if(inicial!=NULL)
	{
		if(inicial->info == dato)
		{
			inicial->repeticiones += 1;

		}
		else if(dato < inicial->info)
		{
			if(inicial->izq != NULL)
			{
				insertarDatoRecursivamente(inicial->izq, dato);
			}
			else
			{
				NodoArbol<T> *nuevo = new NodoArbol<T>(dato);
				inicial->izq = nuevo;
			}

		}
		else
		{
			if(inicial->der != NULL)
			{
				insertarDatoRecursivamente(inicial->der, dato);
			}
			else
			{
				NodoArbol<T> *nuevo = new NodoArbol<T>(dato);
				inicial->der = nuevo;
			}
		}
	}
	else
	{
		NodoArbol<T> *nuevo = new NodoArbol<T>(dato);
		raiz = nuevo;
	}
}

template <class T>
void ABB<T>::desplegarArbol(NodoArbol<T> *inicial)
{

	if(inicial!=NULL)
	{
		desplegarArbol(inicial->izq);
		if(inicial->repeticiones == 0)
		{
			cout<<inicial->info<<endl;
		}
		else
		{
			for(int i = 0; i<inicial->repeticiones; i++) 
				cout<<inicial->info<<' ';
			cout<<endl;
		}
		desplegarArbol(inicial->der);
	}
}
int main()
{
	ABB<int> arbol;
	ifstream arch;
	ofstream archivoSalida;
	string nomarch;
	int dato;
	cout << "Ingrese el nombre del archivo a cargar: "<<endl;
	cin >> nomarch;

	arch.open(nomarch.c_str());
	while (!arch.eof())
	{
		arch >> dato;
		arbol.insertarDatoRecursivamente(arbol.getRaiz(), dato);
	}
	arch.close();

	cout<<"Este es el arbol guardado en el archivo: "<<endl;
	arbol.desplegarArbol(arbol.getRaiz());

	int decision; 
	cout<<"\nDesea insertar mas datos al arbol? \n1)Si \n2) No"<<endl;
	cin>>decision;
	archivoSalida.open(nomarch.c_str(), ios::app);
	while(decision==1)
	{
		cout<<"Inserte un dato entero:"<<endl;
		cin>>dato;

		archivoSalida<<dato<<endl;
		arbol.insertarDatoRecursivamente(arbol.getRaiz(), dato);

		cout<<"\nDesea insertar mas datos al arbol? \n1)Si \n2)No"<<endl;
		cin>>decision;
	}
	archivoSalida.close();

	cout<<"Este es el arbol modificado guardado en el archivo: "<<endl;
	arbol.desplegarArbol(arbol.getRaiz());
}
