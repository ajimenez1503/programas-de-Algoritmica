/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 5: Programación dinámica
Version:0.1

EJERCICIO algoritmo de camino minimo - Floyd

Calcular el camino más corto que une cada par de
vértices de un grafo, considerando que no hay
pesos negativos.

Si el camino mínimo de i a j pasa por k, entonces
los caminos de i a k y de k a j son también
mínimos.

*/
#include <iostream>
#include <iomanip>      // std::setw
#include <vector>
#include <string>
#include <utility>
#include <cstdlib>
using namespace std;

//mostramos la tabla de subproblemas
void mostrar (const vector< vector<int> > & m) {
    cout<<"la tabla es:"<<endl;
    cout<<setw(3);
    cout<<"      ";//<<setw(3);
    for(int i=0; i<m.size(); i++) cout<<i<<setw(3);
    cout<<endl;
    cout<<endl;
    for(int i=0; i<m.size(); i++) {
        cout<<i<<setw(3)<<"   ";
        for(int j=0; j<m[i].size(); j++)
            cout<<m[i][j]<<setw(3);
        cout<<endl;
    }
}

//calculamos la matriz de para calcular los subproblemas
void floyd(int n,vector< vector<int> > & matriz,vector< vector<int> > & p) {

    for(int k=0; k<n; k++) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(matriz[i][k]+matriz[k][j]<matriz[i][j]) {
                    matriz[i][j]=matriz[i][k]+matriz[k][j];
                    p[i][j]=k;
                }
            }
        }
    }
}

//creamos la matriz del grafo del ejemplo
void crear_matriz(vector< vector<int> > & m) {
    m[0][0]=0;
    m[0][1]=5;
    m[0][2]=999;
    m[0][3]=999;
    m[1][0]=50;
    m[1][1]=0;
    m[1][2]=15;
    m[1][3]=5;
    m[2][0]=30;
    m[2][1]=999;
    m[2][2]=0;
    m[2][3]=15;
    m[3][0]=15;
    m[3][1]=999;
    m[3][2]=5;
    m[3][3]=0;
}

//mostramos los caminos minimos entre todos los vertices
void calcular_caminos (const vector< vector<int> > & p) {
    for(int i=0; i<p.size(); i++) {
        for(int j=0; j<p[i].size(); j++)
            if(p[i][j]==-1) {
                cout<<"el camino entre el vertice "<<i<<" y el vertice "<<j<<" es directo."<<endl;
            }
            else {
                cout<<"el camino entre el vertice "<<i<<" y el vertice "<<j<<" pasa por el vertice "<<p[i][j]<<endl;
            }
    }
    cout<<endl;
}

int main() {
    int n = 4;
    vector< vector<int> >  matriz,p;
    p.resize(n, vector<int>(n,0));
    matriz.resize(n, vector<int>(n,-1));
    crear_matriz(matriz);
    mostrar(matriz);
    mostrar(p);
    floyd(n,matriz,p);
    mostrar(matriz);
    mostrar(p);
    calcular_caminos(p);
}
