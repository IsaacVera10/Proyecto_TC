//
// Created by Juan jose on 29/05/2022.
//

#ifndef PROYECTO_TC_BLOQUE_H
#define PROYECTO_TC_BLOQUE_H


struct bloque{
    int* array;
    int size;
    bloque(){
        array = nullptr;
        size = 0;
    }
    void resize(int tamanho){
        int* nuevo = new int[tamanho];
        if(array == nullptr){
            array = nuevo;
        }else{
            for(int x = 0; x < size; ++x){
                nuevo[x] = array[x];
            }
        }
    }
};
#endif //PROYECTO_TC_BLOQUE_H
