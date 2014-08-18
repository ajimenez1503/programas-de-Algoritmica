/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Branch and Bound
Version:0.1

EJERCICIO minimizar asignacion de tareas


Dadas n personas y n trabajos, con C[i][j] el costo que tiene que la
persona i-ésima realice el trabajo j-ésimo.

Realizar una asignación de tareas de forma que:
• Todos los trabajos sean ejecutados
• Todas las personas realicen un trabajo (no hay persona ociosa)
• El costo de la asignación es mínimo

*/

//compilar g++ main.cpp -o main

using namespace std;
#include "solucion.h"
//suponemos costes positivos
// vector<trabajador,tarea>

//mostramos la tarea minima de cada trabajador
void mostrar(const vector <int>  & v) {
    for(int i=0; i<v.size(); i++) {
        cout<<"trabajador "<<i<<" tarea min "<<v[i]<<endl;
    }
    cout<<endl;
}

//mostramos la matriz de costes
void mostrar (const vector< vector<int> > & m) {
    cout<<"la matriz es:"<<endl;
    cout<<setw(3);
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            cout<<m[i][j]<<setw(3);
        cout<<endl;
    }
}

//mostramos la pareja trabajador tarea
void mostrar(const vector <pair<int,int> > & v) {
    for(int i=0; i<v.size(); i++) {
        cout<<"trabajador "<<v[i].first<<" tarea "<<v[i].second<<endl;
    }
    cout<<endl;
}

//creamos la matriz de adyacencia de forma aleatoria
void crear ( vector< vector<int> > & m) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            m[i][j]=(rand()%50)+1;//aleatorio entre 1-50
    }
}


//calculamos tarea minima de cada trabajador
vector<int> calcular_vector_min(const vector< vector<int> > & m) {
    int mini;
    vector<int> min(m.size());
    for(int i=0; i<m.size(); i++) {
        mini=m[i][0];
        for(int j=1; j<m[i].size(); j++) {
            if(mini>m[i][j]) mini=m[i][j];

        }
        min[i]=mini;
    }
    return min;

}

//objetivo minimizar
solucion Branch_and_Bound(int n_objetos,vector< vector<int> >  m,vector<int> v_min) {

    priority_queue<solucion> Q;
    solucion n_e(n_objetos), mejor_solucion(n_objetos) ; //nodoe en expansion
    int k;
    int CG=9999; // Cota Global
    int ganancia_actual;
    n_e.calcularCotaLocal(v_min);
    Q.push(n_e);
    while ( !Q.empty() && (Q.top().CotaLocal() <CG) ) {
        n_e = Q.top();
        Q.pop();
        k = n_e.CompActual();
        for ( n_e.PrimerValorComp(k+1); n_e.HayMasValores(k+1); n_e.SigValComp(k+1,m)) {
            if ( n_e.factible( ) && n_e.EsSolucion() ) {
                ganancia_actual = n_e.Evalua();
                if (ganancia_actual < CG) {
                    CG = ganancia_actual;
                    mejor_solucion = n_e;
                }
            }
            else {
                n_e.calcularCotaLocal(v_min);
                if ( n_e.factible( ) && n_e.CotaLocal()<CG )Q.push( n_e );
            }
        }
    }
    return mejor_solucion;
}

int main() {
    int n=5;
    vector< vector<int> >  m;
    vector<int> v_min;
    m.resize(n, vector<int>(n,-1));
    crear(m);
    mostrar(m);
    v_min=calcular_vector_min(m);
    solucion s;
    s=Branch_and_Bound(n,m,v_min);
    s.mostrar_solucion(m);
    return 0;
}
