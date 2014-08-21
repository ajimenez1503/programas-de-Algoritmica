/* (C) Programmed by:
   	Antonio Jimenez Martínez
	Alejandro Casado Quijada
	Andrés Ortiz Corrales
	Jesús Prieto López
	Salvador Rueda Molina

Asignatura Algoritmica (ALG)
practica 4: Backtracking
Version:0.1

EJERCICIO ITV.

Una estación de ITV consta de m líneas de inspección de vehículos iguales. Hay un total de
n vehículos que necesitan inspección. En función de sus características, cada vehículo
tardara en ser inspeccionado un tiempo ti; i = 1,...., n. Se desea encontrar la manera de
atender a todos los n vehículos y acabar en el menor tiempo posible. Diseñamos e
implementamos un algoritmo vuelta atrás que determine como asignar los vehículos a las
líneas. Utilizando una función de factibilidad y una poda.
*/

using namespace std;

//posibles estados:0,1,2,3... lineas+1
//Comienza en linea 0
//0==NULO
//lineas+1==END
class solucion {
private:

    vector<int> sol; //solucion, cada posicion es un coche y su valor la cola
    vector<int> x;
    vector<int> vehiculos;//cada posicion un coche y su tiempo.
    int lineas,min_time;
public:
    solucion(int numero_vehiculos,int num_lineas) {
        srand(time(0));
        for(int i=0; i<numero_vehiculos; i++) {
            vehiculos.push_back((rand()%50)+1);//aleatorio entre 1-50
        }
        lineas=num_lineas;
        calcular_greedy(); //resultado greedy para tener referencia
    }

    int calc_time(const vector<int> &x2) const { //calcula el tiempo dado por x2
        vector<int> times(lineas,0); //vector con los tiempos de cada linea
        for(int i=0; i<x2.size(); i++) {
            times[x2[i]]+=vehiculos[i]; //en la cola dada por x[i] añado el tiempo del vehiculo i
        }
        int r=times[0];
        for(int i=1; i<times.size(); i++) {
            if(times[i]>r) r=times[i];
        }
        return r;
    }

    //Calcula una solucion mediante algoritmo greedy como cota
    void calcular_greedy() {
        vector<int> times(lineas,0);
        for(int i=0; i<vehiculos.size(); i++) {
            int minlin=0; //linea con menor t
            for(int j=1; j<times.size() && times[minlin]>0; j++)
                if(times[minlin]>times[j]) minlin=j;
            times[minlin]+=vehiculos[i]; //añade el siguiente vehiculo a la linea con menos tiempo
            sol.push_back(minlin);
            min_time=calc_time(sol); //calcula el tiempo solucion de greedy
        }
    }


    //añade un vehiculo a la solucion parcial x
    void add_vehicle() {
        x.push_back(0);
    }
    int num_vehiculos() {
        return vehiculos.size();
    }
    int size() {
        return x.size();
    }

    int num_lineas() {
        return lineas;
    }
    void last_vehicle_change_line() {
        x[x.size()-1]++;
    }
    void erase_vehicle() {
        x.pop_back();
    }
    void mostrar() {
        cout<<"Vehiculos:"<<vehiculos.size()<<"     lineas:"<<lineas<<endl;
        cout<<"Tiempo Solucion:"<<min_time<<endl;
        for(int i=0; i<vehiculos.size(); i++) {
            cout<<"Vehiculo "<<i<<"("<<vehiculos[i]<<") -- linea "<<sol[i]<<endl;
        }
    }

    void actualizar_solucion() {
        int tim=calc_time(x);
        if(tim<min_time) {
            sol=x;
            min_time=tim;
        }
    }
    bool factible() {
        //no puede darse el caso de que no se siga el orden para coger. es decir a partir de un 0 todo 0. no vale (0,1,4,...)
        return (calc_time(x)<min_time);
        //maxtiempo+ lo que qeda /numerolineas<cota
    }

};
