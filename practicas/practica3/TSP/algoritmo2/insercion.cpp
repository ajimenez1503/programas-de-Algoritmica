/* (C) Programmed by:
   	Antonio Jimenez Martínez
	Alejandro Casado Quijada
	Andrés Ortiz Corrales
	Jesús Prieto López
	Salvador Rueda Molina

Asignatura Algoritmica (ALG)
practica 3: greedy (voraz)
Version:0.1

EJERCICIO Comerciante de comercio (TSP) Estrategias de inserción

Dado un conjunto de ciudades y una matriz con las distancias entre todas ellas, un viajante debe recorrer
todas las ciudades exactamente una vez, regresando al punto de partida, de forma tal que la distancia
recorrida sea mínima.
Mas formalmente, dado un grafo G, conexo y ponderado, se trata de hallar el ciclo hamiltoniano de mínimo
peso de ese grafo.

En las estrategias de inserción, la idea es comenzar con un recorrido parcial, que incluya algunas de las
ciudades, y luego extender este recorrido insertando las ciudades restantes.
El recorrido inicial se puede construir a partir de las tres ciudades que formen un triángulo lo más grande
posible: por ejemplo, eligiendo la ciudad que está más a Este, la que está más al Oeste, y la que está más al
norte.
Vamos recorriendo el vector de ciudades no seleccionadas e insertando cada una de ellas en cada posible
posición. Utilizando el criterio de inserción más económica, elegimos aquella ciudad y su posición en el
camino final, que provoque un menor incremente en la longitud total del circuito.


*/

//compilar: g++ insercion.cpp -o insercion
//ejecutar: ./insercion berlin52.tsp


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
#include <list>
using namespace std;

//Lee el fichero de coordenadas de un fichero de TSP y el recorrido óptimo (en ese orden) y da como salida el fichero de coordenadas pero reordenado según el orden óptimo, para poder dibujarlo con gnuplot

class CLParser {
public:

    CLParser(int argc_, char *argv_[],bool switches_on_=false);
    ~CLParser() {}

    string get_arg(int i);
    string get_arg(string s);

private:

    int argc;
    vector<string> argv;

    bool switches_on;
    map<string,string> switch_map;
};

CLParser::CLParser(int argc_, char *argv_[],bool switches_on_) {
    argc=argc_;
    argv.resize(argc);
    copy(argv_,argv_+argc,argv.begin());
    switches_on=switches_on_;
    //map the switches to the actual
    //arguments if necessary
    if(switches_on) {
        vector<string>::iterator it1,it2;
        it1=argv.begin();
        it2=it1+1;
        while(true) {
            if(it1==argv.end()) break;
            if(it2==argv.end()) break;
            if((*it1)[0]=='-')
                switch_map[*it1]=*(it2);
            it1++;
            it2++;
        }
    }
}

string CLParser::get_arg(int i) {
    if(i>=0&&i<argc)
        return argv[i];
    return "";
}

string CLParser::get_arg(string s) {
    if(!switches_on) return "";
    if(switch_map.find(s)!=switch_map.end())
        return switch_map[s];
    return "";
}



