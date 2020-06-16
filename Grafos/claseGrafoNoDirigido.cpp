#include <iostream>

#define MAX 20

using namespace std;

/* Definici�n de la plantilla de la clase GrafoND. Se incluyen como atributos el total de v�rtices (NumVer), 
   los costos/distancias entre los v�rtices (MatAdy) y sus nombres (Vertices).
*/
template<class T>
class GrafoND
{
   private:
      T MatAdy[MAX][MAX];
      int NumVer, Vertices[MAX];
   public:
      // M�todo constructor y m�todos auxiliares para leerla informaci�n relacionada al grafo e 
	  // imprimir los resultados que se obtienen con los dem�s m�todos
	  GrafoND();
	  void Lee();
	  void Imprime(int);
	  
	  // M�todos que permiten el c�lculo del �rbol de costo m�nimo.
	  void Prim();
	  void Kruskal();	
};

// M�todo constructor. Inicializa el n�mero de v�rtices en cero y la matriz de distancias con un valor arbitrario 
// muy grande (999), excepto en la diagonal principal, donde el costo es cero.
template<class T>
GrafoND<T>::GrafoND()
{
	int Ind1, Ind2;
	for (Ind1=0; Ind1<MAX; Ind1++)
       for (Ind2=0; Ind2<MAX; Ind2++)
          if (Ind1 != Ind2)
             MatAdy[Ind1][Ind2]=999;
          else
             MatAdy[Ind1][Ind2]=0;
    NumVer=0;
}

/* M�todo que lee del teclado la informaci�n de la gr�fica. En esta soluci�n el nombre de los v�rtices
   s�lo pueden ser valores enteros. */
template <class T>
void GrafoND<T>::Lee()
{
	int Aristas, Costo, Ind1, Origen, Destino;
    cout << "\n\nIngresa el total de vertices del grafo: ";
    cin >> NumVer;
    for (Ind1=0; Ind1 < NumVer; Ind1++)
    {
       cout << "\nIngresa el nombre del vertice: ";
       cin >> Vertices[Ind1];
    }
    cout << "\n\nIngresa el total de aristas del grafo: ";
    cin >> Aristas;
    Ind1=0;
    while (Ind1 < Aristas)
    {
       cout << "�\nVertice origen: ";
       cin >> Origen;
       cout << "\nVertice destino: ";
       cin >> Destino;
       cout << "\nCosto de ir de " << Origen << " a " << Destino << " : ";
       cin >> Costo;
       MatAdy[Origen-1][Destino-1]=Costo;
       MatAdy[Destino-1][Origen-1]=Costo;
       Ind1++;
    }
}

/* Este m�todo encuentra el �rbol abarcador de costo m�nimo de un grafo. En el arreglo VerAux se almacenan los v�rtices 
  con menor costo que van formando el �rbol abarcador. */
template <class T>
void GrafoND<T>::Prim()
{
	int MCosto[MAX], VerAux[MAX], Ind1, Ind2, VerMen, MenCos;
    // Inicializa el subconjunto de v�rtices VerAux con el valor del primer v�rtice. 
    for (Ind1=0; Ind1<NumVer; Ind1++)
    {
       MCosto[Ind1]=MatAdy[0][Ind1];
       VerAux[Ind1]=0;
    }
    cout << "\n\n\nArcos y costos del arbol abarcador de costo minimo\n\n";
    cout << "\nVertice   Vertice   Costo \n";
    // Encuentra el v�rtice VerMen en (Vertices - VerAux) tal que el costo de ir de dicho v�rtice a uno de VerAux sea m�nimo.
    for (Ind1=0; Ind1 < NumVer-1; Ind1++)
    {
       MenCos=MCosto[1];
       VerMen=1;
       for (Ind2=2; Ind2 < NumVer; Ind2++)
          if (MCosto[Ind2] < MenCos)
          {
             MenCos=MCosto[Ind2];
             VerMen=Ind2;
          }
        cout << "\n " << Vertices[VerMen] << "     �    " << Vertices[VerAux[VerMen]] << "    "<< MatAdy[VerMen][VerAux[VerMen]];
        // Se agrega el v�rtice VerMen a VerAux y se redefinen los costos asociados.
        MCosto[VerMen]=1000;
        for (Ind2=1; Ind2 < NumVer; Ind2++)
           if ((MatAdy[VerMen][Ind2] < MCosto[Ind2]) && MCosto[Ind2] < 1000)
           {
              MCosto[Ind2]=MatAdy[VerMen][Ind2];
              VerAux[Ind2]=VerMen;
           }
    }
	cout << "\n\n";
}

