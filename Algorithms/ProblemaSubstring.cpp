//
// Created by isaac on 30/05/2022.
//
//
// Created by isaac on 30/05/2022.
//

#include "ProblemaSubstring.h"

void Pregunta_1(){
    string alfabeto;
    int num_Ts;

    cin >> alfabeto;
    cin>> num_Ts;

    grafo  AFN = buildAFN(alfabeto, num_Ts);
    AFN.display();

    cout << "estados finales" << endl;
    for(int x = 0; x < 2; ++x){
        cout << AFN.ids_final[x] << " ";
    }
    cout << endl;
    AFN.clear();
}

void Pregunta_2(){
    string alfabeto;
    int num_Ts;

    cin >> alfabeto;
    cin>> num_Ts;

    grafo  AFN = buildAFN(alfabeto, num_Ts);

    int num_Ss;

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

                if(is_Final(AFN, state)) {//Compruebo si el estado actual es final
                    res[x] = true;
                    break;
                }

                int* EstadosPosibles = AFN.get_alcance(state, caract, num_final);
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
            if(is_Final(AFN, current)) {
                res[x] = true;
            }
        }
    }

    //Impresion de si fue aceptado o no
    for(int x = 0; x < num_Ss; ++x){
        if(res[x])
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    //Liberacion de memoria
    delete [] res;
}

void Pregunta_3(){
    string alfabeto;
    int num_Ts;

    cin >> alfabeto;
    cin>> num_Ts;

    grafo  AFN = buildAFN(alfabeto, num_Ts);

    int num_Ss;
    cin>> num_Ss;
    string* Ss = new string[num_Ss]; //Reserva de memoria de las cadenas en S
    int contS = 0;//contador
    while(contS < num_Ss){//Lectura de cadenas
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