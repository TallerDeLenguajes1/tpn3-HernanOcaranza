#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ************************************ declaracion de estructuras *******************************

typedef struct Producto {
    int ProductoID; //Numerado en ciclo iterativo
    int Cantidad; // entre 1 y 10
    char *TipoProducto; // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
}Producto;

typedef struct Cliente {
    int ClienteID; // Numerado en el ciclo iterativo
    char *NombreCliente; // Ingresado por usuario
    int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
    Producto *Productos; //El tamaño de este arreglo depende de la variable “CantidadProductosAPedir”
                        
}Cliente;

// ************************************ declaracion de funciones *******************************

Cliente CargarCliente (int id);

void CargarProducto (Producto *nuevoProducto, int id);

void CargarNProductos (Producto *productos,int cant);

void CargarNClientes (Cliente *clientes, int cant);

float CalcularCostoTotalProducto (Producto produc);

void MostrarProducto (Producto produc);

void MostrarCliente (Cliente clien);

void MostrarNProductos (Producto *produc, int cant);

void MostrarNClientes (Cliente *clientes, int cant);

float TotalAPagarPorCliente (Producto *productos, int cant);

void LiberarMemoria (Cliente *clientes, int cant);

// ************************************ funcion principal *******************************

int main () {
    srand(time(0));
    int cantClientes;
    printf("Ingrese la cantidad de clientes: ");
    scanf("%d", &cantClientes);
    fflush(stdin);
    Cliente *clientes = (Cliente *) malloc(sizeof(Cliente) * cantClientes);
    CargarNClientes(clientes, cantClientes);
    MostrarNClientes(clientes, cantClientes);
    LiberarMemoria(clientes, cantClientes);
    
    getchar();
    return 0;
}


// ************************************ desarrollo de funciones *******************************

Cliente CargarCliente (int id) {
    Cliente nuevoCliente;
    nuevoCliente.ClienteID = id;
    nuevoCliente.NombreCliente = (char *) malloc(sizeof(char) * 50);
    printf("\nIngrese el nombre del cliente: ");
    gets(nuevoCliente.NombreCliente);
    nuevoCliente.CantidadProductosAPedir = rand() % 5 + 1;
    nuevoCliente.Productos = (Producto *) malloc(sizeof(Producto) * nuevoCliente.CantidadProductosAPedir);
    CargarNProductos(nuevoCliente.Productos, nuevoCliente.CantidadProductosAPedir);
    return nuevoCliente;
}

void CargarProducto (Producto *nuevoProducto, int id) {
    char TiposProductos[5][12]={"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

    nuevoProducto->ProductoID = id;
    nuevoProducto->Cantidad = rand() % 10 + 1;
    nuevoProducto->TipoProducto = (char *) malloc(sizeof(char) * 12);
    strcpy(nuevoProducto->TipoProducto, TiposProductos[rand() % 5]);
    nuevoProducto->PrecioUnitario = rand() % 91 + 10;
}

void CargarNProductos (Producto *productos,int cant) {
    for(int ind = 0; ind < cant; ind++) {
        CargarProducto(&productos[ind], ind);
    }
}

void CargarNClientes (Cliente *clientes, int cant) {

    for (int ind = 0; ind < cant; ind++) {
        clientes[ind] = CargarCliente(ind);
    }
}

float CalcularCostoTotalProducto (Producto produc) {
    return produc.Cantidad * produc.PrecioUnitario;
}

void MostrarProducto (Producto produc) {
    printf("\nId: %d", produc.ProductoID);
    printf("\nTipo: %s", produc.TipoProducto);
    printf("\nPrecio: $%.2f", produc.PrecioUnitario);
    printf("\nCantidad: %d", produc.Cantidad);
    printf("\nCosto Total: $%.2f", CalcularCostoTotalProducto(produc));
}

void MostrarCliente (Cliente clien) {
    printf("\nCliente: %d", clien.ClienteID);
    printf("\nNombre: %s", clien.NombreCliente);
    printf("\nCantidad de productos a pedir: %d", clien.CantidadProductosAPedir);
    MostrarNProductos(clien.Productos, clien.CantidadProductosAPedir);
    printf("\n\nTotal a pagar por cliente: $%.2f", TotalAPagarPorCliente(clien.Productos, clien.CantidadProductosAPedir));
}

void MostrarNProductos (Producto *produc, int cant) {
    for(int ind = 0; ind < cant; ind++) {
        printf("\n");
        MostrarProducto(produc[ind]);
    }
}

float TotalAPagarPorCliente (Producto *productos, int cant) {
    float acumulador = 0;
    for(int ind = 0; ind < cant; ind++) {
        acumulador += CalcularCostoTotalProducto(productos[ind]);
    }
    return acumulador;
}

void MostrarNClientes (Cliente *clientes, int cant) {
    for(int ind = 0; ind < cant; ind++) {
        printf("\n\n");
        MostrarCliente(clientes[ind]);
    }
}

void LiberarMemoria (Cliente *clientes, int cant) {
    for(int ind = 0; ind < cant; ind++) {
        for(int j = 0; j < clientes->CantidadProductosAPedir; j++) {
            free(clientes[ind].Productos[j].TipoProducto);
        }
        free(clientes[ind].NombreCliente);
        free(clientes[ind].Productos);
    }
    free(clientes);
}