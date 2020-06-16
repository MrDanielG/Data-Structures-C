#include <iostream>

#define MAX 20

using namespace std;


/* Este método busca una solución (estado final) de un problema representado por medio de un grafo. Recibe 
  como parámetro el nivel máximo de profundidad permitido. En esta implementación se considera el estado final 
  como el último vértice del grafo. Regresa uno si llega al estado meta y cero en caso contrario. En el método 
  se usan los atributos definidos en la clase GrafoND . Se declaran tres objetos de la clase Lista para almacenar 
  los vértices que se van visitando y los pendientes de visitar, así como una lista auxiliar para guardar los 
  vértices adyacentes de uno dado. */

template <class T>
int GrafoND<T>::Profundidad(int NivelProf)
{
	int Indice, EstadoFinal=0, VisitaAux[MAX], Resp=1;
	Lista<T> Visitado, NoVisitado, ListaAux;
	T Vertix;
	
	for (Indice=0; Indice < NumVer; Indice++) 
	   VisitaAux[Indice]=0;
	   
    /* Se guarda el primer vértice (representa el estado inicial) del grafo en la lista NoVisitado. */ 
	NoVisitado.InsertaFinal(Vertices[0]);

    /* En el arreglo auxiliar VisitaAux se indica que el primer vértice ya fue visitado, para evitar caer en ciclos. */ 
	VisitaAux[0]=1;
    
	/* Se repiten los pasos del algoritmo de búsqueda mientras no se llegue al estado final y mientras queden 
	   elementos en la lista NoVisitado . */ 
	Indice=0;
	while (!NoVisitado.ListaVacia() && !EstadoFinal)
	{
		// Se saca el primer elemento de NoVisitado
		Vertix=NoVisitado.Elimina();
		
		// Se evalúa si el vértice no está en Visitado y si no se alcanzó la profunidad límite.
		if (!Visitado.BuscaDesordenada(Vertix) && Indice < NivelProf)
		{
			Visitado.InsertaFinal(Vertix);
			// Se obtienen sus vertices adyacentes
			ListaAux=VerticesAdyacentes(BuscaVertice(Vertix));
			while (!ListaAux.ListaVacia() && !EstadoFinal)
			{
				Vertix=ListaAux.Elimina();
				if (BuscaVertice(Vertix) != NumVer-1 && !VisitaAux[BuscaVertice(Vertix)])
				{
					NoVisitado.InsertaInicio(Vertix);
					VisitaAux[BuscaVertice(Vertix)]=1;
				}
				// Se evalúa si se llegó al último vértice (representa el estado final)
				else
				    if (BuscaVertice(Vertix) == NumVer-1)
					{
						Visitado.InsertaFinal(Vertix);
						EstadoFinal=1;
					} 
			}
			Indice++;
		}
	}
	// Si se llegó al estado final se imprime la secuencia de vértices visitados
	if (EstadoFinal)
	   Visitado.ImprimeIterativo();
	else
	   Resp=0;
	return Resp;          
}

/* Métopdo entero que determina si un vértice dado como parámetro es o no un vértice del grafo. Regresa la 
   posición en la que lo encuentra o un negativo. */
template <class T>
int GrafoND<T>::BuscaVertice(T VertiDato)
{
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
Lista<T> GrafoND<T>::VericesAdyacentes(int VertiDato)
{
	int Indice;
	Lista<T> Adyacentes;
	
	for (Indice=0; Indice < NumVer; Indice++)
	   if (MatAdy[VertiDato][Indice] !=0)
	       Adyacentes.InsertaFinal(Vertices[Indice]);
	return Adyacentes;       
}

/* Este método busca una solución (estado final) de un problema representado por medio de un grafo. Visita todos los
   vértices de un mismo nivel antes de pasar al siguiente. Regresa uno si llega al estado meta o cero en caso contrario.
   Se usan atributos de la clase como el número y nombre de los vértices. Además, se declaran tres objetos de la clase
   Lista para almacenar los vértices visitados, los pendientes de visitar y los adyacentes de un nodo dado. */
template <class T>
int GrafoND<T>::Anchura()
{
	int Indice, EstadoFinal=0, VisitaAux[MAX], Resp=1;
	Lista<T> NoVisitado, Visitado, ListaAux;
	T Vertix;
	
	// El arreglo VisitaAux es un arreglo en el cual se indica si un nodo ya fue expandido.
	for (Indice=0; Indice < NumVer; Indice++)
	   VisitaAux[Indice]=0;
	
	// Se guarda el primer vértice del grafo en la lista NoVisitado
	NoVisitado.InsertaFinal(Vertices[0]);
	VisitaAux[0] =1;
	
	// Ciclo que se ejecuta mientras no se llegue al estado final y queden vértices por visitar
	while (!NoVisitado.ListaVacia() && !EstadoFinal)
	{
		// Saca el primer vértice de la lista NoVisitado
		Vertix=NoVisitado.Elimina();
		
		// Se evalúa que el vértice no esté en la lista Visitado para evitar ciclos
		if (!Visitado.BuscaDesordenada(Vertix))
		{
			Visitado.InsertaFinal(Vertix);
			// Se obtienen los vértices adyacentes del vértice visitado
			ListaAux=VerticesAdyacentes(BuscaVertice(Vertix));
			
			while (!ListaAux.ListaVacia() && !EstadoFinal)
			{
				Vertix=ListaAux.Elimina();
				// Si el sucesor no es el estado final y no está en Visitado entonces se guarda en la lista
				// NoVisitado para que posteriormente se revise.
				if (BuscaVertice(Vertix) != NumVer-1 && !VisitaAux[BuscaVertice(Vertix)])
				{
					NoVisitado.InsertaFinal(Vertix);
					VisitaAux[BuscaVertice(Vertix)]=1;
				}
				else
				    if (BuscaVertice(Vertix) == NumVer-1)
				    {
				    	Visitado.InsertaFinal(Vertix);
				    	EstadoFinal=1;
					}
			}
		}
	}
	// Si se llegó al estado final se imprime la secuencia de vértices visitados
	if (EstadoFinal)
	{
		Visitado.ImprimeIterativo();
		return 1;
	}
	else
	    Resp=0;
	return Resp;	  
}   



int main() 
{
	return 0;
}
