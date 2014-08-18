/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 3: Voraz-Greedy
Version:0.1

EJERCICIO devolver cambio

Problema que respecto un cojunto de monedas ilimitado.
Tiene que devolver una cantidad con dichas monedas.
El algoritmo calcula de forma las monedas a devolver de manera minima.
No siempre garantiza el optimo.

*/
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

//seleccionamos la moneda de mayor valor que a su vez sea menor que cantidad
int seleccion(const vector <int> &c,int cantidad) {
    int i=c.size()-1;
    while(c[i]>cantidad && i>=0) i--;
    return c[i];
}

//mostramos vector
void mostrar(const vector<int> & v) {
    for(int i=0; i<v.size(); i++) {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

//entrada vector de contenedores y el tamaño maximo
//devuelve un vector con los contenedores
vector <int> devolver(vector <int> c ,int k) {
    vector<int> s;
    int obj;
    int vuelta_actual=0;
    while(vuelta_actual<k) {
        obj= seleccion(c,k-vuelta_actual);//seleccionamos la mejor moneda
        if((vuelta_actual + obj) <= k) { //funcion de factibilidad
            s.push_back(obj);//la añadimos
            vuelta_actual+=obj;
        }
    }
    return s;
}


int main(int argc, char *argv[]) {

    int vuelta=4;
    vector <int> prueba;
    prueba.push_back(1);//tenemos monedas de 1 centimos
    prueba.push_back(2);//tenemos monedas de 2 centimos
    prueba.push_back(5);//tenemos monedas de 5 centimos
    prueba.push_back(10);//tenemos monedas de 10 centimos
    vector <int> s;
    s=devolver(prueba,vuelta);
    mostrar(s);
}
