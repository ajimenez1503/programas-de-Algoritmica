/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 2: Divide y Venceras
Version:0.1

EJERCICIO INDICES

Precondicion: el vector debe estar ordenado.
problema del indice.
Devuelve true si el numero del indice se corresponde con el valor de dicha posicion,
es decir, i==v[i]. A partir d la filosofia divide y venceras

*/
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

//mostrar vector
void mostrar(const vector<int> & v) {
    for(int i=0; i<v.size(); i++) {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

//devuelve true si i==v[i]
bool indice(const vector<int>  & v,int i,int f) {
    if(f-i==1) {
        return v[i]==i;
    }
    else {
        int m=(i+f)/2;
        if(m<v[m]) return indice(v,i,m);
        else if(m>v[m]) return indice(v,m,f);
        else return true;//m==v[m]

    }
}

int main()
{
    vector<int> v;//creamos vector
    v.push_back(0);
    v.push_back(2);
    v.push_back(3);
    v.push_back(5);
    v.push_back(99);
    v.push_back(55);
    mostrar(v);
    if(indice(v,0,v.size()))cout<<"Existe"<<endl;
    else cout<<"No existe"<<endl;

}
