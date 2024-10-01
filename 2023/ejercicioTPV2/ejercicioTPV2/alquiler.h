//
// Declaración de la clase alquiler
//
#pragma once

#include <iostream>
#include "coche.h"
#include "Date.h"
#include "listaCoches.h"

using namespace std;

class alquiler {
private:
	Coche* coche;
	Date fecha;
	int dias;

public:
	// Constructores
	alquiler() : coche(), fecha(), dias() {};
	alquiler(Coche* c, Date f, int d); //en verdad no la necesitamos
	//alquiler(const alquiler& alquiler);

	// Operadores de escritura y lectura
	friend ostream& operator<<(ostream& in, const alquiler&); 
	/*friend istream& operator>>(istream& in, alquiler&);*/

	// Operador de comparación
	bool operator < (const alquiler&) const; //nada nada q soy una crack y esto ya no da error

	//getters
	Coche* GetCoche() const;
	Date GetFecha() const; //DA ERROR ya no pero lo dejo pues xq molo mazo sabes
	int GetDias() const;


private: //si, otra vez, pero con metodos estaticos
	
	int getCoste() const;
	//leeAlquiler(const ListaCoches&)

};


