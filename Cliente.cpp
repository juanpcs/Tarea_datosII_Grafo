#include <iostream>
#include <winsock2.h>

using namespace std;

class Cliente{
public:

WSADATA WSAData;//declaracion objeto WSADATA
SOCKET servidor; //socket a utilizar
SOCKADDR_IN addr; //objeto que tiene info del socket como una dir IP o num del puerto
char buffer[1024]; // almacena los datos ingresados

 Cliente()
    {
        cout<<"Intentando conectar con el servidor..."<<endl<<endl;
        //Funcion que le dice a la pc que usaremos sockets,esp. ver. de winsoc2.h y dir del objeto WSADATA creado
        WSAStartup(MAKEWORD(2,0), &WSAData);
        //Inicializamos el socket servidor
        servidor = socket(AF_INET, SOCK_STREAM, 0);
        //1 parametro: especifica la familia de direcciones. ya sea (AF_INET para protocolo ipv4) o (AF_INET6 para el ipv6)
        //2: especificacion de tipo. sock_stream abre una conexion entre dos pc distantes para que se cmuniquen
        //3: en 0, no se usara mucho, es el parametro de protocolo, que depende de la familia de direcciones y el tipo de socket usado antes

//Una vez declarado el socket, se le indica a qué dirección IP debe conectarse y qué puerto debe usar:

        //especifica dir ip del server
        addr.sin_addr.s_addr = inet_addr("192.168.100.1");
        //especifica de nuevo la familia de direcciones
        addr.sin_family = AF_INET;
        //establece el puerto en el que se debe conectar el socket (5555).
        addr.sin_port = htons(5555);

        //Funcion para conectarse al servidor, la función connect () toma tres parámetros
        //El socket del servidor
        //La información de la dirección del socket
        //El tamaño del segundo parámetro.
        connect(servidor, (SOCKADDR *)&addr, sizeof(addr));

        cout << "Se ha realizado la conexion al Servidor exitosamente!" << endl;
    }


    //Funcion para enviar mensajes al cliente
    void Enviar()
    {
        cout<<"Escribe el mensaje a enviar: ";
        cin>>this->buffer;
        //Funcion que envia el mensaje al servidor tiene como parametros:
        //El socket del servidor, Los datos (buffer), El tamaño de los datos, conjunto de banderas que se puede dejar en 0
        send(server, buffer, sizeof(buffer), 0);
        //funcion para limpiar el buffer
        memset(buffer, 0, sizeof(buffer));
        //funcion para limpiar el buffer
        fflush(stdin);
        cout << "Mensaje enviado!" << endl;
    }

};