/*
*/
void leer_puntos(string &nombre, map<int, pair<double, double> > &M) {
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;
    datos.open(nombre.c_str());
    if(datos.is_open()) {
        datos >> s; // Leo "dimension:"
        datos >> n;
        int i=0;
        while(i<n) {
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
void leer_orden(string &nombre, vector<int> &V) {
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;
    datos.open(nombre.c_str());
    if(datos.is_open()) {
        datos >> s; // Leo "dimension:"
        datos >> n;
        V.reserve(n);
        int i=0;
        while(i<n) {
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
void mostrar(const vector< vector<int> > &m) {
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
int euclides(double xi,double yi,double xj,double yj) {
    double aux1=(xj-xi)*(xj-xi);
    double aux2=(yj-yi)*(yj-yi);
    aux2=aux1+aux2;
    int aux=sqrt(aux2);
    return aux;
}

//creamos la matriz de distancias
//Asignamos a la distnacia entre la misma ciudad como -1.
void calcular_matriz(map<int, pair<double, double> >  m,vector< vector<int> > &matriz) {
    for(int i=0; i<matriz.size(); i++) {
        for(int j=0; j<matriz[i].size(); j++)
            if(i!=j) {
                matriz[i][j]=euclides(m[i+1].first,m[i+1].second,m[j+1].first,m[j+1].second);
            }
    }
}
/////////////////////////////////////**************////////////////

//distancia entre  2 iudades
int distancia(int ciudad1,int ciudad2,const vector<vector<int> > &m) {
    ciudad1--;
    ciudad2--;
    return m[ciudad1][ciudad2];
}

//calcula la distancia total de una lista de ciudades
int distancia_total(const list<int> &result,const vector<vector<int> > &m) {
    list<int>::const_iterator it1,it2;
    int dist=0;
    it1=result.begin();
    it2=result.begin();
    it1++;

    for(; it1!=result.end(); it1++) {
        dist+=distancia(*it1,*it2,m);
        it2=it1;
    }
    return dist;
}

//distancia que supone insertar una ciudad
pair<int,list<int>::iterator> aumento_de_distancia(list<int> &result,const vector<vector<int> > &matriz,int ciudad) {
    list<int>::iterator it1=result.begin(); //apunta a la primera ciudad de la lista
    list<int>::iterator it2=result.end();//apunta a la ultima ciudad de la lista
    list<int>::iterator pos=result.begin();
    it2--;
    int dist;
    dist=distancia(*it1,ciudad,matriz)+distancia(*it2,ciudad,matriz);
    dist-=distancia(*it1,*it2,matriz); //dist tiene el aumento de la distancia
    it2=it1;//it2 apunta a la primera ciudad
    it1++;//it apunta a la segunda ciudad
    for(; it1!=result.end(); it1++) {
        int a=*it1;
        int b=*it2;
        int dist2=distancia(a,ciudad,matriz)+distancia(b,ciudad,matriz);
        dist2-=distancia(a,b,matriz);
        if(dist2<dist) {
            dist=dist2;
            pos=it1;
        }
        it2=it1;
        it1++;
    }
    return make_pair(dist,pos);
}

//inserta ciudad en la posicion dada
void insertar_ciudad(list<int> &recorrido,int ciudad,list<int>::iterator it) {
    // it++;
    recorrido.insert(it,ciudad);
}

//elige la ciudad con menor distancia añadida y devuelve pair<pair<ciudad,distancia_añadida,posicion_en_lista>
pair<int,list<int>::iterator> elegir_ciudad(list<int> &result,const vector<vector<int> > &matriz,list<int> &left) {
    list<int>::iterator it,itselec;
    pair<int,list<int>::iterator> selec;
    bool b=false;
    int cit_selec;
    for(it=left.begin(); it!=left.end(); it++) {
        pair<int,list<int>::iterator> selec2;
        int cit=*it;
        selec2=aumento_de_distancia(result,matriz,cit);
        if(b==false) {
            b=true;
            selec=selec2;
            cit_selec=cit;
            itselec=it;
        }
        else if(selec2.first<selec.first) {
            selec=selec2;
            cit_selec=cit;
            itselec=it;
        }
    }
    left.erase(itselec);
    return make_pair(cit_selec,selec.second);
}


//tomamos como nodo inicial la ciudad 1. (0 en la matriz)
//entra la matriz
//devolvemos el vector de ciudades cogidas y la distancia.
list<int> recorrido(const vector<vector<int> > &matriz,const map<int, pair<double, double> >  &m,int &d) {
    int n=1,s=1,w=1;
    list<int> result;
    map<int,pair<double,double> >::const_iterator it=m.begin();
    list<int> left;
    left.push_back(1);
    pair<double,double> pn=(*it).second,ps=(*it).second,pw=(*it).second; //todas las posiciones a la primera ciudad de la lista
    it++;
    for(; it!=m.end(); it++) { //escojemos las ciudades mas al norte,sur y oeste
        left.push_back((*it).first);
        pair<double,double> p=(*it).second;
        int act_cit=(*it).first;
        if(p.first<pw.first) {
            pw=p;
            w=act_cit;
        }
        else if(p.second>pn.second || (n==w && n==1)) {
            pn=p;
            n=act_cit;
        }
        else if(p.second<ps.second || (s==w && s==1)) {
            ps=p;
            s=act_cit;
        }
    }
    //n,s,w forman el triangulo mas grande
    //suponemos que empezamos en n, una de las ciudades del triangulo
    result.push_back(n);
    result.push_back(s);
    result.push_back(w); //añadimos el triangulo al recorrido
    left.remove(n);
    left.remove(s);
    left.remove(w);
    //////////////
    while(left.size()>0) {
        pair<int,list<int>::iterator> pres;
        pres=elegir_ciudad(result,matriz,left);
        insertar_ciudad(result,pres.first,pres.second);
    }
    result.push_back(*(result.begin())); //volvemos a la primera ciudad
    d=distancia_total(result,matriz);
    return result;
}

//devuelve las ciudades ordenadas con sus coordenadas.
//para poder crear el camino en una grafica
void mostrar_resultado(const list<int> &result,const map<int,pair<double,double> > &m) {
    list<int>::const_iterator it;
    for(it=result.begin(); it!=result.end(); it++) {
        pair<double,double> p;
        p=(m.find(*it))->second;
        cout<<*it<<" "<<p.first<<" "<<p.second<<endl;
    }

}
int main(int argc, char *argv[]) {
    map<int, pair<double, double> >  m;//un map con las posicion y las dimensiones.
    vector< vector<int> >  matriz;//cremaos un matriz con la distnacia entre dos pueblos
    list<int> ciu;
    int tama=0,distancia=0;
    string fp;
    if(argc<2) {
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
    ciu=recorrido(matriz,m,distancia);
    mostrar_resultado(ciu,m);
    /*cout<<"La distancia total es: "<<distancia<<" y el orden de las ciudades es:"<<endl;
    for(list<int>::iterator it=ciu.begin();it!=ciu.end();it++) cout<<*it<<" ";
    cout<<endl;*/
    return 0;
}
