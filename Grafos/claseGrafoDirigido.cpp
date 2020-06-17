#include <iostream>
#include <iomanip>

#define MAX 20

using namespace std;

/* Definici�n de la plantilla de la clase Grafo. Se incluyen como atributos: la matriz de costos/distancias
   (MatAdy), el n�mero de v�rtices (NumVer), el nombre de cada deuno de los v�rtices (Vertices), un arreglo
   para las distancias m�nimas entre los v�rtices (DistMin), un arreglo para la cerradura transitiva de la
   matriz de adyacencia (CerTran), y un arreglo para v�rtices intermedios (VerInt). Los tres �ltimos se usan
   como auxiliares en m�todos que se estudiar�n durante el tema de grafos.
*/
template<class T>
class Grafo
{
   private:
      // Declaraci�n del arreglo donde se almacenan las distancias entre los v�rtices
      T MatAdy[MAX][MAX];
      int NumVer, Vertices[MAX], DistMin[MAX], CerTran[MAX][MAX], VerInt[MAX][MAX];
   public:
      // M�todo constructor y m�todos auxiliares para leerla informaci�n relacionada al grafo e
	  // imprimir los resultados que se obtienen con los dem�s m�todos
	  Grafo();
	  void Lee();
	  void Imprime(int);
	  void graph_default();

	  // M�todos que recorren un grafo dirigido, determinando caminos de distancias m�nimas
	  void Warshall();
	  void Floyd();
	  void FloydVerInt();
	  void Dijkstra();
};

// M�todo constructor. Inicializa la matriz de adyacencia MatAdy con un valor arbitrario muy grande (999), indicando que no existe
// camino entre los nodos correspondientes. Adem�s, asigna ceros a los arreglos que usaran en otros m�todos.
template<class T>
Grafo<T>::Grafo()
{
	int Ind1, Ind2;
	for (Ind1=0; Ind1<MAX; Ind1++)
	{
		DistMin[Ind1]=0;
		for (Ind2=0; Ind2<MAX; Ind2++)
		{
			if (Ind1!=Ind2){
			    MatAdy[Ind1][Ind2]=999;
                VerInt[Ind1][Ind2]=999;
                CerTran[Ind1][Ind2]=999;
			}
			else
			{
			   MatAdy[Ind1][Ind2]=0;
			   CerTran[Ind1][Ind2]=0;
			   VerInt[Ind1][Ind2]=0;
			}
		}
	}
	NumVer=0;
}

// Metodo que agraga un grafo por defecto
template<class T>
void Grafo<T>::graph_default()
{
    NumVer=6;
    for(int i=0; i<NumVer; i++)
        Vertices[i]=i+1;

    MatAdy[1 -1][2 -1]= 3;
    MatAdy[1 -1][5 -1]= 2;
    MatAdy[1 -1][6 -1]= 5;
    MatAdy[2 -1][6 -1]= 3;
    MatAdy[2 -1][3 -1]= 1;
    MatAdy[3 -1][4 -1]= 3;
    MatAdy[3 -1][6 -1]= 2;
    MatAdy[5 -1][4 -1]= 2;
    MatAdy[6 -1][5 -1]= 3;

}


// M�todo que lee los datos de la gr�fica dirigida directamente del teclado.
template <class T>
void Grafo<T>::Lee()
{
	int NumArcos, Indice, Origen, Destino;
    cout << "\n Ingresa numero de vertices del grafo dirigido: ";
    cin >> NumVer;
    for (Indice=0; Indice < NumVer; Indice++){
        cout << "\t nombre del vestice " << Indice+1 << " : ";
        cin >> Vertices[Indice];
    }
    cout << "\n Total de aristas del grafo dirigido: ";
    cin >> NumArcos;
    Indice=0;
    while (Indice < NumArcos)
    {
        cout << "\n Vertice ORIGEN : ";
        cin >> Origen;
        cout << "\n Vertice DESTINO : ";
        cin >> Destino;
        cout << "\n\t Distancia de [" << Origen << "] a [" << Destino << "] : ";
        cin >> MatAdy[Origen-1][Destino-1];
        Indice++;
    }
}

