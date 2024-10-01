//
// Implementación de la clase Date
//

#include "coche.h"
#include <iomanip>
#include <string>

using namespace std;

//metodos a implementar
//getCodigo(), getPrecio(), getModelo() const

//constructora
Coche::Coche(int c, int p, string n):
codigo(c), precio (p), nombre(n){}




//getters
int Coche::getPrecio() const
{
	return precio;
}
int Coche::getCodigo() const
{
	return codigo;
}
string Coche::getModelo() const
{
	return nombre;
}




//escritura
ostream& operator<<(ostream& out, const Coche& c)
{
	out << c.nombre << ", con código" << c.codigo <<" y precio " << c.precio;
	return out;
}

//lectura
istream& operator>>(istream& in, Coche& c)
{
	in >> c.codigo >> c.precio;
	std::getline(in, c.nombre);
	return in;
}