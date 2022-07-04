//
// Created by isaac on 4/07/2022.
//

#ifndef PROYECTO_TC_EJERCICIO1_H
#define PROYECTO_TC_EJERCICIO1_H

#include<iostream>
#include <string>
#include "../../Contenedores/Grafo.h"
#include "../../Contenedores/Queue.h"
#include "../../Contenedores/bloque.h"
#include<chrono>
using namespace std;

constexpr int CHAR_LENGT = 1;

string Cadena(string alfabeto);

grafo buildAFN_x(string alfabeto, int num_Ts);

void Ejercicio_1();

#endif //PROYECTO_TC_EJERCICIO1_H
