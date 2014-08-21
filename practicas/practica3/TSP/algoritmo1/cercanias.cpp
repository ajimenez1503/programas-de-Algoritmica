/* (C) Programmed by:
   	Antonio Jimenez Martínez
	Alejandro Casado Quijada
	Andrés Ortiz Corrales
	Jesús Prieto López
	Salvador Rueda Molina

Asignatura Algoritmica (ALG)
practica 3: greedy (voraz)
Version:0.1

EJERCICIO Comerciante de comercio (TSP) vecino mas cercano

Dado un conjunto de ciudades y una matriz con las distancias entre todas ellas, un viajante debe recorrer
todas las ciudades exactamente una vez, regresando al punto de partida, de forma tal que la distancia
recorrida sea mínima.
Mas formalmente, dado un grafo G, conexo y ponderado, se trata de hallar el ciclo hamiltoniano de mínimo
peso de ese grafo.

Primero creamos una matriz con la distancias entre las ciudades, utilizando el algoritmo de Euclides.
Comenzamos seleccionando la ciudad inicial como la 1. Recorremos la fila 1y seleccionamos la ciudad a
menor distancia (columnas). Cuando hacemos esto saltamos a la fila de la ciudad seleccionada y volvemos a
realizar este procedimiento. Tenemos en cuenta que no podemos introducir ciudades repetidas.
Cuando haya introducido de la lista todas las ciudades sin repeticiones, añadimos a la distancia final el
camino entre la última ciudad y la primera, e insertamos de nuevo la ciudad 1 (única que se repite).


*/

//compilar: g++ cercanias.cpp -o cercanias
//ejecutar: ./cercanias berlin52.tsp


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>      // std::setw
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

//Lee el fichero de coordenadas de un fichero de TSP y el recorrido óptimo (en ese orden) y da como salida el fichero de coordenadas pero reordenado según el orden óptimo, para poder dibujarlo con gnuplot

class CLParser
{
public:

    CLParser(int argc_, char * argv_[],bool switches_on_=false);
    ~CLParser() {}

    string get_arg(int i);
    string get_arg(string s);

private:

    int argc;
    vector<string> argv;

    bool switches_on;
    map<string,string> switch_map;
};

CLParser::CLParser(int argc_, char * argv_[],bool switches_on_)
{
    argc=argc_;
    argv.resize(argc);
    copy(argv_,argv_+argc,argv.begin());
    switches_on=switches_on_;

    //map the switches to the actual
    //arguments if necessary
    if (switches_on)
    {
        vector<string>::iterator it1,it2;
        it1=argv.begin();
        it2=it1+1;

        while (true)
        {
            if (it1==argv.end()) break;
            if (it2==argv.end()) break;

            if ((*it1)[0]=='-')
                switch_map[*it1]=*(it2);

            it1++;
            it2++;
        }
    }
}

string CLParser::get_arg(int i)
{
    if (i>=0&&i<argc)
        return argv[i];

    return "";
}

string CLParser::get_arg(string s)
{
    if (!switches_on) return "";

    if (switch_map.find(s)!=switch_map.end())
        return switch_map[s];

    return "";
}



/*
*/
void leer_puntos(string & nombre, map<int, pair<double, double> > & M) {
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;


    datos.open(nombre.c_str());
    if (datos.is_open()) {
        datos >> s; // Leo "dimension:"
        datos >> n;
        int i=0;
        while (i<n) {
            datos >> act >> p.first >> p.second;
            M[act] = p;
            i++;
        }

        datos.close();
    }
    else {
        cout << "Error de Lectura en " << nombre << endl;
    }
}



/*
*/
void leer_orden(string & nombre, vector<int> & V) {
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;

    datos.open(nombre.c_str());
    if (datos.is_open()) {
        datos >> s; // Leo "dimension:"
        datos >> n;
        V.reserve(n);
        int i=0;
        while (i<n) {
            datos >> act;
            V.push_back(act);
            i++;
        }

        datos.close();
    }
    else {
        cout << "Error de Lectura en " << nombre << endl;
    }
}
//////////////////////////////////////////////////////////////

