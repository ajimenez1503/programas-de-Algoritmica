/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 5: Programación dinámica
Version:0.1

EJERCICIO mochila 0-1

 conjunto S de n objetos, donde cada objeto, i, tiene
– bi beneficio positivo
– wi peso positivo

Seleccionar los elementos que nos garantizan un beneficio
máximo pero con un peso global menor o igual que W.

Los objetos no se pueden fraccionar.

La mejor selección de elementos del conjunto
1,2,...,k para una mochila de tamaño w se puede
definir en función de selecciones de elementos
de 1,2,...,k-1, para mochilas de tamaño menor.
*/

#include <iostream>
#include <iomanip>      // std::setw
#include <vector>
#include <utility>
#include <cstdlib>
//vector<beneficio,peso>
using namespace std;


//crear el conunto de objetos de forma aleatoria
//vector<beneficio,peso>
vector <pair<int,int> > genera(int n) {
    vector <pair<int,int> > T(n);
    srand(time(0));
    for(int i=0; i<n; i++) {
        T[i].first=(rand()%50)+1;//aleatorio entre 1-100
        T[i].second=(rand()%50)+1;//aleatorio entre 1-100
    }
    return T;
}

//mostramos el conjunto de objetos
void mostrar(const vector <pair<int,int> > & v) {
    for(int i=0; i<v.size(); i++) {
        cout<<v[i].first<<" "<<v[i].second<<endl;
    }
    cout<<endl;
}

//mostramos la tabla de subproblemas
void mostrar (const vector< vector<int> > & m) {
    cout<<"la tabla es:"<<endl;
    cout<<setw(3);
    cout<<"      ";//<<setw(3);
    for(int i=0; i<m[0].size(); i++) cout<<i<<setw(3);
    cout<<endl;
    cout<<endl;
    for(int i=0; i<m.size(); i++) {
        cout<<i<<setw(3)<<"   ";
        for(int j=0; j<m[i].size(); j++)
            cout<<m[i][j]<<setw(3);
        cout<<endl;
    }
}

//devuelve el maximo de dos numeros
int max(int a,int b) {
    if(a>=b) return a;
    else return b;
}

//calcula cuantos objetos utilizamos para un peso determinado
int mochila(int n,int m,vector< vector<int> > & matriz,const vector <pair<int,int> > & c) {
    for(int i=1; i<n; i++) {//empezamso en i=1 ya que si i==0 matriz[0][j]=0
        for(int j=1; j<m; j++) {//empezamso en j=1 ya que si j==0 matriz[i][0]=0
            if (j<c[i].second) {//si el peso del objeto es mayor que la capacidad de la mochila
                matriz[i][j]=matriz[i-1][j];//tomamos el objeto anterior
            }
            else {
                matriz[i][j]=max(matriz[i-1][j],c[i].first+matriz[i-1][j-c[i].second]);
            }
        }
    }
    return matriz[n-1][m-1];
}


//Calcula que objetos usamos
void objetosusados(const vector< vector<int> > & matriz,int n,int m,const vector <pair<int,int> > & c) {
    n--;
    m--;
    while(m!=0) {
        if(n>0 && matriz[n][m]==matriz[n-1][m]) {
            n--;
        }
        else {
            cout<<"cogemos un obejto de beneficio "<<c[n].first<<" y de peso "<<c[n].second<<endl;
            m=m-c[n].second;
            n--;
        }
    }
}

int main() {
    int n = 5;
    int m=6;//tamaÃño maximo
    vector <pair<int,int> >  prueba;
    prueba.resize(n);
	prueba[0].first=0;
	prueba[0].second=0;
	prueba[1].first=12;
	prueba[1].second=2;
	prueba[2].first=10;
	prueba[2].second=1;
	prueba[3].first=20;
	prueba[3].second=3;
	prueba[4].first=15;
	prueba[4].second=2;
    //prueba=genera(n);
    cout<<"mostramos objetos"<<endl;
    mostrar(prueba);
    cout<<"tamaño maximo "<<m-1<<endl;
    vector< vector<int> >  matriz;
    matriz.resize(n, vector<int>(m,0));
    cout<<"El beneficio es : "<<mochila(n,m,matriz,prueba)<<endl;
    mostrar(matriz);
    cout<<endl;
    objetosusados(matriz,n,m,prueba);

}
