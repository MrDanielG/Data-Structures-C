#include <iostream>

#define MAX 20

using namespace std;


/* Este m�todo busca una soluci�n (estado final) de un problema representado por medio de un grafo. Recibe 
  como par�metro el nivel m�ximo de profundidad permitido. En esta implementaci�n se considera el estado final 
  como el �ltimo v�rtice del grafo. Regresa uno si llega al estado meta y cero en caso contrario. En el m�todo 
  se usan los atributos definidos en la clase GrafoND . Se declaran tres objetos de la clase Lista para almacenar 
  los v�rtices que se van visitando y los pendientes de visitar, as� como una lista auxiliar para guardar los 
  v�rtices adyacentes de uno dado. */

template <class T>
int GrafoND<T>::Profundidad(int NivelProf)
{
	int Indice, EstadoFinal=0, VisitaAux[MAX], Resp=1;
	Lista<T> Visitado, NoVisitado, ListaAux;
	T Vertix;
	
	for (Indice=0; Indice < NumVer; Indice++) 
	   VisitaAux[Indice]=0;
	   
    /* Se guarda el primer v�rtice (representa el estado inicial) del grafo en la lista NoVisitado. */ 
	NoVisitado.InsertaFinal(Vertices[0]);

    /* En el arreglo auxiliar VisitaAux se indica que el primer v�rtice ya fue visitado, para evitar caer en ciclos. */ 
	VisitaAux[0]=1;
    
	/* Se repiten los pasos del algoritmo de b�squeda mientras no se llegue al estado final y mientras queden 
	   elementos en la lista NoVisitado . */ 
	Indice=0;
	while (!NoVisitado.ListaVacia() && !EstadoFinal)
	{
		// Se saca el primer elemento de NoVisitado
		Vertix=NoVisitado.Elimina();
		
		// Se eval�a si el v�rtice no est� en Visitado y si no se alcanz� la profunidad l�mite.
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
				// Se eval�a si se lleg� al �ltimo v�rtice (representa el estado final)
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
	// Si se lleg� al estado final se imprime la secuencia de v�rtices visitados
	if (EstadoFinal)
	   Visitado.ImprimeIterativo();
	else
	   Resp=0;
	return Resp;          
}

/* M�topdo entero que determina si un v�rtice dado como par�metro es o no un v�rtice del grafo. Regresa la 
   posici�n en la que lo encuentra o un negativo. */
template <class T>
int GrafoND<T>::BuscaVertice(T VertiDato)
{
	int Indice=0, Resp=-1;
	
	// Busca el nombre del v�rtice dado en el arreglo que guarda los nombres de todos los v�rtices del grafo
	while (Indice < NumVer && Vertices[Indice] != VertiDato)
	   Indice++;
	if (Indice < NumVer)
	   Resp=Indice;
	return Resp;      
}

/* M�todo que genera una lista con los v�rtices adyacentes de un v�rtice dado como par�metro. Recibe como par�metro
   el nombre de un v�rtice y da como resultado una lista con sus v�rtices adyacentes. */
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

/* Este m�todo busca una soluci�n (estado final) de un problema representado por medio de un grafo. Visita todos los
   v�rtices de un mismo nivel antes de pasar al siguiente. Regresa uno si llega al estado meta o cero en caso contrario.
   Se usan atributos de la clase como el n�mero y nombre de los v�rtices. Adem�s, se declaran tres objetos de la clase
   Lista para almacenar los v�rtices visitados, los pendientes de visitar y los adyacentes de un nodo dado. */
template <class T>
int GrafoND<T>::Anchura()
{
	int Indice, EstadoFinal=0, VisitaAux[MAX], Resp=1;
	Lista<T> NoVisitado, Visitado, ListaAux;
	T Vertix;
	
	// El arreglo VisitaAux es un arreglo en el cual se indica si un nodo ya fue expandido.
	for (Indice=0; Indice < NumVer; Indice++)
	   VisitaAux[Indice]=0;
	
	// Se guarda el primer v�rtice del grafo en la lista NoVisitado
	NoVisitado.InsertaFinal(Vertices[0]);
	VisitaAux[0] =1;
	
	// Ciclo que se ejecuta mientras no se llegue al estado final y queden v�rtices por visitar
	while (!NoVisitado.ListaVacia() && !EstadoFinal)
	{
		// Saca el primer v�rtice de la lista NoVisitado
		Vertix=NoVisitado.Elimina();
		
		// Se eval�a que el v�rtice no est� en la lista Visitado para evitar ciclos
		if (!Visitado.BuscaDesordenada(Vertix))
		{
			Visitado.InsertaFinal(Vertix);
			// Se obtienen los v�rtices adyacentes del v�rtice visitado
			ListaAux=VerticesAdyacentes(BuscaVertice(Vertix));
			
			while (!ListaAux.ListaVacia() && !EstadoFinal)
			{
				Vertix=ListaAux.Elimina();
				// Si el sucesor no es el estado final y no est� en Visitado entonces se guarda en la lista
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
	// Si se lleg� al estado final se imprime la secuencia de v�rtices visitados
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
