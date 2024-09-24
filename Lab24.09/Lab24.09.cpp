// PAULA SIERRA LUQUE


#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "Date.h"

using namespace std;

struct Ejemplar {
    int codigo;
    char tipo;
    string nombre;
};

struct Prestamo {
    int codigo;
    Date fecha;
    int usuario;
};

struct Catalogo {
    Ejemplar* ejemplar;
    int tam;
    int cont;
};

struct ListaPrestamos {
    Prestamo* prestamo;
    int tam;
    int cont;
};


// devuelve true (1) si ha podido cargar el fichero, false si no
bool leerCatalogo(Catalogo& c) { // tiene q ser &
    ifstream entrada;
    entrada.open("catalogo.txt");

    if (!entrada.is_open()) return false;

    // lee primer numero y lo guarda en tam
    int tam;
    entrada >> tam;
    //c->tam = tam;

    Ejemplar* ejemplares = new Ejemplar();

    // recorro hasta tam
    for (int i = 0; i < tam; i++) {
        int cod;
        entrada >> cod;
        //c[i].ejemplar->codigo = cod;
    }

    
    entrada.close();

    return true;
}

// devuelve true (1) si ha podido cargar el fichero, false si no
// 
bool leerPrestamos() {
    ifstream catalogo("prestamos.txt");
    return catalogo.is_open();
}

int main()
{
    Catalogo* catalogo = new Catalogo();

    //leerCatalogo(catalogo);

    cout << catalogo->tam << endl;
    //cout << catalogo[0]->ejemplar->nombre << endl;
    



    // borrar la memoria dinamica creada
    delete catalogo;
}

