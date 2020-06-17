#include <iostream>

#define MAX 20

#include "Lista.h"

using namespace std;


/* Este método busca una solución (estado final) de un problema representado por medio de un grafo. Recibe
  como parámetro el nivel máximo de profundidad permitido. En esta implementación se considera el estado final
  como el último vértice del grafo. Regresa uno si llega al estado meta y cero en caso contrario. En el método
  se usan los atributos definidos en la clase GrafoND . Se declaran tres objetos de la clase Lista para almacenar
  los vértices que se van visitando y los pendientes de visitar, así como una lista auxiliar para guardar los
  vértices adyacentes de uno dado. */


  template<class T>
class GrafoND
{
   private:
      T MatAdy[MAX][MAX];
      int NumVer, Vertices[MAX];
   public:

	  GrafoND();
	  void Lee();
	  void graph_default();

	  int Profundidad(int);
	  int BuscaVertice(T);
	  void VerticesAdyacentes(int, Lista<T>*);
	  int Anchura();
};

template<class T>
GrafoND<T>::GrafoND(){
	int Ind1, Ind2;
	for (Ind1=0; Ind1<MAX; Ind1++)
       for (Ind2=0; Ind2<MAX; Ind2++)
          if (Ind1 != Ind2)
             MatAdy[Ind1][Ind2]=999;
          else
             MatAdy[Ind1][Ind2]=0;
    NumVer=0;
}

template <class T>
void GrafoND<T>::graph_default(){
    NumVer=6;
    for(int i=0; i<NumVer; i++)
        Vertices[i]=i+1;

//    MatAdy[1 -1][2 -1]= 3;
//    MatAdy[1 -1][5 -1]= 2;
//    MatAdy[1 -1][6 -1]= 5;
//    MatAdy[2 -1][6 -1]= 3;
//    MatAdy[2 -1][3 -1]= 1;
//    MatAdy[3 -1][4 -1]= 3;
//    MatAdy[3 -1][6 -1]= 2;
//    MatAdy[5 -1][4 -1]= 2;
//    MatAdy[6 -1][4 -1]= 3;
//    MatAdy[6 -1][5 -1]= 3;
//
//    MatAdy[2 -1][1 -1]= 3;
//    MatAdy[5 -1][1 -1]= 2;
//    MatAdy[6 -1][1 -1]= 5;
//    MatAdy[6 -1][2 -1]= 3;
//    MatAdy[3 -1][2 -1]= 1;
//    MatAdy[4 -1][3 -1]= 3;
//    MatAdy[6 -1][3 -1]= 2;
//    MatAdy[4 -1][5 -1]= 2;
//    MatAdy[4 -1][6 -1]= 3;
//    MatAdy[5 -1][6 -1]= 3;

    MatAdy[1 -1][2 -1]= 3;
    MatAdy[1 -1][5 -1]= 2;
    MatAdy[1 -1][6 -1]= 2;
    MatAdy[2 -1][5 -1]= 3;
    MatAdy[2 -1][3 -1]= 1;
    MatAdy[3 -1][5 -1]= 3;
    MatAdy[3 -1][4 -1]= 2;
    MatAdy[5 -1][4 -1]= 2;
    MatAdy[5 -1][6 -1]= 3;
    MatAdy[6 -1][4 -1]= 3;

    MatAdy[2 -1][1 -1]= 3;
    MatAdy[5 -1][1 -1]= 2;
    MatAdy[6 -1][1 -1]= 2;
    MatAdy[5 -1][2 -1]= 3;
    MatAdy[3 -1][2 -1]= 1;
    MatAdy[5 -1][3 -1]= 3;
    MatAdy[4 -1][3 -1]= 2;
    MatAdy[4 -1][5 -1]= 2;
    MatAdy[6 -1][5 -1]= 3;
    MatAdy[4 -1][6 -1]= 3;

}

// las listas se usaran como pilas
template <class T>
int GrafoND<T>::Profundidad(int NivelProf){
	int Indice=0, EstadoFinal=0, VisitaAux[MAX], Resp=1, plok, posicion;
	Lista<T> Visitado, NoVisitado, ListaAux;
	T Vertix;

	for (Indice=0; Indice < NumVer; Indice++)
	   VisitaAux[Indice]=0;

    /* Se guarda el primer vértice (representa el estado inicial) del grafo en la lista NoVisitado. */
	NoVisitado.InsertaFinal(Vertices[0]);

    /* En el arreglo auxiliar VisitaAux se indica que el primer vértice ya fue visitado, para evitar caer en ciclos. */
	VisitaAux[0]=1;

	while (Indice <= NivelProf){
	    Indice++;

        Vertix=NoVisitado.RegresaPrimero()->RegresaInfo();
        plok=NoVisitado.EliminaPrimero();

        Visitado.InsertaFinal(Vertix);
        posicion=BuscaVertice(Vertix);
        VisitaAux[posicion]=1;

        VerticesAdyacentes(posicion, &ListaAux);

        cout << "\n Vertice [ " << Vertix << " ] lista adyaciencia: ";
        ListaAux.ImprimeIterativo();

        if(NoVisitado.vacia()){
            while(!ListaAux.vacia()){
                    Vertix=ListaAux.RegresaPrimero()->RegresaInfo();
                    plok=ListaAux.EliminaPrimero();
                    if(!VisitaAux[BuscaVertice(Vertix)])
                        NoVisitado.InsertaFinal(Vertix);
                    //NoVisitado.ImprimeIterativo();
            }
        }
        else
        {
            T VerticeBan=NoVisitado.RegresaPrimero()->RegresaInfo(), repetido;
            while(!ListaAux.vacia()){
                Vertix=ListaAux.RegresaPrimero()->RegresaInfo();
                plok=ListaAux.EliminaPrimero();
                if(!VisitaAux[BuscaVertice(Vertix)]){
//                    if(Vertix == VerticeBan && ListaAux.RegresaPrimero()){

                    if(Vertix == VerticeBan && !ListaAux.vacia()){
                        repetido=Vertix;
                        Vertix=ListaAux.RegresaPrimero()->RegresaInfo();
                        plok=ListaAux.EliminaPrimero();
                        NoVisitado.InsertaAntes(Vertix, VerticeBan);
                        NoVisitado.InsertaAntes(repetido, Vertix);
                    }
                    else
                    {
                        NoVisitado.InsertaAntes(Vertix, VerticeBan);
                    }
//                        NoVisitado.InsertaAntes(Vertix, VerticeBan);
                }
                //NoVisitado.ImprimeIterativo();
            }
        }
	}
	cout << "\n Recorrido del DFS (Deph First Search): ";
	Visitado.ImprimeIterativo();
}

