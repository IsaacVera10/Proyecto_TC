//
// Created by Juan jose on 27/05/2022.
//
#include "Grafo.h"

Nodeg::Nodeg(int i, string trans){
    id = i;
    transicion = trans;
    next = nullptr;
}

grafo::grafo(int c): capacity{c}{
    Lista = new Nodeg* [c];
    size = 0;
    num_idsF = 0;
}

void grafo:: CreateVertex(int id){
    if(capacity == size)
        resize();
    Lista[size] = new Nodeg(id, "");//No se puede poner cadena vacia( '') por lo que puse ' '

    ++size;
}


void grafo:: CreateEdge(string trans, int id1, int id2){
    Nodeg* nuevo = new Nodeg(id2, trans);
    nuevo->next =  Lista[id1]->next;
    Lista[id1]->next = nuevo;
}

void grafo::resize(){
    Nodeg** NuevaLista = new Nodeg*[capacity * 2];
    for(int x = 0; x < capacity; ++x){
        NuevaLista[x] = Lista[x];
    }
    //int temp = size;
    //clear();
    Lista = NuevaLista;
    //size = temp;
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

void grafo::createEfinal(int num_e){
    ids_final = new int[num_e];
}

void grafo::setEfinal(int id){
    ids_final[num_idsF] = id;
    ++num_idsF;
}



int* grafo::GetAlcance(int estado, string transicion, int &size){
    static int array[20];

    int cont=0;
    Nodeg* temp = Lista[estado];

    while(temp!= nullptr){
        //cout<<temp->transicion<<" ";
        if(temp->transicion.size() != 1){//si es que evalua alfabeto
            for(int i=0;i<temp->transicion.size();i++){
                char var[1];
                var[0]=transicion.at(0);
                if(temp->transicion[i]==var[0]){
                    array[cont] = temp->id;
                    size++;
                    cont++;
                }
            }
        }else {
            if (temp->transicion == transicion) {
                array[cont] = temp->id;
                size++;
                cont++;
            }
        }
        temp = temp->next;
    }

    return array;
}

void grafo::clear(){
    for(int x = 0; x < size; ++x){
        //Similar a un clear de un foward_list
        Nodeg* head = Lista[x];
        while(head != nullptr){
            Nodeg* temp = head;
            head = head ->next;
            delete temp;
        }

    }
    delete [] Lista;
    size = 0;
}

