#include <iostream>
#include <winsock2.h>

using namespace std;

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
        cout << "Buscando conexiones entrantes." << endl;
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


};

int main()
{
  Servidor *servidor = new Servidor();
  while(true)
  {
      servidor->Recibir();
      servidor->Enviar();
  }
  }
