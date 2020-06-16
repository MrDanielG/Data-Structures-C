#include <iostream>
#include <string.h>

using namespace std;

/* Ejemplo que imprime los datos de los ascendientes femeninos de un individuo. Primero crea el �rbol geneal�gico 
   y posteriormente genera el reporte. */

// Definici�n de la clase Persona
class Persona
{
  private:
    int AgnoNac, Vive;
    char NomPers[64], LugNac[64];
  public:
    Persona();
    Persona(int, int, char[], char[]);
    friend istream & operator>> (istream & , Persona & );
    friend ostream & operator<< (ostream & , Persona & );
};

// Declaraci�n del m�todo constructor por omisi�n
Persona::Persona()
{
}

// Declaraci�n del m�todo constructor con par�metros
Persona::Persona(int ANac, int Vi, char NomP[], char LugN[])
{
	AgnoNac= ANac;
    Vive= Vi;
    strcpy(NomPers, NomP);
    strcpy(LugNac, LugN);
}

// Sobrecarga del operador >> para permitir la lectura de objetos tipo Persona de manera directa
istream & operator>>(istream & Lee, Persona & ObjPers)
{
    cout << "\n\nIngresa nombre de la Persona: ";
    Lee >> ObjPers.NomPers;
    cout << "\n\nIngresa agno de nacimiento: ";
    Lee >> ObjPers.AgnoNac;
    cout << "\n\nIngresa lugar de nacimiento: ";
    Lee >> ObjPers.LugNac;
    cout << "\n\n Esta viva?:";
    Lee >> ObjPers.Vive;
    return Lee;
}

// Sobrecarga del operador << para permitir la escritura de objetos tipo Persona de manera directa
ostream & operator<< (ostream & Escribe, Persona & ObjPers)
{
	Escribe << "\n\nDatos de la Persona\n";
    Escribe << "\nNombre: " << ObjPers.NomPers;
    Escribe << "\nLugar de nacimiento: " << ObjPers.LugNac;
    Escribe << "\nAgno de nacimiento: " << ObjPers.AgnoNac;
    if (ObjPers.Vive == 1)
       Escribe << "\nEsta viva.\n";
    else
       Escribe << "\nNo esta viva.\n";
    return Escribe;
}

// Prototipo de la plantilla de la clase ArbolBinario. As�, en la clase NodoArbol se podr� hacer referencia a ella
template <class T>
class ArbolBinario;

/* Declaraci�n de la clase NodoArbol. Cada nodo almacena la informaci�n que es la raz�n de ser de la estructura tipo 
   �rbol y las direcciones de su hijo izquierdo y de su hijo derecho. */
template <class T>
class NodoArbol
{
  private:
    T Info;
    NodoArbol<T> *HijoIzq;
    NodoArbol<T> *HijoDer;
  public:
    NodoArbol();
    T RegresaInfo();
    void ActualizaInfo(T);
    friend class ArbolBinario<T>;
};

/* Declaraci�n del m�todo constructor por omisi�n. Inicializa las ligas a los sub�rboles con el valor de NULL. Indica 
   nodo sin descendientes. */
template <class T>
NodoArbol<T>::NodoArbol()
{
    HijoIzq=NULL;
    HijoDer=NULL;
}

// M�todo que regresa la informaci�n almacenada en el nodo
template <class T>
T NodoArbol<T>::RegresaInfo()
{
    return Info;
}

//M�todo para actualizar la informaci�n almacenada en el nodo
template <class T>
void NodoArbol<T>::ActualizaInfo(T Dato)
{
    Info=Dato ;
}

// Declaraci�n de la clase ArbolBinario. Tiene un apuntador al nodo ra�z
template<class T>
class ArbolBinario
{
  private:
    NodoArbol<T> *Raiz;
  public:
    ArbolBinario();
    NodoArbol<T> *RegresaRaiz();
    void CreaArbol(NodoArbol<T> *);
    void ImprimeIzq(NodoArbol<T> *);
};

// Declaraci�n del m�todo constructor. Inicializa el puntero a la ra�z con el valor NULL. Indica que el �rbol est� vac�o
template <class T>
ArbolBinario<T>::ArbolBinario()
{
    Raiz=NULL;
}

// M�todo que regresa el valor del apuntador a la ra�z del �rbol
template <class T>
NodoArbol<T> *ArbolBinario<T>::RegresaRaiz()
{
    return Raiz;
}

// M�todo que crea un �rbol binario
template <class T>
void ArbolBinario<T>::CreaArbol(NodoArbol<T> *Apunt)
{
    char Resp;
    Apunt=new NodoArbol<T>;
    cout << "\n\nIntroduce la informacion a almacenar: ";
    cin >> Apunt->Info;
    cout << "\n\n" << Apunt->Info << " Tiene hijo izquierdo (S/N)? ";
    cin >> Resp;
    if (Resp == 's')
    {
       CreaArbol(Apunt->HijoIzq);
       Apunt->HijoIzq= Raiz;
    }
    cout << "\n\n" << Apunt->Info << " Tiene hijo derecho (S/N)? ";
    cin >> Resp;
    if (Resp == 's')
    {
       CreaArbol(Apunt->HijoDer);
       Apunt->HijoDer= Raiz;
    }
    Raiz=Apunt;
}

/* M�todo que imprime la informaci�n almacenada en las ra�ces de todos los sub�rboles izquierdos. La primera vez 
   recibe como dato la ra�z del �rbol. */
template <class T>
void ArbolBinario<T>::ImprimeIzq(NodoArbol<T> *Apunt)
{
    if (Apunt)
    {
        if (Apunt->HijoIzq)
        {
           cout << Apunt->HijoIzq->Info;
           ImprimeIzq(Apunt->HijoIzq);
        }
        ImprimeIzq(Apunt->HijoDer);
    }
}

int main()
{
    ArbolBinario<Persona> Genealogico;
    Persona Individuo;
    NodoArbol<Persona> *Ap;
    Ap=Genealogico.RegresaRaiz();
    // Se invoca el m�todo que crea el �rbol geneal�gico
    Genealogico.CreaArbol(Ap);
    Ap=Genealogico.RegresaRaiz();
    // Se recupera la informaci�n del individuo
    Individuo=Ap->RegresaInfo();
    cout << "\n\n\n_____________________________________ \n\n";
    cout << "Los ascendientes femeninos de: \n" << Individuo;
    cout << "\n\n_____________________________________ \n";
    // Se invoca el m�todo que imprime los datos de los ascendientes femeninos
    Genealogico.ImprimeIzq(Ap);
	return 0;
}
