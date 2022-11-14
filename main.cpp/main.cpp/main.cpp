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
    string tiempoRecorrido;

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
    struct Rutas* rutasRecorridas;
    
    Persona(string n,struct Lugar* lugarInicio){

        nombre = n;
        antP=NULL;
        sigP= NULL;
        listaAmigos=NULL;
        this->lugarInicio = lugarInicio;
        rutasRecorridas = NULL;
    }

}*listaDePersonas;


/**
 *insercion al inicio de la lista de lugares.
 *@param lug Nombre del nuevo lugar
 */
//insercion al inicio de la lista de lugares.
struct Lugar* insertarLugar(string lug){
    struct Lugar *nuevoLugar = new Lugar(lug);

    nuevoLugar->sigV = grafo;
    grafo = nuevoLugar;
    return nuevoLugar;
}

/**
 * Metodo para obtener un lugar deseado.
 * @param nombreLugar Nombre del lugar.
 * @return Estructura de tipo lugar si la encuentra,sino nulo.
 */ 
struct Lugar * getLugar(string nombreLugar){
        struct Lugar *tempV = grafo;
        while(tempV != NULL){
            if(tempV->lugar == nombreLugar)
                return tempV;

            tempV = tempV->sigV;
        }
    return NULL;//no lo encontro
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
Persona* getPersona(string nombre,Persona* listaPersonas){
    Persona*temp = listaPersonas;
    while(temp != NULL)
    {
        if(temp->nombre == nombre)
            return temp;
        temp =  temp -> sigP ;
    }
    return NULL;
}

/**
 *Metodo para imprimir todas las personas presentes en la lista de personas.
 */
void imprimirPersona(){

    if(listaDePersonas == NULL){
        cout<<"La lista de personas esta vacia"<<endl;
        return;
    }
    Persona* temp = listaDePersonas;
    while (temp->sigP != NULL){
        temp = temp -> sigP;
    }
    while (temp != NULL){
        cout<<"La persona " <<temp-> nombre<<" empezo en el lugar de  "<<temp->lugarInicio->lugar<<" se encuentra en la lista\n";
        temp = temp -> antP;
        
    }
   

}

/**
 * Metodo para validar la existencia de una persona.
 * @param nombre Nombre de la persona a validar.
 * @param lugarInicio Lugar donde inicio en el grafo la persona.
 * @return Booleano verdadero si se encontro la persona ,falso si no existe en la lista.
 */ 
bool validarPersona(string nombre,string lugarInicio,Persona* listaPersonas){
    Persona*temp = listaPersonas;
    while(temp != listaPersonas)
    {
        if( (temp->nombre == nombre) && (temp->lugarInicio->lugar == lugarInicio) )
            return true;
        cout<<"Sigue buscando"<<endl;
        temp = temp -> sigP;
    }
    return false;

}

/**
 *Metodo para insertar personas en la lista 
 *@param nombre Nombre de la persona
 *@param lugarInicio Lugar de inicio de la persona.
 *@return Objeto tipo persona agregada a la lista,nulo si no ya existe
 */ 
Persona* insertarPersona(string nombre,string lugarInicio){
    bool existe = validarPersona(nombre,lugarInicio,listaDePersonas);

    if(existe)
    {
        cout<<"La persona ya existe en la lista"<<endl;
        return NULL;
    }
        
    Persona*nuevo = new Persona(nombre,getLugar(lugarInicio));
  
    nuevo -> sigP = listaDePersonas;
    if(listaDePersonas != NULL){
        listaDePersonas -> antP = nuevo;
    }
    listaDePersonas = nuevo;

    return nuevo;
}


/**
 * Metodo para obtener una ruta especifica en la sublista.
 * @param origen lugar de inicio
 * @param destino lugar de llegada
 * @return existeRuta true si existe la ruta o false si no.
 */ 
bool existeRuta = false;
bool buscarRuta( struct Lugar *origen, string destino){

    if((origen == NULL) or (origen->siVisitado== true))
        return existeRuta;

        if(origen->lugar == destino){
                existeRuta= true;
                return existeRuta;
        }
        origen->siVisitado =true;

    struct Ruta *tempA =origen->subLArcos;
    while(tempA != NULL){ 
        buscarRuta(getLugar(tempA->tiempoRecorrido), destino);
        tempA = tempA->sigAr;
    }
    return existeRuta;
}

bool borrarPersona(string nombre){
    Persona* personaEliminar = getPersona(nombre,listaDePersonas);

    if(personaEliminar == NULL){
        cout<<"Esta persona no existe en la lista"<<endl;
        return false;
    
    }
    else if(listaDePersonas->nombre == nombre){
            listaDePersonas = listaDePersonas->sigP;
            return true;
    }else
    {//si esta en medio o al final de la lista
        Persona *temp = listaDePersonas;
        Persona *tempAnt= listaDePersonas;
        while(temp != NULL){
            if(temp->nombre == nombre){//borrar
                    tempAnt->sigP  = temp->sigP;
                    return true;
            }
            tempAnt= temp;
            temp = temp->sigP;
        }
    }
    return false;
}

/**
 * Metodo para agregar nuevo amigo a la lista de amistades de una persona.
 * @param nombrePersona Nombre de la persona.
 * @param nombreAmigo Nuevo amigo a agregar a lista.
 */ 
void agregarAmistadPersona(string nombrePersona,string nombreAmigo){
   Persona*persona = getPersona(nombrePersona,listaDePersonas);

    if(persona == NULL){
        cout<<"No se le puede agregar amigos a la persona ,ya que esta no existe en el grafo."<<endl;
    }

    Persona*personaBackup = persona;
    Persona*amigo = getPersona(nombreAmigo,listaDePersonas);

    if(amigo == NULL){
        cout<<"La nueva amistad no existe en el grafo ,intenta agregandolo primero a este."<<endl;
    }

    Persona*amigoBackup = amigo;
    amigo = new Persona(amigo->nombre,amigo->lugarInicio);
    
    amigo -> sigP = persona->listaAmigos;
    if(persona->listaAmigos != NULL){
        persona->listaAmigos -> antP = amigo;
    }
    persona->listaAmigos = amigo;

    personaBackup = new Persona(personaBackup->nombre,personaBackup->lugarInicio);
    
    personaBackup -> sigP = amigoBackup->listaAmigos;
    if(amigoBackup->listaAmigos != NULL){
        amigoBackup->listaAmigos -> antP = personaBackup;
    }
    amigoBackup->listaAmigos = personaBackup;


}

/**
 * Metodo para mostrar en consola todas las amistades de una persona
 * @param nombrePersona Nombre de la persona a mostrar amistades
 */ 
void imprimirAmistades(string nombrePersona){
    Persona* persona = getPersona(nombrePersona,listaDePersonas);

    if(persona == NULL){
        cout<<"La persona no se encontro en el grafo"<<endl;
        return;
    }

    Persona* amistades = persona->listaAmigos;

    if(amistades == NULL){
        cout<<persona->nombre<<" no tiene amigos."<<endl;
        return;
    }
    
    Persona* temp = amistades;
    while (temp->sigP != NULL){
        temp = temp -> sigP;
    }
    while (temp != NULL){
        cout<<"La persona " <<persona-> nombre<<" es amigo de  "<<temp -> nombre<<endl;
        temp = temp -> antP;
        
    }
}

/**
 * Metodo para mostrar en consola aquellas personas que no tienen amigos
 */ 
void personasSinAmigos(){
    Persona* temp = listaDePersonas;
    while (temp->sigP != NULL){
        temp = temp -> sigP;
    }
    while (temp != NULL){
        if(temp ->listaAmigos == NULL){
            cout<<temp -> nombre<<" no tiene amigos. "<<endl;
        }
        temp = temp -> antP;
        
    }
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
    pressKeyToContinue();
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
    //menu();
    struct Lugar* l1 = insertarLugar("SJ");
    struct Lugar* l2 = insertarLugar("Heredia");
    struct Lugar* l3 = insertarLugar("PQ");

    Persona*p2 = insertarPersona("V","Heredia");
    Persona*p1 = insertarPersona("Manuel","SJ");
    Persona*p3 = insertarPersona("J","PQ");
    //borrarPersona("Manuel");
    //agregarAmistadPersona("Manuel","J");
    //agregarAmistadPersona("Manuel","V");
    imprimirPersona();
    //imprimirAmistades("Manuel");
    personasSinAmigos();
    return 0;
}
