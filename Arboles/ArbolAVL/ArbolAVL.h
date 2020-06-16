//
// Created by Shado on 10/10/2018.
//

#ifndef PRACTICA_10_ARBOLAVL_H
#define PRACTICA_10_ARBOLAVL_H

#include<iostream>
#include <fstream>
#include <sstream>
using namespace std;
/* Prototipo de la plantilla de la clase ArbolAVL. De esta forma, en la clase
NodoArbolAVL se podrá hacer referencia a ella. */

template <class T>
class ArbolAVL;

/* Declaración de la clase de un nodo de un árbol avl. Además de almacenar la
información, las direcciones de los hijos izquierdo y derecho, guarda el factor
de equilibrio. */
template <class T>
class NodoArbolAVL
{
private:
    NodoArbolAVL<T> *HijoIzq;
    NodoArbolAVL<T> *HijoDer;
    T Info;
    int FE;
public:
    NodoArbolAVL();
    T RegresaInfo();
    void ActualizaInfo(T);
    friend class ArbolAVL<T>;
};

/* Declaración del método constructor. Inicializa los apuntadores a ambos hijos
con el valor de NULL, indicando vacío. */
template <class T>
NodoArbolAVL<T>::NodoArbolAVL()
{
    HijoIzq=NULL;
    HijoDer=NULL;
}

/* Método que regresa la información almacenada en el nodo. */
template <class T>
T NodoArbolAVL<T>::RegresaInfo()
{
    return Info;
}

/* Método que permite actualizar la información almacenada en el nodo. */
template <class T>
void NodoArbolAVL<T>::ActualizaInfo(T Dato)
{
    Info=Dato;
}

/* Declaracion de la clase ArbolAVL. Se incluyen sólo los protoripos de los
métodos presentados anteriormente. */
template <class T>
class ArbolAVL
{
private:
    NodoArbolAVL<T> *Raiz;
public:
    ArbolAVL();
    NodoArbolAVL<T> *RegresaRaiz();
    NodoArbolAVL<T> *Busca(NodoArbolAVL<T> *, T);
    void InsertaAVL(T, NodoArbolAVL<T> *, int *);
    NodoArbolAVL<T> * RotacionHI_HD(NodoArbolAVL<T> *, NodoArbolAVL<T> *);
    NodoArbolAVL<T> * RotacionHD_HI(NodoArbolAVL<T> *, NodoArbolAVL<T> *);
    NodoArbolAVL<T> * RotacionHI_HI(NodoArbolAVL<T> *, NodoArbolAVL<T> *);
    NodoArbolAVL<T> * RotacionHD_HD(NodoArbolAVL<T> *, NodoArbolAVL<T> *);
    NodoArbolAVL<T> * ReestructuraI(NodoArbolAVL<T> *, int *);
    NodoArbolAVL<T> * ReestructuraD(NodoArbolAVL<T> *, int *);
    void EliminaAVL(NodoArbolAVL<T> *, NodoArbolAVL<T> *, int *, T);
    void Sustituye (NodoArbolAVL<T> *, NodoArbolAVL<T> *, int *);
    void Imprime(NodoArbolAVL<T> *, T);
};

/* Declaración del método constructor. Inicializa el apuntador a la raíz con el
valor NULL, indicando que el árbol está vacío. */
template <class T>
ArbolAVL<T>::ArbolAVL()
{
    Raiz=NULL;
}

/* Método que regresa el apuntador a la raíz de árbol. */
template <class T>
NodoArbolAVL<T> *ArbolAVL<T>::RegresaRaiz()
{
    return Raiz;
}

/* Método que busca un valor dado como parámetro en el árbol. Recibe como
parámetros el apuntador del nodo a visitar (la primera vez es la raíz) y el
dato a buscar. Regresa el apuntador al nodo donde lo encontró o NULL si no
está en el árbol. */
template <class T>
NodoArbolAVL<T> *ArbolAVL<T>::Busca(NodoArbolAVL<T> *Apuntador, T Dato)
{
    if (Apuntador !=NULL)
        if (Apuntador->Info==Dato)
            return Apuntador;
        else
        if (Apuntador->Info > Dato)
            return Busca(Apuntador->HijoIzq, Dato);
        else
            return Busca(Apuntador->HijoDer, Dato);
    else
        return NULL;
}

