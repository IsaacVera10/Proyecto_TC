#include <iostream>
#include <string>
#include <queue>
#include "Grafo.h"
#include "Contenedores/Queue.h"

using namespace std;
constexpr int CHAR_LENGTH = 1;

/*
//Verifica que para cada simbolo en T, este esta dentro del alfabeto
bool  is_Correct(string T, string alfabeto){ // o(N^2)
    for(char item: T){
        for(char simbolo: alfabeto){
            if(item == simbolo)
                break;
            if(simbolo == alfabeto.back())
                return false;
        }
    }
    return true;
}*/

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


//ejemplo: bloque* fila son bloques
int igualdad(bloque* fila, int sizeFila, bloque& contenido){
    bool var = true;

    bloque temp;
    for(int i = 0; i < sizeFila; ++i){
        temp.array = fila[i].array;
        temp.size = fila[i].size;

        if(temp.size != contenido.size){
            var=false;
        }else{
            for(int j=0;j<contenido.size;++j){//comparo cada caracter
                if(contenido.array[j] != temp.array[j]){
                    var = false;
                }
            }
        }
        if(var == true)
            return i;

        var=true;
    }

    return -1;
}

bloque calculate(bloque& arreglo, char caracter, grafo graph){
    bloque result;

    int cont = 0;
    int indicator = 0;

    for(int i=0;i<arreglo.size;i++){
        int* temp= graph.get_alcance(arreglo.array[i], caracter, cont);

        result.resize(result.size + cont);

        for(int j=0;j<cont;j++){
            result.array[indicator] = temp[j];
            indicator++;
            result.size++;
        }
        cont = 0;
    }

    return result;
}




grafo funcion_pregunta_1(string alfabeto, int num_Ts){
    grafo resultado(10);

    string* Ts = new string[num_Ts]; //Reserva de memoria de las cadenas en T

    int contT = 0;//contador

    while(contT < num_Ts){//Lectura de cadenas
        cin >> Ts[contT];
        ++contT;
    }

    //CODIGO DEL PROBLEMA
    resultado.CreateVertex(0);// Nodo inicial.
    resultado.CreateEdge(alfabeto, 0, 0); //Transicion consigo mismo.
    resultado.createEfinal(num_Ts);

    contT = 1; //Me ayudara a llevar la cuenta del vertice donde estoy.
    bool primero = true;

    for(int x = 0; x < num_Ts; ++x) {
        for (auto caracter: Ts[x]) {
            resultado.CreateVertex(contT); //Primero creo el vertice
            string ch_string(CHAR_LENGTH, caracter);

            //Si es el primer caracter de T debe tener una conexion con el vertice 0
            if (primero) {
                resultado.CreateEdge(ch_string, 0, contT);
                primero = false;
            } else {
                //Sino se conecta con el anterior
                resultado.CreateEdge(ch_string, contT - 1, contT);
            }

            ++contT;
        }
        resultado.setEfinal(contT-1);
        primero = true;
    }

    return resultado;
}

void Pregunta_1(){
    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;

    grafo  a = funcion_pregunta_1(alfabeto, num_Ts);
    a.display();

    cout << "estados finales" << endl;
    for(int x = 0; x < 2; ++x){
        cout << a.ids_final[x] << " ";
    }
    cout << endl;
    a.clear();
}

//verifica si el estado es final o no
bool is_Final(grafo g, int estado){
    for(int x = 0; x < g.num_idsF; ++x){
        if(estado == g.ids_final[x]) return true;
    }
    return false;
}

