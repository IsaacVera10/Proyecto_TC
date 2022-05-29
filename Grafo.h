//
// Created by Juan jose on 27/05/2022.
//
#ifndef TC_BORRADOR_GRAFO_H
#define TC_BORRADOR_GRAFO_H

#include <iostream>
#include <string>
using namespace std;

struct Nodeg{
    int id;//indice del vertice dentro del array y su nombre.
    string transicion;
    Nodeg* next;

    Nodeg(int i, string trans);
};

class grafo{
    Nodeg** Lista;
    int capacity;
    int size;
public:
    int num_idsF;
    int* ids_final;
    grafo(int c);

    void CreateVertex(int id);
    void CreateEdge(string trans, int id1, int id2);
    void resize();
    void display();
    void createEfinal(int num_e);
    void setEfinal(int id);
    void clear();
    int* GetAlcance(int estado, string transicion);
};
#endif //TC_BORRADOR_GRAFO_H
