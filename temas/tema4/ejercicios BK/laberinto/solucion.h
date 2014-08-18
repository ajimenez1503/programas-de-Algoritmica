/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Backtracking
Version:0.1

EJERCICIO laberinto
El laberinto puede modelarse como una serie
de nodos. En cada nodo hay que
tomar una decisión que nos conduce a otros nodos.
Buscar en el laberinto hasta encontrar una
salida. Si no se encuentra una salida, informar de
ello.
Hay 4 movimientos. Intentamos sucesivamente
movernos en cada una de las 4 direcciones.

En este problema la longitud del vector solución no
es constante, es la lista de posiciones
hasta llegar a la salida.


*/

using namespace std;
#define F 7
#define C 8
//x representa las acciones
//0 nulo,1 arriba,2 abajo,3 izq,4 derecha, 5 end
class solucion {
private:
    int posf,posc;//posicionesactuales
    vector<int> x;//representa la solucion
    vector< vector<char> >laberinto;
    vector< vector<int> >pasado;//si ha pasado esta a 1 y sino ha pasado a 0.
public:
    solucion(int i,int f) { //constructor
        //////////////////////////////////////crear laberinto
        vector < char > aux;
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('#');
        laberinto.push_back(aux);
        aux.clear();
        aux.push_back('#');
        aux.push_back(' ');
        aux.push_back(' ');
        aux.push_back(' ');
        aux.push_back(' ');
        aux.push_back(' ');
        aux.push_back('#');
        aux.push_back('#');
        laberinto.push_back(aux);
        aux.clear();
        aux.push_back('#');
        aux.push_back(' ');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back(' ');
        aux.push_back(' ');
        aux.push_back('#');
        aux.push_back('#');
        laberinto.push_back(aux);
        aux.clear();
        aux.push_back('#');
        aux.push_back(' ');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back(' ');
        aux.push_back(' ');
        aux.push_back('#');
        laberinto.push_back(aux);
        aux.clear();
        aux.push_back('#');
        aux.push_back(' ');
        aux.push_back('#');
        aux.push_back(' ');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back(' ');
        aux.push_back('#');
        laberinto.push_back(aux);
        aux.clear();
        aux.push_back('#');
        aux.push_back(' ');
        aux.push_back(' ');
        aux.push_back(' ');
        aux.push_back(' ');
        aux.push_back('#');
        aux.push_back(' ');
        aux.push_back('#');
        laberinto.push_back(aux);
        aux.clear();
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('S');
        aux.push_back('#');
        aux.push_back('#');
        aux.push_back('#');
        laberinto.push_back(aux);
        aux.clear();
        /*          laberinto={{'#','#','#','#','#','#','#','#'},
                               {'#',' ',' ',' ',' ',' ','#','#'},
                               {'#',' ','#','#',' ',' ','#','#'},
                               {'#',' ','#','#','#',' ',' ','#'},
                               {'#',' ','#',' ','#','#',' ','#'},
                               {'#',' ',' ',' ',' ','#',' ','#'},
                               {'#','#','#','#','S','#','#','#'}};
        */
        //////////////////////////////////////crear laberinto
        posf=i;
        posc=f;
        pasado.resize(F, vector<int>(C,0));
        pasado[posf][posc]=1;
    }
    void imprimir_laberinto() {
        for(int i=0; i<F; i++) {
            for(int j=0; j<C; j++)
                cout<<laberinto[i][j];
            cout<<endl;
        }
        cout<<endl;
    }

    void mostrar_salida() {
        cout<<"estamos en la posicion: "<<posf<<" "<<posc<<endl;
        for(int i=0; i<size(); i++) {
            if(x[i]==0) cout<<" nulo     ";
            else  if(x[i]==1) cout<<" arriba     ";
            else  if(x[i]==2) cout<<" abajo     ";
            else  if(x[i]==3) cout<<" izq     ";
            else  if(x[i]==4) cout<<" derch     ";
            else  if(x[i]==5) cout<<" end     ";
        }
        cout<<endl;
    }
    int size() const {
        x.size();
    }
    void iniciacomp(int k) {
        x.push_back(0);//0=NULO

    }
    void sigvalcomp(int k) {
        x[k]++;
    }
    bool todosgenerados(int k) {
        //5==NULO
        return x[k]==5;//devuelve true si estamos ya en el ultimo.
    }
    int decision(int k) {
        return x[k];
    }
    void procesasolucion() {
        mostrar_salida();
        cout<<endl;
    }
    bool encontrada() {
        return laberinto[posf][posc]=='S';
    }
    bool factible(int k) {
        if(x[k]==1) {
            if(posf-1>=0 && posf-1<F && (laberinto[posf-1][posc]==' ' || laberinto[posf-1][posc]=='S') && pasado[posf-1][posc]==0) {
                posf-=1;//modificamos posf
                pasado[posf][posc]=1;
                return true;
            }
        }//arriba
        else  if(x[k]==2) {
            if(posf+1>=0 && posf+1<F && (laberinto[posf+1][posc]==' ' || laberinto[posf+1][posc]=='S')&& pasado[posf+1][posc]==0) {
                posf+=1;//modificamos posf
                pasado[posf][posc]=1;
                return true;
            }
        }//abajo
        else  if(x[k]==3) {
            if(posc-1>=0 && posc-1<C && (laberinto[posf][posc-1]==' ' || laberinto[posf][posc-1]=='S') && pasado[posf][posc-1]==0) {
                posc-=1;//modificamos posf
                pasado[posf][posc]=1;
                return true;
            }
        }//izq
        else  if(x[k]==4) {
            if(posc+1>=0 && posc+1<C && (laberinto[posf][posc+1]==' ' || laberinto[posf][posc+1]=='S')&& pasado[posf][posc+1]==0) {
                posc+=1;//modificamos posf
                pasado[posf][posc]=1;
                return true;
            }
        }//derch
        return false;
    }
    void libera_posiciones(int k) { //desacemos cambios.
        if(k<size()-1) {//nos desacemos del ultimo elemento del vector variable. ya que ese es para k+1
            x.pop_back();
        }
        if(x[k]==1) {
            pasado[posf][posc]=0;
            posf+=1;//modificamos posf

        }//arriba
        else  if(x[k]==2) {
            pasado[posf][posc]=0;
            posf-=1;//modificamos posf
        }//abajo
        else  if(x[k]==3) {
            pasado[posf][posc]=0;
            posc+=1;//modificamos posf

        }//izq
        else  if(x[k]==4) {
            pasado[posf][posc]=0;
            posc-=1;//modificamos posf
        }//derch
    }

};
