//Inicializacion librerias para el socket
#include <iostream>
#include <winsock2.h>
//Inicializacion librerias para el grafo
#include <stdio.h>
#include <stdlib.h>

//defininedo estructuras a utilizrpor el grafo
#define Nodo struct nodo
#define Arista struct arista
#define Lista struct pila
using namespace std;


Nodo{
    //Atributos de la estuctura
	char dato; //dato que tendra el nodo
	Nodo* siguiente; // apuntador nodo al siguiente
	Arista* adyacencia;// apuntador arista, que sera la lista de los nodos relacionados al nodo inicializado
	int visitado,terminado;//
	int monto;//
	char anterior;//
};

Arista{
    //Atributos de la estuctura
	Nodo*vrt; //nodo apuntador
	Arista*siguiente; //arista apuntador al siguiente, sera como una lista tambien
	int peso;
};

Lista{
    //Atributos de la estuctura
	Nodo* dato;
	Lista*siguiente;
};

//para empezar a crear la lista de vertices con estruct Nodo
//Hacemos esto para tener como referencia un inicio
Nodo*inicio=NULL;
Lista*ini=NULL;
Lista*final=NULL;



class Servidor{
public:
    //variables
    WSADATA WSAData;//declaracion objeto WSADATA
    SOCKET Server, cliente; //sockets a utilizar
    SOCKADDR_IN serverAddr, clientAddr; //objeto que tiene info del socket como una dir IP o num del puerto
    char buffer[1024];// almacena los datos ingresados


