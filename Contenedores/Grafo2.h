
//
// Created by isaac on 3/07/2022.
//

#ifndef PROYECTO_TC_GRAFO2_H
#define PROYECTO_TC_GRAFO2_H
#include <iostream>
#include <string>
#include "bloque.h"
using namespace std;


struct Nodes{
    string id;//indice del vertice dentro del array y su nombre.
    bloque estados;
    string transicion;
    Nodes* next;

    Nodes(string i, bloque states, string trans);
};

class grafo2{
    Nodes** Lista;
    int capacity;
    int size;
public:
    int num_idsF;
    string* ids_final;
    grafo2(int c);

    void CreateVertex(string id, bloque states);
    void CreateEdge(string trans, string id1, string id2);
    void resize();
    void display();
    void createEfinal(int num_e);
    void setEfinal(string id);
    void clear();
    int get_size();
};
#endif //PROYECTO_TC_GRAFO2_H
