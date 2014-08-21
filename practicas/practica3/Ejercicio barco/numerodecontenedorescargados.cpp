/* (C) Programmed by:
   	Antonio Jimenez Martínez
	Alejandro Casado Quijada
	Andrés Ortiz Corrales
	Jesús Prieto López
	Salvador Rueda Molina

Asignatura Algoritmica (ALG)
practica 3: greedy (voraz)
Version:0.1

EJERCICIO Problema barco: maximizar el numero de contenedores cargados

Se tiene un buque mercante cuya capacidad de carga es de K toneladas y un conjunto de
contenedores c1 , . . . , cn cuyos pesos respectivos son p1 , . . . , pn (expresados también en
toneladas).
Teniendo en cuenta que la capacidad del buque es menor que la suma total de los pesos
de los contenedores:
Diseñamos un algoritmo que maximice el número de contenedores cargados.
No siempre encuentra el óptimo.

*/

//compilar g++ numerodetoneladascargados.cpp -o num -std=gnu++0x

#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
using namespace std;

//seleccionar el contenedor con menor peso
int seleccion(const vector <int> &c) {
    int min=c[0];
    int minpos=0;
    int p;
    for(int i=1; i<c.size(); i++) {
        p=c[i];
        if(min >=p) {
            min=p;
            minpos=i;
        }
    }
    return minpos;
}
//entrada vector de contenedores y el tamaño maximo
//devuelve un vector con los contenedores

vector <int> Barco(vector <int> c ,int k) {
    vector<int> s;
    int obj;
    int x;//posicion del vector de candidatos
    int peso_actual=0;
    while(!c.empty() && peso_actual<=k) {
        x= seleccion(c);
        obj =c[x];
        c[x]=c[c.size()-1];
        c.pop_back();
        if((peso_actual + obj) <= k) { //funcion de factibilidad
            s.push_back(obj);
            peso_actual+=obj;
        }
    }
    return s;
}

//genera un vector de tamaños aleatorios
vector<int> genera(int n) {
    vector<int> T(n);
    srand(time(0));
    for(int i=0; i<n; i++) {
        T[i]=(rand()%100)+1;//aleatorio entre 1-100
    }
    return T;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cerr << "Formato " << argv[0] << " <numero contenedores>" << "\n";
        return -1;
    }
    //variables para el tiempo
    std::chrono::high_resolution_clock::time_point tantes, tdespues;
    std::chrono::duration<double> transcurrido;
    int n = atoi(argv[1]);
    int tamamax=40*n;//tamaño de los contenedores en funcion del nuemero de contenedores
    vector <int> prueba;
    prueba=genera(n);
    vector <int> s;
    tantes = std::chrono::high_resolution_clock::now(); //coger tiempo antes de la operación
    s=Barco(prueba,tamamax);
    tdespues = std::chrono::high_resolution_clock::now();//coger tiempo después de la operación
    transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(tdespues - tantes);
    std::cout <<"Para tamaño: "<<n<< " tiempo: " << transcurrido.count() << "\n";
    /*for(int i=0;i<s.size();i++)
    	cout<<s[i]<<" ";
    cout<<endl;*/
}
