/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Backtracking
Version:0.1

EJERCICIO 8 reinas
Colocar 8 reinas en un tablero de tamaño 8x8 sin
que se ataquen entre ellas.
*/
//compilar g++ main.cpp -o main
using namespace std;
#include "solucion.h"

void back_recursivo(solucion &sol,int k) {
    if(k==sol.size())   sol.procesasolucion();
    else {
        sol.iniciacomp(k);
        sol.sigvalcomp(k);
        while(!sol.todosgenerados(k)) {
            if(sol.factible(k)) {
                back_recursivo(sol,k+1);
                sol.VueltaAtras(k+1);//para que en las siguientes iteracioens no se tnega en cuenta k+1
            }
            sol.sigvalcomp(k);
        }
    }
}

int main(int argc, char *argv[]) {

    int n = 10;
    solucion s(n);
    int aux=0;
    s.mostrar();
    back_recursivo(s,aux);
    return 0;
}
