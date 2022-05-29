#include <iostream>
#include <string>
#include <queue>
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
    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;

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

//verifica si el estado es final o no
bool is_Final(grafo g, int estado){
    for(int x = 0; x < g.num_idsF; ++x){
        if(estado == g.ids_final[x]) return true;
    }
    return false;
}

void Pregunta_2(){
    grafo  a = funcion_pregunta_1();

    int num_Ss;
    cout<<"Introduzca la cantidad de cadenas(S):";
    cin>> num_Ss;
    string* Ss = new string[num_Ss]; //Reserva de memoria de las cadenas en S
    int contS = 0;//contador
    while(contS < num_Ss){//Lectura de cadenas
        cin >> Ss[contS];
        ++contS;
    }

    //Respuestas
    bool* res = new bool[num_Ss]; //Me indica si la cadena fue aceptada o no
    int pos_res = 0; //Me indica en que posicion dentro del array estoy.

    queue<int> cola;
    int size_cola;//Me ayuda a llevar la cuenta de cuantos estados debo verificar.

    for(int x = 0; x < num_Ss; ++x){//Recorremos cada cadenas
        cola.push(0); //A cada iteracion primero ponemos el estado inicial.
        size_cola = 1;

        for(auto caract: Ss[x]){//Recorremos cada caracter de S
            while(size_cola > 0){
                //Se recorre cada elemento de la cola(Los estados) con el caracter actual
                int state = cola.front();
                int num_final;//Me dice a cuantos estados puedo llegar
                cola.pop();
                //Verificacion de a que estados puedo llegar, desde el estadoCurrent con la transicion(caract)
                //Posible solucion, implementar un metodo en el grafo. int* GetAlcance(int estado, char transicion, int& variable_tamanho)

                if(is_Final(a, state)) {
                    //Salir de la iteracion de esta cadena y pasar a la siguiente cadena.
                    res[pos_res] = true;
                    break;
                }

                int* EstadosPosibles; // = getAlcance(state, caract);
                for(int x = 0; x <  num_final; ++x){
                    cola.push(EstadosPosibles[x]);
                }
                --size_cola;
            }

            size_cola = cola.size();
        }
        //Verifico que los estados que quedan en la cola no sean estados finales. y ademas limpio la cola para la siguiente iteracion.
        while(!cola.empty()){
            int current = cola.front();
            cola.pop();

            if(is_Final(a, current))
                    res[pos_res] = true;
        }

        res[pos_res] = false;
        ++pos_res;
    }



}


void ejemplo(){
    grafo nuevo(2);
    nuevo.createEfinal(2);

    nuevo.CreateVertex(0);
    nuevo.CreateVertex(1);
    nuevo.CreateVertex(2);
    nuevo.CreateEdge("ed", 0, 0);
    nuevo.CreateEdge("e", 0, 1);
    nuevo.CreateEdge("d", 1, 2);

    nuevo.setEfinal(1);
    nuevo.setEfinal(2);

    nuevo.display();
    for(int x = 0; x < 3; x++){
        cout << x << " is Final " <<  is_Final(nuevo, x) << endl;
    }
    //Funcion is_Final funciona correctamente.


}

int main() {
    //Pregunta_1();
    //Pregunta_2();
    // codigo git: git pull ,  git reset --hard f7f436dbaaf0a4cfd71870f1d82536208c6675dc
    int size = 0;

    grafo a = funcion_pregunta_1();
    a.display();
    int* array = a.GetAlcance(0,"w", size);

    cout<<endl;

    for(int i=0;i<size;i++){
        cout<<*(array+i)<<" ";
    }

    cout<<endl<<size;

    //ejemplo();

    return 0;
}