#include <iostream>
#include <string.h>

using namespace std;

/* Ejemplo que imprime los datos de los ascendientes femeninos de un individuo. Primero crea el árbol genealógico 
   y posteriormente genera el reporte. */

// Definición de la clase Persona
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

// Declaración del método constructor por omisión
Persona::Persona()
{
}

// Declaración del método constructor con parámetros
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

// Prototipo de la plantilla de la clase ArbolBinario. Así, en la clase NodoArbol se podrá hacer referencia a ella
template <class T>
class ArbolBinario;

/* Declaración de la clase NodoArbol. Cada nodo almacena la información que es la razón de ser de la estructura tipo 
   árbol y las direcciones de su hijo izquierdo y de su hijo derecho. */
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

/* Declaración del método constructor por omisión. Inicializa las ligas a los subárboles con el valor de NULL. Indica 
   nodo sin descendientes. */
template <class T>
NodoArbol<T>::NodoArbol()
{
    HijoIzq=NULL;
    HijoDer=NULL;
}

// Método que regresa la información almacenada en el nodo
template <class T>
T NodoArbol<T>::RegresaInfo()
{
    return Info;
}

//Método para actualizar la información almacenada en el nodo
template <class T>
void NodoArbol<T>::ActualizaInfo(T Dato)
{
    Info=Dato ;
}

// Declaración de la clase ArbolBinario. Tiene un apuntador al nodo raíz
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

// Declaración del método constructor. Inicializa el puntero a la raíz con el valor NULL. Indica que el árbol está vacío
template <class T>
ArbolBinario<T>::ArbolBinario()
{
    Raiz=NULL;
}

// Método que regresa el valor del apuntador a la raíz del árbol
template <class T>
NodoArbol<T> *ArbolBinario<T>::RegresaRaiz()
{
    return Raiz;
}

// Método que crea un árbol binario
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

/* Método que imprime la información almacenada en las raíces de todos los subárboles izquierdos. La primera vez 
   recibe como dato la raíz del árbol. */
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
    // Se invoca el método que crea el árbol genealógico
    Genealogico.CreaArbol(Ap);
    Ap=Genealogico.RegresaRaiz();
    // Se recupera la información del individuo
    Individuo=Ap->RegresaInfo();
    cout << "\n\n\n_____________________________________ \n\n";
    cout << "Los ascendientes femeninos de: \n" << Individuo;
    cout << "\n\n_____________________________________ \n";
    // Se invoca el método que imprime los datos de los ascendientes femeninos
    Genealogico.ImprimeIzq(Ap);
	return 0;
}
