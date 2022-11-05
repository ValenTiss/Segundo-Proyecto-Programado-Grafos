//
//  main.cpp
//  main.cpp
//
//  Created by Valen Tissera on 29/10/22.
//

#include <iostream>

using namespace std;

/**
 *Metodo para x
 *@param z
 *@param y
 *@return retorna booleano
 */

struct Vertice{ //Creacion del Vertice con el lugar que los turistas van a visitar
    string lugar;

    struct Vertice * sigV; //Enlace de los vertices en una lista
    struct Arco *subLArcos; //Arcos que salen del vertice

    bool siVisitado;
    Vertice (string lug){
        lugar = lug;
        sigV = NULL;
        subLArcos = NULL;
        siVisitado = false;
    }


};

struct Arco{
    int tiempoRecorrido;
    struct Arco* sigAr; 
    Arco(int tr){
        tiempoRecorrido = tr;
        sigAr = NULL;

    }

};

struct Vertice *grafo; // Apuntador del incio del grafo
.









void menu(){

    cout<<"Bienvenid@ al Proyecto 2 de Estructuras de Datos";
    cout<<endl;
    cout<<"-----Consultas------"<<endl;
    cout<<"1) Mostrar el estado de las personas en cada avance";
    cout<<endl<<"2) Persona con mas amigos";
    cout<<endl<<"3) Primera persona en terminar la caminata";
    cout<<endl<<"4) Ultima persona en terminar la camita";
    cout<<endl<<"-----Reportes------";
    cout<<endl<<"5) Imprimir grafo en amplitud, con toda la info almacenada";
    cout<<endl<<"6) Imprimir en profundidad el grafo ( se indica cual vertice de incio)";
    cout<<endl<<"7) Imprimir las rutas para las personas que avanzan de la forma 3 y 4";
    cout<<endl<<"9) Imprimir la cantidad y el nombre de los amigos que logro realizar una persona";
    cout<<endl<<"10) Quien o quienes no encontraron ningun amigo";
    cout<<endl<<"11 Cuales personas no pudieron realizar la caminada por no haber una ruta, o por no haber conexion conexa";
}

int main()
{
    menu();
}
