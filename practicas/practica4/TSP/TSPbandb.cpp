/* (C) Programmed by:
   	Antonio Jimenez Martínez
	Alejandro Casado Quijada
	Andrés Ortiz Corrales
	Jesús Prieto López
	Salvador Rueda Molina

Asignatura Algoritmica (ALG)
practica 4: Branch and Bound
Version:0.1

EJERCICIO Comerciante de comercio (TSP) Estrategias Branch and Bound

Dado un conjunto de ciudades y una matriz con las distancias entre todas ellas, un viajante debe recorrer
todas las ciudades exactamente una vez, regresando al punto de partida, de forma tal que la distancia
recorrida sea mínima.
Mas formalmente, dado un grafo G, conexo y ponderado, se trata de hallar el ciclo hamiltoniano de mínimo
peso de ese grafo.

Para emplear un algoritmo de ramificación y poda es necesario utilizar una cota inferior: un valor menor o
igual que el verdadero coste de la mejor solución (la de menor coste) que se puede obtener a partir de la
solución parcial en la que nos encontremos.
Para realizar la poda, guardamos en todo momento en una variable C el costo de la mejor solución obtenida
hasta ahora (que se utiliza como cota superior global: la solución óptima debe tener un coste menor a esta
cota). Esa variable puede inicializarse con el costo de la solución obtenida utilizando un algoritmo voraz
(como los utilizados en la practica 2). Si para una solución parcial, su cota inferior es mayor o igual que la
cota global (superior) entonces se puede realizar la poda.
Como criterio para seleccionar el siguiente nodo que hay que expandir del árbol de búsqueda (la solución
parcial que tratamos de expandir), se emplear el criterio LC o “más prometedor”.
En este caso consideraremos como nodo más prometedor aquel que presente el menor valor de cota
inferior.
Para ello se debe de utilizar una cola con prioridad que almacene los nodos ya generados (nodos vivos).

*/

//compilar: g++ TSPbandb.cpp -o TSPbandb
//ejecutar: ./TSPbandb berlin52.tsp
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
#include <queue>          // std::priority_queue
#include <list>          // std::list
using namespace std;

//Lee el fichero de coordenadas de un fichero de TSP y el recorrido óptimo (en ese orden) y da como salida el fichero de coordenadas pero reordenado según el orden óptimo, para poder dibujarlo con gnuplot
//--------------------------------------------------class CLParser------------------------------------------------
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
//--------------------------------------------------class CLParser------------------------------------------------

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
//mostrar vector
void mostrar (const vector<int> & m) {
    cout<<"el vector  es:"<<endl;
    for(int i=0; i<m.size(); i++) {
        cout<<m[i]<<"  ";
    }
    cout<<endl;
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
    //no le añadimos de nuevo el nodo 1..
    //c.push_back(1);
    return c;
}

//devuelve las ciudades ordenadas con sus coordenadas.
//añade la ciduad 1
void mostrar_resultado(const vector<int> &result,const map<int,pair<double,double> > &m) {
    for(int i=0; i<result.size(); i++) {
        pair<double,double> p;
        p=(m.find(result[i]))->second;
        cout<<result[i]<<" "<<p.first<<" "<<p.second<<endl;
    }
    pair<double,double> p;
    p=(m.find(1))->second;
    cout<<1<<" "<<p.first<<" "<<p.second<<endl;
}
vector<int> calcularMenorArista(const vector< vector<int> > & m) {
    vector<int> salida(m.size());
    int min=0,j;
    for(int i=0; i<m.size(); i++) {
        min=m[i][0];
        j=1;
        if(min==-1) {
            min=m[i][1];
            j++;
        }
        for(; j<m[i].size(); j++) {
            if(m[i][j]<min && m[i][j]!=-1)	min=m[i][j];
        }
        salida[i]=min;
    }
    return salida;
}


