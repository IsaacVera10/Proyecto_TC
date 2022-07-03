//
// Created by isaac on 30/05/2022.
//

#include "Funciones.h"

bool is_Final(grafo g, int estado){
    for(int x = 0; x < g.num_idsF; ++x){
        if(estado == g.ids_final[x]) return true;
    }
    return false;
}

bool is_Final(int* array, int size, int estado){
    for(int x = 0; x < size; ++x){
        if(estado == array[x]) return true;
    }
    return false;
}

bloque calculate(bloque& arreglo, char caracter, grafo graph){
    bloque result;

    int cont = 0;
    int indicator = 0;

    for(int i=0;i<arreglo.size;i++){
        int* temp= graph.get_alcance(arreglo.array[i], caracter, cont);

        result.resize(result.size + cont);

        for(int j=0;j<cont;j++){
            result.array[indicator] = temp[j];
            indicator++;
            result.size++;
        }
        cont = 0;
    }

    return result;
}

int igualdad(bloque* fila, int sizeFila, bloque& contenido){
    bool var = true;

    bloque temp;
    for(int i = 0; i < sizeFila; ++i){
        temp.array = fila[i].array;
        temp.size = fila[i].size;

        if(temp.size != contenido.size){
            var=false;
        }else{
            for(int j=0;j<contenido.size;++j){//comparo cada caracter
                if(contenido.array[j] != temp.array[j]){
                    var = false;
                }
            }
        }
        if(var == true)
            return i;

        var=true;
    }

    return -1;
}

grafo buildAFN(string alfabeto, int num_Ts){
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

grafo2 buildAFD(string alfabeto, int num_Ts, grafo graph){
    grafo2 resultado(10);
////////
    string* Ts = new string[num_Ts]; //Reserva de memoria de las cadenas en T

    int contT = 0;//contador

    while(contT < num_Ts){//Lectura de cadenas
        cin >> Ts[contT];
        ++contT;
    }
///////
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