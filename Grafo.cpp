//Inicializacion librerias
#include <stdio.h>
#include <stdlib.h>
//defininedo estructuras a utilizr
#define Nodo struct nodo
#define Arista struct arista
#define Lista struct pila

//Inicializacion de la estructura de los nodos
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

void insertarNodo();
void agregarArista(Nodo*aux,Nodo*aux2,Arista*nuevo);
void insertarArista();
void visualizarGrafo();

int main(){
    int opcion,N,i;
	printf("Ingrese número de vertices:");
    scanf("%i",&N);
    for(i=0;i<N;i++){
    	insertarNodo();
	}
	system("cls");//borramos lo que hay en pantalla
    do{
    	printf("-----------\n");
        printf(" 1. Insertar Vertice                 \n");
        printf(" 2. Insertar Arista                  \n");
        printf(" 3. Mostrar Listas                   \n");
        printf(" 4. Recorrer Grafo x                  \n");
        printf(" 5. Dijkstra       x                 \n");
        printf(" 6. Salir                            \n");
        printf("------------\n");
        printf("Escoge opcion:");
        scanf("%i",&opcion);
        switch(opcion){
            case 1:
                    insertarNodo();
                    break;
            case 2: insertarArista();
                    break;
            case 3: visualizarGrafo();
                    break;
            case 4: //recorridos();
                    break;
            case 5: //dijkstra();
			        break;
			case 6: break;
            default: printf("Opcion no valida...!!!\n");
                     break;
        }
        system("pause");//hacemos una pausa
        system("cls"); //borramos lo que hay en pantalla
    }while(opcion!=6);
    return 1;
}

//Funcion para insertar los nodos, no tiene parametros
void insertarNodo(){

    Nodo* aux;//nodo apuntador auxiliar
	Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));//nodo a insertar y reservamos su espacio en memoria
	fflush(stdin);
	printf("Ingrese vertice:");
	scanf("%c",&nuevo->dato);//le asignamos el dato al vertice
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
void insertarArista(){
    //variables para vertices a entrelazar
    char ini, fin;
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
    printf("Ingresar Nodo Inicial y Final:");
    scanf("%c %c",&ini,&fin);
    printf("Ingresar Peso de la arista:");
    scanf("%i",&nuevo->peso);
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
