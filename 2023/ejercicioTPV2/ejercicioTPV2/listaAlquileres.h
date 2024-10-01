//
// Declaración de la clase Date
//
#pragma once

#include <iostream>
#include "alquiler.h"
#include "listaCoches.h"

class listaAlquileres {
private:
	alquiler* lista;
	int size;
	int cont;


public:
	// Constructores
	listaAlquileres() : lista(), size(), cont() {};
	listaAlquileres(alquiler* alquiler, int size, int cont);
	//listaAlquileres(const listaAlquileres& listaAlquileres);

	//Operadores
	friend ostream& operator<<(ostream& in, const listaAlquileres&);
	bool leerAlquileres(listaCoches listaC);

	void DESTRUIR();

private: 
	/*ListaAlquileres(), ~ListaAlquileres()
		ordena()
		insertaAlquiler(const Alquiler&)
		leeAlquileres(const ListaCoches&)*/
};
