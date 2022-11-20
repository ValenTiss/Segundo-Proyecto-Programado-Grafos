#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

//Definiciones para poder recorrer rutas.
#define INF 999

//---------------------------- Estructuras del Grafo ---------------------------- //
/**
 *Estructura de lugar, simboliza los lugares presentes en el grafo.
 */

struct Lugar{ //Creacion del Vertice con el lugar que los turistas van a visitar
    string lugar;
    struct Lugar * sigV; //Enlace de los vertices en una lista.
    struct Ruta *subLArcos;//Sublista de arcos.

    bool siVisitado;

    /**
     * Metodo constructor de la estructura lugar.
     * @param lug Nombre del lugar.
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
     * Metodo constructor de la estructra ruta.
      * @param tr Tiempo que tarda en recorrerse esta ruta.
     */ 
    Ruta(string tr,string destino){
        tiempoRecorrido = tr;
        this->destino = destino;
        sigAr = NULL;

    }

};

struct Lugar *grafo; // Apuntador del incio del grafo.


/**
 * Estrucutra que simboliza a las personas que se encontraran presentes en el grafo.
 */ 
struct Persona{//Creacion de la persona (doble) con su lista de amigos.
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
     * Metodo constructor de la estructura de persona.
     * @param n Nombre de la persona.
     * @param lugarInicio Lugar de inicio de esta persona.
     * @param lugarDestino Lugar de destino de esta persona.
     * 
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
    }

}*listaDePersonas; // Lista de las personas en el grafo.

//---------------------------- Metodos de Lugares ---------------------------- //

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
 *@param lug Nombre del nuevo lugar.
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
// Declaracion de metodos para usar mas adelante
bool borrarRuta(string origen,string destino);
void cambiarLugarPersonas(Lugar* lugar);

/**
 *Borrar aquellas rutas que conectaban con el lugar que se acaba de borrar,metodo ligado a borrar lugar
 *@param lugarBorrar lugar destino el cual se quiere borrar todas las rutas relacionadas.
 */
void borrarRutaInexistente(string lugarBorrar){
        Lugar*tempL = grafo;
        while(tempL != NULL){
            Ruta*tempR = tempL->subLArcos;
            while(tempR != NULL){
                if(tempR->destino == lugarBorrar)
                    borrarRuta(tempL->lugar,lugarBorrar);
                tempR = tempR -> sigAr;
            }
            tempR = tempR -> sigAr;
        }
}

/**
 *Borrar un lugar del grafo
 *@param lugar el cual se va a borrar
 *@return Booleano que indica si
 */
bool borrarLugar(string lugar){
    Lugar* lugarEliminar = getLugar(lugar);

    if(lugarEliminar == NULL){
        cout<<"Esta lugar no existe en el grafo"<<endl;
        return false;
    
    }
    else if(grafo == getLugar(lugar)){
        grafo = grafo->sigV;
        //cambiarLugarPersona();
        borrarRutaInexistente(lugar);
        return true;
    }else
    {//si esta en medio o al final de la lista
        Lugar *temp = grafo;
        Lugar *tempAnt= grafo;
        while(temp != NULL){
            if(grafo == getLugar(lugar)){//borrar
                cambiarLugarPersonas(getLugar(lugar));
                borrarRutaInexistente(lugar);
                tempAnt->sigV  = temp->sigV;
                return true;
            }
            tempAnt= temp;
            temp = temp->sigV;
        }
    }
    return false;
}

/**
 *Metodo para mostrar en consola todas aquellas personas las cuales no encontraron ruta para llegar a su destino.*
 */


/**
 *Metodo para contar cuantas lugares existen en el grafo
 *@return Entero que contiene la cantidad de lugares existentes en el grafo.
 */

int sizeGrafo(){
    int i = 0;
    Lugar* temp = grafo;
    while(temp != NULL){
        i += 1;
        temp = temp -> sigV;
    }
    return i;
}

/**
 *Metodo para encontrar la posicion.
 *@param pos Posicion a buscar.
 *
 *@return Lugar  encontrado
 */
Lugar* posicionLugar(int pos){
    Lugar* temp = grafo;
    int i = 0;
    while(temp != NULL){
        if(pos == i)
            return temp;
        i += 1;
        temp = temp -> sigV;
    }
    return NULL;
}

