
#include "ProblemaTestVacio.h"
using namespace std;
/*
Suponiendo que se ingresan los valores:
    b
    SAB
    4
    SA
    SBA
    AS
    Bb
para representar:
    S −> A|BA
    A −> S
    B −> b

b: terminales
SAB: Variables
4: numero de reglas
Despues son las reglas.
*/

void Pregunta_5(){
    string generadores;
    string variables;
    int num_reglas;

    cin >> generadores;//Se ingresan los terminales, generadores inciales
    cin >> variables;//La primera variable sera la inicial.
    cin >> num_reglas;

    string* reglas = new string [num_reglas];

    cin.ignore();
    for(int x = 0; x < num_reglas; ++x){
        getline(cin, reglas[x]);
    }

    //ALGORITMO
    bool cambiazo = true; //Verifica que hubo cambios en el ciclo previo.
    for(int r = 0; r < num_reglas; ++r){
        if(!cambiazo){//Si no hubo ningun cambio el ciclo previo entonces salgo.
            break;
        }

        cambiazo = false; //reset a la variable

        for(int x = 0; x < num_reglas; ++x){

            int cont = 0;
            //Se recorre despues despues del segundo caracter ya que son  'variable' y ' '
            for(int j = 2; j < reglas[x].length(); ++j){
                if(generadores.find(reglas[x][j]) != std::string::npos)
                    cont += 1;
            }

            //Verifico que los de la  "izquierda" sean generadores y que la variable no este en generadores.
            if(cont == (reglas[x].length()-2) &&  generadores.find(reglas[x][0]) == std::string::npos){
                generadores.push_back(reglas[x][0]);
                cambiazo = true;
            }
        }
    }

    //comprobamos si la variable inicial es generadora.
    if(generadores.find(reglas[0][0]) == std::string::npos){
        cout << "SI" << endl;
    }else{
        cout << "NO" << endl;
    }

    delete [] reglas;
}


//Suponiendo que pair no es de la libreria estandar.
void Pregunta_6(){
    string terminales;
    string variables;
    int num_reglas;

    cin >> terminales;//Se ingresan los terminales, generadores inciales
    cin >> variables;//La primera variable sera la inicial.
    cin >> num_reglas;

    pair<string, int>* reglasContadas = new pair<string, int> [num_reglas]; //Reglas_count

    pair<bool, DoubleList<blocks>>* generadores = new pair<bool, DoubleList<blocks>> [variables.length()]; //el tamaño no sería variables?

    QueueNode<char> cola;

    cin.ignore();
    for(int x = 0; x < num_reglas; ++x){
        getline(cin, reglasContadas[x].first);
        reglasContadas[x].second=0;
    }

    //OLVIDALO, seria agregar complejidad nomas, he probado un poco como seria y seria tedioso hacerlo creo, trabajalogo
    //normalmente con la posicion dentro de la regla.


    //CIERTO MANO, si detectas que algun cont es = 0 al terminar una regla agregas el primer caracter de la regla en la cola.ok
    //Seteo los contadores y marcar ocurrencias
    for(int i=0;i<num_reglas;i++){
        for(int j=2;j<reglasContadas[i].first.length();j++){//contadores
            if(variables.find(reglasContadas[i].first[j])!=string::npos){ //Si el caracter es una variable
                reglasContadas[i].second++; //aumenta el contador de cada regla si encuentra una variable en la dependencia

                //Marcación de ocurrencias
                blocks temporal;
                temporal.ocurrencia = &reglasContadas[i];
                temporal.position = j;
                generadores[variables.find(reglasContadas[i].first[j])].second.push_back(temporal);
            }

        }
        //cout<<reglasContadas[i].first<<" "<<reglasContadas[i].second<<endl;
        if(reglasContadas[i].second==0)
            cola.push(reglasContadas[i].first[0]);
    }
    /*
    for(int i=0;i<variables.length();i++){
        cout<<variables[i]<<"   ";
        auto temp = generadores[i].second.front();

        while(temp!=nullptr){
            cout<<temp->data.ocurrencia<<" - "<<temp->data.position<<"   |    ";
            temp = temp->next;
        }
        cout<<endl;
    }*/


    //ALGORITMO
    /*
     IDEAS SOBRE EL ALGORITMO:
        Cuando se "setean" los contadores, si se detecta algun 0 se ingresa a la cola.

        Mientras la cola no este vacia, yo hago pop en la cola, busco esa variable dentro del string variables,
        con la posicion dada por el, dentro de "generadores" seteo  el booleano como True y recorro los elementos del doubleList. modificando el cont(-1)
        por cada ocurrencia, si despues de bajar el cont en 1 detecto que cont == 0, agrego el primer caracter de la regla, la variable, dentro de la cola.

        Cuando termino la ejecucion busco la variable inicial dentro del string variables y con esa posicion voy al array generadores
        verificando si para esa posicion el bool es TRUE o FALSE.

     Posibilidades:
        Guardo en la cola el caracter de la variable. UTILIZARE ESTA.
        guardo en la cola la posicion del caracter dentro del string variables. Complicado de implementar.
    */




    while(!cola.empty()){
        char current = cola.pop();

        //Busco la posicion del current en variables
        int pos = variables.find(current);

        //Seteo el bool a true para esa variables
        generadores[pos].first = true;

        // Recorro los elementos para modificar el cont de las reglas
        for(int x = 0; x < generadores[pos].second.size_double(); ++x){
            //puntero a la tupla dentro de reglasContadas
            auto iter = generadores[pos].second.pop_front().ocurrencia;

            //Reduzco en 1 el contador.
            iter->second -= 1;
            int position_var = variables.find(iter->first[0]);

            //Si determino que el contador es 0 agrego la variable a la cola. si es que no es que ya es generadora
            if(iter->second == 0 && !generadores[position_var].first) {
                cola.push(iter->first[0]);
            }
        }
    }

    int position = variables.find((reglasContadas[0].first)[0]);
    //Verifico si la variable inicial es generadora o no.
    if(generadores[position].first)
        cout << "NO";
    else
        cout << "SI";

    delete [] reglasContadas;
    delete [] generadores;
}

