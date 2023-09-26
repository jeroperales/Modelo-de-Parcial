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

///ESTRUCTURA CLIENTE
typedef struct
{

    char nombre[50];
    int mediodepago; //1 efectivo, 2 patacones, 3 dolar     ahorro
    float totalCompra;
} stCliente ;

///NODO CLIENTE
typedef struct nodoCliente
{
    stCliente dato;
    struct nodoCliente* siguiente;
    struct nodoCliente* anterior;
} nodoCliente;



//PROTOTIPADO
nodoConsola* inicLista();
nodoConsola* cargarNodo(stConsola consola);
stConsola cargaConsola(stConsola aux);
void mostrarNODO (nodoConsola* nodo);
void mostrarLista(nodoConsola* lista);
nodoConsola* ordenaListaStock(nodoConsola* lista, nodoConsola* nuevoNodo);
nodoConsola* agregarPrincipio(nodoConsola* lista, nodoConsola* nuevoNodo);
void muestraPrecio(float precioBuscar, nodoConsola* lista);
int confirmaStock(nodoConsola* lista, char marca[], char modelo[], int stock);
nodoConsola*CargarArchivo(char archivo[],nodoConsola*lista);
nodoConsola*archiALista(char archivo[], nodoConsola* lista);
stCliente datosCliente(stCliente aux);

//MAIN
int main()
{
    int stock;
    int flag;
    int intopc;
    int loop = 1;
    int resta;
    float precioBuscar;
    char marca[20];
    char modelo[20];
    char opc = 's';
    stConsola consola;
    nodoConsola* nodo;
    nodoConsola* lista;
    stConsola a;
    stCliente cliente;
    lista = inicLista();
    char nombre[] = {"miArchivito.bin"};
    lista = archiALista(nombre, lista);


    //MENU
    while (loop == 1)
    {
        printf("\n\n");
        printf("================MENU================\n");
        printf(" 1- Cargar lista de forma ordenada \n");
        printf(" 2- Buscar y ordenar por PRECIO una lista dada (RECURSIVO)\n");
        printf(" 3- Confirmar cantidad de stock\n");
        printf(" 4- Restar cantidad de stock deseado\n");
        printf("====================================");
        fflush(stdin);
        printf("\nIngrese una opcion: \n");
        scanf("%i", &intopc);

        switch(intopc)
        {
        case 1:
            //PUNTO 1 y 2
            lista = CargarArchivo("miArchivito.bin", lista);
            system ("cls");
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

        case 4: /*Hacer una función dado el nombre de un cliente y su medio de pago, compre varios productos. Revise el stock antes de comprar y luego reste la cantidad comprada.
         Estos clientes se añadirán al FINAL de la lista doble. Guardar el total de la compra en su estructura.*/
           cliente = datosCliente(cliente);
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
                resta = restaStock(lista, marca, modelo, stock);

            }
            else
            {
                printf("NO TENES SUFICIENTE STOCK\n");
            }


            break;



        default:
            system ("cls");
            printf("INGRESE UNA OPCION VALIDA \n");
            break;
        }
    }
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
    aux->siguiente=NULL;


    return aux;
}


stConsola cargaConsola(stConsola aux) //FUNCION BASICA DE CARGA DE CONSOLA
{

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

nodoConsola*CargarArchivo(char archivo[],nodoConsola*lista)
{
    FILE*archi;
    nodoConsola*aux;
    char letra='s';
    stConsola a;
    archi=fopen(archivo,"ab");
    if(archi!=NULL)
    {
        while(letra=='s')
        {
            a=cargaConsola(a);
            aux=cargarNodo(a);
            lista = ordenaListaStock(lista, aux);
            fwrite(&a,sizeof(stConsola),1,archi);
            printf("Ingrese s si desea continuar: \n");
            fflush(stdin);
            scanf("%c",&letra);
        }
    }
    fclose(archi);
    return lista;
}

nodoConsola*archiALista(char archivo[], nodoConsola* lista)
{
    FILE*archi;
    nodoConsola*aux;
    stConsola a;
    archi=fopen(archivo,"rb");
    if(archi!=NULL)
    {
        while(fread(&a,sizeof(stConsola),1,archi)==1)
        {
            aux=cargarNodo(a);
            lista = ordenaListaStock(lista, aux);
        }
        fclose(archi);
    }


    return lista;
}
void mostrarNODO (nodoConsola* nodo)
{
    printf("\n-----NODO-----\n");

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


stCliente datosCliente(stCliente aux) //FUNCION QUE CARGA UN NOMBRE Y UN MEDIO DE PAGO
{

    printf("INGRESE NOMBRE DE UN CLIENTE\n");
    fflush(stdin);
    gets(aux.nombre);
    printf("INGRESE MEDIO DE PAGO\n");
    scanf("%i", &aux.mediodepago);
    return aux;

}

int restaStock(nodoConsola* lista, char marca[], char modelo[], int stock)
{
    int resta;
    nodoConsola* aux = lista;
    while (strcmp(marca,aux->dato.marca) != 0)
    {
        aux = aux->siguiente;

    }
    resta = aux->dato.stock - stock;
    aux->dato.stock = resta;

    printf("VALOR DE STOCK NUEVO\n");
    mostrarNODO(aux);

    return resta;
}