/**
 *Metodo para conocer  que posicion ocupa un lugar en el grafo.
 *@param lugar Lugar el cual queremos determinar su posicion.
 *@return Entero que tiene la posicion.
 */
int posicionLugar(Lugar* lugar){
    int i = 0;
    Lugar* temp = grafo;
    while(temp != NULL){
        if(temp->lugar == lugar->lugar)
            return i;
        i += 1;
        temp = temp -> sigV;
    }
    return i;
}
/**
 *Metodo para contar cuantas rutas existen en un lugar designado.
 *@param lugar Lugar que se eliigio para hacer el conteo de rutas.
 *@return Entero con el numero de rutas existentes en un lugar.
 */
int sizeLugar(Lugar* lugar){
    Ruta*TempR = lugar -> subLArcos;
    int i = 0;
    while(TempR != NULL){
        i += 1;
        TempR = TempR -> sigAr;
    }
    return i;
}

/**
 *Metodo para mostrar cuales lugares existen
 */

void imprimirLugares(){
    Lugar* temp = grafo;
    while(temp != NULL){
        cout<<"El lugar de nombre "<< temp->lugar <<" se encuentra en el grafo en la posicion "<< posicionLugar(temp)<<" ."<<endl;
        temp = temp -> sigV;
    }
}



//---------------------------- Metodos de Consultas ---------------------------- //
//Variable globales
bool existeRuta = false;

//Declaracion de metodos
bool buscarRuta(struct Lugar *origen, string destino);

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


/**
 *Metodo para mostrar en consola todas aquellas personas las cuales no encontraron ruta para llegar a su destino.*
 */

void personasSinRutas(){
    Persona*tempP = listaDePersonas;
    while (tempP != NULL) {
        buscarRuta(tempP->lugarInicio, tempP->lugarDestino->lugar);
        if(!existeRuta)
            cout<<"La persona con el nombre "<< tempP->nombre << " no encontro ruta para llegar a su destino."<<endl;
        existeRuta = false;
        tempP = tempP -> sigP;
    }
    
}

//---------------------------- Metodos de Rutas ---------------------------- //

/**
 *Metodo para obtener una ruta en el grafo
 *@param origen Lugar de origen de la ruta a buscar.
 *@param destino Lugar de destino de la ruta a buscar
 *@return La ruta si se encuentra ,nulo si no se encuentra
 */
Ruta* getRuta(struct Lugar*origen,string destino)
{
    Lugar*tempL = grafo;
    while(tempL != NULL){
        Ruta*tempR = tempL ->subLArcos;
        while(tempR){
            if((tempL == origen) &&(getLugar(tempR->destino)))
                return tempR;
            tempR = tempR -> sigAr;
        }
            
        tempL = tempL ->sigV;
    }
    return NULL;
}
/**
 * Metodo para obtener una ruta especifica en la sublista.
 * @param origen lugar de inicio
 * @param destino lugar de llegada
 * @return existeRuta true si existe la ruta o false si no.
 */
bool buscarRuta(struct Lugar *origen, string destino)
{
    if((origen == NULL) or (origen->siVisitado== true))
        return existeRuta;

        if(origen->lugar == destino){
                existeRuta= true;
                 return existeRuta;
        }
        origen->siVisitado =true;

    struct Ruta *tempA =origen->subLArcos;
    while(tempA != NULL){

        buscarRuta(getLugar(tempA->destino), destino);
        tempA = tempA->sigAr;
    }
    return NULL;
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

    //se inserto al inicio de la sublista de Arcos del primer lugar.
    nuevaRuta->sigAr = lugarAnexo->subLArcos;
    lugarAnexo->subLArcos = nuevaRuta;

    struct Ruta *nuevaRutaP = new Ruta(tiempoRecorrido,anexo);
    //se inserto al inicio de la sublista de Arcos del segundo lugar.
    nuevaRutaP->sigAr = lugarConexo->subLArcos;
    lugarConexo->subLArcos = nuevaRutaP;

    return nuevaRuta;
}

