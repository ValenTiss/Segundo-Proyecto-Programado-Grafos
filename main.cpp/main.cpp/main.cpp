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

/**
 * Estrucutra que simboliza las rutas presentes en el grafo.
 */ 
struct Ruta{
    int tiempoRecorrido;

    struct Ruta* sigAr;

    Ruta(int tr){

        tiempoRecorrido = tr;
        sigAr = NULL;

    }

};

struct Lugar *grafo; // Apuntador del incio del grafo

/**
 * Estrucutra que simboliza a las personas.
 */ 
struct Persona{//Creacion de la persona (doble) con su lista de amigos
    string nombre;
    Persona* antP;
    Persona* sigP;
    Persona* listaAmigos;
    struct Lugar* lugarInicio;
    
    Persona(string n,Lugar* lugarInicio){

        nombre = n;
        antP=NULL;
        sigP= NULL;
        listaAmigos=NULL;
        this->lugarInicio = lugarInicio;

    }

}*listaDePersonas;


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
 *@param origen Nombre del lugar de origen de la ruta.
 *@param destino Nombre del lugar de destino de la ruta.
 *@param tiempoReccorido tiempo resultante de recorrer toda la ruta.
 */
void insertarRuta(string origen ,string destino,int tiempoRecorrido){

        struct Ruta *nuevaRuta = new Ruta(tiempoRecorrido);

        //se inserto al inicio de la sublista de Rutas
        nuevaRuta->sigAr = nuevaRuta->sigAr;
        nuevaRuta->sigAr = nuevaRuta;


}

/**
 * Metodo para obtener una persona especifica en la lista.
 * @param nombre Nombre de la persona la cual se esta buscando.
 * @param lugarInicio Lugar de inicio de la persona a buscar.
 * @return La persona si se encuentra en la lista, nulo si no se encuentra 
 */ 
Persona* getPersona(string nombre,Lugar* lugarInicio){
    Persona*temp = listaDePersonas;
    while(temp != NULL)
    {
        if( (temp->nombre == nombre) && (temp->lugarInicio == lugarInicio) )
            return temp;
        temp -> sigP = temp;
    }
    return NULL;
}
/**
 * Metodo para validar la existencia de una persona.
 * @param nombre Nombre de la persona a validar.
 * @param lugarInicio Lugar donde inicio en el grafo la persona.
 * @return Booleano verdadero si se encontro la persona ,falso si no existe en la lista.
 */ 
boolean validarPersona(string nombre,Lugar* lugarInicio){
    Persona*temp = listaDePersonas;
    while(temp != NULL)
    {
        if( (temp->nombre == nombre) && (temp->lugarInicio == lugarInicio) )
            return true;
        temp -> sigP = temp;
    }
    return false;

}

/**
 *Metodo para insertar personas en la lista 
 *@param nombre Nombre de la persona
 *@param lugarInicio Lugar de inicio de la persona.
 *@return Objeto tipo persona agregada a la lista,nulo si no ya existe
 */ 
Persona* insertarPersona(string nombre,Lugar* lugarInicio){
    boolean existe = validarPersona(nombre,lugarInicio);

    if(existe)
        return NULL;

    Persona*nuevo = new Persona(nombre,lugarInicio);

    if(listaDePersonas == NULL){
        listaDePersonas = nuevo;
        nuevo ->sigP = nuevo;
    }else
    {
        nuevo -> sigP = listaDePersonas;
        Persona*temp = listaDePersonas;
        while(temp -> sig != listaDePersonas)
        {
            temp = temp -> sig;
        } 
        temp -> sig = nuevo;
        listaDePersonas = nuevo;
    }
    return nuevo;
}

/**
 * Metodo para borrar persona de la lista.
 * @param nombre
 * @param lugarInicio 
 * @return 
 */ 
void borrarPersona(string nombre,Lugar*lugarInicio){
    if(existe)
        return;
    
    
}





/**
 *Cargar  datos
 */

void CargarDatosRuta(){
    insertarRuta("origen","destino",33);
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

void dibujarMenu(int opcion)
{
    cout<<"[X] Presione esc para salir. "<<endl<<endl;
    switch(opcion)
    {
        case 0:
        {
                cout<<endl<<"...:: Bienvenido al menu ::..."<<endl;
                cout<<"[1] - Desplegar las opciones de mantenimiento de datos."<<endl;
                cout<<"[2] - Desplegar las opcines de consultas al sistema."<<endl;
                cout<<"[3] - Desplegar las opciones de reportes del sistema."<<endl;
                break;
        }
            
        case 1:
        {
            cout<<"[1] - Desplegar las opciones de mantenimiento de datos."<<endl;
            cout<<"\t[1] -  Insertar,modifcar o borrar datos en la lista de personas."<<endl;
            cout<<"\t[2] -  Insertar,modifcar o borrar datos en la lista de lugares."<<endl;
            cout<<"\t[3] -  Insertar,modifcar o borrar datos en la lista de rutas."<<endl;
            break;
        }
        case 2:
        {
            cout<<"[2] - Desplegar las opcines de consultas al sistema."<<endl;
            cout<<"\t[1] -  Mostrar el estado de las personas en cada avance"<<endl;
            cout<<"\t[2] -  Persona con mas amigos"<<endl;
            cout<<"\t[3] -  Primera persona en terminar la caminata"<<endl;
            cout<<"\t[4] -  Ultima persona en terminar la camita"<<endl;
            break;
        }
        case 3:
        {
            cout<<"[3] - Desplegar las opciones de reportes del sistema."<<endl;
            cout<<endl<<"\t[1] -  Imprimir grafo en amplitud, con toda la info almacenada"<<endl;
            cout<<endl<<"\t[2] -  Imprimir en profundidad el grafo ( se indica cual vertice de incio)"<<endl;
            cout<<endl<<"\t[3] -  Imprimir las rutas para las personas que avanzan de la forma 3 y 4"<<endl;
            cout<<endl<<"\t[4] -  Imprimir la cantidad y el nombre de los amigos que logro realizar una persona"<<endl;
            cout<<endl<<"\t[5] -  Quien o quienes no encontraron ningun amigo"<<endl;
            cout<<endl<<"\t[6] -  Cuales personas no pudieron realizar la caminada por no haber una ruta, o por no haber conexion conexa"<<endl;
            break;
        }
        
        
    }
}

/**
 * Metodo para interactuar con el usuario ,atraves de la consola.
 */
void menu(){
     
        cout<<"\x1B[2J\x1B[H";
        int c;
        do {
            dibujarMenu(0);
            c=getchar();
            switch((int)c - '0')
            {
            case 1:
                {
                    dibujarMenu(1);
                    int opcionUno = getchar();
                
                    break;
                }
            case 2:
                {
                    dibujarMenu(2);
                    int opcionDos = getchar();
                    break;
                }
            case 3:
                {
                    dibujarMenu(3);
                    int opcionTres = getchar();
                    break;
                }
            default:
                {
                    cout<<"Entrada invalida."<<endl;
                    break;
                }
            }
            bool apretoEscape = pressKeyToContinue();
            if(apretoEscape)
                c = (int)27;
        } while ((int)c != 27);
}

int main()
{
    menu();
    return 0;
}
