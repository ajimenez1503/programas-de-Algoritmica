/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Branch and Bound
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

#include <queue>          // std::priority_queue
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "solucion.h"

//creamos los objetos de la mochila de forma aleatoria
vector <pair<float,float> > genera(int n) {
    vector <pair<float,float> > T(n);
    srand(time(0));
    for(int i=0; i<n; i++) {
        T[i].first=(rand()%50)+1;//aleatorio entre 1-100
        T[i].second=(rand()%50)+1;//aleatorio entre 1-100
    }
    return T;
}

//ordenamos los objetos de la mochila por su beneficio en orden decreciente
void ordenar(vector <pair<float,float> > & v) {
    int j;
    pair<float,float> temp;
    for(int i=1; i<v.size(); i++) {
        temp=v[i];
        j=i-1;
        while((v[j].first/v[j].second<temp.first/temp.second) && (j>=0) ) {
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=temp;

    }

}

//mostramos los objetos de la mochila
void mostrar(const vector <pair<float,float> > & v) {
    for(int i=0; i<v.size(); i++) {
        cout<<v[i].first<<" "<<v[i].second<<" densidad "<<v[i].first/v[i].second<<endl;
    }
    cout<<endl;
}


//objetivo maximizar beneficio
solucion Branch_and_Bound(int n_objetos,vector <pair<float,float> >  v ,int tama) {

    priority_queue<solucion> Q;
    solucion n_e(n_objetos,tama), mejor_solucion(n_objetos,tama) ; //nodoe en expansion
    int k;
    float CG=0; // Cota Global
    float ganancia_actual;
    n_e.calcularCotaLocal(v);
    Q.push(n_e);
    while ( !Q.empty() && (Q.top().CotaLocal() > CG) ) {
        n_e = Q.top();
        Q.pop();
        k = n_e.CompActual();
        for ( n_e.PrimerValorComp(k+1); n_e.HayMasValores(k+1); n_e.SigValComp(k+1,v)) {
            if ( n_e.factible( ) && n_e.EsSolucion() ) {
                ganancia_actual = n_e.Evalua();
                if (ganancia_actual > CG) {
                    CG = ganancia_actual;
                    mejor_solucion = n_e;
                }
            }
            else {
                n_e.calcularCotaLocal(v);
                if ( n_e.factible( ) && n_e.CotaLocal()>CG )Q.push( n_e );
            }
        }
    }
    return mejor_solucion;
}

int main(int argc, char *argv[]) {
    int tama=100;
    int n = 5;
    vector <pair<float,float> >  prueba;
    prueba=genera(n);
    ordenar(prueba);
    cout<<"mostramos objetos"<<endl;
    mostrar(prueba);
    solucion s;
    s=Branch_and_Bound(n,prueba,tama);
    s.mostrar_solucion(prueba);
    return 0;
}
