#include <iostream>
#include <string>
#include "Algorithms/ProblemaSubstring.h"

using namespace std;

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


//ejemplo: bloque* fila son bloques


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

    bloque a;
    a.array = new int[1] {};//Array solo con el estado 0
    a.size = 1;
    bloque prueba = calculate(a, 'e', nuevo);

    for(int x = 0; x < prueba.size; ++x){
        cout << prueba.array[x] << " ";
    }
    cout << endl;
    //Salida esperada: 0 1 o tambien: 1 0
}


void prueba_Alcance(){
    int size = 0;

    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;


    grafo a = buildAFN(alfabeto, num_Ts);
    a.display();
    cout<<a.get_size();
    int* array = a.GetAlcance(0,"w", size);

    cout<<endl;

    for(int i=0;i<size;i++){
        cout<<*(array+i)<<" ";
    }

    cout<<endl<<size;

}

void ejemplo1(){
    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;
    grafo  a = buildAFN(alfabeto, num_Ts);

    bloque* MatrizFilas = new bloque[a.get_size()*alfabeto.length()];

    int pos_Matriz = 0; //Me indica la posicion dentro de la matrizFilas.

    int* Efinales = new int[num_Ts];//Contiene los estados finales del AFD
    int pos_EFinales = 0;

    //Agrego el array con el estado inicial.
    int* inicial = new int [1] {};
    MatrizFilas[pos_Matriz].array = inicial;
    MatrizFilas[pos_Matriz].size = 1;
    ++pos_Matriz;

    for(int i=0;i<alfabeto.length();i++){
        bloque llegada = calculate(MatrizFilas[0], alfabeto[i], a);
        for(int j=0;j<llegada.size;j++){
            cout<<llegada.array[j]<<" ";
        }
        cout<<endl;
    }

    bloque abc;
    abc.array = inicial;
    abc.size = 1;

    if(igualdad(MatrizFilas,1 ,abc) == -1){
        cout << "No esta en la matriz" << endl;
    }else{
        cout << "Esta en la matriz " << endl;
    }


    cout << endl;

}


void prueba_igualdad(){
    bloque* ArrBloque = new bloque[2];
    int* arr = new int[1];
    arr[0] = 3;
    ArrBloque[0].array = arr;
    ArrBloque[0].size = 1;

    int* arr2 = new int[2];
    arr2[0] = 0;
    arr2[1] = 1;
    ArrBloque[1].array = arr2;
    ArrBloque[1].size = 2;


    bloque prueba;
    prueba.array = arr2;
    prueba.size = 2;

    if(igualdad(ArrBloque,2 ,prueba) == -1){
        cout << "No esta en la matriz" << endl;
    }else{
        cout << "Esta en la matriz " << endl;
    }

    bloque a;
    int* ar = new int[3] {0,1,2};
    a.array = ar;
    a.size = 3;


    if(igualdad(ArrBloque,2 ,a) == -1){
        cout << "No esta en la matriz" << endl;
    }else{
        cout << "Esta en la matriz " << endl;
    }

}

int main() {
    //Pregunta_1();
    //Pregunta_2();
    // codigo git: git pull ,  git reset --hard f7f436dbaaf0a4cfd71870f1d82536208c6675dc

    //ejemplo();
    //prueba_Alcance();
    Pregunta_3();

    //ejemplo1();
    //prueba_igualdad();

    return 0;
}