    Servidor()
    {   //Funcion que le dice a la pc que usaremos sockets,esp. ver. de winsoc2.h y dir del objeto WSADATA creado
        WSAStartup(MAKEWORD(2,0), &WSAData);
        //Inicializamos el socket servidor
        //1 parametro: especifica la familia de direcciones. ya sea (AF_INET para protocolo ipv4) o (AF_INET6 para el ipv6)
        //2: especificacion de tipo. sock_stream abre una conexion entre dos pc distantes para que se cmuniquen
        //3: en 0, no se usara mucho, es el parametro de protocolo, que depende de la familia de direcciones y el tipo de socket usado antes
        Server = socket(AF_INET, SOCK_STREAM, 0);

//Una vez declarado el socket, se le indica a qué dirección IP debe conectarse y qué puerto debe usar:


        //No hay una dirección IP, porque es el servidor, y será accesible automáticamente desde la IP de la computadora que lo está ejecutando.
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        //especifica de nuevo la familia de direcciones
        serverAddr.sin_family = AF_INET;
        //establece el puerto en el que se debe conectar el socket (5555)
        serverAddr.sin_port = htons(5555);

//Luego se vincula el socket con la dirección IP y el número de puerto.
//En cierto modo, es como la función connect () (los parámetros son los mismos) pero para el lado del servidor
        bind(Server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
        //Función que comienza a escuchar para permitir que los clientes se conecten. El primer parámetro es el servidor de socket, el segundo se deja en 0.
        listen(Server, 0);
        cout << "Buscando conexiones entrantes..." << endl;
        //variable para almacenar el tamaño de la dir del cliente
        int clientAddrSize = sizeof(clientAddr);
        //La función de aceptación permite un intento de conexión entrante en un socket.
        if((cliente = accept(Server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            cout << "Cliente conectado!"<<endl;
        }
    }

    //Funcion para Recibir mensajes del cliente
    string Recibir()
    {
    //Funcion que recibe el mensaje del servidor tiene como parametros:
    //El socket del servidor, Los datos (buffer), El tamaño de los datos, conjunto de banderas que se puede dejar en 0
      recv(cliente, buffer, sizeof(buffer), 0);
      cout << "El cliente dice: " << buffer << endl;

      //Funcion que resetea el buffer a 0
      memset(buffer, 0, sizeof(buffer));
      //funcion para limpiar el buffer
        fflush(stdin);

    }


    //Funcion para Recibir mensajes del cliente
    string Recibir2()
    {

    //Funcion que recibe el mensaje del servidor tiene como parametros:
    //El socket del servidor, Los datos (buffer), El tamaño de los datos, conjunto de banderas que se puede dejar en 0
      recv(cliente, buffer, sizeof(buffer), 0);

      //for(int i=1;i<5;i++){
             //cout << "OCNYTADOR: " << ;
             cout << "El cliente dice: " <<*buffer;
    	insertarNodo(1);
    	insertarNodo(2);
    	insertarNodo(3);
    	insertarNodo(4);
	//}

	//for(int i=1;i<9;i++){
    	insertarArista(1,2,7);
    	insertarArista(1,4,2);
    	insertarArista(2,4,2);
    	insertarArista(4,3,8);
    	insertarArista(3,1,7);


	 cout << "El cliente dice SIRVIO: ";
	visualizarGrafo();
	//Enviar()//lo que muestra el visualizar



      //Funcion que resetea el buffer a 0
      memset(buffer, 0, sizeof(buffer));
      //funcion para limpiar el buffer
        fflush(stdin);


    }


    void grafo()
{

        insertarNodo(1);
    	insertarNodo(2);
    	insertarNodo(3);
    	insertarNodo(4);

    	insertarArista(1,2,7);
    	insertarArista(1,4,2);
    	insertarArista(2,4,2);
    	insertarArista(4,3,8);
    	insertarArista(3,1,7);

cout << "El Grafo creado es: "<<endl;

	visualizarGrafo();



}



    //Funcion para enviar mensajes al cliente
    void Enviar()
    {
        cout<<"Escribe el mensaje a enviar: ";
        cin>>this->buffer;
        //Funcion que envia el mensaje al servidor tiene como parametros:
        //El socket del servidor, Los datos (buffer), El tamaño de los datos, conjunto de banderas que se puede dejar en 0
        send(cliente, buffer, sizeof(buffer), 0);
        //funcion para limpiar el buffer
        memset(buffer, 0, sizeof(buffer));
        //funcion para limpiar el buffer
        fflush(stdin);
        cout << "Mensaje enviado!" << endl;
    }


    //Funcion para cerrar el socket
    void CerrarSocket()
    {
      //Funcion que desconecta el socket del cliente
        closesocket(cliente);
        cout << "Socket cerrado, cliente desconectado." << endl;
    }

//----------------------------------------GRAFO--------------------------------------------------
    void insertarNodo(char verti){

    Nodo* aux;//nodo apuntador auxiliar
	Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));//nodo a insertar y reservamos su espacio en memoria
	fflush(stdin);
	//printf("Ingrese vertice:");
	//scanf("%c",&nuevo->dato);//le asignamos el dato al vertice
	nuevo->dato=verti;

	//inicializamos los datos del nodo
	nuevo->siguiente=NULL;
    nuevo->adyacencia=NULL;
    nuevo->visitado=nuevo->terminado=0;
    nuevo->monto=-1;
    nuevo->anterior=0;
    //vemos si la lista de veertices esta vacia
    if(inicio==NULL){
            //si es verdad inicio sera igual al nuevo nodo
        inicio=nuevo;
    }else{
        //si hay mas de un nodo, usamos el auxiliar
        aux=inicio;
    //recorremos el auxiliar hasta llegar al ultimo nodo
        while(aux->siguiente!=NULL){
            aux=aux->siguiente;
        }
        //le signamos el nuevo dato al ultimo nodo
        aux->siguiente=nuevo;
      }

 }

 //funcion para insertar las aristas
void insertarArista(char ini,char fin, int peso){
    //variables para vertices a entrelazar

   // char ini, fin;
    Arista* nuevo=(Arista*)malloc(sizeof(Arista));//inicializacion de una nueva arista y rserva de su campo para alamacenarla en memoria
    //inicializar datos de la arista
    nuevo->siguiente=NULL;
    //inicializar nodos auxiliares
    Nodo* aux;
	Nodo* aux2;
	//verificamos que la lista de nodos no este vacia
    if(inicio==NULL){
         printf("Error: El grafo está vacio\n");
         return;
    }
    fflush(stdin);
    //printf("Ingresar Nodo Inicial y Final:");
    //scanf("%c %c",&ini,&fin);


    //&ini=ini2;
    //&fin=fin2;
    //printf("Ingresar Peso de la arista:");
    //scanf("%i",&nuevo->peso);
    nuevo->peso=peso;
    //igualamos los auxiliares a inicio para encontrar los 2 vertices que el usuario digito, en la lista
    aux=inicio;
    aux2=inicio;
    //buscamos el vertice final
    while(aux2!=NULL){
        if(aux2->dato==fin){
            break;
        }
        aux2=aux2->siguiente;
    }
    //si no lo encotramos
    if(aux2==NULL){
    	printf("Error:Vertice no encontrado\n");
    	return;
	}
	//buscamos el vertice inicial
    while(aux!=NULL){
            //si el dato en aux es igual al vertice ingresado, se ejecuta la funcion agregr arista
        if(aux->dato==ini){
            //le pasamos a la funcion agregar arista el vertice inicial, final y la nueva arista
            agregarArista(aux,aux2,nuevo);
            return;
        }
        aux = aux->siguiente;
    }
    if(aux==NULL)
    	printf("Error:Vertice no encontrado\n");
}

//Funcion para agrgar la arista entre los 2 nodos
//le pasamos como parametros el nodo inicial, el nodo final, y la arista a insertar
void agregarArista(Nodo* aux,Nodo* aux2,Arista* nuevo){
    Arista* a;
    //si la lista de ayacencia del nodo inical es nula  es porque es el primer nodo
    if(aux->adyacencia==NULL){
	    aux->adyacencia=nuevo;//entoces se agrega la nueva arista a lista de ayacencia
        nuevo->vrt=aux2;//la arista en su parte del vertice apunta al nodo final en este caso aux 2
    }else{ //en el caso que no este vacia la lista de ayacencia

        //recorremos a que es el auxiliar
	    a=aux->adyacencia;
        while(a->siguiente!=NULL)
            a=a->siguiente;
        nuevo->vrt=aux2;//la arista en su parte del vertice apunta al nodo final en este caso aux 2
        a->siguiente=nuevo;
    }
}

//Funcion para mostrar el grafo creado
void visualizarGrafo(){
    Nodo*aux=inicio;
    Arista* ar;
    printf("Nodos\n");
    while(aux!=NULL){
	    printf("%c:    ",aux->dato);
        if(aux->adyacencia!=NULL){
            ar=aux->adyacencia;
            while(ar!=NULL){
			    printf(" %c",ar->vrt->dato);
                ar=ar->siguiente;
            }
        }
        printf("\n");
        aux=aux->siguiente;
    }
    printf("\n");
}



};



int main()
{
  Servidor *servidor = new Servidor();

  servidor->grafo();
  while(true)
  {
      servidor->Recibir();
      servidor->Enviar();
  }
  }