/* Método que imprime el contenido del árbol. Recibe como parámetro el
apuntador al nodo a visitar (la primera vez es la raíz del árbol).
Utiliza recorrido en-orden para que el contenido se imprima en orden
creciente. */
template <class T>
void ArbolAVL<T>::Imprime(NodoArbolAVL<T> *Apuntador, T num)
{
    if (Apuntador !=NULL)
    {
        if(Apuntador->HijoDer)
            Imprime(Apuntador->HijoDer, num+5);

        for(int i=0;i<num;i++){
            cout<<" ";
        }
        cout<<"{";
        cout<<" ---";
        cout<<Apuntador->Info<<endl;

        if(Apuntador->HijoIzq)
            Imprime(Apuntador->HijoIzq, num+5);
    }
}

/* Método que realiza la rotacion simple HI-HI en un árbol AVL. Además, reasigna
   el FE del nodo involucrado en la rotación. */
template <class T>
NodoArbolAVL<T> *ArbolAVL<T>::RotacionHI_HI(NodoArbolAVL<T> *Apunt, NodoArbolAVL<T> *ApAux1)
{
    Apunt->HijoIzq=ApAux1->HijoDer;
    ApAux1->HijoDer=Apunt;
    Apunt->FE=0;
    return ApAux1;
}

/* Método que realiza la rotación simple HD-HD en un árbol AVL. Además, reasigna
   el FE del nodo involucrado en la rotación. */
template <class T>
NodoArbolAVL<T> *ArbolAVL<T>::RotacionHD_HD(NodoArbolAVL<T> *Apunt, NodoArbolAVL<T> *ApAux1)
{
    Apunt->HijoDer=ApAux1->HijoIzq;
    ApAux1->HijoIzq=Apunt;
    Apunt->FE=0;
    return ApAux1;
}

/* Método que realiza la rotación compuesta HI-HD en un árbol AVL. Además,
   reasigna los FE de los nodos involucrados en la rotación. */
template <class T>
NodoArbolAVL<T> *ArbolAVL<T>::RotacionHI_HD(NodoArbolAVL<T> *Apunt, NodoArbolAVL<T> *ApAux1)
{
    NodoArbolAVL<T> *ApAux2;
    ApAux2=ApAux1->HijoDer;
    Apunt->HijoIzq=ApAux2->HijoDer;
    ApAux2->HijoDer=Apunt;
    ApAux1->HijoDer=ApAux2->HijoIzq;
    ApAux2->HijoIzq=ApAux1;
    if (ApAux2->FE==-1)
        Apunt->FE=1;
    else
        Apunt->FE=0;
    if (ApAux2->FE==1)
        ApAux1->FE=-1;
    else
        ApAux1->FE=0;
    return ApAux2;
}

/* Método que realiza la rotación compuesta HD-HI en un árbol AVL. Además,
   reasigna los FE de los nodos involucrados en la rotación. */
template <class T>
NodoArbolAVL<T> *ArbolAVL<T>::RotacionHD_HI(NodoArbolAVL<T> *Apunt, NodoArbolAVL<T> *ApAux1)
{
    NodoArbolAVL<T> *ApAux2;
    ApAux2=ApAux1->HijoIzq;
    Apunt->HijoDer=ApAux2->HijoIzq;
    ApAux2->HijoIzq=Apunt;
    ApAux1->HijoIzq=ApAux2->HijoDer;
    ApAux2->HijoDer=ApAux1;
    if (ApAux2->FE==1)
        Apunt->FE=-1;
    else
        Apunt->FE=0;
    if (ApAux2->FE==-1)
        ApAux1->FE=1;
    else
        ApAux1->FE=0;
    return ApAux2;
}

/* Método que inserta un nuevo elemento en un árbol AVL. Recibe como parámetros
   el dato a insertar, un apuntador al nodo a visitar (la primera vez es la
   raiz) y un entero (Band) que la primera vez tiene el valor 0. */
