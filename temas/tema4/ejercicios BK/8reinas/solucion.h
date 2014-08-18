/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Backtracking
Version:0.1

EJERCICIO 8 reinas
Colocar 8 reinas en un tablero de tamaño 8x8 sin
que se ataquen entre ellas, es decir,
que no esten ni en la misma fila, ni columna, ni diagonal.

soluciones para este problema, pueden representarse
como 8 tuplas (x1,...,xn) en las que xi es la columna en la que se
coloca la reina i. 
*/

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
//posibles estados: nulo,1,2,3,4,5,6,7,8,end
//tablero 8x8
//x[i]=k i=columna y k=fila
class solucion {
private:
    vector<int> x;//representa la solucion
    vector<bool> fila;//representa las fila
    vector<bool> DD;//representa la diagonal derecha
    vector<bool> DI;//representa la diagonal izq
public:
    solucion() { //constructor
        for(int i=0; i<15; i++) {
            if(i<8) {
                x.push_back(0);//0=NULO
                fila.push_back(1);//fila[i]==1 significa que esta libre
            }
            DD.push_back(1);//DD[i]==1 significa que esta libre
            DI.push_back(1);//DI[i]==1 significa que esta libre
        }
    }
    int size() const {
        x.size();
    }
    void iniciacomp(int k) {
        x[k]=0;//0=NULO
    }
    void sigvalcomp(int k) {
        x[k]++;
    }
    bool todosgenerados(int k) {
        //9==NULO
        return x[k]==9;//devuelve true si estamos ya en el ultimo.
    }
    int decision(int k) {
        return x[k];
    }
    void procesasolucion() {
        for(int i=0; i<size(); i++) {
            cout<<x[i]<<"  ";
        }
        cout<<endl;
    }
    bool factible(int k) {
	// Si X[k]=j, entonces la reina de la columna k, situada en fila j,
	// no puede acosar a ninguna de las k-1 anteriores reinas.
        if (fila[x[k]] && DD[k-x[k]+7] && DI[k+x[k]]) {
            fila[x[k]]=0;
            DD[k-x[k]+7] =0;
            DI[k+x[k]]=0;
            return true;
        } else return false;
    }
    void libera_posiciones(int k) {
        fila[x[k]]=1;
        DD[k-x[k]+7] =1;
        DI[k+x[k]]=1;
    }

};
