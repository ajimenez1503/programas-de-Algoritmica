using namespace std;
//estados 2,1,0,-1
class solucion {
private:
    vector<int> x;//vector estatico
    int pos_e;//pos de la ultima decision
    int tama;//tamaño maxim
    float ga,vo,estimador;//ganacia , volumen y estimador

public:
    solucion () { //constructor por defecto

    }

    solucion(int n,int tamano) { //constructor
        tama=tamano;
        ga=vo=0;
        pos_e=-1;
        x.resize(n,2);
    }
    int size() const {
        x.size();
    }
    bool EsSolucion() {
        return size()==pos_e+1;
    }
    int CompActual() {
        return pos_e;
    }
    void PrimerValorComp(int k) {
        pos_e=k;
        x[k]=2;//2=NULO
    }
    float Evalua() {
        return ga;
    }
    float CotaLocal() const {
        return estimador;
    }
    void SigValComp(int k,const vector <pair<float,float> > & orig) {
        x[k]--;
        if(x[k]==1) {//si lo cogemos el valor en k, se lo sumamos a s
            vo+=orig[k].second;
            ga+=orig[k].first;
        }
        if(x[k]==0) {//si no cogemos le valor en k, se lo restamos a s, ( ya que lo habiamos introducido antes en la x[k]==1).
            vo-=orig[k].second;
            ga-=orig[k].first;
        }
    }
    bool HayMasValores(int k) {
        return (k<size() && x[k]>-1);//devuelve false si estamos ya en el ultimo.
    }

    void mostrar_solucion(const vector <pair<float,float> > & orig) {
        cout<<"Solucion"<<endl;
        float peso=0.0,beneficio=0.0;
        for(int i=0; i<size(); i++) {
            if(x[i]==1) { //elemento selecionado
                cout<<orig[i].first<<" "<<orig[i].second<<" densidad "<<orig[i].first/orig[i].second<<endl;
                peso+=orig[i].second;
                beneficio+=orig[i].first;
            }
        }
        cout<<endl<<"beneficio total es: "<<beneficio<<" y el peso total es: "<<peso<<endl;
    }
    void calcularCotaLocal(const vector <pair<float,float> > & orig) { //claculamos la estimacion como el problema de la mochola por greedy fraccioanria
        estimador=ga;
        float aux_peso=vo;
        int k=pos_e+1;
        while(aux_peso<=tama and k<orig.size()) {
            estimador+=orig[k].first;
            aux_peso+=orig[k].second;
            k++;
        }
        if(k<orig.size()) estimador+=orig[k].first;


    }
    bool factible() {
        return (vo<=tama);
    }

    bool operator<(const solucion &s )const {
        return estimador<s.estimador;
    }


};