/* M�todo que imprime informaci�n relacionada a un grafo dirigido. Por medio de un n�mero entero se selecciona lo
  que se va a imprimir, lo cual depende del m�todo aplicado para recorrer el grafo. */
template <class T>
void Grafo<T>::Imprime(int Opc)
{
	int Ind1, Ind2;
    switch(Opc){
	    // Impresi�n de la matriz de adyacencia o de costos.
        case 0:{
            cout << "\n\n Matriz de Adyacencia o de Costos: \n\n";

        cout << "      ";
            for (Ind1=0; Ind1 < NumVer; Ind1++)
                cout << setw(6) << Vertices[Ind1];
            cout << endl;

        cout << "      ";
            for (Ind1=0; Ind1 < NumVer; Ind1++)
                cout << "------";
            cout << endl;

                for (Ind1=0; Ind1 < NumVer; Ind1++)
                {
                	cout << setw(3) <<  Vertices[Ind1] << setw(3) << " | ";
                    for (Ind2=0; Ind2 < NumVer; Ind2++)
                        cout << setw(6) << MatAdy[Ind1][Ind2];
                    cout << endl;
                }
                cout << "\n\n";
                break;
        }

        // Impresi�n de la cerradura transitiva correspondiente a la matriz de adyacencia.
		// Se obtiene cuando se aplica el m�todo de Warshall
        case 1:{
            cout << "\n\n Cerradura Transitiva de la Matriz de Adyacencia: " << endl;
                for (Ind1=0; Ind1 < NumVer; Ind1++)
                {
                   cout << Vertices[Ind1] << " : ";
                   for (Ind2=0; Ind2 < NumVer; Ind2++)
                       cout << CerTran[Ind1][Ind2] << "\t";
                       cout << endl;
                }

                cout << "\n\n";
                break;
        }

        // Impresi�n de la matriz de distancias m�nimas entre todos los v�rtices del grafo.
		// Se obtiene por medio del m�todo de Floyd.
        case 2:{
            cout << " ---> [ Floyd ] --------------";
            cout << "\n\n\n Matriz de Distancias Minimas: " << endl;
        cout << "      ";
            for (Ind1=0; Ind1 < NumVer; Ind1++)
                cout << setw(6) << Vertices[Ind1];
            cout << endl;

        cout << "      ";
            for (Ind1=0; Ind1 < NumVer; Ind1++)
                cout << "------";
            cout << endl;

                for (Ind1=0; Ind1 < NumVer; Ind1++)
                {
                	cout << setw(3) <<  Vertices[Ind1] << setw(3) << " | ";
                    for (Ind2=0; Ind2 < NumVer; Ind2++)
                        cout << setw(6) << MatAdy[Ind1][Ind2];
                    cout << endl;
                }
                cout << "\n\n";
                break;
        }

        // Impresi�n de la matriz con los v�rtices intermedios usados para establecer los caminos de distancias m�nimas.
		// Esta impresi�n complementa la de la opci�n 2 cuando se aplica el m�todo FloydVerInt.
        case 3:{
            cout << "\n ------[ Floyd Vertic Intermedioe  ]---------------------------\n";
            cout << "\n\n Vertices Intermedios para lograr distancias minimas: " << endl;

            cout << "      ";
            for (Ind1=0; Ind1 < NumVer; Ind1++)
                cout << setw(6) << Vertices[Ind1];
            cout << endl;

            cout << "      ";
            for (Ind1=0; Ind1 < NumVer; Ind1++)
                cout << "------";
            cout << endl;

            for (Ind1=0; Ind1 < NumVer; Ind1++)
                {
                	cout << setw(3) <<  Vertices[Ind1] << setw(3) << " | ";
                    for (Ind2=0; Ind2 < NumVer; Ind2++)
                        cout << setw(6) << VerInt[Ind1][Ind2];
                    cout << endl;
                }
                cout << "\n\n";
                break;
        }

        // Impresi�n de las distancias m�nimas entre un v�rtice y los dem�s. Se obtiene con el m�todo de Dijkstra.
        case 4:{
            int origen=0;
            cout << "\n ------[ DIJKSTRA ]-------------------------------------------\n";
            for(int Ind1=0; Ind1<NumVer; Ind1++)
                if(DistMin[Ind1] == 0)
                    origen=DistMin[Ind1];

            cout << "\n Distancias minimas a partir del ORIGEN [" << origen+1 << "]\n\n";

            cout << setw(15) <<" Vertices : ";
            for (Ind1=0; Ind1 < NumVer; Ind1++)
                cout << setw(6) << Vertices[Ind1];
            cout << endl;

            cout << setw(15) <<" Dist. Min. : ";
            for (Ind1=0; Ind1 < NumVer; Ind1++)
                cout << setw(6) << DistMin[Ind1];

            cout << "\n\n";
            break;
        }

        default:
            cout << " Opcion NO valida. " << endl;
            break;
    }
    cout << endl;
}

