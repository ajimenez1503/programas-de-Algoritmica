/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 2: Divide y Venceras
Version:0.1

EJERCICIO mergesort

Ordenamos un vector por la filosofia merge sort.
Dividimos el problema, los ordenamos y despues combinamos los suproblemas.
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

//ordenar un vector
vector<int> mergeSort(const vector<int>  & v,int l,int r) {
    vector<int> s;
    if(r-l==1) {
        s.push_back(v[l]);
    }
    else {
        int m=(l+r)/2;
        vector<int> s1,s2;
        s1=mergeSort(v,l,m);
        s2=mergeSort(v,m,r);

        int i=0,j=0;
        while(i<s1.size() && j<s2.size()) {
            if(s1[i]<s2[j]) {
                s.push_back(s1[i]);
                i++;
            }
            else {
                s.push_back(s2[j]);
                j++;
            }

        }
        while(i<s1.size()) {
            s.push_back(s1[i]);
            i++;
        }
        while(j<s2.size()) {
            s.push_back(s2[j]);
            j++;
        }
    }
    return s;

}

int main()
{
    vector<int> v,v2;//creamos un vector
    v.push_back(4);
    v.push_back(3);
    v.push_back(7);
    v.push_back(2);
    v.push_back(99);
    v.push_back(55);
    mostrar(v);
    v2=mergeSort(v,0,v.size());//ordenamos el vector
    mostrar(v2);
}
