/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 5: Programación dinámica
Version:0.1

EJERCICIO devolver cambio

Problema que respecto un cojunto de monedas ilimitado.
Tiene que devolver una cantidad con dichas monedas.
El algoritmo calcula de forma las monedas a devolver de manera minima.
A prtir de la filosofía de programación dinámica, garantiza el optimo.

*/

#include <iostream>
#include <iomanip>      // std::setw
#include <vector>
#include <utility>

using namespace std;


//mostramos la tabla de de los subproblemas
void mostrar (const vector< vector<int> > & m,const vector<int> & c,int tama) {
    cout<<"la tabla es:"<<endl;
    cout<<setw(3);
    cout<<"      ";//<<setw(3);
    for(int i=0; i<tama; i++) cout<<i<<setw(3);
    cout<<endl;
    cout<<endl;
    for(int i=0; i<m.size(); i++) {
        cout<<c[i]<<setw(3)<<"   ";
        for(int j=0; j<m[i].size(); j++)
            cout<<m[i][j]<<setw(3);
        cout<<endl;
    }
}

//calcula el minimo de dos numeros
int min(int a,int b) {
    if(a<=b) return a;
    else return b;
}

//Rellenamos la tabla de arriba a abajo y de izquierda a derecha
//Si la solución para m(i,j) no incluye una moneda de tipo i, entonces
//m(i,j)=m(i-1,j)

//Si la solución para m(i,j) sí incluye una moneda de tipo i, entonces
//m(i,j)=1+m(i,j-ci)

//devuelve el numero de monedas a usar
int devolverCambio(int n,int m,vector< vector<int> > & matriz,const vector<int> & c) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(j==0) {
                matriz[i][0]=0;
            }
            else if (i==0 && j<c[i]) {
                matriz[i][j]=99999;//mas infinito
            }
            else if (i==0) {
                matriz[i][j]=1+matriz[i][j-c[0]];
            }
            else if (j<c[i]) {
                matriz[i][j]=matriz[i-1][j];
            }
            else {
                matriz[i][j]=min(matriz[i-1][j],1+matriz[i][j-c[i]]);
            }
        }
    }
    return matriz[n-1][m-1];
}

//comprobamos que monedas hemos usado
//Si m[i,j] = m[i-1,j] no se escoge una moneda de tipo i
//Si m[i,j] = 1+m[1,j-c[i]] se escoge una moneda de tipo i
void monedasusadas(const vector< vector<int> > & matriz,int n,int m,const vector<int> & c) {
    n--;
    m--;
    while(m!=0) {
        if(n>0 && matriz[n][m]==matriz[n-1][m]) {
            n--;
        }
        else if(matriz[n][m]==1+matriz[n][m-c[n]]) {
            cout<<"cogemos una moneda de "<<c[n]<<" centimos"<<endl;
            m=m-c[n];
        }
    }
}

int main() {
    int n,m=9;//m=cambio
    cout<<"tenemos que cambiar "<<m-1<<" centimos."<<endl;
    vector<int> monedas;//valor de cada moneda
    monedas.push_back(1);//añadimos moneda de 1 centimo
    monedas.push_back(4);//añadimos moneda de 4 centimo
    monedas.push_back(6);//añadimos moneda de 6 centimo
    n=monedas.size();
    vector< vector<int> >  matriz;
    matriz.resize(n, vector<int>(m,1));
    cout<<"El numero de monedas del cambio es: "<<devolverCambio(n,m,matriz,monedas)<<endl;
    mostrar(matriz,monedas,m);
    cout<<endl;
    monedasusadas(matriz,n,m,monedas);

}