/* M�todo que determina si existe un camino entre cada uno de los v�rtices del grafo dirigido. CerTran es una matriz que
   representa la cerradura transitiva de la matriz de adyacencia. */
template <class T>
void Grafo<T>::Warshall(){

    int Ind1, Ind2, Ind3;
    /* En la posici�n i,j de la matriz de adyacencia se asign� el valor 999 si no existe un camino directo del v�rtice i al
	   v�rtice j. La cerradura transitiva se forma inicialmente a partir de la matriz de adyacencia. */
    for (Ind1=0; Ind1 < NumVer; Ind1++)
        for (Ind2=0; Ind2 < NumVer; Ind2++)
            if (MatAdy[Ind1][Ind2] !=999 && Ind1!=Ind2)
               CerTran[Ind1][Ind2]=1;
    /* Se recorren todos los v�rtices para determinar si existe un camino entre �l y los dem�s, usando otros v�rtices como
	   intermedios. */
    for (Ind3=0; Ind3 < NumVer; Ind3++)
       for (Ind1=0; Ind1 < NumVer; Ind1++)
          for (Ind2=0; Ind2 < NumVer; Ind2++)
             CerTran[Ind1][Ind2] |= CerTran[Ind1][Ind3] && CerTran[Ind3][Ind2];
}

/* M�todo que encuentra el camino de costo m�nimo entre todos los v�rtices del grafo dirigido. Va modificando la matriz de
   adyacencia a medida que encuentra un camino m�s corto entre dos v�rtices. */
template <class T>
void Grafo<T>::Floyd(){
	int Ind1, Ind2, Ind3;
    for (Ind3=0; Ind3 < NumVer; Ind3++)
       for (Ind1=0; Ind1 < NumVer; Ind1++)
          for (Ind2=0; Ind2 < NumVer; Ind2++){
              //cout << " ---> " << MatAdy[Ind1][Ind3] + MatAdy[Ind3][Ind2] << " y " << MatAdy[Ind1][Ind2] << endl;
             if (MatAdy[Ind1][Ind3]+MatAdy[Ind3][Ind2] < MatAdy[Ind1][Ind2]){
                    MatAdy[Ind1][Ind2]=MatAdy[Ind1][Ind3]+MatAdy[Ind3][Ind2];
                    //cout << MatAdy[Ind1][Ind2] << endl;
                    }

          }

}

/* M�todo Floyd modificado para que, adem�s de encontrar las distancias m�nimas entre todos los v�rtices de un grafo, genere una
   matriz (VerInt) con los v�rtices intermedios utilizados para minimizar las distancias. Este m�todo usa los atributos Vertices
   (arreglo que almacena los nombres de todos los v�rtices del grafo) y VerInt (arreglo donde se van guardando los v�rtices
   intermedios. Fue inicializado en 0 en el m�todo constructor). */
template <class T>
void Grafo<T>::FloydVerInt(){
    int Ind1, Ind2, Ind3;
    for (Ind3=0; Ind3 < NumVer; Ind3++)
       for (Ind1=0; Ind1 < NumVer; Ind1++)
          for (Ind2=0; Ind2 < NumVer; Ind2++){
             if (MatAdy[Ind1][Ind3]+MatAdy[Ind3][Ind2] < MatAdy[Ind1][Ind2])
             {
                    MatAdy[Ind1][Ind2]=MatAdy[Ind1][Ind3]+MatAdy[Ind3][Ind2];
                    //cout << "\n Vertice intermedio entre ["<<Ind1+1<< "] y [" << Ind2+1 << "] "  <<Vertices[Ind3] << endl;

                    VerInt[Ind1][Ind2]=Vertices[Ind3];
            }

          }
}

