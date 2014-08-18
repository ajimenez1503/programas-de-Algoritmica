/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Backtracking
Version:0.1

EJERCICIO mochila
Tenemos n objetos y una mochila. El objeto i tiene un
peso wi y la mochila tiene una capacidad M.
Si metemos en la mochila el objeto i, generamos un
beneficio de valor pi
El objetivo es rellenar la mochila de tal manera que se
maximice el beneficio que producen los objetos que se
transportan, con la limitación de la capacidad de valor M.

El espacio de soluciones consiste en asignar valores 0 ó 1 a cada objeto
(seleccionar o no el objeto)
*/


//compilar g++ main.cpp -o main
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "solucion.h"

void back_recursivo(solucion &sol,int k) {
    if(k==sol.size()) {
        sol.procesasolucion();
    }
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
    int tama=50;
    int n = 5;
    solucion s(n,tama);
    int aux=0;
    back_recursivo(s,aux);
    return 0;
}
