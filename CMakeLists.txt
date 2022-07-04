cmake_minimum_required(VERSION 3.21)
project(Proyecto_TC)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto_TC
        main.cpp
        Contenedores/Grafo.h
        Contenedores/Grafo.cpp
        Contenedores/double.h
        Contenedores/Queue.h
        Contenedores/bloque.h
        Algorithms/Funciones.h
        Algorithms/Funciones.cpp
        Algorithms/ProblemaSubstring.h
        Algorithms/ProblemaSubstring.cpp
        Algorithms/ProblemaTestVacio.cpp
        Algorithms/ProblemaTestVacio.h
        Contenedores/blocks.h
        Contenedores/Grafo2.cpp
        Contenedores/Grafo2.h
        Contenedores/tupla.h
        Experimentacion_numerica/Ejercicio1/Ejercicio1.cpp
        Experimentacion_numerica/Ejercicio1/Ejercicio1.h Contenedores/tupla.h)
