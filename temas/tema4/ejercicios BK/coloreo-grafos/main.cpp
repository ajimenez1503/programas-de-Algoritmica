/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Backtracking
Version:0.1

EJERCICIO coloreo de grafos

Un caso especial famoso del problema de la n-colorabilidad
es el problema de los cuatro colores para grafos planos que,
dado un mapa cualquiera, consiste en saber si ese mapa podrá
 pintarse demanera que no haya dos zonas colindantes con el
mismo color, y además pueda hacerse ese coloreo
solo con cuatro colores.

*/
//compilar g++ main.cpp -o main
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>      // std::setw
using namespace std;
#include "solucion.h"

void back_recursivo(solucion & sol,int k,bool & salir) {
    if(k==sol.size()) {
        sol.procesasolucion();
		salir=true;
		
    }
    else {
        sol.iniciacomp(k);
        sol.sigvalcomp(k);
        while(!sol.todosgenerados(k) && !salir) {
            if(sol.factible(k)) {
                back_recursivo(sol,k+1,salir);
            }
            sol.sigvalcomp(k);
        }
    }
}
int main() {
	bool salir=false;
    solucion s(10);
    s.mostrar_matriz();
    int aux=0;
    back_recursivo(s,aux,salir);
    return 0;

}
