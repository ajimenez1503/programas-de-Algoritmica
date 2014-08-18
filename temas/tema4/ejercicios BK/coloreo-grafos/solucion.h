using namespace std;
//posibles estados: nulo,1,2,3,4,end
//4 colores
class solucion {
private:
    vector<int> x;//representa la solucion x[i]=color
    vector< vector<int> > m;//matriz de adyacencia de vertices .m[i][j]=1 vertice i y vertice j estan unidos. m[i][j]=o vertice i y vertice j no estan unidos.
public:
    solucion(int n) { //constructor
        m.resize(n, vector<int>(n,1));
        x.resize(n,0);
        crear();
    }
    //mostrar matriz de adjacencia
    void mostrar_matriz () {
        cout<<setw(3);
        for(int i=0; i<m.size(); i++) {
            for(int j=0; j<m[i].size(); j++)
                cout<<m[i][j]<<setw(3);
            cout<<endl;
        }
    }
    //creamos la matriz de adyacencia. Lo hacemos de forma aleatoria
    // m[i][j]=1 son adyacentes
    // m[i][j]=0 no son adyacentes
    void crear () {
        for(int i=0; i<m.size(); i++) {
            for(int j=0; j<m[i].size(); j++)
                if(i>j) {
                    m[i][j]=(rand()%2);//aleatorio entre 0-1;
                    m[j][i]=m[i][j];
                }
        }
    }
    //muestra los nodos que son adyacentes
    void mostrar () {
        for(int i=0; i<m.size(); i++) {
            cout<<"vertice "<<i<<" es adyacente a:";
            for(int j=0; j<m[i].size(); j++)
                if(m[i][j]==1) cout<<j<<"  ";
            cout<<endl;
        }
    }
    int size() const {
        x.size();
    }
    void iniciacomp(int k) {
        x[k]=0;//0=NULO
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
        for(int i=0; i<size(); i++) {
            cout<<"vertice "<<i<<" color: "<<x[i]<<endl;
        }
    }

    //si el nodo k tiene el mismo colo que un nodo adyacente suyo false.
    bool factible(int k) {
        for(int i=0; i<m[k].size(); i++)
            if(m[k][i]==1 && x[k]==x[i] && i!=k) return false;
        return true;
    }
};