void Pregunta_2(){
    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;

    grafo  a = funcion_pregunta_1(alfabeto, num_Ts);

    int num_Ss;
    cout << "Introduzca la cantidad de Ss: ";
    cin>> num_Ss;
    string* Ss = new string[num_Ss]; //Reserva de memoria de las cadenas en S
    int contS = 0;//contador
    while(contS < num_Ss){//Lectura de cadenas
        cin >> Ss[contS];
        ++contS;
    }

    bool* res = new bool[num_Ss] {}; //Me indica si las cadenas fueron aceptadas o no, por defecto seran false;

    QueueNode<int> cola;
    int size_cola;//Tamanho de la cola en la iteracion pasada.

    for(int x = 0; x < num_Ss; ++x){
        cola.push(0);
        size_cola = 1;

        for(auto caract: Ss[x]){
            while(size_cola > 0){
                int state = cola.front();
                cola.pop();
                int num_final = 0;//Me dice a cuantos estados puedo llegar

                if(is_Final(a, state)) {//Compruebo si el estado actual es final
                    res[x] = true;
                    break;
                }

                int* EstadosPosibles = a.get_alcance(state, caract, num_final);
                for(int x = 0; x <  num_final; ++x){
                    cola.push(EstadosPosibles[x]);
                }
                --size_cola;
            }
            if(res[x]) //Si ya determine que la cadena es aceptada, salto a la siguiente cadena.
                break;

            size_cola = cola.size();
        }

        //Verifico que los estados que quedan en la cola no sean estados finales. Ademas limpio la cola para la siguiente iteracion.
        while(!cola.empty()){
            int current = cola.front();
            cola.pop();
            if(is_Final(a, current)) {
                res[x] = true;
            }
        }
    }

    //Impresion de si fue aceptado o no
    for(int x = 0; x < num_Ss; ++x){
        if(res[x])
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;
    }

    //Liberacion de memoria
    delete [] res;
}


bool is_Final(int* array, int size, int estado){
    for(int x = 0; x < size; ++x){
        if(estado == array[x]) return true;
    }
    return false;
}

void Pregunta_3(){
    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;

    grafo  AFN = funcion_pregunta_1(alfabeto, num_Ts);

    int num_Ss;
    cout << "Introduzca la cantidad de Ss: ";
    cin>> num_Ss;
    string* Ss = new string[num_Ss];
    int contS = 0;
    while(contS < num_Ss){
        cin >> Ss[contS];
        ++contS;
    }

    //A lo mas se tendra |Vertices| * |alfabeto| filas en la matriz del AFD.
    bloque* arrayBloque = new bloque[AFN.get_size()*alfabeto.length()];
    int pos_array = 0; //Me indica la posicion dentro de la matrizFilas.

    int* Efinales = new int[num_Ts];//Contiene los estados finales del AFD
    int pos_EFinales = 0;

    //Agrego el array con el estado inicial.
    int* inicial = new int [1] {};
    arrayBloque[pos_array].array = inicial;
    arrayBloque[pos_array].size = 1;
    ++pos_array;

    int** matrizAFD = new int*[AFN.get_size()*alfabeto.length()];
    for(int x = 0; x < AFN.get_size()*alfabeto.length(); ++x){
        matrizAFD[x] = new int[alfabeto.length()];
    }

    int fCurrent = 0; //indica que fila estoy recorriendo.

    //Por aqui esta el error
    while(fCurrent < pos_array){
        for (int j = 0; j < alfabeto.length(); j++) {
            bloque llegada = calculate(arrayBloque[fCurrent], alfabeto[j], AFN);
            int position = igualdad(arrayBloque, pos_array ,llegada);

            if(position == -1){//Si no existe dentro de los vertices position = -1, entonces lo agrego a las filas.
                position = pos_array;
                arrayBloque[pos_array] = llegada;
                ++pos_array;
            }

            matrizAFD[fCurrent][j] = position; //Registro la posicion dentro de la MatrizFilas.

            //Compruebo para cada estado del array si alguno es final.
            for(int x = 0; x < llegada.size; ++x){
                if(is_Final(AFN, llegada.array[x])) {
                    Efinales[pos_EFinales] = position;
                    ++pos_EFinales;
                }
            }
        }

        ++fCurrent;
    }



    //Recorrido dentro del AFD
    bool* res = new bool[num_Ss] {}; //Me indica si las cadenas fueron aceptadas o no, por defecto seran false;

    for(int x = 0; x < num_Ss; ++x){//Se recorre cada cadena.
        int state_current = 0; //Inicio en el estado 0

        //Verifico si el estado 0 es un estado final
        if(is_Final(Efinales, pos_EFinales, state_current)){
            res[x] = true;
            continue;
        }

        for(auto item: Ss[x]){//Se recorre cada elemento.
            int posAlfabeto = alfabeto.find(item);
            state_current = matrizAFD[state_current][posAlfabeto]; //Me indica a que estado transicionare.

            //Verifico si es un estado final.
            if(is_Final(Efinales, pos_EFinales, state_current)){
                res[x] = true;
                break;
            }
        }
    }

    //Impresion de si fue aceptado o no
    for(int x = 0; x < num_Ss; ++x){
        if(res[x])
            cout << "SI" << endl;
        else
            cout << "NO" << endl;
    }

    //Limpiando la memoria.

    for(int x = 0; x < AFN.get_size()*alfabeto.length(); ++x){
        delete [] matrizAFD[x];
    }
    delete [] matrizAFD;
    delete [] arrayBloque;
    delete [] Efinales;
    delete [] res;
}


