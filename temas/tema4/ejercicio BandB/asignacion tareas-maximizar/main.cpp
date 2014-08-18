/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Branch and Bound
Version:0.1

EJERCICIO maximizar asignacion de tareas


Dadas n personas y n trabajos, con C[i][j] el costo que tiene que la
persona i-ésima realice el trabajo j-ésimo.

Realizar una asignación de tareas de forma que:
• Todos los trabajos sean ejecutados
• Todas las personas realicen un trabajo (no hay persona ociosa)
• El costo de la asignación es maximo

*/

//compilar g++ main.cpp -o main
using namespace std;
#include "solucion.h"
//maximizar rendimiento de tareas
//suponemos costes positivos
// vector<trabajador,tarea>

//mostramos vector de trabajores y tareas
void mostrar(const vector <int>  & v) {
    for(int i=0; i<v.size(); i++) {
        cout<<"trabajador "<<i<<" tarea min "<<v[i]<<endl;
    }
    cout<<endl;
}

//mostramos la matriz de rendmientos de trabajadores y tareas
void mostrar (const vector< vector<int> > & m) {
    cout<<"la matriz es:"<<endl;
    cout<<setw(3);
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            cout<<m[i][j]<<setw(3);
        cout<<endl;
    }
}

//creamos la matriz de rendimiento de trabajadores y tareas de forma aleatroia
void crear ( vector< vector<int> > & m) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            m[i][j]=(rand()%50)+1;//aleatorio entre 1-50
    }
}

//creamos un vector que sea contenta el rendimiento maximo de cada trabajajdore en las sigientes tareas
vector<int> calcular_vector_max(const vector< vector<int> > & m) {
    int maxi;
    vector<int> max(m.size());
    for(int i=0; i<m.size(); i++) {
        maxi=m[i][0];
        for(int j=1; j<m[i].size(); j++) {
            if(maxi<m[i][j]) maxi=m[i][j];

        }
        max[i]=maxi;
    }
    return max;

}

//objetivo maximizar
//devuelve la mejor solucion.
//le pasamos el numero de trabajadores y la matriz de rendimientos y el vector de maximos
solucion Branch_and_Bound(int n_objetos,vector< vector<int> >  m,vector<int> v_max) {

    priority_queue<solucion> Q;
    solucion n_e(n_objetos), mejor_solucion(n_objetos) ; //nodoe en expansion
    int k;
    int CG=0; // Cota Global. La igualamos a 0 ya que
    int ganancia_actual;
    n_e.calcularCotaLocal(v_max);
    Q.push(n_e);
    while ( !Q.empty() && (Q.top().CotaLocal() >CG) ) {
        n_e = Q.top();
        Q.pop();
        k = n_e.CompActual();
        for ( n_e.PrimerValorComp(k+1); n_e.HayMasValores(k+1); n_e.SigValComp(k+1,m)) {
            if ( n_e.factible( ) && n_e.EsSolucion() ) {
                ganancia_actual = n_e.Evalua();
                if (ganancia_actual > CG) {
                    CG = ganancia_actual;
                    mejor_solucion = n_e;
                }
            }
            else {
                n_e.calcularCotaLocal(v_max);
                if ( n_e.factible( ) && n_e.CotaLocal()>CG )Q.push( n_e );
            }
        }
    }
    return mejor_solucion;
}

int main() {
    int n=5;
    vector< vector<int> >  m;
    vector<int> v_max;
    m.resize(n, vector<int>(n,-1));
    crear(m);
    mostrar(m);
    v_max=calcular_vector_max(m);
    solucion s;
    s=Branch_and_Bound(n,m,v_max);
    s.mostrar_solucion(m);
    return 0;
}
