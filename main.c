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
void mostrarLista(nodoConsola* lista);
nodoConsola* ordenaListaStock(nodoConsola* lista, nodoConsola* nuevoNodo);
nodoConsola* agregarPrincipio(nodoConsola* lista, nodoConsola* nuevoNodo);
void muestraPrecio(float precioBuscar, nodoConsola* lista);
int confirmaStock(nodoConsola* lista, char marca[], char modelo[], int stock);

//MAIN
int main()
{
    int stock;
    int flag;
    int intopc;
    float precioBuscar;
    char marca[20];
    char modelo[20];
    char opc = 's';
    stConsola consola;
    nodoConsola* nodo;
    nodoConsola* lista;
    lista = inicLista();

    //MENU

    printf("================MENU================\n");
    printf(" 1- Cargar lista de forma ordenada \n");
    printf(" 2- Buscar y ordenar por PRECIO una lista dada (RECURSIVO)\n");
    printf(" 3- Confirmar cantidad de stock\n");
    printf("====================================");
    fflush(stdin);
    printf("\nIngrese una opcion: \n");
    scanf("%i", &intopc);


    switch(intopc)
    {
    case 1:
        //PUNTO 1 y 2
        while (opc == 's')
        {
            consola=cargaConsola();
            nodo=cargarNodo(consola);
            lista = ordenaListaStock(lista, nodo);

            printf("\nSI DESEA INGRESAR OTRA CONSOLA, INGRESE s\n");
            fflush(stdin);
            scanf("%c", &opc);
        }
        printf("LISTA ORDENADA POR STOCK: \n");
        mostrarLista(lista);
        break;

    case 2:
        printf("\nPRECIO A BUSCAR: ");
        fflush(stdin);
        scanf("%f", &precioBuscar);
        muestraPrecio(precioBuscar, lista);
        break;

    case 3:
        printf("\n QUE MARCA ESTAS BUSCANDO?\n");
        fflush(stdin);
        gets(marca);
        printf("\n QUE MODELO ESTAS BUSCANDO?\n");
        fflush(stdin);
        gets(modelo);
        printf("\n CANTIDAD DE STOCK A BUSCAR?\n");
        fflush(stdin);
        scanf("%i", &stock);

        flag = confirmaStock(lista, marca, modelo, stock);

        if (flag == 1)
        {
            printf("TIENE SUFICIENTE STOCK \n");
        }
        else
        {

            printf("NO TENES SUFICIENTE STOCK\n");
        }
        break;

        return 0;
    }
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



nodoConsola* ordenaListaStock(nodoConsola* lista, nodoConsola* nuevoNodo)
{
    nodoConsola* aux;
    nodoConsola* aux2;


    if(lista != NULL)
    {
        if(nuevoNodo->dato.stock < lista->dato.stock )
        {
            lista = agregarPrincipio(lista, nuevoNodo);
        }
        else
        {
            aux = lista;
            aux2 = lista->siguiente;

            while((aux2 != NULL)&&(nuevoNodo->dato.stock > aux2->dato.stock))
            {
                aux = aux2;
                aux2 = aux2->siguiente;
            }

            nuevoNodo->siguiente = aux2;
            aux->siguiente = nuevoNodo;
        }
    }
    else
    {
        lista = nuevoNodo;
    }

    return lista;
}

nodoConsola* agregarPrincipio(nodoConsola* lista, nodoConsola* nuevoNodo)
{
    if (lista!=NULL)
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    else
    {
        lista = nuevoNodo;
    }
    return lista;
}

void muestraPrecio(float precioBuscar, nodoConsola* lista)
{
    nodoConsola* aux = lista;

    if (lista)
    {
        if(lista->dato.precioEnMiles == precioBuscar)
        {
            mostrarNODO(lista);
        }
        muestraPrecio(precioBuscar, aux->siguiente);

    }
    else
    {
        printf("\n===================\n");
        printf("LA LISTA ESTA VACIA\n");
        printf("===================\n");
        exit (0);
    }
}



int confirmaStock (nodoConsola* lista, char marca[], char modelo[], int stock)
{
    int flag = 0;
    nodoConsola* aux = lista;

    if(lista)
    {
        while(aux!= NULL && flag ==0)
        {
            if(strcmp(aux->dato.marca,marca)==0 && strcmp(aux->dato.modelo,modelo)==0)
            {
                if(aux->dato.stock>=stock)
                {
                    flag = 1;
                }

            }
            aux=aux->siguiente;

        }
    }
    else
    {
        printf("\n===================\n");
        printf("LA LISTA ESTA VACIA\n");
        printf("===================\n");
        exit (0);
    }

    return flag;
}
