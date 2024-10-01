//
// Declaración de la clase Date
//

#pragma once

#include <iostream>
#include <string>

using namespace std; //si no no me va el string

class Coche {
private:
	int codigo;
	int precio;
	string nombre;

public:
	//constructores
	Coche() : codigo(), precio(), nombre() {};
	Coche(int c, int p, string n);
	//Coche(const Coche& coche);
	
	// Operadores de lectura y escritura
	friend ostream& operator<<(ostream&, const Coche&);
	friend istream& operator>>(istream&, Coche&);

	//getters
	int getPrecio()const;
	int getCodigo() const;
	string getModelo() const;
		

};