// Funci�n auxiliar que obtiene el valor m�s peque�o de dos dados como par�metros. La utiliza el m�todo de Kruskal.
int Minimo (int Val1, int Val2)
{
	int Min= Val1;
    if (Val2 < Min)
      Min=Val2;
    return Min;
}

// Funci�n auxiliar que obtiene el valor m�s grande de dos dados como par�metros. La utiliza el m�todo de Kruskal. 
int Maximo (int Val1, int Val2)
{
	int Max= Val1;
    if (Val2 > Max)
       Max= Val2;
    return Max;
}

// Este m�todo encuentra el �rbol abarcador de costo m�nimo de un grafo. 
template <class T>
void GrafoND<T>::Kruskal()
{
	/* El arreglo auxiliar ArisCosto[][] almacena en cada rengl�n los datos de una arista: v�rtices adyacentes y costo. 
	   El arreglo Partic[] almacena particiones de Vertices. Inicialmente Partic= {{1},{2},...,{NumVer}}. */
    int ArisCosto[2*MAX][3], Partic[MAX], Ind1, Ind2, Ver1, Ver2, TotAris, Menor, Mayor, Band;

    // Inicializa Partic[]. 
    for (Ind1=0; Ind1 < NumVer; Ind1++)
       Partic[Ind1]=Ind1;

    // Inicializa ArisCosto[][] 
    Ver1=0;
    Ver2=0;
    TotAris=0;
    for (Ind1=0; Ind1 < NumVer; Ind1++)
       for (Ind2=Ind1; Ind2 < NumVer; Ind2++)
          if (MatAdy[Ind1][Ind2] != 0 && MatAdy[Ind1][Ind2] != 999)
          {
             ArisCosto[Ver1][Ver2++]=Ind1;
             ArisCosto[Ver1][Ver2++]=Ind2;
             ArisCosto[Ver1++][Ver2]=MatAdy[Ind1][Ind2];
             Ver2=0;
             TotAris++;
          }
    // Ciclo en el cual se seleccionan aristas y se agregan los v�rtices mientras existan v�rtices en Partic que 
	// se encuentren en distintas particiones.
    Band=0;
    while (Band != 1)
    {
       // Se selecciona la arista de menor costo. 
       Menor=999;
       for (Ind1=0; Ind1 < TotAris; Ind1++)
          if (ArisCosto[Ind1][2] < Menor)
          {
             Ver1=ArisCosto[Ind1][0];
             Ver2=ArisCosto[Ind1][1];
             Menor=ArisCosto[Ind1][2];
             Ind2=Ind1;
          }
       // Se elimina la arista de menor costo de la matriz ArisCosto.
       ArisCosto[Ind2][2]=999;
       // Se verifica que la arista (Ver1, Ver2) una dos v�rtices que pertenecen a particiones diferentes.
       if (Partic[Ver1] != Partic[Ver2])
       {
          cout << "\nVertice: " << Vertices[Ver1] << " Vertice: " << Vertices[Ver2] << " Costo: " << MatAdy[Ver1][Ver2] << "\n\n";
          Mayor=Maximo(Partic[Ver1], Partic[Ver2]);
          for (Ind1=0; Ind1 < NumVer; Ind1++)
             if (Ind1 == Ver1 || Ind1 == Ver2 || Partic[Ind1] == Mayor)
                Partic[Ind1]=Minimo(Partic[Ver1], Partic[Ver2]);
       }
       // Ciclo para determinar si quedan v�rtices en particiones diferentes. 
       Ind1=0;
       while (Ind1 < NumVer && !Band) 
       {
          if (Partic[Ind1] != 0)
             Band=1;
          Ind1++;
       }
       // Si existen particiones en Partic se debe seguir con el proceso.
       Band=!Band;
    }
}



int main() 
{
	return 0;
}
