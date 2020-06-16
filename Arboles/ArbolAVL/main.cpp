#include <iostream>
#include "ArbolAVL.h"
int main() {
    int DatosI[] = {66,44,85,22,50,73,90,9,37,47,88,94,39};
    int DatosE[] = {73,66,50,47,39,94};
    int band = 1;
    ArbolAVL<int> Arbol1;
    NodoArbolAVL<int> *NodoAnt = Arbol1.RegresaRaiz();
    for (auto i: DatosI){
        std::cout << "\nInserta: " << i << std::endl<<std::endl;
        Arbol1.InsertaAVL(i ,Arbol1.RegresaRaiz(), &band);
        Arbol1.Imprime(Arbol1.RegresaRaiz(), band);
    }

    std::cout << "\n--------- ARBOL PRE ELIMINACION ------------\n" << std::endl;
    Arbol1.Imprime(Arbol1.RegresaRaiz(), band);

    std::cout << "\n--------- ARBOL POST ELIMINACION ------------\n" << std::endl;
    for (auto i: DatosE){
        std::cout << "\nElimina: " << i << std::endl<<std::endl;
        Arbol1.EliminaAVL(Arbol1.RegresaRaiz(), NodoAnt, &band, i);
        Arbol1.Imprime(Arbol1.RegresaRaiz(), band);
    }

    std::cout << "\nDaniel Garnica Sanchez" << std::endl;
    return 0;
}