template <class T>
void ArbolAVL<T>::InsertaAVL(T Dato, NodoArbolAVL<T> *Apunt, int *Band)
{
    NodoArbolAVL<T> *ApAux1, *ApAux2;
    if (Apunt!=NULL)
    {
        if (Dato<Apunt->Info)
        {
            /* Se invoca el método con el subarbol izq.*/
            InsertaAVL(Dato, Apunt->HijoIzq, Band);
            Apunt->HijoIzq=Raiz;
            if (0<*Band)   /* Verifica si crecio el subarbol izquierdo.*/
                switch (Apunt->FE)
                {
                    case 1: {
                        Apunt->FE=0;
                        *Band=0;
                        break;
                    }
                    case 0: {
                        Apunt->FE=-1;
                        break;
                    }
                    case -1: {
                        ApAux1=Apunt->HijoIzq;
                        if (ApAux1->FE<=0)
                            Apunt=RotacionHI_HI(Apunt, ApAux1);
                        else
                            Apunt=RotacionHI_HD(Apunt, ApAux1);
                        Apunt->FE=0;
                        *Band=0;
                    }
                }
        }
        else
        if (Dato>Apunt->Info)
        {
            /* Invoca el método con el subarbol derecho. */
            InsertaAVL(Dato, Apunt->HijoDer, Band);
            Apunt->HijoDer=Raiz;
            if (0<*Band)   /* Verifica si crecio el subarbol derecho. */
                switch (Apunt->FE)
                {
                    case -1: {
                        Apunt->FE=0;
                        *Band=0;
                        break;
                    }
                    case 0: {
                        Apunt->FE=1;
                        break;
                    }
                    case 1: {
                        ApAux1=Apunt->HijoDer;
                        if (ApAux1->FE>=0)
                            Apunt=RotacionHD_HD(Apunt, ApAux1);
                        else
                            Apunt=RotacionHD_HI(Apunt, ApAux1);
                        Apunt->FE=0;
                        *Band=0;
                    }
                }
        }
        Raiz=Apunt;
    }
    else
    {
        /* Inserta un nuevo nodo y actualiza el valor de Band indicando que el
           arbol crecio. */
        ApAux2=new NodoArbolAVL<T>();
        ApAux2->Info=Dato;
        ApAux2->FE=0;
        *Band=1;
        Raiz=ApAux2;
    }
}

/* Metodo auxiliar del metodo EliminaAVL que reestructura el árbol cuando la
   altura de la rama izquierda ha disminuido. */
template <class T>
NodoArbolAVL<T>* ArbolAVL<T>::ReestructuraI(NodoArbolAVL<T> *Nodo, int *Aviso)
{
    NodoArbolAVL<T> *ApAux;
    if (*Aviso>0)
    {
        switch (Nodo->FE)
        {
            case -1: Nodo->FE=0;
                break;
            case 0:  Nodo->FE=1;
                break;
            case 1:  ApAux=Nodo->HijoDer;
                if (ApAux->FE>=0) // Rotacion HD-HD
                {
                    Nodo->HijoDer=ApAux->HijoIzq;
                    ApAux->HijoIzq=Nodo;
                    switch (ApAux->FE)
                    {
                        case 0: Nodo->FE=1;
                            ApAux->FE=-1;
                            *Aviso=0;
                            break;
                        case 1: Nodo->FE=0;
                            ApAux->FE=0;
                            break;
                    }
                    Nodo=ApAux;
                }
                else   // Rotacion HD-HI
                {
                    Nodo=RotacionHD_HI(Nodo, ApAux);
                    Nodo->FE=0;
                }
                break;
        }
    }
    return Nodo;
}

/* Metodo auxiliar del metodo EliminaAVL que reestructura el árbol cuando la
   altura de la rama derecha ha disminuido. */
template <class T>
NodoArbolAVL<T>* ArbolAVL<T>::ReestructuraD(NodoArbolAVL<T> *Nodo, int *Aviso)
{
    NodoArbolAVL<T> *ApAux;
    if (*Aviso>0)
    {
        switch (Nodo->FE)
        {
            case 1:  Nodo->FE=0;
                break;
            case 0:  Nodo->FE=-1;
                *Aviso=0;
                break;
            case -1: ApAux=Nodo->HijoIzq;
                if (ApAux->FE<=0) // Rotacion HI-HI
                {
                    Nodo->HijoIzq=ApAux->HijoDer;
                    ApAux->HijoDer=Nodo;
                    switch (ApAux->FE)
                    {
                        case 0: Nodo->FE=-1;
                            ApAux->FE=1;
                            *Aviso=0;
                            break;
                        case -1:Nodo->FE=0;
                            ApAux->FE=0;
                            break;
                    }
                    Nodo=ApAux;
                }
                else   // Rotacion HI-HD
                {
                    Nodo=RotacionHI_HD(Nodo, ApAux);
                    Nodo->FE=0;
                }
                break;
        }
    }
    return Nodo;
}

