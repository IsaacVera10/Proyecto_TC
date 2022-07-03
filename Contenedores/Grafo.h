//
// Created by Juan jose on 27/05/2022.
//
#ifndef TC_BORRADOR_GRAFO_H
#define TC_BORRADOR_GRAFO_H

#include <iostream>
#include <string>
using namespace std;

/*
 nodeh{
    string id;//135; problema de guardarlo asi, es que puede confundirse con los estados 13 y 5,
    //en lugar de ller estados: 1, 3 y 5. Por ello seria mejor guardar un array con los estados que forma.
    array estados; {1,3,5}
    transiciones:
     nodeg* next;
 */

//1 - w -> 2
//1 - e -> 05

/*
struct nodeS{
    string id; //135
    bloque estados;
    string transiciones;
    nodeg* next; //fowardList
,
 }
 */

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
    int* GetAlcance(int estado, string transicion, int &tam);
    int* get_alcance(int estado, char transicion, int &tam);
    int get_size();
};
#endif //TC_BORRADOR_GRAFO_H