/* Métopdo entero que determina si un vértice dado como parámetro es o no un vértice del grafo. Regresa la
   posición en la que lo encuentra o un negativo. */
template <class T>
int GrafoND<T>::BuscaVertice(T VertiDato){
	int Indice=0, Resp=-1;

	// Busca el nombre del vértice dado en el arreglo que guarda los nombres de todos los vértices del grafo
	while (Indice < NumVer && Vertices[Indice] != VertiDato)
	   Indice++;
	if (Indice < NumVer)
	   Resp=Indice;
	return Resp;
}

/* Método que genera una lista con los vértices adyacentes de un vértice dado como parámetro. Recibe como parámetro
   el nombre de un vértice y da como resultado una lista con sus vértices adyacentes. */
template <class T>
void GrafoND<T>::VerticesAdyacentes(int VertiDato, Lista<T> *ploks){
    ploks->~Lista();
	for (int Indice=0; Indice < NumVer; Indice++)
	   if (MatAdy[VertiDato][Indice] !=0 && MatAdy[VertiDato][Indice] !=999)
            ploks->InsertaFinal(Vertices[Indice]);
}

/* Este método busca una solución (estado final) de un problema representado por medio de un grafo. Visita todos los
   vértices de un mismo nivel antes de pasar al siguiente. Regresa uno si llega al estado meta o cero en caso contrario.
   Se usan atributos de la clase como el número y nombre de los vértices. Además, se declaran tres objetos de la clase
   Lista para almacenar los vértices visitados, los pendientes de visitar y los adyacentes de un nodo dado. */
template <class T>
int GrafoND<T>::Anchura(){
	int Indice, EstadoFinal=0, VisitaAux[MAX], Resp=1, plok, posicion;
	Lista<T> NoVisitado, Visitado, ListaAux, cont;
	T Vertix;

	// El arreglo VisitaAux es un arreglo en el cual se indica si un nodo ya fue expandido.
	for (Indice=0; Indice < NumVer; Indice++)
	   VisitaAux[Indice]=0;

	// Se guarda el primer vértice del grafo en la lista NoVisitado
	NoVisitado.InsertaFinal(Vertices[0]);
	VisitaAux[0] =1;

    while (!NoVisitado.vacia()){

        Vertix=NoVisitado.RegresaPrimero()->RegresaInfo();
        plok=NoVisitado.EliminaPrimero();

        Visitado.InsertaFinal(Vertix);
        posicion=BuscaVertice(Vertix);

        VerticesAdyacentes(posicion, &ListaAux);

        cout << "\n Vertice [ " << Vertix << " ] lista adyaciencia: ";
        ListaAux.ImprimeIterativo();

        if(NoVisitado.vacia()){
            while(!ListaAux.vacia()){
                    Vertix=ListaAux.RegresaPrimero()->RegresaInfo();
                    plok=ListaAux.EliminaPrimero();
                    posicion=BuscaVertice(Vertix);
                    if(!VisitaAux[posicion])
                        NoVisitado.InsertaFinal(Vertix);
                    VisitaAux[posicion]=1;
                    //NoVisitado.ImprimeIterativo();
            }
        }
        else
        {
            T VerticeBan=NoVisitado.RegresaPrimero()->RegresaInfo(), repetido;
            while(!ListaAux.vacia()){
                Vertix=ListaAux.RegresaPrimero()->RegresaInfo();
                plok=ListaAux.EliminaPrimero();
                posicion=BuscaVertice(Vertix);
                if(!VisitaAux[posicion])
                    NoVisitado.InsertaFinal(Vertix);
                VisitaAux[posicion]=1;
                //NoVisitado.ImprimeIterativo();
            }
        }
	}
	cout << "\n Recorrido del BFS (Breadth First Search): ";
	Visitado.ImprimeIterativo();
}


int main()
{
    GrafoND<int> ploks;
    ploks.graph_default();
    ploks.Profundidad(11);
    cout << "\n\n\n" << endl;
    ploks.Anchura();
	return 0;
}
