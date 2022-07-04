//
// Created by isaac on 4/07/2022.
//

#include "Ejercicio1.h"
#include <fstream>

string Cadena(string alfabeto){
    char strrnd[10];
    srand(time(NULL));
    string result;
    for(int i=0; i <= 9; i++){
        int ite = 0 + rand() % ((alfabeto.length()-1) - 0);
        result.push_back(alfabeto[ite]);
    }
    return result;
};

grafo buildAFN_x(string alfabeto, int num_Ts){
    grafo resultado(10);

    string* Ts = new string[num_Ts]; //Reserva de memoria de las cadenas en T

    int contT = 0;//contador

    while(contT < num_Ts){//Lectura de cadenas
        Ts[contT] = Cadena(alfabeto);
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
            string ch_string(CHAR_LENGT, caracter);

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

void Ejercicio_1(){
    string alfabeto= "ABCDEFGHIJKLMNOPQRSTVWXYZ1234567890abcdefghijklmnopqrstuvwxyz";
    int num_Ts;

    ofstream file("tiempo1.txt",ios::app | ios::out);
//start
    for(int x=2;x<1000000;x++){
        auto start = std::chrono::high_resolution_clock::now();
        grafo AFN = buildAFN_x(alfabeto, x);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double,std::milli> float_ms = end - start;
        string time = to_string(float_ms.count()/1000.00);
        file.write(time.data(),time.size());
        file<<'\n';
    }
//end
}
