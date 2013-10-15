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
		NodoArbol<T>* getRaiz(){return raiz;}
		void inserta (T dato);
		bool existe (T dato);
		int obtenerNivel(T dato);
		T obtenerAbuelo(T dato);
		void obtenerAntepasados(T dato);
		void obtenerAntepasadosComunes(T dato1, T dato2);
		void obtenerPrimos(T dato);

		int contarNodosPadre(NodoArbol<T> *inicial);
		void desplegarArbol(NodoArbol<T> *inicial);
		int obtenerNivelRecursivamente(NodoArbol<T> *inicial);
		int contarNodos(NodoArbol<T> *inicial);
		double calcularPromedio(NodoArbol<T> *inicial, int numeroDeNodos);

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

//TAREA PARA EL JUEVES
template <class T>
int ABB<T>::contarNodosPadre(NodoArbol<T> *inicial)
{
	if(inicial!=NULL)
	{
		if(inicial->izq != NULL || inicial->der != NULL)
			return 1+contarNodosPadre(inicial->izq)+contarNodosPadre(inicial->der);
		else
			return 0;
	}else
	{
		return 0;
	}
}

template <class T>
void ABB<T>::desplegarArbol(NodoArbol<T> *inicial)
{

	if(inicial!=NULL)
	{
		if(inicial->izq != NULL || inicial->der != NULL)
			cout<<"Padre: "<<inicial->info<<endl;
		else
			cout<<"Hoja: "<<inicial->info<<endl;
		desplegarArbol(inicial->izq);
		desplegarArbol(inicial->der);
	}
}

template <class T>
int ABB<T>::obtenerNivelRecursivamente(NodoArbol<T> *inicial)
{
	int nivel_izquierdo, nivel_derecho;
	if(inicial!=NULL)
	{
		nivel_izquierdo = obtenerNivelRecursivamente(inicial->izq);
		nivel_derecho = obtenerNivelRecursivamente(inicial->der);
		return (nivel_izquierdo > nivel_derecho) ? (nivel_izquierdo+1):(nivel_derecho+1);
	}
	else
	{
		return 0;
	}
}

template <class T>
int ABB<T>::contarNodos(NodoArbol<T> *inicial)
{
	if(inicial!=NULL)
	{
		return 1+contarNodos(inicial->izq)+contarNodos(inicial->der);
	}else
	{
		return 0;
	}
}

template <class T>
double ABB<T>::calcularPromedio(NodoArbol<T> *inicial, int numeroDeNodos)
{
	if(inicial!=NULL)
	{
		return (inicial->info)*(1.00)/numeroDeNodos + calcularPromedio(inicial->izq, numeroDeNodos) + calcularPromedio(inicial->der, numeroDeNodos);

	}else
	{
		return 0;
	}
}
//FIN DE TAREA PARA EL JUEVES
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

	cout<<"Contando nodos padre:"<<endl;
	cout<<arbol.contarNodosPadre(arbol.getRaiz())<<endl;
	cout<<arbol.contarNodosPadre(arbol.getRaiz()->der)<<endl;
	
	//cout<<"Despliego arbol: "<<endl;
	//arbol.desplegarArbol(arbol.getRaiz());

	cout<<"Contando niveles del arbol:"<<endl;
	cout<<arbol.obtenerNivelRecursivamente(arbol.getRaiz())<<endl;
	cout<<arbol.obtenerNivelRecursivamente(arbol.getRaiz()->izq)<<endl;
	cout<<arbol.obtenerNivelRecursivamente(arbol.getRaiz()->der)<<endl;

	cout<<"Calcular promedio:"<<endl;
	cout<<arbol.calcularPromedio(arbol.getRaiz(),arbol.contarNodos(arbol.getRaiz()))<<endl;
	cout<<arbol.calcularPromedio(arbol.getRaiz()->izq,arbol.contarNodos(arbol.getRaiz()->izq))<<endl;
	
}
