/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 4: Backtracking
Version:0.1

EJERCICIO mochila
Tenemos n objetos y una mochila. El objeto i tiene un
peso wi y la mochila tiene una capacidad M.
Si metemos en la mochila el objeto i, generamos un
beneficio de valor pi
El objetivo es rellenar la mochila de tal manera que se
maximice el beneficio que producen los objetos que se
transportan, con la limitación de la capacidad de valor M.

El espacio de soluciones consiste en asignar valores 0 ó 1 a cada objeto
(seleccionar o no el objeto)
*/

using namespace std;
//estados 2(nulo),1,0,-1(end)
class solucion {
private:
    float b_local,b_global;
    vector<int> x;
    vector <pair<float,float> > orig;//precondicion vector ordenado
    int m;
    float s;
    //m es el tamaño maximo
    //s es la suma de lo que llevamos
public:
    solucion(int n,int tama) { //constructor
        m=tama;
        s=0;
        b_local=0.0;
        b_global=0.0;
        x.resize(n,2);
        orig.resize(n);
        genera_orig(n);
        ordenar_orig();
        mostrar_orig();
    }
    int size() const {
        x.size();
    }
    void iniciacomp(int k) {
        x[k]=2;//2=NULO
    }
    void sigvalcomp(int k) {
        x[k]--;
        if(x[k]==1) {//si lo cogemos el valor en k, se lo sumamos a s
            s+=orig[k].second;
            b_local+=orig[k].first;
        }
        if(x[k]==0) {//si no cogemos le valor en k, se lo restamos a s, ( ya que lo habiamos introducido antes en la x[k]==1).
            s-=orig[k].second;
            b_local-=orig[k].first;
        }
    }
    bool todosgenerados(int k) {
        return x[k]==-1;//devuelve true si estamos ya en el ultimo.
    }
    int decision(int k) {
        return x[k];
    }
    //expresa la solucion
    void procesasolucion() {
        if(b_global<b_local) {
            b_global=b_local;
            cout<<"solucion"<<endl;
            for(int i=0; i<size(); i++) {
                if(x[i]==1) { //elemento selecionado
                    cout<<orig[i].first<<" "<<orig[i].second<<" densidad "<<orig[i].first/orig[i].second<<endl;
                }
            }
            cout<<endl<<"beneficio total es: "<<b_global<<endl;
        }
        b_local=0;
    }

    //comprueba si es factible
    bool factible(int k) {
        return (s<=m);
    }
    void VueltaAtras(int k) {
        if(k!=size()) {
            x[k] = 2;//y pone k a nulo ya que en le back_recursivo(k+1) lo habram modificado.
        }
    }

    //ordena el vector de objetos a partir de la densidad
    void ordenar_orig() {
        int j;
        pair<float,float> temp;
        for(int i=1; i<orig.size(); i++) {
            temp=orig[i];
            j=i-1;
            while((orig[j].first/orig[j].second<temp.first/temp.second) && (j>=0) ) {
                orig[j+1]=orig[j];
                j--;
            }
            orig[j+1]=temp;

        }

    }

//muestra el vectro de objetos original
    void mostrar_orig() {
        cout<<"mostrar original"<<endl;
        for(int i=0; i<orig.size(); i++) {
            cout<<orig[i].first<<" "<<orig[i].second<<" densidad "<<orig[i].first/orig[i].second<<endl;
        }
        cout<<endl;
    }

//crea el vector de objetos de forma aleatoria
    void genera_orig(int n) {
        srand(time(0));
        for(int i=0; i<n; i++) {
            orig[i].first=(rand()%50)+1;//aleatorio entre 1-100
            orig[i].second=(rand()%50)+1;//aleatorio entre 1-100
        }
    }

};