bool borrarRuta(string origen ,string destino){
    Ruta* rutaEliminar = getRuta(getLugar(origen),destino);

    if(rutaEliminar == NULL){
        cout<<"Esta ruta no existe en el grafo"<<endl;
        return false;
    
    }
    
    Ruta*rutasBuscar = getLugar(origen)->subLArcos;
    
    if(rutasBuscar == rutaEliminar){
        rutasBuscar = rutasBuscar->sigAr;
        return true;
    }else
    {//si esta en medio o al final de la lista
        Ruta *temp = rutasBuscar;
        Ruta *tempAnt= rutasBuscar;
        while(temp != NULL){
            if(temp->destino == destino){//borrar
                    tempAnt->sigAr  = temp->sigAr;
                    return true;
            }
            tempAnt= temp;
            temp = temp->sigAr;
        }
    }
    return false;
}

//---------------------------- Metodos de Persona ---------------------------- //

/**
 * Metodo para obtener una persona especifica en la lista.
 * @param nombre Nombre de la persona la cual se esta buscando.
 * @param listaPersonas Lugar de inicio de la persona a buscar.
 * @return La persona si se encuentra en la lista, nulo si no se encuentra.
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
 *Metodo para insertar personas en la lista.
 *@param nombre Nombre de la persona.
 *@param lugarInicio Lugar de inicio de la persona.
 *@return Objeto tipo persona agregada a la lista,nulo si no ya existe.
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
 *Metodo para borrar objetos de tipo persona de la lista.
 *@param nombre Nombre de la persona la cual se quiere eliminar.
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
 *Metodo utilizado para cambiar lugar de las personas cuando un lugar se esta por borrar,metodo relacionado con borrar lugar.
 *@param lugar Lugar donde se van a ir las personas.
 */
void cambiarLugarPersonas(Lugar* lugar){
    Persona*tempP = listaDePersonas;
    Persona*personasCambiar;
    while(tempP != NULL){
        if(tempP->lugarInicio == lugar){
            tempP -> sigP = personasCambiar;
            if(personasCambiar != NULL){
                personasCambiar -> antP = tempP;
            }
            personasCambiar = tempP;
        }
        tempP = tempP -> sigP;
    }
    
    //encontramos lugar mas cercano
    Ruta*tempR =lugar->subLArcos;
    Lugar*lugarCambiar = getLugar(tempR->destino);
    int tiempoHuida = stoi(tempR->tiempoRecorrido);
    while(tempR != NULL){
        if(tiempoHuida > stoi(tempR->tiempoRecorrido)){
            lugarCambiar = getLugar(tempR->destino);
        }
        tempR = tempR -> sigAr;
    }
    
    //Cambiamos a todas las personas de lugar
    tempP = personasCambiar;
    while(tempP != NULL){
        if(tempP -> lugarInicio)
            tempP->lugarInicio = lugarCambiar;
        if(tempP -> lugarDestino)
            tempP->lugarDestino = lugarCambiar;
        tempP->lugarActual = lugarCambiar;
    }
}

/**
 * Metodo para mostrar en consola todas las amistades de una persona.
 * @param nombrePersona Nombre de la persona a mostrar amistades.
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
 * Metodo para modificar a una persona en la lista dentro del grafo.
 * @param persona Nombre de la persona a modificar.
 * @param nuevaPersona Nombre de la nueva persona.
 */ 


void modificarPersona(string persona, string nuevaPersona, Persona*listaDePersonas){

    Persona* modificar = getPersona(persona, listaDePersonas);
        if(modificar!= NULL){
            modificar->nombre = nuevaPersona;
        }
     

}

/**
 * Metodo para modificar un lugar en la lista dentro del grafo.
 * @param lugar Nombre del lugar que se va a modificar.
 * @param nuevoLugar Nombre del nuevo lugar.
 */ 


void modificarLugar(string lugar, string nuevoLugar){

    Lugar* modificar = getLugar(lugar);
        if(modificar!= NULL){
            modificar->lugar = nuevoLugar;
        }

}

/**
 * Metodo para modificar la ruta de un lugar a otro
 * @param anexo Nombre del lugar de origen de la ruta a modificar.
 * @param conexo Nombre del lugar de destino de la ruta a modificar.
 * @param tiempoRecorrido Tiempo recorrido a modificar.
 * @param nuevoAnexo Nuevo nombre del lugar origen.
 * @param nuevoConexo Nuevo nombre del lugar destino.
 * @param nuevoTR Nuevo tiempo de recorrido.
 */ 

