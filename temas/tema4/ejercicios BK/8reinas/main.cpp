/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Backtracking
Version:0.1

EJERCICIO 8 reinas
Colocar 8 reinas en un tablero de tamaño 8x8 sin
que se ataquen entre ellas, es decir,
que no esten ni en la misma fila, ni columna, ni diagonal.

soluciones para este problema, pueden representarse
como 8 tuplas (x1,...,xn) en las que xi es la columna en la que se
coloca la reina i. 
*/


//compilar g++ main.cpp -o main

using namespace std;
#include "solucion.h"

void back_recursivo(solucion & sol,int k) {
    if(k==sol.size())   sol.procesasolucion();
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
    solucion s;
	int aux=0;
    back_recursivo(s,aux);
 }
