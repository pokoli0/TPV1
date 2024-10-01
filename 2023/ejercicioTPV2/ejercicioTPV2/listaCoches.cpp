//
// Implementación de la clase Date
//
#include "listaCoches.h"
#include <iomanip>

using namespace std;

//metodos a implementar
//buscaCoche(int) const
//insertaCoche(const Coche&)



//constructora
listaCoches::listaCoches(Coche** c, int s, int co):
	lista(c), size(s), cont(co) {}

bool listaCoches::leerCoches()
{
	ifstream entrada("coches.txt");
	if (!entrada.is_open())
		return false;

	else
	{
		entrada >> *this;
		return true;
	}
}

Coche* listaCoches::Buscacoche(int codigo)
{
	int i = 0;
	bool encontrado = false;
	while (i < cont && !false)
	{
		if (lista[i]->getCodigo() == codigo)
			encontrado = true;
		else
			i++;

	}
	
	if (encontrado)
		return lista[i];
	else
		return nullptr;
}


//lectura
istream& operator>>(istream& in, listaCoches& l)
{
	in >> l.cont;
	l.size = l.cont + 10;
	l.lista = new Coche*[l.size];

	for (int i = 0; i < l.cont; i++)
	{
		l.lista[i] = new Coche();
		in >> *(l.lista[i]);
	};

	return in;	
}