void modificarRuta(string anexo ,string conexo,string tiempoRecorrido, string nuevoAnexo, string nuevoConexo, string nuevoTR){

    //Ruta * modificar = buscarRuta(ruta);

       // if(modificar!= NULL){
                //modificar->destino = nuevaRuta;
           // }


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
 *Metodo para contar cuantas amistades tiene una persona
 *@param persona Persona la cual queremo averiguar la cantidad de amigos.
 *@return Entero con la cantidad de amigos
 */
int contarAmigos(Persona* persona){
    int i = 0;
    Persona*temp = persona->listaAmigos;
    while (temp != NULL){
        temp = temp -> sigP;
        i += 1;
    }
    return i;
}

/**
 *Metodo para mostrar cuales personas son las que tienen mas amgos
 */
void personasConMasAmigos(){
    Persona*personaSociable = listaDePersonas;
    
    Persona*temp  = listaDePersonas;
    int i = contarAmigos(personaSociable);
    
    while (temp->sigP != NULL){
        temp = temp -> sigP;
    }
    while (temp != NULL){
        int qtyAmigos = contarAmigos(temp);
        if(qtyAmigos > i){
            i = qtyAmigos;
            personaSociable = temp;
        }
        temp = temp -> antP;
        
    }
    if(i == 1)
        cout<<"La persona que mas amigos tiene es "<< personaSociable->nombre <<" y su unico amigo es: "<<endl;
    else
        cout<<"La persona que mas amigos tiene es "<< personaSociable->nombre <<" y sus " << i << " amigos son: "<<endl;
    
    Persona*mostrarAm = personaSociable->listaAmigos;
    while(mostrarAm != NULL){
        cout<<"\t -"<< personaSociable ->listaAmigos->nombre<<endl;
        mostrarAm = mostrarAm -> sigP;
    }
    
}

//---------------------------- Metodos para el Grafo ---------------------------- //

/**
 *Metodo que Carga datos automaticos para que las listas no se encuentren vacias.
 */
void CargarDatos(){
    insertarLugar("San Jose");
    insertarLugar("Heredia");
    insertarLugar("Alajuela");
    insertarLugar("San Carlos");
    insertarRuta("Heredia", "Alajuela", "4");
    insertarRuta("Heredia", "San Carlos", "4");
    //insertarRuta("San Jose", "Heredia","12");;
    //insertarRuta("San Jose", "Alajuela","23");
    insertarRuta("San Jose", "San Carlos","5");
    
    insertarPersona("Valentin", "San Jose", "Heredia");
    insertarPersona("Juan", "Heredia", "San Carlos");
    insertarPersona("Jorge", "San Jose", "San Carlos");
    
    agregarAmistadPersona("Valentin", "Juan");
    
    //N = sizeGrafo();
}


/**
 *Metodo que obtiene el minimo de dos numeros.
 * @param a Numero a comparar.
 * @param b Numero a comparar.
 */
int minimo(int a,int b)
{
    if(a>b)
        return b;
    else
        return a;
}


//---------------------------- Tipos de avance ---------------------------- //
/**
 *Metodo para que una persona avance de manera aleatoria a traves del grafo
 *@param persona Persona la cual se va a mover
 *@param lugarAnterior Si se llama al metodo, este parametro debe ser un string vacio ("").
 */

void avanzarAleatorio(Persona* persona, string lugarAnterior){

    Lugar* inicio= persona->lugarActual;
    vector<string> lugares;
    int ind;
    string lugarSet;
    string lugarAnt;

    cout<<endl;
    cout<<"Lugar actual "<<inicio->lugar<<endl;
    
    if((inicio == NULL) or (inicio->siVisitado == true)){
        cout<<endl;
        return;
    }
    
    inicio->siVisitado = true;
    lugarAnt=lugarAnterior;
    struct Ruta * tempR = inicio->subLArcos;
    while(tempR != NULL){
        cout<<"Hay ruta entre: "<<inicio->lugar<<" y "<<tempR->destino<<endl;
        if(tempR->destino!=lugarAnt){
            lugares.push_back(tempR->destino);    
        }
        else{
            cout<<"No se puede viajar hacia: "<<tempR->destino<<", porque es el lugar anterior."<<endl;
        }
        tempR = tempR->sigAr;
            ///
            
    }
    if(lugares.size()>=1){
        srand((unsigned int)time(NULL));
        ind=rand()%lugares.size();
    }else{
        cout<<"No hay mas vertices hacia donde ir desde el lugar actual. Fin del recorrido.";
        cout<<endl;
        return;
    }
    for (size_t x = 0; x < lugares.size(); x++) {
        cout <<"Desde "<<inicio->lugar<<" se puede viajar hacia: "<<lugares[x] <<endl;
    }
    for (size_t i = 0; i < lugares.size(); i++) {
        cout<<"Cantidad de lugares a los que se puede viajar desde el vertice actual: "<<lugares.size()<<endl;
        cout<<"El lugar escojido es "<<lugares[ind]<<endl;
        lugarAnt=inicio->lugar;
        cout<<"Lugar anterior: "<<lugarAnt<<endl;
        
        if(lugarAnt!=lugares[ind]){
            lugarSet= lugares[ind];    
            persona->lugarActual=getLugar(lugarSet);
            lugares.clear();
            inicio=persona->lugarActual;
            if (inicio->lugar!=lugarAnt){
                avanzarAleatorio(persona, lugarAnt);
            }      
        }
    }
}


/**
 *Metodo para encontrar la ruta mas corta hacia un destino.
 *@param persona Objeto tipo persona la cual quiere tomar la ruta corta.
 */
void rutaCortaDestino(Persona *persona){
    //Pasamos las rutas a una matriz
    int N = sizeGrafo();
    int A[N][N];
    Lugar* temp =  grafo;
    int y = 0;
    while(temp != NULL){
        Ruta*tempRutas = temp->subLArcos;
        cout << temp ->lugar<< " : ";
        int pos;
        for(int x = 0;x < N ;x++)
        {
            A[y][x] = INF;
        }
        while(tempRutas != NULL)
        {
            pos = posicionLugar(getLugar(tempRutas->destino));
            A[y][pos] = stoi(tempRutas->tiempoRecorrido);
            tempRutas = tempRutas->sigAr;
        }
        temp = temp->sigV;
        for(int w = 0; w < N ;w++){
            if(A[y][w] == INF)
                cout<< " INF ";
            else
                cout<<A[y][w]<<" ";
        }
        y += 1;
        
        cout<<endl;
    }
    
    
    int D[N][N],i,j,vi,min,ve,S[N];
        
    for(i = 0;i<N;i++)
    {
        S[i] = 0;
    }
    
    vi = posicionLugar(persona->lugarInicio)+ 1;
    S[vi-1] = 1;
    
    for(i = 0;i<N;i++){
        D[0][i] = A[vi-1][i];
    }
    
    for(j=0;j<N-1;j++)
    {
        min=INF;
        ve=0;
        for(i=0;i<N;i++)
        {
            if(D[j][i]<min && S[i]==0)//el mas pequeÒo de todos los no visitados
            {
                min=D[j][i];
                ve=i;
                //cout<<min<<endl;
                
            }
        }
        S[ve]=1;
        
        for(i=0;i<N;i++)
        {
            D[j+1][i]=minimo(D[j][i],D[j][ve]+A[ve][i]);

            cout<<D[j+1][i]<<endl;
        }
        
    }
    
    cout << "\t";
    for(i=0;i<N;i++)
        cout << (i+1) << "\t";

    cout << endl;

    for(j=0;j<N;j++)
    {
        cout << (j+1) << "\t";
        for(i=0;i<N;i++)
        {
            if(D[j][i]==INF)
                cout << "INF\t";
            else
                cout << D[j][i] << "\t";
        }
        cout << endl;
    }
    
    int rutaCortamin = D[N-1][posicionLugar(persona->lugarInicio)-1];//Ruta corta [tño grafo -1 ] [pos lugar en el grafo - 1]
        
}


/**
 *Metodo para encontrar la ruta por tiempo.
 *@param tiempo El tiempo que se dura para llegar al lugar.
 *@param origen El punto de inicio (anexo) del lugar.
 *@param destino El punto de destino (conexo) del lugar.
 */
Ruta* buscarRutaPorTiempo(int tiempo,string origen,string destino){
    Ruta* rutasRecorridas;
    Ruta* tempR = getLugar(origen)->subLArcos;
    int intento = 0;
    while(tempR != NULL)
    {
        rutasRecorridas = tempR;
        
        for(int i = 0;i < sizeLugar(getLugar(tempR->destino)) ;i++){
            intento = stoi(tempR->tiempoRecorrido);
            while(intento < tiempo){
                
            }
        }
        
        tempR = tempR ->sigAr;
    }
    return 0;
}

//variables globales
string rutaMenor = "";
int distanciaMenor = 0;
Lugar* lugaresVisitados;
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

        if(anexo->lugar == destino)
        {
            if((distanciaMenor==0) || (dis < distanciaMenor)){
                    distanciaMenor =dis;
                    rutaMenor = ruta+" "+destino;
            }
            existeRuta= true;
             return existeRuta;
        }
    anexo->siVisitado =true;

    struct Ruta *tempR =anexo->subLArcos;
    while(tempR != NULL){
        lugaresVisitados = getLugar(anexo->lugar);
        lugaresVisitados = lugaresVisitados -> sigV;
        rutaCorta(getLugar(tempR->destino), destino, ruta+" "+anexo->lugar, dis + stoi(tempR->tiempoRecorrido));
        tempR = tempR->sigAr;
    }
    anexo->siVisitado =false;
    
    return NULL;
}


