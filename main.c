#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

///ESTRUCTURA CONSOLA
typedef struct
{
    int codigoProducto;
    char marca[50]; // Nintendo Switch, Xbox, Playstation
    float precioEnMiles;
    int stock;
    char modelo[50];// Común, Pro, Slim
} stConsola ;

///NODO CONSOLA
typedef struct nodoConsola
{
    stConsola dato ;
    struct nodoConsola * siguiente;
} nodoConsola;



//PROTOTIPADO
nodoConsola* inicLista();
nodoConsola* cargarNodo(stConsola consola);
stConsola cargaConsola();
void mostrarNODO (nodoConsola* nodo);
void ordenaListaStock(nodoConsola* lista, nodoConsola* nuevoNodo);

//MAIN
int main()
{
    stConsola consola;
    nodoConsola* nodo;
    nodoConsola* lista;


    consola=cargaConsola();

    //PUNTO 1

    nodo=cargarNodo(consola);


    lista = inicLista();






    return 0;
}

nodoConsola* inicLista()
{
    return NULL;
}

nodoConsola* cargarNodo(stConsola consola)
{
    nodoConsola* aux = (nodoConsola*)malloc (sizeof(nodoConsola));
    aux->dato = consola;
    aux->siguiente = NULL;
    return aux;
}


stConsola cargaConsola() //FUNCION BASICA DE CARGA DE CONSOLA
{
    stConsola aux;

    printf("INGRESE NOMBRE DE CONSOLA: (Nintendo Switch, Xbox, Playsyation...\n");
    fflush(stdin);
    gets(aux.marca);
    printf("INGRESE MODELO DE CONSOLA: (Comun, Pro, Slim\n");
    fflush(stdin);
    gets(aux.modelo);
    printf("INGRESE CODIGO DE PRODUCTO\n");
    fflush(stdin);
    scanf("%i",&aux.codigoProducto);
    printf("INGRESE PRECIO EN MILES\n");
    fflush(stdin);
    scanf("%f",&aux.precioEnMiles);
    printf("INGRESE STOCK DE PRODUCTO\n");
    fflush(stdin);
    scanf("%i", &aux.stock);

    return aux;
}

void mostrarNODO (nodoConsola* nodo)
{
    printf("\n\n-----NODO-----\n");

    printf("NOMBRE: %s \n", nodo->dato.marca);
    printf("MODELO: %s \n", nodo->dato.modelo);
    printf("CODIGO: %i \n", nodo->dato.codigoProducto);
    printf("PRECIO: %.2f \n", nodo->dato.precioEnMiles);
    printf("STOCK: %i \n", nodo->dato.stock);

}

void mostrarLista(nodoConsola* lista)
{
    nodoConsola* aux = lista;
    while (aux!=NULL)
    {
        mostrarNODO(aux);
        aux=aux->siguiente;
    }
}


void ordenaListaStock(nodoConsola* lista, nodoConsola* nuevoNodo)
{

    nodoConsola* aux=lista;
    nodoConsola* seg = lista->siguiente;
    int flag=0;


    if (lista!= NULL)
    {
        while(aux->siguiente !=NULL && flag == 0)
        {
            if (nuevoNodo->dato.stock < aux->dato.stock)
            {

                nuevoNodo->siguiente = aux;
                lista = nuevoNodo;
                flag = 1;

            }
            else
            {
                aux = aux->siguiente;
            }
        }
    }
    else{
        lista = nuevoNodo;
    }

    if (flag == 0)
    {
        aux->siguiente = nuevoNodo;
    }

}


