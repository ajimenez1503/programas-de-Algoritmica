/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 2: Divide y Venceras
Version:0.1

EJERCICIO quicksort

Ordenamos un vector por la filosofia quicksort.
Tomamos un pivote y a la izquierda de el posicionamos los valores menores o iguales
y a la derecha de el ponemos los mayores.
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

//swap
void intercambiar(int &a,int &b) {
    int aux=a;
    a=b;
    b=aux;
}

//elegimos el pivote y posicionamos los valores
int particion(vector<int>  & T,int i,int f) {
    int pivote=T[i],inicial=i;
    while ((T[i] <= pivote) && (i <= f)) i++;
    while (T[f] > pivote)f--;

    while (i < f) {
        intercambiar(T[i],T[f]);
        while (T[i] <= pivote)i++;
        while (T[f] > pivote)f--;
    }
    intercambiar(T[inicial],T[f]);
    return f;
}

//funcionpara ordenar
void quickSort(vector<int>  & v,int i,int f) {
    if(f>i) {
        int p=particion(v,i,f);
        quickSort(v,i,p);
        quickSort(v,p+1,f);
    }
}

int main()
{
    vector<int> v;//crear vector
    v.push_back(4);
    v.push_back(2);
    v.push_back(3);
    v.push_back(5);
    v.push_back(99);
    v.push_back(1);
    v.push_back(6);
    v.push_back(999);
    v.push_back(10);
    mostrar(v);
    quickSort(v,0,v.size());//ordenamos vector
    mostrar(v);

}