//
//int N = 1;
//
//bool hasCycle;
//
//// Function to check if a vertex v
//// can be added at index pos in
//// the Hamiltonian Cycle
//bool isSafe(int v, int graph[][N], vector<int> path, int pos)
//{
//
//    // If the vertex is adjacent to
//    // the vertex of the previously
//    // added vertex
//    if (graph[path[pos - 1]][v] == 0)
//        return false;
//
//    // If the vertex has already
//    // been included in the path
//    for (int i = 0; i < pos; i++)
//        if (path[i] == v)
//            return false;
//
//    // Both the above conditions are
//    // not true, return true
//    return true;
//}
//
//// Recursive function to find all
//// hamiltonian cycles
//void FindHamCycle(int graph[][N], int pos, vector<int> path, bool visited[], int J)
//{
//    // If all vertices are included
//    // in Hamiltonian Cycle
//    if (pos == J) {
//
//        // If there is an edge
//        // from the last vertex to
//        // the source vertex
//        if (graph[path[path.size() - 1]][path[0]] != 0) {
//
//            // Include source vertex
//            // into the path and
//            // print the path
//            path.push_back(0);
//            for (int i = 0; i < path.size(); i++) {
//                cout << path[i] << " ";
//            }
//            cout << endl;
//
//            // Remove the source
//            // vertex added
//            path.pop_back();
//
//            // Update the hasCycle
//            // as true
//            hasCycle = true;
//        }
//        return;
//    }
//
//    // Try different vertices
//    // as the next vertex
//    for (int v = 0; v < J; v++) {
//
//        // Check if this vertex can
//        // be added to Cycle
//        if (isSafe(v, graph, path, pos) && !visited[v]) {
//
//            path.push_back(v);
//            visited[v] = true;
//
//            // Recur to construct
//            // rest of the path
//            FindHamCycle(graph, pos + 1, path, visited, J);
//
//            // Remove current vertex
//            // from path and process
//            // other vertices
//            visited[v] = false;
//            path.pop_back();
//        }
//    }
//}
//
//// Function to find all possible
//// hamiltonian cycles
//void hamCycle(int *graph[][N], int J)
//{
//    // Initially value of boolean
//    // flag is false
//    hasCycle = false;
//
//    // Store the resultant path
//    vector<int> path;
//    path.push_back(0);
//
//    // Keeps the track of the
//    // visited vertices
//    bool visited[J];
//
//    for (int i = 0; i < J; i++)
//        visited[i] = false;
//
//    visited[0] = true;
//
//    // Function call to find all
//    // hamiltonian cycles
//    FindHamCycle(graph, 1, path, visited, J);
//
//    if (!hasCycle) {
//
//        // If no Hamiltonian Cycle
//        // is possible for the
//        // given graph
//        cout << "No Hamiltonian Cycle" << "possible " << endl;
//        return;
//    }
//}
//
//
//void createBoolValues(){
//    //Pasamos las rutas a una matriz
//
//    bool A[N][N];
//    Lugar* temp =  grafo;
//    int y = 0;
//    while(temp != NULL){
//        Ruta*tempRutas = temp->subLArcos;
//        cout << temp ->lugar<< " : ";
//        int pos;
//        for(int x = 0;x < N ;x++)
//        {
//            A[y][x] = 0;
//        }
//        while(tempRutas != NULL)
//        {
//            pos = posicionLugar(getLugar(tempRutas->destino));
//            A[y][pos] = 1;
//            tempRutas = tempRutas->sigAr;
//        }
//        temp = temp->sigV;
//        for(int w = 0; w < N ;w++){
//            if(A[y][w] == 0)
//                cout<< "\t0 ";
//            else
//                cout<<"\t"<< 1;
//        }
//        y += 1;
//
//        cout<<endl;
//    }
//    hamCycle(A, N);
//}


