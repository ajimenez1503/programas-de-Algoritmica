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
#include <queue>          // std::priority_queue
#include <iostream>
#include <iomanip>      // std::setw
#include <vector>
#include <cstdlib>
using namespace std;
//estados -1,0,1,2,3,...n-1,n
//-1 nulo
//n end
//x[i]=j; x[trabajador]=actividad
//trabajador filas
//tareas columnas
class solucion {
private:
    vector <int>  x;
    int pos_e;//pos de la ultima decision
    float coste,estimador;//coste y estimador

public:
    solucion () { //constructor por defecto

    }

    solucion(int n) { //constructor
        coste=0;
        estimador=0;
        pos_e=-1;
        x.resize(n,0);
    }
    int size() const {
        x.size();
    }
    bool EsSolucion() {
        return size()==pos_e+1;
    }
    int CompActual() {
        return pos_e;
    }
    void PrimerValorComp(int k) {
        pos_e=k;
        x[k]=0;//-1=NULO
    }
    float Evalua() {
        return coste;
    }
    float CotaLocal() const {
        return estimador;
    }
    void SigValComp(int k,const vector< vector<int> > & orig) {
        x[k]++;
        coste+=orig[k][x[k]];
        if(x[k]>0) { //le tenemos que resta la anterior
            coste-=orig[k][x[k]-1];
        }
    }
    bool HayMasValores(int k) {
        return (k<size() && x[k]<size());//devuelve true si estamos ya en el ultimo.
    }
    void calcularCotaLocal(const vector<int> & orig) {
        estimador=coste;
        int k=pos_e+1;
        while(k<orig.size()) {
            estimador+=orig[k];
            k++;
        }
    }
    bool factible() {
        for(int i=0; i<pos_e; i++) {
            if(x[i]==x[pos_e]) return false;
        }
        return true;
    }

    bool operator<(const solucion &s )const {
        return estimador>s.estimador;
    }

    void mostrar_solucion(const vector< vector<int> > & orig) {
        cout<<"solucion"<<endl;
        int aux_coste=0;
        for(int i=0; i<x.size(); i++) {
            cout<<"trabajador "<<i<<" tarea "<<x[i]<<endl;
            aux_coste+= orig[i][x[i]];
        }
        cout<<endl<<"coste total es: "<<aux_coste<<endl;
    }

};