void ejemplo(){
    grafo nuevo(2);
    nuevo.createEfinal(2);

    nuevo.CreateVertex(0);
    nuevo.CreateVertex(1);
    nuevo.CreateVertex(2);
    nuevo.CreateEdge("ed", 0, 0);
    nuevo.CreateEdge("e", 0, 1);
    nuevo.CreateEdge("d", 1, 2);

    nuevo.setEfinal(1);
    nuevo.setEfinal(2);

    bloque a;
    a.array = new int[1] {};//Array solo con el estado 0
    a.size = 1;
    bloque prueba = calculate(a, 'e', nuevo);

    for(int x = 0; x < prueba.size; ++x){
        cout << prueba.array[x] << " ";
    }
    cout << endl;
    //Salida esperada: 0 1 o tambien: 1 0
}


void prueba_Alcance(){
    int size = 0;

    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;


    grafo a = funcion_pregunta_1(alfabeto, num_Ts);
    a.display();
    cout<<a.get_size();
    int* array = a.GetAlcance(0,"w", size);

    cout<<endl;

    for(int i=0;i<size;i++){
        cout<<*(array+i)<<" ";
    }

    cout<<endl<<size;

}

void ejemplo1(){
    string alfabeto;
    int num_Ts;

    cout<<"Introduzca el alfabeto:";
    cin >> alfabeto;
    cout<<"Introduzca la cantidad de cadenas:";
    cin>> num_Ts;
    grafo  a = funcion_pregunta_1(alfabeto, num_Ts);

    bloque* MatrizFilas = new bloque[a.get_size()*alfabeto.length()];

    int pos_Matriz = 0; //Me indica la posicion dentro de la matrizFilas.

    int* Efinales = new int[num_Ts];//Contiene los estados finales del AFD
    int pos_EFinales = 0;

    //Agrego el array con el estado inicial.
    int* inicial = new int [1] {};
    MatrizFilas[pos_Matriz].array = inicial;
    MatrizFilas[pos_Matriz].size = 1;
    ++pos_Matriz;

    for(int i=0;i<alfabeto.length();i++){
        bloque llegada = calculate(MatrizFilas[0], alfabeto[i], a);
        for(int j=0;j<llegada.size;j++){
            cout<<llegada.array[j]<<" ";
        }
        cout<<endl;
    }

    bloque abc;
    abc.array = inicial;
    abc.size = 1;

    if(igualdad(MatrizFilas,1 ,abc) == -1){
        cout << "No esta en la matriz" << endl;
    }else{
        cout << "Esta en la matriz " << endl;
    }


    cout << endl;

}


void prueba_igualdad(){
    bloque* ArrBloque = new bloque[2];
    int* arr = new int[1];
    arr[0] = 3;
    ArrBloque[0].array = arr;
    ArrBloque[0].size = 1;

    int* arr2 = new int[2];
    arr2[0] = 0;
    arr2[1] = 1;
    ArrBloque[1].array = arr2;
    ArrBloque[1].size = 2;


    bloque prueba;
    prueba.array = arr2;
    prueba.size = 2;

    if(igualdad(ArrBloque,2 ,prueba) == -1){
        cout << "No esta en la matriz" << endl;
    }else{
        cout << "Esta en la matriz " << endl;
    }

    bloque a;
    int* ar = new int[3] {0,1,2};
    a.array = ar;
    a.size = 3;


    if(igualdad(ArrBloque,2 ,a) == -1){
        cout << "No esta en la matriz" << endl;
    }else{
        cout << "Esta en la matriz " << endl;
    }

}

int main() {
    //Pregunta_1();
    //Pregunta_2();
    // codigo git: git pull ,  git reset --hard f7f436dbaaf0a4cfd71870f1d82536208c6675dc

    //ejemplo();
    //prueba_Alcance();
    Pregunta_3();

    //ejemplo1();
    //prueba_igualdad();

    return 0;
}