/* Método auxiliar del método EliminaAVL que sustituye el elemento que se desea
   eliminar por el que se encuentra más a la derecha del subárbol izquierdo. */
template <class T>
void ArbolAVL<T>::Sustituye(NodoArbolAVL<T> *Nodo, NodoArbolAVL<T> *ApAux, int *Avisa)
{
    if (Nodo->HijoDer!=NULL)
    {
        Sustituye(Nodo->HijoDer, ApAux, Avisa);
        if (ApAux->HijoIzq==NULL)
            Nodo->HijoDer=NULL;
        else
            Nodo->HijoDer=ApAux->HijoIzq;
        Nodo=ReestructuraD(Nodo, Avisa);
    }
    else
    {
        ApAux->Info=Nodo->Info;
        Nodo=Nodo->HijoIzq;
        *Avisa=1;
    }
    ApAux->HijoIzq=Nodo;
}

/* Método que elimina un elemento en un árbol AVL. Luego de la eliminación se
   actualizan los factores de equilibrio de cada nodo hasta la raíz y se
   reestructura el árbol si fuera necesario. */
template <class T>
void ArbolAVL<T>::EliminaAVL(NodoArbolAVL<T> *Apunt, NodoArbolAVL<T> *ApAnt, int *Avisa, T Dato)
{
    NodoArbolAVL<T> *ApAux;
    int Bandera;
    if (Apunt!=NULL)
        if (Dato<Apunt->Info)
        {
            if (*Avisa>0)
                Bandera=1;
            else
            if (*Avisa!=0)
                Bandera=-1;
            *Avisa=-1;
            EliminaAVL(Apunt->HijoIzq, Apunt, Avisa, Dato);
            Apunt=ReestructuraI(Apunt, Avisa);
            if (ApAnt!=NULL)
                switch(Bandera)
                {
                    case -1: ApAnt->HijoIzq=Apunt;
                        break;
                    case 1:  ApAnt->HijoDer=Apunt;
                        break;
                    default: break;
                }
            else
                Raiz=Apunt;
        }
        else
        {
            if (Dato>Apunt->Info)
            {
                if (*Avisa<0)
                    Bandera=-1;
                else
                if (*Avisa!=0)
                    Bandera=1;
                *Avisa=1;
                EliminaAVL(Apunt->HijoDer, Apunt, Avisa, Dato);
                Apunt=ReestructuraD(Apunt, Avisa);
                if (ApAnt!=NULL)
                    switch (Bandera)
                    {
                        case -1: ApAnt->HijoIzq=Apunt;
                            break;
                        case 1:  ApAnt->HijoDer=Apunt;
                            break;
                        default: break;
                    }
                else
                    Raiz=Apunt;
            }
            else
            {
                ApAux=Apunt;
                if (ApAux->HijoDer==NULL)
                {
                    Apunt=ApAux->HijoIzq;
                    if (*Avisa!=0)
                        if (*Avisa<0)
                            ApAnt->HijoIzq=Apunt;
                        else
                            ApAnt->HijoDer=Apunt;
                    else
                    if (Apunt==NULL)
                        Raiz=NULL;
                    else
                        Raiz=Apunt;
                    *Avisa=1;
                }
                else
                if (ApAux->HijoIzq==NULL)
                {
                    Apunt=ApAux->HijoDer;
                    if (*Avisa!=0)
                        if (*Avisa<0)
                            ApAnt->HijoIzq=Apunt;
                        else
                            ApAnt->HijoDer=Apunt;
                    else
                    if (Apunt==NULL)
                        Raiz=NULL;
                    else
                        Raiz=Apunt;
                    *Avisa=1;
                }
                else
                {
                    Sustituye(ApAux->HijoIzq, ApAux, Avisa);
                    Apunt=ReestructuraI(Apunt, Avisa);
                    if (ApAnt!=NULL)
                        if (*Avisa<=0)
                            ApAnt->HijoIzq=Apunt;
                        else
                            ApAnt->HijoDer=Apunt;
                    else
                        Raiz=Apunt;
                }
            }
        }
    else
        cout << "\n\nEl dato a eliminar no se encuentra!.\n\n";
}

#endif //PRACTICA_10_ARBOLAVL_H
