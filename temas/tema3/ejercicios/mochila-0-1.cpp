/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 3: Voraz-Greedy
Version:0.1

EJERCICIO mochila 0-1

Tenemos n objetos y una mochila. El objeto i tiene un
peso wi y la mochila tiene una capacidad M.
Si metemos en la mochila el objeto i, generamos un
beneficio de valor pi
El objetivo es rellenar la mochila de tal manera que se
maximice el beneficio que producen los objetos que se
transportan, con la limitación de la capacidad de valor
M.

Pero si los objetos no se pueden fraccionar la estrategia
greedy no es óptima, es solo una heurística.

*/

#include <iostream>
#include <vector>
#include <cstdlib>// sdt::rand
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


//seleccionamso la maxima densidad (beneficio/peso)
int seleccion(const vector <pair<float,float> > &c) {
    float max=c[0].first/c[0].second;
    int maxpos=0;
    float p;
    for(int i=1; i<c.size(); i++) {
        p=c[i].first/c[i].second;
        if(max <p) {
            max=p;
            maxpos=i;
        }
    }
    return maxpos;
}

/* elegir en cada paso el objeto com mayor beneficio de entre los compatibles
con las decisiones ya tomadas.
*/
vector <pair<float,float> >  mochila(vector <pair<float,float> >  c ,int k) {
    vector <pair<float,float> >  s;
    pair<float,float> obj;
    int x;//posicion del vector de candidatos
    float peso_actual=0;
    while(!c.empty() && peso_actual<k) {
        x= seleccion(c);
        obj =c[x];
        c[x]=c[c.size()-1];
        c.pop_back();
        if((peso_actual + obj.second) <= k) { //funcion de factibilidad
            s.push_back(obj);
            peso_actual+=obj.second;
        }
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
    int tamamax=200;//tamaño maximo de la mochila
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
