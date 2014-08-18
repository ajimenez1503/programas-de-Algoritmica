/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 3: Voraz-Greedy
Version:0.1

EJERCICIO Seleccionar actividades

Tenemos la entrada de una Exposición que
organiza un conjunto de actividades
- Para cada actividad conocemos su horario de comienzo y fin.
- Con la entrada podemos asistir a todas las actividades.
- Hay actividades que se solapan en el tiempo.

Objetivo: Asistir al mayor número de actividades posible =>
Problema de selección de actividades
*/
#include <utility>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

//ordenamos por orden crecioente de finalizacion (second)
void ordenar(vector <pair<int,int> > & v) {
    int j;
    pair<int,int> temp;
    for(int i=1; i<v.size(); i++) {
        temp=v[i];
        j=i-1;
        while((v[j].second>temp.second) && (j>=0) ) {
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=temp;

    }

}

//mostramos el vector de actividades
void mostrar(const vector <pair<int,int> > & v) {
    for(int i=0; i<v.size(); i++) {
        cout<<v[i].first<<" "<<v[i].second<<endl;
    }
    cout<<endl;
}


//Seleccionar la siguiente actividad en el orden que comience
//después de que la actividad previa termine.
vector <pair<int,int> > asignar(vector <pair<int,int> > c ) {
    int i=0;
    vector <pair<int,int> > s;
    s.push_back(c[i]);
    i++;
    pair<int,int> obj;
    while(i<c.size()) {
        obj=c[i];
        if(obj.first>s[s.size()-1].second)//funcion de factivilidad
            s.push_back(obj);//añadimos la actividad
        i++;
    }
    return s;
}


//creamos el vector de actividades de forma aleatoria
vector <pair<int,int> > genera(int n) {
    vector <pair<int,int> > T(n);
    srand(time(0));
    for(int i=0; i<n; i++) {
        T[i].first=(rand()%50)+1;//aleatorio entre 1-100
        T[i].second=T[i].first+5;
    }
    return T;
}

int main(int argc, char *argv[]) {

    int n = 10;//10 actividades
    vector <pair<int,int> > prueba;
    prueba=genera(n);
    ordenar(prueba);
    cout<<"mostramos las actividades"<<endl;
    mostrar(prueba);
    vector <pair<int,int> > s;
    s=asignar(prueba);
	cout<<"mostramos las actividades seleccionadas"<<endl;
    mostrar(s);
}
