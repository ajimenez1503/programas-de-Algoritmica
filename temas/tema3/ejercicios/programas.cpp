/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 3: Voraz-Greedy
Version:0.1

EJERCICIO Seleccion de programas

Dado un conjunto T de n programas, cada uno con
tamano t1, ..., tn y un dispositivo de capacidad maxima C
Objetivo: Seleccionar el mayor numero de programas que se pueden almacenar en C.

*/
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;


//msotramos el vector de programas
void mostrar(const vector<int> & v) {
    for(int i=0; i<v.size(); i++) {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

//seleccionamos el programa de tamaño minimo
int seleccion(const vector <int> &c) {
    int min=c[0];
    int minpos=0;
    int p;
    for(int i=1; i<c.size(); i++) {
        p=c[i];
        if(min >p) {
            min=p;
            minpos=i;
        }
    }
    return minpos;
}

//entrada vector de programas y el tamaño maximo
//devuelve un vector con los programas seleccionados
vector <int> Selpro(vector <int> c ,int k) {
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

//creamos vector de programas con los peso aleatorios
vector<int> genera(int n) {
    vector<int> T(n);
    srand(time(0));
    for(int i=0; i<n; i++) {
        T[i]=(rand()%100)+1;//aleatorio entre 1-100
    }
    return T;
}

int main(int argc, char *argv[]) {

    int n = 10;//10 programas

    int tamamax=200;//tamaño de los progrmas
    vector <int> prueba;
    prueba=genera(n);
    cout<<"mostramos los programas"<<endl;
    mostrar(prueba);
    vector <int> s;
    s=Selpro(prueba,tamamax);
    mostrar(s);

}
