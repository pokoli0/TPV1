// María Solórzano y Paula Sierra Grupo5
//

#include <iostream>
#include "Date.h"
#include "coche.h"
#include "listaCoches.h"
#include "alquiler.h"
#include "listaAlquileres.h"
#include "checkML.h"





int main()
{
    listaCoches listac;
    listaAlquileres listaa;

    if (listac.leerCoches())
    {
        if (listaa.leerAlquileres(listac))
        {
            std::cout << listaa;
            //std::cout << "todo pana \n";

            listac.DESTRUIR();
            listaa.DESTRUIR();

        }
        
    }
    else
        std::cout << "ERROR EN LA LECTURA";

    
}


