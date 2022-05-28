#include <iostream>
#include <string>
#include "Grafo.h"
using namespace std;

//Verifica que para cada simbolo en T, este esta dentro del alfabeto
bool is_Correct(string T, string alfabeto){ //o(N^2)
    for(char item: T){
        for(char simbolo: alfabeto){
            if(item == simbolo)
                break;
            if(simbolo == alfabeto.back())
                return false;
        }
    }
    return true;
}

grafo Pregunta_1(){
    grafo resultado(10);

    string alfabeto;
    int num_Ts;
    cin >> alfabeto >> num_Ts;

    string* Ts = new string[num_Ts];
    int contT = 0;

    while(contT < num_Ts){
        cin >> Ts[contT];
        ++contT;
    }


    //Entrada de las cadenas a probar:
    int num_cadenas;
    cin >> num_cadenas;
    string* Ss = new string[num_cadenas];

    contT = 0;
    while(contT < num_cadenas){
        cin >> Ts[contT];
        ++contT;
    }



    cout << "Todo bien por ahora" << endl;

    delete [] Ts;
    delete [] Ss;
    return resultado;
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
    ejemplo();
    return 0;
}