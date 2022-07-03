//
// Created by isaac on 30/05/2022.
//

#ifndef PROYECTO_TC_FUNCIONES_H
#define PROYECTO_TC_FUNCIONES_H


#include "../Contenedores/Grafo.h"
#include "../Contenedores/Grafo2.h"
#include "../Contenedores/bloque.h"
using namespace std;
constexpr int CHAR_LENGTH = 1;

//verifica si el estado es final o no
bool is_Final(grafo g, int estado);

bool is_Final(int* array, int size, int estado);

bloque calculate(bloque& arreglo, char caracter, grafo graph);

grafo buildAFN(string alfabeto, int num_Ts);

int igualdad(bloque* fila, int sizeFila, bloque& contenido);

grafo buildAFD(string alfabeto, int num_Ts, grafo graph);


#endif //PROYECTO_TC_FUNCIONES_H
