/* (C) Programmed by:
   	Antonio Jimenez Martínez
	Alejandro Casado Quijada
	Andrés Ortiz Corrales
	Jesús Prieto López
	Salvador Rueda Molina

Asignatura Algoritmica (ALG)
practica 2: Divide y Venceras
Version:0.1

EJERCICIO vector unimodal.

Sea un vector v de números de tamaño n, todos distintos, de forma que existe un índice p
(que no es ni el primero ni el último) tal que a la izquierda de p los números están ordenados
de forma creciente y a la derecha de p están ordenados de forma decreciente;
es decir ∀i, j ≤ p, i < j ⇒ v[i] < v[j] y ∀i, j ≥ p, i < j ⇒ v[i] > v[j] (de forma que el máximo se
encuentra en la posición p).
*/

//compilar g++ dyvunimodal.cpp -o dyvunimodal -std=gnu++0x

#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>

using namespace std::chrono;
//generador de ejemplos para el problema de la serie unimodal de números. Se genera un índice aleatorio entre 1 y n-2, se asigna el mayor entero (n-1) a ese índice, a los índices anteriores a p se le asignan valores en orden creciente (0,1,...,p-1) y a los índices mayores que p se le asignan valores en orden decreciente (n-2, n-1,...,p

double uniforme() //Genera un número uniformemente distribuido en el
//intervalo [0,1) a partir de uno de los generadores
//disponibles en C.
{
    double u;
    u = (double) rand();
    u = u/(double)(RAND_MAX+1.0);
    return u;
}

std::vector<int> genera (int n) {
    std::vector<int> T(n);
    srand(time(0));
    double u=uniforme();
    int p=1+(int)((n-2)*u);
    T[p]=n-1;
    for (int i=0; i<p; i++) T[i]=i;
    for (int i=p+1; i<n; i++) T[i]=n-1-i+p;
    return T;
}



int dyvunimodal(const std::vector<int> &v,int inicio,int fin) {
    int siz=fin-inicio+1;
    if(siz>2) {
        int p=(siz/2)+inicio;
        int a=v[p-1];
        int b=v[p+1];
        int vp=v[p];
        if(vp>a && vp>b) return vp; //si lo encuentra en la primera iteracion
        else {
            if(vp<b) {//coger la segunda mitad desde vp
                return dyvunimodal(v,p+1,fin);
            }
            if(vp>b) {//coger la primera mitad desde vp
                return dyvunimodal(v,inicio,p);
            }
        }
    }
    else {
        if(siz==2) { //si quedan 2 elementos, coje el mayor
            if(v[inicio]>v[fin]) return v[inicio];
            else return v[fin];
        }
        else //v.size()==1 si queda uno, lo devuelve
            return v[inicio];
    }
}


int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        std::cerr << "Formato " << argv[0] << " <num_elem>" << "\n";
        return -1;
    }
    high_resolution_clock::time_point tantes, tdespues;
    duration<double> transcurrido;
    int n = atoi(argv[1]);
    std::vector<int> t;
    t=genera(n);
    tantes = high_resolution_clock::now();
    dyvunimodal(t,0,n-1);//calcula de forma bruta el maximo en un vector unimodal
    tdespues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double> >(tdespues - tantes);
    std::cout <<"Para tamaño: "<<n<< " tiempo: " << transcurrido.count() << "\n";
    return 0;



}
