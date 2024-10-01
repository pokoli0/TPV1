// María Solórzano y Paula Sierra Grupo5
//

#include <fstream>
#include <windows.h>
#include "Date.h"
#include<string>
#include <stdlib.h> //creo que hace falta para usar new

using namespace std;

//BUENAS TARDES PROFE mira te comento
//nos dan error algunas cosas por motivos misteriosos y tmbn nos da error de LNK1104
//todos estos errores nos han empezado a dar literalmente ayer
//la función getline tmbn nos da error a veces (literalmente intermitentemente)


struct Coche {
    int codigo;
    int precio;
    string nombre;
};

struct Alquiler {
    Coche* coche;
    Date fecha;
    int dias;

   // bool operator<(const Alquiler& izdo, const Alquiler& dcho) {
   //     return (izdo.fecha < dcho.fecha);
   // } para q funcione el sort tenemos q meter este código q nos ha dado el profe.
    //como el sort no funciona, pues esto tampoco. prueba a descomentarlo a ver si te funciona a tí.
};

struct ListaCoches {
    Coche* listacoches;
    int size;
    int cont;
};

struct ListaAlquileres {
    Alquiler* listaAlquileres;
    int size;
    int cont;
};


bool leerModelos(ListaCoches listaCoches)
{
    ifstream entrada("coches.txt");
    
    if (!entrada.is_open())
        return false;

    
    entrada >> listaCoches.cont; //primera entrada: contador
    listaCoches.size = listaCoches.cont + 10;
    listaCoches.listacoches = new Coche[listaCoches.size];
    //string aux;

    
    for (int i = 0; i < listaCoches.cont; i++) //rellenamos la lista
    {
        entrada >> listaCoches.listacoches[i].codigo; //segunda entrada: codigo
        entrada >> listaCoches.listacoches[i].precio; //tercera entrada: precio
        
        /*entrada >> listaCoches.listacoches[i].nombre;
        entrada >> aux;
        listaCoches.listacoches[i].nombre += " "+aux;*/

        getline(entrada, listaCoches.listacoches[i].nombre); //por motivos misteriosos da error
    }
}

int buscarCoche(ListaCoches lista, int cod)
{
    /*dada la lista de coches y un código, devuelve la posición (índice) del elemento de la
    lista de coches con ese código; si no se encuentra el código devuelve ‐1. Debe implementarse como
    búsqueda binaria.*/
    int ind = -1, i = 0; bool encontrado = false;
    while (i < lista.size && !encontrado) {
        if (lista.listacoches[i].codigo == cod) { //esto probablemente se pueda escribir mas corto 
            encontrado = true;
            ind = i; // creo q quiere el indice del elemento. El puntero lo asingo fuera. 
            // si quisiera posicion de memoria para asignar el puntero directamente, tendríamos que devolover un puntero.
        }
        i++;
    }
    return ind;
}

bool leerAlquileres(ListaCoches listacoches, ListaAlquileres listaAlquileres)
{
    ifstream entrada("rent.txt");
    if (!entrada.is_open())
        return false;

    /*Cada alquiler debe incluir un campo de tipo
    Coche* con el puntero al coche al que hace referencia el alquiler (que será nullptr en caso de no
    encontrarse el código en la lista de coches). Llamar aqui a buscarCoche(lista,codigo).
    */

    
    int codCoche, indCoche; //variables auxiliares
    entrada >> listaAlquileres.cont;
    listaAlquileres.size = listaAlquileres.cont + 10;
    listaAlquileres.listaAlquileres = new Alquiler[listaAlquileres.size];
    for (int i = 0; i < listaAlquileres.cont; i++) //rellenamos la lista
    {
        entrada >> codCoche; 
        indCoche = buscarCoche(listacoches, codCoche); //cogemos el indice del coche en la lista
        if (indCoche == -1)
            listaAlquileres.listaAlquileres[i].coche = nullptr;
        else
            *listaAlquileres.listaAlquileres[i].coche = listacoches.listacoches[indCoche];  //asignamos el puntero coche

        entrada >> listaAlquileres.listaAlquileres[i].fecha;
        entrada >> listaAlquileres.listaAlquileres[i].dias; 
    }

}

void ordenarAlquileres( ListaAlquileres listaAlquileres)
{
    //vale te cuento
    //el sort es lo q nos ha dado para ordenar esto. en mi ordenador no me funciona el sort (es del namespace std asiq
    //no entiendo xq no funciona pero bueno.)
    
    //asiq he hecho yo el algoritmo de ordenación. creo q funciona.



    Alquiler aux;
    for (int i = 0; i < listaAlquileres.cont; i++) {
        int idx = i;                             //idx es el índice del menor elemento encontrado
        for (int j = i + 1; j < listaAlquileres.cont; j++) {
            if (listaAlquileres.listaAlquileres[j].fecha < listaAlquileres.listaAlquileres[idx].fecha) {
                idx = j;  //si encuentras uno menor, cambia el índice.
            }
        }

        aux = listaAlquileres.listaAlquileres[idx];  //auxiliar para guardar uno de los valores al hacer el cambio
        listaAlquileres.listaAlquileres[idx] = listaAlquileres.listaAlquileres[i];
        listaAlquileres.listaAlquileres[i] = aux;
    } 

    //sort(listaAlquileres.listaAlquileres[0], listaAlquileres.listaAlquileres[listaAlquileres.cont]);
}



void mostrarAlquileres(ListaAlquileres listaAlquiler)
{
    for (int i = 0; i < listaAlquiler.cont; i++)
    {
        if (listaAlquiler.listaAlquileres->coche == nullptr)
            cout << "ERROR, ALQUILER NO ENCONTRADO";
        else {
            cout << listaAlquiler.listaAlquileres[i].fecha << " "
                << listaAlquiler.listaAlquileres[i].coche->nombre << " "
                << listaAlquiler.listaAlquileres[i].dias << " dia(s) por "
                << (listaAlquiler.listaAlquileres[i].coche->precio * listaAlquiler.listaAlquileres[i].dias)
                << " euros." << endl;
        }
        

    }
    delete[] listaAlquiler.listaAlquileres;
}



int main()
{
    SetConsoleOutputCP(CP_UTF8);

    
    ListaCoches listaCoches;
    listaCoches.cont = 0;
    listaCoches.listacoches = nullptr;
    listaCoches.size = 0;

    ListaAlquileres listaAlquileres;
    listaAlquileres.cont = 0;
    listaAlquileres.listaAlquileres = nullptr;
    listaAlquileres.size = 0;

    if (leerModelos(listaCoches));
    {
        leerAlquileres(listaCoches, listaAlquileres);
    }
    

    mostrarAlquileres(listaAlquileres);
   
}

