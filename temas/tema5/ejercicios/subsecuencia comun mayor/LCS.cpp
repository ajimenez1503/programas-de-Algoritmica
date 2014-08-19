/* (C) Programmed by:
   Antonio Jimenez Martínez

Asignatura Algoritmica (ALG)
Problemas tema 5: Programación dinámica
Version:0.1

EJERCICIO subsecuencia mayor comun

averiguar la subcadena de simbolos en orden, de mayor longitud.
No tiene que ser caracteres consecutivos.

*/

#include <iostream>
#include <iomanip>      // std::setw
#include <vector>
#include <string>
#include <utility>
#include <cstdlib>
using namespace std;

//mostramos cadeas de texto
void mostrar(vector<char> s1,vector<char> s2) {
    for(int i=0; i<s1.size(); i++) cout<<s1[i]<<setw(3);
    cout<<endl;
    for(int i=0; i<s2.size(); i++) cout<<s2[i]<<setw(3);
    cout<<endl;
}

//mostramos la tabla de suproblemas
void mostrar (const vector< vector<int> > & m,vector<char> s1,vector<char> s2) {
    cout<<"la tabla es:"<<endl;
    cout<<setw(3);
    cout<<"      ";//<<setw(3);
    for(int i=0; i<s2.size(); i++) cout<<s2[i]<<setw(3);
    cout<<endl;
    cout<<endl;
    for(int i=0; i<s1.size(); i++) {
        cout<<s1[i]<<setw(3)<<"   ";
        for(int j=0; j<m[i].size(); j++)
            cout<<m[i][j]<<setw(3);
        cout<<endl;
    }
}

//calcula el maximo de dos numeros
int max(int a,int b) {
    if(a>=b) return a;
    else return b;
}

//devuelve el tamaño de la subcadena maxima.
//si x[i ]==y[ j ]  c[i-1, j -1] + 1
//en otro caso  max(c[i, j - 1], c[i - 1, j ])
int lcs(int n,vector< vector<int> > & matriz,vector<char> s1,vector<char> s2) {
    for(int i=1; i<n; i++) {
        for(int j=1; j<n; j++) {
            if (s1[i]==s2[j]) {
                matriz[i][j]=matriz[i-1][j-1]+1;
            }
            else {
                matriz[i][j]=max(matriz[i-1][j],matriz[i][j-1]);
            }
        }
    }
    return matriz[n-1][n-1];
}

//calcula cuales han sido las letras usadas
void letrasusadas(const vector< vector<int> > & matriz,int n,vector<char> s1,vector<char> s2) {
    int i=n-1;
    int j=n-1;
    while(j>0 && i>0) {
        if(i>0 && j>0 && matriz[i][j]==(matriz[i-1][j-1]+1) && s1[i]==s2[j]) {
            cout<<"usamos "<<s1[i]<<endl;
            j--;
            i--;
        }
        else if (j>0 && matriz[i][j]==matriz[i][j-1]) {
            j--;
        }
        else if(i>0 && matriz[i][j]==matriz[i-1][j]) {
            i--;
        }
    }
}

int main() {
    int n = 6;
    //////////////////////////
    vector<char> s1, s2;
    s1.push_back(' ');
    s2.push_back(' ');
    s1.push_back('B');
    s1.push_back('D');
    s1.push_back('C');
    s1.push_back('A');
    s1.push_back('B');
    s2.push_back('A');
    s2.push_back('B');
    s2.push_back('C');
    s2.push_back('B');
    s2.push_back('W');
    //////////////////////////
    mostrar(s1,s2);
    vector< vector<int> >  matriz;
    matriz.resize(n, vector<int>(n,0));
    cout<<"La longitud maxima es : "<<lcs(n,matriz,s1,s2)<<endl;
    mostrar(matriz,s1,s2);
    cout<<endl;
    letrasusadas(matriz,n,s1,s2);

}
