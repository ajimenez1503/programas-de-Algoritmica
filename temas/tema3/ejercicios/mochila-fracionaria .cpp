/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 3: Voraz-Greedy
Version:0.1

EJERCICIO mochila fraccionaria

Tenemos n objetos y una mochila. El objeto i tiene un
peso wi y la mochila tiene una capacidad M.
Si metemos en la mochila el objeto i, generamos un
beneficio de valor pi
El objetivo es rellenar la mochila de tal manera que se
maximice el beneficio que producen los objetos que se
transportan, con la limitación de la capacidad de valor
M.

Los objatos se puede fraccionar para conseguir
completar el tamaño de la mochila exacto.


Ya hemos visto que si los objetos se pueden fraccionar,
el algoritmo greedy da la solución óptima.

*/

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
//vector<beneficio,peso>

//ordenamos por orden decrecioente de desidad first/second
void ordenar(vector <pair<float,float> > & v) {
    int j;
    pair<float,float> temp;
    for(int i=1; i<v.size(); i++) {
        temp=v[i];
        j=i-1;
        while((v[j].first/v[j].second<temp.first/temp.second) && (j>=0) ) {
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=temp;

    }

}

//mostramos el vector de benecicio peso y la densidad
void mostrar(const vector <pair<float,float> > & v) {
    for(int i=0; i<v.size(); i++) {
        cout<<v[i].first<<" "<<v[i].second<<" densidad "<<v[i].first/v[i].second<<endl;
    }
    cout<<endl;
}


/* elegir en cada paso el objeto com mayor beneficio de entre los compatibles
con las decisiones ya tomadas.
Cuando ya no podemos coger un objeto completo por el peso, lo fraccionamos.
*/
vector <pair<float,float> >  mochila(vector <pair<float,float> >  c ,int k) {
    vector <pair<float,float> >  s;
    float peso_restante=k;
    int i=0;
    while(c[i].second<=peso_restante && i<c.size()) {
        s.push_back(c[i]);
        peso_restante-=c[i].second;
        i++;
    }

    //si del buble anterior ha salid porque el siguiente elemento entra pero le falta espacio a la mochila, lo fraccionamos.
    if(i<c.size()) {
        pair<float,float> obj;
        obj.first=(peso_restante/c[i].second)*c[i].first;//el beneficio en funcion del peso que le introducimos
        obj.second=peso_restante;//el peso
        s.push_back(obj);
    }
    return s;
}


//creamos el vector de objetos de forma aleatoria
vector <pair<float,float> > genera(int n) {
    vector <pair<float,float> > T(n);
    srand(time(0));
    for(int i=0; i<n; i++) {
        T[i].first=(rand()%50)+1;//aleatorio entre 1-100
        T[i].second=(rand()%50)+1;//aleatorio entre 1-100
    }
    return T;
}

int main(int argc, char *argv[]) {
    int n = 10;
    int tamamax=200;//tamaño de los contenedores en funcion del nuemero de contenedores
    vector <pair<float,float> >  prueba;
    prueba=genera(n);
    ordenar(prueba);
    cout<<"mostramos objetos"<<endl;
    mostrar(prueba);
    vector <pair<float,float> >  s;
    s=mochila(prueba,tamamax);
    cout<<"mostramos objetos seleccionados"<<endl;
    mostrar(s);
}
