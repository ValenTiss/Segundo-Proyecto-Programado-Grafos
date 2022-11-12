//
//  main.cpp
//  main.cpp
//
//  Created by Valen Tissera on 29/10/22.
//

#include <iostream>

using namespace std;

/**
 *Estructura lugar simboliza los lugares presentes en el
 */

struct Lugar{ //Creacion del Vertice con el lugar que los turistas van a visitar
    string lugar;

    struct Lugar * sigV; //Enlace de los vertices en una lista
    struct Ruta *subLArcos;//lo modifique porque decir lugar//Arcos que salen del vertice

    bool siVisitado;
    Lugar (string lug){
        lugar = lug;
        sigV = NULL;
        subLArcos = NULL;
        siVisitado = false;
    }

};

struct Ruta{
    int tiempoRecorrido;
    struct Ruta* sigAr;
    Ruta(int tr){
        tiempoRecorrido = tr;
        sigAr = NULL;

    }

};

struct Lugar *grafo; // Apuntador del incio del grafo

struct Persona{//Creacion de la persona (doble) con su lista de amigos
    string nombre;
    Persona* antP;
    Persona* sigP;
    Persona* listaAmigos;
    struct Lugar* lugarInicio;
    
    Persona(string n){
        nombre = n;
        antP=NULL;
        sigP= NULL;
        listaAmigos=NULL;
        lugarInicio=NULL;
    }

};


/**
 *insercion al inicio de la lista de lugares.
 *@param lug Nombre del nuevo lugar
 */
//insercion al inicio de la lista de lugares.
void insertarLugar(string lug){
            struct Lugar *nuevoLugar = new Lugar(lug);

            nuevoLugar->sigV = grafo;
            grafo = nuevoLugar;
}

/**
 *insercion al inicio de la lista de rutas.
 *@param tiempoReccorido tiempo resultante de recorrer toda la ruta.
 */
void insertarRuta(string origen ,string destino,int tiempoRecorrido){


        struct Ruta *nuevaRuta = new Ruta(tiempoRecorrido);


        //se inserto al inicio de la sublista de Rutas
        nuevaRuta->sigAr = nuevaRuta->sigAr;
        nuevaRuta->sigAr = nuevaRuta;


}


/**
 *Cargar  datos
 */

void CargarDatosRuta(){
    insertarRuta(33);
}



bool pressKeyToContinue(){
    cout<<"[esc] - Presione escape para salir (x)\n\n\n"<<endl;
    cout<<"Presione alguna tecla para limpiar ...";
    char c = getchar();
    if((int)c != 27){
        cout<<"\x1B[2J\x1B[H";
        return false;
    }
    return true;
}

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
    cout<<endl<<"11) Cuales personas no pudieron realizar la caminada por no haber una ruta, o por no haber conexion conexa";
}

int main()
{
    menu();
}
