

#include "alquiler.h"
#include <iomanip>

//posibles metodos a implementar aqui:
	//getFecha(), getDias() const
	//getCoste() const
	//leeAlquiler(const ListaCoches&)


//constructora(s)
alquiler::alquiler(Coche* c, Date f, int d):
	coche(c), fecha(f), dias (d) {}				//retiro lo dicho soy tonta y los necesitamos




//operadores
bool alquiler::operator<(const alquiler& a) const
{
	return (fecha < a.fecha);
}

//getters
Coche* alquiler::GetCoche() const
{
	return coche;
}

Date alquiler::GetFecha() const
{
	return fecha;
}

int alquiler::GetDias() const
{
	return dias;
}



int alquiler::getCoste() const
{
	return (coche->getPrecio()*dias);
}

//escritura
ostream& operator<<(ostream& out, const alquiler& a)
{
	if (a.coche != nullptr)
	{
		out << a.fecha << " " << a.coche->getModelo() << " "
			<< a.dias << " dia(s) por " << a.getCoste() << "euros.";
	}

	else
		out << "MODELO NO ENCONTRADO";
	
	
	return out;
}