//mostrar matriz
void mostrar (const vector< vector<int> > & m) {
    cout<<"la matriz es:"<<endl;
    cout<<setw(3);
    for(int i=0; i<m.size(); i++) {
        cout<<"Ciudad "<<i+1<<": "<<endl;
        for(int j=0; j<m[i].size(); j++)
            cout<<m[i][j]<<" ";
        cout<<endl;
        cout<<endl;
    }
}
//calcular distancia
int euclides (double xi,double yi,double xj,double yj) {
    double aux1=(xj-xi)*(xj-xi);
    double aux2=(yj-yi)*(yj-yi);
    aux2=aux1+aux2;
    int aux=sqrt(aux2);
    return aux;

}
//creamos la matriz de distancias
//Asignamos a la distnacia entre la misma ciudad como -1.
void calcular_matriz(map<int, pair<double, double> >  m,vector< vector<int> > & matriz) {
    for(int i=0; i<matriz.size(); i++) {
        for(int j=0; j<matriz[i].size(); j++)
            if(i!=j) {
                matriz[i][j]=euclides(m[i+1].first,m[i+1].second,m[j+1].first,m[j+1].second);
            }

    }
}
//rellenamos la columna de -1 para que esta no se vuelva a utilizar.
void modificar_columna(vector< vector<int> > & m,int colum) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            if(colum==j) {
                m[i][j]=-1;
            }
    }
}
//tomamos como nodo inicial la ciudad 1.
//entra la matriz
//devolvemos el vector de ciudades cogidas y la distancia.
vector<int> recorrido(vector< vector<int> >  matriz,int & d) {
    vector<int>c;//ciudades selecionadas
    int nodo=0,min=0,pos=0,i=1,j=0;
    //primero introducimos el primero nodo en el vector
    c.push_back(nodo+1);
    for(; i<matriz.size(); i++) { //contador
        j=1;
        while(matriz[nodo][j]==-1) {
            j++;
        }
        min=matriz[nodo][j];
        pos=j;
        for(; j<matriz[nodo].size(); j++) {
            if(matriz[nodo][j]!=-1 and min>matriz[nodo][j]) {
                min=matriz[nodo][j];
                pos=j;
            }
        }
        nodo=pos;
        c.push_back(nodo+1);
        modificar_columna(matriz,nodo);
        d+=min;
    }
    //añadirle la distnacia del ultimo nodo al inicio
    d+=matriz[nodo][0];
    //le añadimos de nuevo el nodo 1..
    c.push_back(1);
    return c;
}

//devuelve las ciudades ordenadas con sus coordenadas.
//para poder crear el camino en una grafica
void mostrar_resultado(const vector<int> &result,const map<int,pair<double,double> > &m) {
    for(int i=0; i<result.size(); i++) {
        pair<double,double> p;
        p=(m.find(result[i]))->second;
        cout<<result[i]<<" "<<p.first<<" "<<p.second<<endl;
    }
}

int main(int argc, char * argv[])
{

    map<int, pair<double, double> >  m;//un map con las posicion y las dimensiones.
    vector< vector<int> >  matriz;//cremaos un matriz con la distnacia entre dos pueblos
    vector<int> ciu;
    int tama=0,distancia=0;
    string fp;
    if (argc<2) {
        cout << "Error Formato:  tsp puntos" << endl;
        exit(1);
    }

    CLParser cmd_line(argc,argv,false);
    fp = cmd_line.get_arg(1);
    leer_puntos(fp,m);
    tama=m.size();
    matriz.resize(tama, vector<int>(tama,-1));
    calcular_matriz(m,matriz);
    //mostrar(matriz);
    ciu=recorrido(matriz,distancia);
    // cout<<"La distancia total es: "<<distancia<<" y el orden de las ciudades es:"<<endl;
    //for(int i=0; i<ciu.size(); i++) cout<<ciu[i]<<"   ";
    mostrar_resultado(ciu,m);
    cout<<endl;
    return 0;
}
