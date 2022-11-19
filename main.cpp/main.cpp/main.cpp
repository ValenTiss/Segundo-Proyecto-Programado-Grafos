//
//  main.cpp
//  main.cpp
//
//  Created by Valen Tissera on 29/10/22.
//

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//Definiciones para poder recorrer rutas
#define INF 999

/**
 *Estructura lugar simboliza los lugares presentes en el
 */

struct Lugar{ //Creacion del Vertice con el lugar que los turistas van a visitar
    string lugar;
    struct Lugar * sigV; //Enlace de los vertices en una lista
    struct Ruta *subLArcos;//lo modifique porque decir lugar//Arcos que salen del vertice

    bool siVisitado;

    /**
     * Metodo constructor de la estructura lugar
     * @param lug Nombre del lugar
     */ 
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
    string destino;

    /**
     * Metodo constructor de la estructra ruta
      * @param tr Tiempo que tarda en recorrerse esta ruta
     */ 
    Ruta(string tr,string destino){
        tiempoRecorrido = tr;
        this->destino = destino;
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
    struct Lugar* lugarActual;
    struct Lugar* lugarDestino;
    struct Ruta* rutasRecorridas;
    struct Lugar* lugaresVisitados;
    
    /**
     * Metodo constructor de la estructura persona
     * @param n Nombre de la persona
     * @param lugarInicio Lugar de inicio de esta persona
     * @param lugarActual Lugar de actual de esta persona
     * @param lugarDestino Lugar de destino de esta persona
     */ 
    Persona(string n,struct Lugar* lugarInicio ,Lugar* lugarDestino){
        nombre = n;
        antP=NULL;
        sigP= NULL;
        this->lugarInicio = lugarInicio;
        this->lugarActual = lugarInicio;
        this->lugarDestino = lugarDestino;
        listaAmigos=NULL;
        rutasRecorridas = NULL;
        lugaresVisitados = lugarInicio;
        lugaresVisitados ->sigV;
    }

}*listaDePersonas;



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
 *Insercion al inicio de la lista de lugares.
 *@param lug Nombre del nuevo lugar
 */
//insercion al inicio de la lista de lugares.
struct Lugar* insertarLugar(string lug){
    Lugar*verificarLugar = getLugar(lug);

    if(verificarLugar != NULL){
        cout<<"Este lugar ya existe."<<endl;
        return NULL;
    }
    
    struct Lugar *nuevoLugar = new Lugar(lug);