/**
 *Metodo que al pulsar alguna tecla seguidamente el enter limpie la consola y continue.
 */

//---------------------------- Metodos para el Menu ---------------------------- //

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
 *Metodo para el mantenimiento de las listas, menu interactivo con el usuario.
 *@param opcion Opcion ingresada por el usuario a ejecutar.
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
            cout<<"[3] - Modificar persona que se encuentra en el grafo."<<endl;
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
                }
                    
                case 2:
                {
                    string nombreP, esperar;
                    cout<<"Ingrese el nombre de la persona que desea eliminar: ";
                    cin>>nombreP;
                    borrarPersona(nombreP);
                    
                    break;
                }
                case 3:
                {
                    string nombreP, esperar;
                    cout<<"Ingrese el nombre de la persona que desea modificar: ";
                    cin>>nombreP;
                    //modificarPersona(nombreP);
                    
                    break;
                }
                    break;
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
                        
                        break;
                    }
                        
                    case 2:
                    {
                        string nombreL, esperar;
                        cout<<"Ingrese el nombre del lugar que desea eliminar: ";
                        cin>>nombreL;
                        //borrarLugar(nombreL);
                        break;
                    }
                        
                    case 3:
                    {
                        string nombreL,lugarNuevo, esperar;
                        cout<<"Ingrese el nombre del lugar que desea modificar: ";
                        cin>>nombreL;
                        cout<<endl<<"Ingrese el nombre del lugar que desea modificar: ";
                        cin>>lugarNuevo;
                        
                        modificarLugar(nombreL, lugarNuevo);
                        break;
                    }
                        
                }
                break;
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
                            
                        }
                        break;
                    }
                        
                    case 2:
                    {
                        string nombreA, nombreC, distancia, esperar;
                        cout<<"Ingrese el nombre del inicio de la ruta que desea eliminar: ";
                        cin>>nombreA;
                        cout<<"Ingrese el nombre del destino de la ruta que desea eliminar: ";
                        cin>>nombreC;
                        cout<<"Ingrese la distancia de la ruta que desea eliminar: ";
                        cin>>nombreC;
                        //borrarRuta(nombreA,nombreC, distancia);
                        
                        break;
                    }
                        
                    case 3:
                    {
                        string nombreA,nuevaA,nombreC,nuevoC, distancia,  esperar;
                        cout<<"Ingrese el nombre del anexo de la ruta que desea modificar: ";
                        cin>>nombreA;
                        cout<<endl<<"Ingrese el nombre de la nueva ruta: ";
                        cin>>nuevaA;
                        cout<<"Ingrese el nombre del conexo la ruta que desea modificar: ";
                        cin>>nombreC;
                        cout<<endl<<"Ingrese el nombre del nuevo conexo la nueva ruta: ";
                        cin>>nuevoC;
                        cout<<endl<<"Ingrese la nueva distancia que va a tener la ruta: ";
                        cin>>distancia;
                        //modificarRuta(nombreA,nuevaA,nombreC,nuevoC,distancia);
                        
                        
                        break;
                    }
                        
                        
                }
                break;
            }
            
        }
    }
}
    


