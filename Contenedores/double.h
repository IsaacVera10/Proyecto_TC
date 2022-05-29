//
// Created by Juan jose on 29/05/2022.
//

#ifndef PROYECTO_TC_DOUBLE_H
#define PROYECTO_TC_DOUBLE_H

#include <iostream>
#include <string>
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(){
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class DoubleList{
public:
    Node<T>* head;
    Node<T>* tail;
    int nodes;
public:
    DoubleList(){
        head = nullptr;
        tail = nullptr;
        nodes = 0;
    }
    ~DoubleList(){

    }

    T front_Double(){
        return head->data;
    }

    T back_Double(){
        return tail->data;
    }

    void push_front(T data){
        Node<T>* nuevo= new Node<T>();
        nuevo->data = data;

        if(size_double() == 0){
            head = nuevo;
            tail = nuevo;
        }else{
            nuevo->next = head;
            head->prev = nuevo;
            head = nuevo;
        }

        ++nodes;
    }

    void push_back(T data){
        Node<T>* nuevo= new Node<T>();
        nuevo->data = data;

        if(size_double() == 0){
            head = nuevo;
            tail = nuevo;
        }else{
            nuevo->prev = tail;
            tail->next = nuevo;
            tail = nuevo;
        }
        ++nodes;
    }

    T pop_front(){
        if(size_double() == 0) exit(0);

        Node<T>* temp = head;
        int valor = temp->data;

        if(size_double() == 1){
            head = nullptr;
            tail = nullptr;

        }else{
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        --nodes;

        return valor;
    }

    T pop_back(){
        if(size_double() == 0) exit(0);

        Node<T>* temp = tail;
        int valor = temp->data;

        if(size_double() == 1){
            head = nullptr;
            tail = nullptr;

        }else{
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
        --nodes;

        return valor;
    }

    bool is_empty(){
        return nodes == 0;
    }

    int size_double(){
        return nodes;
    }

    void clear_Double(){
        while (head!=nullptr){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
        nodes = 0;
    }

    std::string name(){
        return "DoubleList";
    }
};

#endif //PROYECTO_TC_DOUBLE_H
