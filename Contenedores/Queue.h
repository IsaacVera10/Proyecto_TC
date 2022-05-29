#ifndef PROYECTO_TC_QUEUE_H
#define PROYECTO_TC_QUEUE_H



#include "double.h"

template <typename T>
class QueueNode : public DoubleList<T> {
public:
    QueueNode() : DoubleList<T>() {};
    void push(T data);
    T pop();
    T front();
    bool empty();
    int size();

};

template <class T>
void QueueNode<T>::push(T data){
    this->push_back(data);
}

template <class T>
T QueueNode<T>::pop(){
    T result=this->pop_front();
    return result;
}

template <class T>
bool QueueNode<T>::empty(){
    return this->is_empty();
}

template<typename T>
T QueueNode<T>::front(){
    return this->front_Double();
}
template<typename T>
int QueueNode<T>::size(){
    return this->size_double();
}

#endif //PROYECTO_TC_QUEUE_H
