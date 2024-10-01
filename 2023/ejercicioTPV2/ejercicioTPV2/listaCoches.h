//
// Declaración de la clase Date
//
#pragma once
#include <iostream>
#include "Coche.h"
#include <fstream>



class listaCoches {
private:
	Coche** lista;
	int size;
	int cont;

public:
	// Constructores
	listaCoches() : lista(), size(), cont() {};
	listaCoches(Coche** c, int s, int co);
	//listaCoches(const ListaCoches& date); no lo necesitamos

	// Operador de lectura escritura
	//friend ostream& operator<<(ostream& in, const listaCoches&); no lo necesitamos enverdad
	friend istream& operator>>(istream& in, listaCoches&);

	void DESTRUIR()
	{
		for (int i = 0; i < cont; i++)
		{
			delete lista[i];
		}
		delete[] lista;
		cont = 0;
		size = 0;
	}

	bool leerCoches();
	Coche* Buscacoche(int codigo);


//private: //metodos estaticos (he copiao pegao del ppt)

	/*buscaCoche(int) const;
	insertaCoche(const Coche&);*/


};