//* Funci�n auxiliar que obtiene el valor m�s peque�o de dos dados como par�metros. La utiliza el m�todo de Dijkstra.
int Minimo(int Val1, int Val2){
	int Min= Val1;
    if (Val2 < Min)
       Min=Val2;
    return Min;
}


// Metodo que encuentra la distancia minina de un origen(Vertice) a los demas vertices del graph
template <class T>
void Grafo<T>::Dijkstra(){
	int Aux[MAX], VertInc[MAX], Ver1, Ver2, Ind1, Ind2, Menor, Band, Origen;
    /* El arreglo VertInc se utiliza para guardar los v�rtices elegidos por ser los de la distancia m�nima. El arreglo Aux
	   es un arreglo l�gico que indica si el nodo de la posici�n i ya fue incluido en VertInc y de esta manera evitar ciclos. */
    for (Ind1= 0; Ind1 < NumVer; Ind1++)
    {
        Aux[Ind1]=0;
        VertInc[Ind1]=0;
    }
    cout << "\n\n Ingresa el vertice origen: ";
    cin >> Origen;
    Aux[Origen-1]=1;
    /* El arreglo donde se guardan las distancias m�nimas del Origen a los dem�s v�rtices se inicializa con los valores
	   de la matriz de adyacencia. */
    for (Ind1= 0; Ind1 < NumVer; Ind1++){
        DistMin[Ind1]=MatAdy[Origen-1][Ind1];
        //cout << setw(6) << DistMin[Ind1];
    }

    for (Ind1=0; Ind1<NumVer; Ind1++)
    {
        /* Se busca el v�rtice Ver1 en (Vertices - VertInc) tal que DistMin[Ver1] sea el m�nimo valor. Se usa el 999 como
		   valor inicial ya que es el elegido para indicar que no existe camino entre dos v�rtices. */
        Menor= 999;
        for (Ind2= 0; Ind2 < NumVer; Ind2++){
            //cout << "\n Longitud de ["<< Ind1+1<< "] a [" << Ind2+1 << "] es " << DistMin[Ind2] << endl;
            if (DistMin[Ind2] < Menor && !Aux[Ind2] )
            {
                Ver1=Ind2;
                Menor=DistMin[Ind2];
            }
        }

        // Se incluye Ver1 a VertInc y se actualiza el arreglo Aux.
        VertInc[Ind1]=Ver1;
        //cout << "\n Vertice menor: " << VertInc[Ind1] << endl;
        //cout << "\n Longitud menor -> " << Menor << endl;
        Aux[Ver1]=1;
        // Se busca la distancia m�nima para cada v�rtice Ver2 en (Vertices - VertInc).
        Ver2=0;
        while (Ver2 < NumVer)
        {
            Band=0;
            Ind2= 0;
            while (Ind2 < NumVer && !Band)
                if (VertInc[Ind2] == Ver2){
                    Band=1;
                }
                else{
                    Ind2++;
                    Band=0;
                }


                if (!Band){
                    //cout << "\n ---> " << DistMin[Ver2] << "---" << DistMin[Ver1] + MatAdy[Ver1][Ver2] << endl;
                    DistMin[Ver2]=Minimo(DistMin[Ver2],DistMin[Ver1] + MatAdy[Ver1][Ver2]);
                }

                Ver2++;
        }
    }
}


int main()
{
    Grafo<int> graph_int;
    graph_int.graph_default();
    graph_int.Lee();
    graph_int.Imprime(0);

    graph_int.Dijkstra();
    graph_int.Imprime(4);

    graph_int.FloydVerInt();
    graph_int.Imprime(3);

    graph_int.Floyd();
    graph_int.Imprime(2);

    graph_int.Warshall();
    graph_int.Imprime(1);




	return 0;
}
