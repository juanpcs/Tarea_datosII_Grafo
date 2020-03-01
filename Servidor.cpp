#include <iostream>
#include <winsock2.h>

using namespace std;

class Servidor{
public:
    //variables
    WSADATA WSAData;//declaracion objeto WSADATA
    SOCKET Servidor, cliente; //sockets a utilizar
    SOCKADDR_IN serverAddr, clientAddr; //objeto que tiene info del socket como una dir IP o num del puerto
    char buffer[1024];// almacena los datos ingresados

    Servidor()
    {   //Funcion que le dice a la pc que usaremos sockets,esp. ver. de winsoc2.h y dir del objeto WSADATA creado
        WSAStartup(MAKEWORD(2,0), &WSAData);
        //Inicializamos el socket servidor
        //1 parametro: especifica la familia de direcciones. ya sea (AF_INET para protocolo ipv4) o (AF_INET6 para el ipv6)
        //2: especificacion de tipo. sock_stream abre una conexion entre dos pc distantes para que se cmuniquen
        //3: en 0, no se usara mucho, es el parametro de protocolo, que depende de la familia de direcciones y el tipo de socket usado antes
        Servidor = socket(AF_INET, SOCK_STREAM, 0);

//Una vez declarado el socket, se le indica a qué dirección IP debe conectarse y qué puerto debe usar:


        //No hay una dirección IP, porque es el servidor, y será accesible automáticamente desde la IP de la computadora que lo está ejecutando.
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        //especifica de nuevo la familia de direcciones
        serverAddr.sin_family = AF_INET;
        //establece el puerto en el que se debe conectar el socket (5555)
        serverAddr.sin_port = htons(5555);

//Luego se vincula el socket con la dirección IP y el número de puerto.
//En cierto modo, es como la función connect () (los parámetros son los mismos) pero para el lado del servidor
        bind(Servidor, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
        //Función que comienza a escuchar para permitir que los clientes se conecten. El primer parámetro es el servidor de socket, el segundo se deja en 0.
        listen(server, 0);
        cout << "Escuchando para conexiones entrantes." << endl;
        //variable para almacenar el tamaño de la dir del cliente
        int clientAddrSize = sizeof(clientAddr);
        //La función de aceptación permite un intento de conexión entrante en un socket.
        if((cliente = accept(Servidor, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            cout << "Cliente conectado!" << endl;
        }
    }




};
