#include "listaAlquileres.h"
#include "alquiler.h"
#include "Coche.h"
#include "listaCoches.h"

//constructora
listaAlquileres::listaAlquileres(alquiler* alquiler, int size, int cont):
lista(alquiler), size(size), cont(cont) {}

bool listaAlquileres::leerAlquileres(listaCoches listaC)
{
	ifstream entrada("rent.txt");
	if (!entrada.is_open())
		return false;

	else
	{
		entrada >> cont;
		size = cont + 10;
		lista = new alquiler[size];
		Coche* puntcoche;
		int cod, dias;
		Date fecha;

		for (int i = 0; i < cont; i++)
		{
			entrada >> cod >> fecha >> dias;
			puntcoche = listaC.Buscacoche(cod);
			lista[i] = alquiler(puntcoche, fecha, dias);
		}
		return true;
	}
	
}

void listaAlquileres::DESTRUIR()
{
	delete[] lista;
	size = 0;
	cont = 0;
}

//escritura
ostream& operator<<(ostream& out, const listaAlquileres& l)
{
	for (int i = 0; i < l.size; i++)
	{
		out << l.lista[i];
	}
	return out;
}