int distanciaCiudades(int c1,int c2,const vector< vector<int> > & m) { //restar uno ya que la ciduad n, en la matriz es la n-1
    return m[c1-1][c2-1];

}
//--------------------------------------------------class Solucion------------------------------------------------
class Solucion {
public:
    //constructor
    Solucion(int tama) {
        pos_e=distancia=estimador=0;
        x.push_back(1);//le pasamos la ciduad 1
        ciudadesRestantes.assign(tama-1,0);//-1 ya que la ciudad 1 no se la metemos
        crearCiudades();
    }
    //creamos la lista de ciudades
    void crearCiudades() {
        int i=2;//empezamos en la ciudada 2 ya que el un lo metemos inicialmente.
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            *it=i;
            i++;
        }
    }
    //calcula la cota por greedy
    void greedy(const vector< vector<int> >  & matriz) {
        x=recorrido(matriz,distancia);
        ciudadesRestantes.clear();

    }
    int getDistancia() {
        return distancia;
    }
    //calcula la cota a partirdel vectro de arista menores
    void calcularCotaLocal(const vector<int> & arista_menor) { //en arista_menor en la posicion 0, tenemos la ciudad 1.
        estimador=distancia;
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            estimador+=arista_menor[(*it)-1];//creo que es -1
        }
        //podemos tambn añadirle siempre la arista de la ciudad 1, ya que tenemos que volver, ->estimador mas preciso
        estimador+=arista_menor[0];
    }
    int CotaLocal() const {
        return estimador;
    }
    bool EsSolucion(int tama) {
        return x.size()==tama;
    }

    //devuelve en un vector el resto de ciudades
    vector<int> resto_ciudades() {
        vector<int> aux;
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            aux.push_back(*it);
        }
        return aux;
    }
    //añadade una ciudad al vectro y sus distnacia
    void anadirciudad(int a,const vector< vector<int> >  &m) {
        //Le volvemos a restar uno ya que la ciduad n, en la matriz es la n-1
        distancia+=distanciaCiudades(x.back(),a,m);//añade la distancia para ir a la ciudad
        x.push_back(a);
    }
    //quita una ciudad del vector y si distnacia
    void quitarciudad(const vector< vector<int> > & m) {
        //le quitamos a la ultima ciduad la que habia
        //Le volvemos a restar uno ya que la ciduad n, en la matriz es la n-1
        distancia-=distanciaCiudades(x[x.size()-2],x.back(),m);//quita la distancia para ir a la ciudad
        x.pop_back();//quitamos la ultima ciudad añadida
    }

    void quitarcidudadRestante(int a) {
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            if(*it==a) {
                ciudadesRestantes.erase(it);
                break;
            }
        }
    }
    void anadircidudadRestante(int a) {
        ciudadesRestantes.push_back(a);

    }
    //calcula distancia
    int Evalua(const vector< vector<int> > & m) { //devuelve la distnacia y añade la distancia para ir a la ciudad 1.
        distancia+=distanciaCiudades(x.back(),1,m);
        return distancia;
    }
    bool operator<( const Solucion & s) const { //ordenados de menos a mayor
        return estimador > s.estimador;
    }

    void mostrar() {
        cout<<" las ciudades son:"<<endl;
        for(int i=0; i<x.size(); i++) cout<<x[i]<<"   ";
        cout<<x[0]<<endl;
        cout<<"la distancia es: "<<distancia<<endl;
    }
    vector<int> devolverSolucion() {
        return x;
    }
private:
    vector<int> x; // Almacenamos la solucion
    int pos_e; // Posicion de la ultima decision en X
    int distancia;
    int estimador; // Valor del estimador para el nodo X
    list<int> ciudadesRestantes;
};
//--------------------------------------------------class Solucion------------------------------------------------
//////////////////////////////////////////////////////////////
Solucion Branch_and_Bound(const vector< vector<int> > & matriz,const vector<int> & arista_menor,int tama)
{
    vector<int> aux;
    priority_queue<Solucion> Q;
    Solucion n_e(tama), mejor_solucion(tama) ; //nodoe en expansion
    mejor_solucion.greedy(matriz);//calculamos la cota pro greedy
    int CG=mejor_solucion.getDistancia(); // Cota Global
    int distancia_actual=0;
    Q.push(n_e);
    while ( !Q.empty() && (Q.top().CotaLocal() < CG) ) {
        n_e = Q.top();
        Q.pop();
        aux=n_e.resto_ciudades();
        for(int i=0; i<aux.size(); i++) {
            n_e.anadirciudad(aux[i],matriz);//añadimos ciudad y le sumamos distancia
            n_e.quitarcidudadRestante(aux[i]);//quietamos la ciudad de ciudadrestante
            if ( n_e.EsSolucion(tama) ) {
                distancia_actual = n_e.Evalua(matriz);
                if (distancia_actual < CG) {
                    CG = distancia_actual;
                    mejor_solucion = n_e;
                }
            }
            else {
                n_e.calcularCotaLocal(arista_menor);
                if (n_e.CotaLocal()<CG ) {
                    Q.push( n_e );
                }
            }
            n_e.quitarciudad(matriz);//la ultima que se ha añadido
            n_e.anadircidudadRestante(aux[i]);//añadimos la ultma que se quito
        }
    }
    return mejor_solucion;
}

////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
    map<int, pair<double, double> >  m;//un map con las posicion y las dimensiones.
    vector< vector<int> >  matriz;//cremaos un matriz con la distnacia entre dos pueblos
    vector<int> ciu;//vector
    vector<int> menor_arista;
    int tama=0,distancia=0;
    //--------------------------------------------------------------------
    //calcualr matriz, menor_arista y m.
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
    menor_arista=calcularMenorArista(matriz);
    //------------------------------------------------------------------------
    Solucion s=Branch_and_Bound(matriz,menor_arista,tama);
    //s.mostrar();
    ciu=s.devolverSolucion();
    distancia=s.getDistancia();
    mostrar_resultado(ciu,m);//añade la ciduad 1
    cout<<"distancia: "<<distancia<<endl;
    cout<<endl;
    return 0;
}
