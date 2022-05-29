#include <iostream>
#include <string>
#include "Grafo.h"
using namespace std;
constexpr int CHAR_LENGTH = 1;

/*
//Verifica que para cada simbolo en T, este esta dentro del alfabeto
bool  is_Correct(string T, string alfabeto){ // o(N^2)
    for(char item: T){
        for(char simbolo: alfabeto){
            if(item == simbolo)
                break;
            if(simbolo == alfabeto.back())
                return false;
        }
    }
    return true;
}*/

grafo funcion_pregunta_1(){
    grafo resultado(10);

    string alfabeto;
    int num_Ts;
    cout<<"Introduzca el alfabeto:"; cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";cin>> num_Ts;

    string* Ts = new string[num_Ts]; //Reserva de memoria de las cadenas en T

    int contT = 0;//contador

    while(contT < num_Ts){//Lectura de cadenas
        cin >> Ts[contT];
        ++contT;
    }

    //CODIGO DEL PROBLEMA
    resultado.CreateVertex(0);// Nodo inicial.
    resultado.CreateEdge(alfabeto, 0, 0); //Transicion consigo mismo.
    resultado.createEfinal(num_Ts);

    contT = 1; //Me ayudara a llevar la cuenta del vertice donde estoy.
    bool primero = true;

    for(int x = 0; x < num_Ts; ++x) {
        for (auto caracter: Ts[x]) {
            resultado.CreateVertex(contT); //Primero creo el vertice
            string ch_string(CHAR_LENGTH, caracter);

            //Si es el primer caracter de T debe tener una conexion con el vertice 0
            if (primero) {
                resultado.CreateEdge(ch_string, 0, contT);
                primero = false;
            } else {
                //Sino se conecta con el anterior
                resultado.CreateEdge(ch_string, contT - 1, contT);
            }

            ++contT;
        }
        resultado.setEfinal(contT-1);
        primero = true;
    }

    return resultado;
}

void Pregunta_1(){
    grafo  a = funcion_pregunta_1();
    a.display();

    cout << "estados finales" << endl;
    for(int x = 0; x < 2; ++x){
        cout << a.ids_final[x] << " ";
    }
    cout << endl;

    a.clear();
}

void Pregunta_2(){
    grafo  a = funcion_pregunta_1();

    int num_Ss;
    cout<<"Introduzca la cantidad de cadenas(S):";cin>> num_Ss;

    string* Ss = new string[num_Ss]; //Reserva de memoria de las cadenas en S

    int contS = 0;//contador

    while(contS < num_Ss){//Lectura de cadenas
        cin >> Ss[contS];
        ++contS;
    }

    //Codigo
}


void ejemplo(){
    grafo nuevo(2);
    nuevo.CreateVertex(0);
    nuevo.CreateVertex(1);
    nuevo.CreateVertex(2);
    nuevo.CreateEdge("ed", 0, 0);
    nuevo.CreateEdge("e", 0, 1);
    nuevo.CreateEdge("d", 1, 2);
    nuevo.display();
}

int main() {
    Pregunta_1();
    //Pregunta_2();
    // codigo git: git pull ,  git reset --hard f7f436dbaaf0a4cfd71870f1d82536208c6675dc

    return 0;
}