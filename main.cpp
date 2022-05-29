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



grafo funcion_pregunta_1(string alfabeto, int num_Ts){
    grafo resultado(10);

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
    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;

    grafo  a = funcion_pregunta_1(alfabeto, num_Ts);
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
    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;

    grafo  a = funcion_pregunta_1(alfabeto, num_Ts);

    int num_Ss;
    cout << "Introduzca la cantidad de Ss: ";
    cin>> num_Ss;
    string* Ss = new string[num_Ss]; //Reserva de memoria de las cadenas en S
    int contS = 0;//contador
    while(contS < num_Ss){//Lectura de cadenas
        cin >> Ss[contS];
        ++contS;
    }

    bool* res = new bool[num_Ss] {}; //Me indica si las cadenas fueron aceptadas o no, por defecto seran false;

    queue<int> cola;
    int size_cola;//Tamanho de la cola en la iteracion pasada.

    for(int x = 0; x < num_Ss; ++x){
        cola.push(0);
        size_cola = 1;

        for(auto caract: Ss[x]){
            while(size_cola > 0){
                int state = cola.front();
                cola.pop();
                int num_final = 0;//Me dice a cuantos estados puedo llegar

                if(is_Final(a, state)) {//Compruebo si el estado actual es final
                    res[x] = true;
                    break;
                }

                string ch_string(CHAR_LENGTH, caract);
                int* EstadosPosibles = a.GetAlcance(state, ch_string, num_final);
                for(int x = 0; x <  num_final; ++x){
                    cola.push(EstadosPosibles[x]);
                }
                --size_cola;
            }
            if(res[x]) //Si ya determine que la cadena es aceptada, salto a la siguiente cadena.
                break;

            size_cola = cola.size();
        }

        //Verifico que los estados que quedan en la cola no sean estados finales. Ademas limpio la cola para la siguiente iteracion.
        while(!cola.empty()){
            int current = cola.front();
            cola.pop();
            if(is_Final(a, current)) {
                res[x] = true;
            }
        }
    }

    //Impresion de si fue aceptado o no
    for(int x = 0; x < num_Ss; ++x){
        if(res[x])
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;
    }

    //Liberacion de memoria
    delete [] res;
}

void Pregunta_3(){
    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;

    grafo  a = funcion_pregunta_1(alfabeto, num_Ts);

    int* matriz_dfn[a.get_size()][alfabeto.length()];
    int size_dfn=0;
    int count =0;

    for(int i=0;i<a.get_size();i++){
        for(int j=0;j<alfabeto.length();j++){
            string temp;
            matriz_dfn[i][j] = a.get_alcance(i,alfabeto[j],size_dfn);
            for(int k=0;k<size_dfn;k++){
                cout<<*(matriz_dfn[i][j]+k)<<",";
            }
            size_dfn=0;
            cout<<"   ";
        }
        cout<<endl;
    }


    


    grafo result_dfn(10);


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


void prueba_Alcance(){
    int size = 0;

    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;


    grafo a = funcion_pregunta_1(alfabeto, num_Ts);
    a.display();
    cout<<a.get_size();
    int* array = a.GetAlcance(0,"w", size);

    cout<<endl;

    for(int i=0;i<size;i++){
        cout<<*(array+i)<<" ";
    }

    cout<<endl<<size;

}
int main() {
    //Pregunta_1();
    //Pregunta_2();
    // codigo git: git pull ,  git reset --hard f7f436dbaaf0a4cfd71870f1d82536208c6675dc

    //ejemplo();
    //prueba_Alcance();
    Pregunta_3();

    return 0;
}