    nuevoLugar->sigV = grafo;
    grafo = nuevoLugar;
    return nuevoLugar;
}

/**
 *Metodo para recorrer en amplitud los lugares.
 */
void amplitud(){
        struct Lugar *tempL = grafo;

        while(tempL != NULL){//RECORRE LA LISTA DE VERTICES
            cout<<"\n Lugar: "<<tempL->lugar<<"->\t";
            struct Ruta *tempR = tempL->subLArcos;

            while(tempR != NULL){//RECORRE LOS ARCOS DE LA LISTA DE ARCOS DEL VERTICE
                    cout<<"desde "<<tempL->lugar<<" hasta "<<tempR->destino<<" se tarda "<<tempR->tiempoRecorrido<<" minutos ,  ";
                tempR = tempR->sigAr;
            }
            tempL = tempL->sigV;
        }
}

/**
 *Metodo para recorrer en profundidad los lugares
 *@param inicio Lugar donde se quiere hacer el recorrido
 */
void profundidad (struct Lugar *inicio){
        if((inicio == NULL) or (inicio->siVisitado == true)){
                cout<<endl;
            return;
        }

        inicio->siVisitado = true;

        struct Ruta * tempR = inicio->subLArcos;
        while(tempR != NULL){
            cout<<inicio->lugar<<" a "<<tempR->destino<<" "<<tempR->tiempoRecorrido<<" minutos,  ";

            profundidad(getLugar(tempR->destino));

            tempR = tempR->sigAr;
        }

}


bool existeRuta = false;
/**
 * Metodo para obtener una ruta especifica en la sublista.
 * @param origen lugar de inicio
 * @param destino lugar de llegada
 * @return existeRuta true si existe la ruta o false si no.
 */
bool buscarRuta(struct Lugar *origen, string destino){

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

/**
 Metodo para contar cuantas rutas existen en un
 */

int rutasQty(Lugar* lugar){
    return 0;
}

/**
 *Metodo para mostrar en consola todas las rutas con su debido tiempo de recorrido,este metodo es recursivo.
 *@param anexo Lugar de origen.
 *@param destino Lugar de destino.
 *@param ruta Rutas las cuales se toman.
 *@param dis Tiempo que se tarda en recorrer hasta el destino.
 *@return Booleano que examina si existe rutas.
 */
bool imprimirRutaconDistancias(struct Lugar *anexo, string destino, string ruta, int dis){
    if((anexo == NULL) or (anexo->siVisitado == true))
            return existeRuta;

            if(anexo->lugar == destino){
                    cout<<"\nLa ruta es: "<<ruta<<destino<<" La distancia es: "<<dis;
                    existeRuta= true;
                     return existeRuta;
            }
        anexo->siVisitado =true;

        struct Ruta *tempR =anexo->subLArcos;
        while(tempR != NULL){
            imprimirRutaconDistancias(getLugar(tempR->destino), destino,
                                      ruta+anexo->lugar, dis + stoi(tempR->tiempoRecorrido));
            tempR = tempR->sigAr;
        }
        anexo->siVisitado =false;
    return false;
}

//variables globales
string rutaMenor = "";
int distanciaMenor = 0;

/**
 *Meotdo para encontrar la ruta mas corta hacia un lugar,este metodo es recursivo.
 *@param anexo Lugar de origen a encontrar ruta.
 *@param destino Lugar de destino al cual se quiere llegar.
 *@param ruta Rutas las cuales se tienen que tomar para llegar al destino.
 *@param dis Distancia recorrida para llegar al destino.
 *@return Booleano que examina la existencia de rutas entre los lugares.
 */
bool rutaCorta(struct Lugar *anexo, string destino, string ruta, int dis){
    if((anexo == NULL) or (anexo->siVisitado == true))
        return existeRuta;

        if(anexo->lugar == destino){
                if((distanciaMenor==0) || (dis < distanciaMenor)){
                        distanciaMenor =dis;
                        rutaMenor = ruta+destino;
                }
                existeRuta= true;
                 return existeRuta;
        }
    anexo->siVisitado =true;

    struct Ruta *tempR =anexo->subLArcos;
    while(tempR != NULL){

        rutaCorta(getLugar(tempR->destino), destino, ruta+anexo->lugar, dis + stoi(tempR->tiempoRecorrido));
        tempR = tempR->sigAr;
    }
    anexo->siVisitado =false;
    return false;
}

/**
 *insercion al inicio de la lista de rutas.
 *@param anexo Nombre del lugar de origen de la ruta.
 *@param conexo Nombre del lugar de destino de la ruta.
 *@param tiempoRecorrido tiempo resultante de recorrer toda la ruta.
 */
Ruta* insertarRuta(string anexo ,string conexo,string tiempoRecorrido){
    Lugar*lugarAnexo = getLugar(anexo);

    if(lugarAnexo == NULL){
        cout<<"El lugar "<<anexo <<" no existe en el grafo."<< endl;
        return NULL;
    }

    Lugar*lugarConexo = getLugar(conexo);

    if(lugarConexo == NULL){
        cout<<"El lugar "<<conexo <<" no existe en el grafo."<< endl;
        return NULL;
    }


    struct Ruta *nuevaRuta = new Ruta(tiempoRecorrido,conexo);

    //se inserto al inicio de la sublista de Arcos del primer lugar
    nuevaRuta->sigAr = lugarAnexo->subLArcos;
    lugarAnexo->subLArcos = nuevaRuta;

    struct Ruta *nuevaRutaP = new Ruta(tiempoRecorrido,anexo);
    //se inserto al inicio de la sublista de Arcos del segundo lugar
    nuevaRutaP->sigAr = lugarConexo->subLArcos;
    lugarConexo->subLArcos = nuevaRutaP;

    return nuevaRuta;
}


/**
 * Metodo para obtener una persona especifica en la lista.
 * @param nombre Nombre de la persona la cual se esta buscando.
 * @param listaPersonas Lugar de inicio de la persona a buscar.
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
Persona* insertarPersona(string nombre,string lugarInicio,string lugarDestino){
    bool existe = validarPersona(nombre,lugarInicio,listaDePersonas);

    if(existe)
    {
        cout<<"La persona ya existe en la lista"<<endl;
        return NULL;
    }
    Lugar* lugarI = getLugar(lugarInicio);
    Lugar* lugarD = getLugar(lugarDestino);
    if(lugarI == NULL){
        cout<<"El lugar de inicio no existe."<<endl;
        return NULL;
    }

    if(lugarD == NULL){
        cout<<"El lugar destino no existe."<<endl;
        return NULL;
    }

    Persona*nuevo = new Persona(nombre,lugarI,lugarD);
    
    nuevo -> sigP = listaDePersonas;
    if(listaDePersonas != NULL){
        listaDePersonas -> antP = nuevo;
    }
    listaDePersonas = nuevo;

    return nuevo;
}

/**
 *Metodo para borrar objetos de tipo persona de la lista
 *@param nombre Nombre de la persona la cual se quiere eliminar
 *@return Falso si no se pudo insertar,verdadero si se pudo borrar.
 */
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
    amigo = new Persona(amigo->nombre,amigo->lugarInicio,amigo->lugarDestino);
    
    amigo -> sigP = persona->listaAmigos;
    if(persona->listaAmigos != NULL){
        persona->listaAmigos -> antP = amigo;
    }
    persona->listaAmigos = amigo;

    personaBackup = new Persona(personaBackup->nombre,personaBackup->lugarInicio,personaBackup->lugarDestino);
    
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
    insertarRuta("origen","destino","33");
}

/**
 *Metodo para que una persona avance de manera aleatoria
 *@param persona Persona la cual se va a mover
 */
void avanzarAleatorio(Persona* persona){

    Lugar* inicio= persona->lugarActual;
    Lugar* listaDeDestinos;
    vector<string> lugares;
    int ind;


    if((inicio == NULL) or (inicio->siVisitado == true)){
                cout<<endl;
            return;
        }
        inicio->siVisitado = true;

        struct Ruta * tempR = inicio->subLArcos;
        while(tempR != NULL){

            lugares.push_back(tempR->destino);

            tempR = tempR->sigAr;
        }

        for (size_t i = 0; i < lugares.size(); i++) {
                cout << "lugares"<<lugares[i] <<endl;
            }


    //ind=rand()%(lugares.size()-0+1)+0;
    //cout<<ind<<"hola"<<endl;
    cout<<lugares.size()<<endl;
    cout<<" el lugar escojido es "<<lugares[1]<<endl;//Valentin aca tiene que ir el valor aleatorio para escojer un lugar en la lista
    
}


/**
 *Metodo  para encontrar la ruta mas corta hacia un destino
 *@param persona Objeto tipo persona la cual quiere tomar la ruta corta.
 */
void rutaCortaDestino(Persona *persona){
    Lugar*lugarExaminar = persona->lugarInicio;
    
    
    
}

/**
 *Metodo para interactuar con el usuario
 *@param opcion Opcion ingresada por el usuario a ejecutar
 */
void mantenimientoListas(int opcion){
    //Persona [1]
    // Lugar  [2]
    // Ruta   [3]
    switch (opcion)
    {
    case 1:
    {
        cout<<"[1] - Ingresar nuevo persona al grafo"<<endl;
        cout<<"[2] - Borrar persona al grafo."<<endl;
        cout<<"[3] - Modificar persona que se encunetra en el grafo."<<endl;
        int opcionPersona;
        cin>>opcionPersona;


        switch(opcionPersona)
        {
            case 1:
            {
                string nombreP,inicioP,destinoP;
                cout<<"Ingrese el nombre de la nueva persona: ";
                cin>>nombreP;
                cout<<"\nIngrese el nombre del lugar de inicio: ";
                cin>>inicioP;
                cout<<"\nIngrese el nombre del lugar de destino:";
                cin>>destinoP;
                Persona*nuevaPersona = insertarPersona(nombreP, inicioP, destinoP);
                
                if(nuevaPersona == NULL){
                    cout<<"\nLa persona no se pudo agregar al grafo, intente nuevamente"<<endl;
                    
                };

                string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;
            }

            case 2:
            {
                string nombreP, esperar;
                cout<<"Ingrese el nombre de la persona que desea eliminar: ";
                cin>>nombreP;
                borrarPersona(nombreP);



                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;
            }
            case 3:
            {   
                string nombreP, esperar;
                cout<<"Ingrese el nombre de la persona que desea modificar: ";
                cin>>nombreP;
                //modificarPersona(nombreP);


                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;
            }


        }
    }

    case 2:
    {
        cout<<"[1] - Ingresar nuevo lugar al grafo"<<endl;
        cout<<"[2] - Borrar lugar al grafo."<<endl;
        cout<<"[3] - Modificar lugar que se encunetra en el grafo."<<endl;
        int opcionLugar;
        cin>>opcionLugar;


        switch(opcionLugar)
        {
            case 1:
            {
                string nombreL;
                cout<<"Ingrese el nombre del lugar: ";
                cin>>nombreL;
                Lugar*nuevoLugar = insertarLugar(nombreL);
                
                if(nuevoLugar == NULL){
                    cout<<"\nEl lugar no se pudo agregar, intente nuevamente"<<endl;
                    
                };

                string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;
            }

            case 2:
            {
                string nombreL, esperar;
                cout<<"Ingrese el nombre del lugar que desea eliminar: ";
                cin>>nombreL;
                //borrarLugar(nombreL);
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;
            }

            case 3:
            {   
                string nombreL, esperar;
                cout<<"Ingrese el nombre del lugar que desea modificar: ";
                cin>>nombreL;
                //modificarLugar(nombreL);


                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;
            }


        }
    }



    case 3:
    {
        cout<<"[1] - Ingresar nueva ruta al grafo"<<endl;
        cout<<"[2] - Borrar ruta al grafo."<<endl;
        cout<<"[3] - Modificar ruta que se encunetra en el grafo."<<endl;
        int opcionRuta;
        cin>>opcionRuta;


        switch(opcionRuta)
        {
            case 1:
            {
                string nombreA, nombreC, distancia;
                cout<<"Ingrese el nombre del anexo: ";
                cin>>nombreA;
                cout<<"Ingrese el nombre del conexo: ";
                cin>>nombreC;
                cout<<"Ingrese la distancia: ";
                cin>>distancia;

                Ruta*nuevaRuta = insertarRuta(nombreA,nombreC,distancia);
                
                if(nuevaRuta == NULL){
                    cout<<"\nLa ruta no se pudo agregar, intente nuevamente"<<endl;
                    
                };

                string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;
            }

            case 2:
            {
                string nombreL, esperar;
                cout<<"Ingrese el nombre del lugar que desea eliminar: ";
                cin>>nombreL;


                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;
            }
            
            case 3:
            {   
                string nombreP, esperar;
                cout<<"Ingrese el nombre de la persona que desea modificar: ";
                cin>>nombreP;
                //modificarLugar(nombreL);


                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;
            }


        }



    }
    }
}

void consultas(int opcion){
    switch (opcion)
    {

    case 1:
    {
        cout<<endl<<"Estado de las personas en cada avance: "<<endl;
        //metodo

        string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;


    }

    case 2:
    {
        cout<<endl<<"La persona con mas amigos: "<<endl;
        //metodo

        string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;

    }

    case 3:
    {
        cout<<endl<<"Primera persona en terminar la caminata: "<<endl;
        //metodo

        string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;

    }

    case 4:
    {

        cout<<endl<<"Ultima persona en terminar la caminata: "<<endl;
        //metodo

        string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;

    }



}

}


void reportes(int opcion){

    switch (opcion)
    {

    case 1:
    {
        cout<<endl<<"Grafo en amplitud, con toda la info almacenada: "<<endl;
        amplitud();

        string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;


    }

    case 2:
    {

        cout<<endl<<"...Profundidad del grafo... "<<endl;
        cout<<endl<<"Los lugares son los siguientes: "<<endl;
        //imprimirLugares();
        cout<<endl;
        cout<<endl<<"Indique cual vertice(Lugar) desea ver: "<<endl;

        //profundidad();
        //metodo
        string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;

    }

    case 3:
    {
        cout<<endl<<"Rutas para las personas que avanzan de la forma 3 y 4 son las siguientes: "<<endl;
        //metodo

        string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;

    }

    case 4:
    {
        string nombreP;
        cout<<endl<<"Indique cual persona desea ver la cantidad y nombre de amigos: "<<endl;
        cin>>nombreP;
        imprimirAmistades(nombreP);

        string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;

    }

    case 5:
    {
        cout<<endl<<"Quien o quienes no encontraron ningun amigo: "<<endl;
        //metodo

        string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;

        
    }

    case 6:
    {
        cout<<endl<<"Cuales personas no pudieron realizar la caminada por no haber una ruta, o por no haber conexion conexa: "<<endl;
        //metodo
        
        string esperar;
                cout<<"Ingrese alguna tecla y presione enter para continuar: ";
                cin>>esperar;
                break;

        
    }



}



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
/**
 * Metodo para dibujar menu
 * 
 * @param opcion opcion 
*/
void dibujarMenu(int opcion)
{
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
     
        int c;
        do {
            dibujarMenu(0);
            c=getchar();
            switch((int)c - '0')
            {
            case 1:
                {
                    dibujarMenu(1);
                    int opcionUno;
                    cin>>opcionUno;
                    mantenimientoListas(opcionUno);
                    break;
                }
            case 2:
                {
                    dibujarMenu(2);
                    int opcionDos;
                    cin>>opcionDos;
                    consultas(opcionDos);
                    break;
                }
            case 3:
                {
                    dibujarMenu(3);
                    int opcionTres;
                    cin>>opcionTres;
                    reportes(opcionTres);
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
