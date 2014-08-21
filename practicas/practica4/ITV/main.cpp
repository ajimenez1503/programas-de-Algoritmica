/* (C) Programmed by:
   	Antonio Jimenez Martínez
	Alejandro Casado Quijada
	Andrés Ortiz Corrales
	Jesús Prieto López
	Salvador Rueda Molina

Asignatura Algoritmica (ALG)
practica 4: Backtracking
Version:0.1

EJERCICIO ITV.

Una estación de ITV consta de m líneas de inspección de vehículos iguales. Hay un total de
n vehículos que necesitan inspección. En función de sus características, cada vehículo
tardara en ser inspeccionado un tiempo ti; i = 1,...., n. Se desea encontrar la manera de
atender a todos los n vehículos y acabar en el menor tiempo posible. Diseñamos e
implementamos un algoritmo vuelta atrás que determine como asignar los vehículos a las
líneas. Utilizando una función de factibilidad y una poda.
*/
//compilar  g++ main.cpp -o main -std=gnu++0x
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdlib>
#include <chrono>
using namespace std::chrono;
#include "solucion.h"

void back_recursivo(solucion &s) {
    if(s.size()<s.num_vehiculos()) {
        int lin=0;
        s.add_vehicle();
        while(lin<s.num_lineas()) {
            if(s.factible()) {
                back_recursivo(s);
                s.erase_vehicle(); //elimina el vehiculo temporal creado en back_recursivo
            }
            s.last_vehicle_change_line();
            lin++;
        }
    }
    else {
        s.actualizar_solucion();
        s.add_vehicle(); //Añade un vehiculo extra, ya que no se llama a back_recursivo y si se llamara  a erase_vehicle
    }
}




int main(int argc, char *argv[]) {
    high_resolution_clock::time_point tantes, tdespues;
    duration<double> transcurrido;
    if(argc != 3) {
        std::cerr << "Formato " << argv[0] << " <num_vehiculos> <num_lineas" << "\n";
        return -1;
    }
    int n = atoi(argv[1]);
    int l=atoi(argv[2]);
    solucion s(n,l);

    tantes = high_resolution_clock::now();
    back_recursivo(s);
    //s.mostrar();
    tdespues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double> >(tdespues - tantes);
    std::cout <<"Para "<<n<< " vehiculos ha tardado: " << transcurrido.count() << "\n";
    return 0;
}