void consultas(int opcion){
    cout<<"[1] -  Mostrar el estado de las personas en cada avance"<<endl;
    cout<<"[2] -  Persona con mas amigos"<<endl;
    cout<<"[3] -  Primera persona en terminar la caminata"<<endl;
    cout<<"[4] -  Ultima persona en terminar la camita"<<endl;
    switch (opcion)
    {
            
            
        case 1:
        {
            cout<<endl<<"Estado de las personas en cada avance: "<<endl;
            //metodo
            
            break;
            
            
        }
            
        case 2:
        {
            cout<<endl<<"La persona con mas amigos: "<<endl;
            personasConMasAmigos();
            
            break;
            
        }
            
        case 3:
        {
            cout<<endl<<"Primera persona en terminar la caminata: "<<endl;
            //metodo
            
            break;
            
        }
            
        case 4:
        {
            
            cout<<endl<<"Ultima persona en terminar la caminata: "<<endl;
            //metodo
            break;
            
        }
    }
    pressKeyToContinue();
}
    




void reportes(int opcion){
    cout<<"[1] -  Imprimir grafo en amplitud, con toda la info almacenada"<<endl;
    cout<<"[2] -  Imprimir en profundidad el grafo ( se indica cual vertice de incio)"<<endl;
    cout<<"[3] -  Imprimir las rutas para las personas que avanzan de la forma 3 y 4"<<endl;
    cout<<"[4] -  Imprimir la cantidad y el nombre de los amigos que logro realizar una persona"<<endl;
    cout<<"[5] -  Quien o quienes no encontraron ningun amigo"<<endl;
    cout<<"[6] -  Cuales personas no pudieron realizar la caminada por no haber una ruta, o por no haber conexion conexa"<<endl;
    switch (opcion)
    {

        case 1:
        {
            cout<<endl<<"Grafo en amplitud, con toda la info almacenada: "<<endl;
            amplitud();
            break;

        }

        case 2:
        {
            string nombreLugar;
            cout<<endl<<"...Profundidad del grafo... "<<endl;
            cout<<endl<<"Los lugares son los siguientes: "<<endl;
            imprimirLugares();
            cout<<endl<<"Indique cual vertice(Lugar) desea ver: ";
            cin>>nombreLugar;
            while(getLugar(nombreLugar) == NULL){
                cout<<"Este lugar no existe ,intente nuevamente: ";
                cin>>nombreLugar;
            }
            
            profundidad(getLugar(nombreLugar));
            break;

        }

        case 3:

        {
            cout<<endl<<"Rutas para las personas que avanzan de la forma 3 y 4 son las siguientes: "<<endl;
            //metodo
            break;

        }

        case 4:
        {
            string nombreP;
            cout<<endl<<"Indique cual persona desea ver la cantidad y nombre de amigos: "<<endl;
            cin>>nombreP;
            imprimirAmistades(nombreP);
            break;

        }

        case 5:
        {
            cout<<endl<<"Quien o quienes no encontraron ningun amigo: "<<endl;
            personasSinAmigos();
            break;

            
        }

        case 6:
        {
            cout<<endl<<"Cuales personas no pudieron realizar la caminada por no haber una ruta, o por no haber conexion conexa: "<<endl;
            personasSinRutas();
            break;
        }
    }
    pressKeyToContinue();


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
            cout<<"\t[1] -  Imprimir grafo en amplitud, con toda la info almacenada"<<endl;
            cout<<"\t[2] -  Imprimir en profundidad el grafo ( se indica cual vertice de incio)"<<endl;
            cout<<"\t[3] -  Imprimir las rutas para las personas que avanzan de la forma 3 y 4"<<endl;
            cout<<"\t[4] -  Imprimir la cantidad y el nombre de los amigos que logro realizar una persona"<<endl;
            cout<<"\t[5] -  Quien o quienes no encontraron ningun amigo"<<endl;
            cout<<"\t[6] -  Cuales personas no pudieron realizar la caminada por no haber una ruta, o por no haber conexion conexa"<<endl;
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
    //menu()
    CargarDatos();
    return 0;
}
