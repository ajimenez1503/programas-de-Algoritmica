/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Backtracking
Version:0.1

EJERCICIO laberinto
El laberinto puede modelarse como una serie
de nodos. En cada nodo hay que
tomar una decisión que nos conduce a otros nodos.
Buscar en el laberinto hasta encontrar una
salida. Si no se encuentra una salida, informar de
ello.
Hay 4 movimientos. Intentamos sucesivamente
movernos en cada una de las 4 direcciones.

En este problema la longitud del vector solución no
es constante, es la lista de posiciones
hasta llegar a la salida.


*/

//compilar g++ main.cpp -o main
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "solucion.h"
void back_recursivo(solucion & sol,int k) {
    if(sol.encontrada())   sol.procesasolucion();
    else {
        sol.iniciacomp(k);
        sol.sigvalcomp(k);
        while(!sol.todosgenerados(k)) {
            if(sol.factible(k)) {
                back_recursivo(sol,k+1);
                sol.libera_posiciones(k);
            }
            sol.sigvalcomp(k);
        }
    }
}

int main() {
    solucion s(5,2);
    s.imprimir_laberinto();
    int aux=0;
    back_recursivo(s,aux);
    return 0;

}


