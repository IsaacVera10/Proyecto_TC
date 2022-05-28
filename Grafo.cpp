//
// Created by Juan jose on 27/05/2022.
//

#include "Grafo.h"

Nodeg:: Nodeg(int i, Nodeg** pos, string trans){
    id = i;
    transicion = trans;
    next = nullptr;
}

grafo:: grafo(int c): capacity{c}{
    Lista = new Nodeg* [c];
    size = 0;
}

void grafo:: CreateVertex(int id){
    if(capacity == size)
        resize();
    Lista[size] = new Nodeg(id, Lista+size, "");//No se puede poner cadena vacia( '') por lo que puse ' '

    ++size;
}


void grafo:: CreateEdge(string trans, int id1, int id2){
    Nodeg* nuevo = new Nodeg(id2, Lista + id2, trans);
    nuevo->next =  Lista[id1]->next;
    Lista[id1]->next = nuevo;
}

void grafo::resize(){
    Nodeg** NuevaLista = new Nodeg*[capacity * 2];
    for(int x = 0; x < capacity; ++x){  //Se transfiere todos los datos a la nuevalista
        NuevaLista[x] = Lista[x];
    }

    Lista = NuevaLista;
    capacity = capacity*2;
}


void grafo::display(){
    for(int x = 0; x<size; ++x){
        Nodeg* temp = Lista[x];
        cout << temp->id << " ";
        while(temp->next != nullptr){
            cout << "-" << temp->next->transicion << "-> " << temp->next->id << " ";
            temp = temp->next;
        }

        cout << endl;
    }
}


void grafo::clear(){
    for(int x = 0; x < size; ++x){
        Nodeg* temp = Lista[x];
        Nodeg* temp2 = Lista[x]->next;
        while(temp2 != nullptr) {
            delete temp;
            temp = temp2;
            temp2 = temp2->next;
        }
        delete temp;
    }
    delete [] Lista;
}

grafo:: ~grafo(){
    clear();
}