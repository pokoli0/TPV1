//
// Declaraci�n de la clase Date
//

#include <iostream>

#ifndef DATE_H_
#define DATE_H_

class Date {
private:
	int day;
	int month;
	int year;

public:
	// Constructores
	Date();
	Date(int d, int m, int y);
	Date(const Date& date);

	// Operadores aritm�ticos
	void operator++();
	void operator+=(int n);

	// Operador de comparaci�n
	bool operator<(const Date& date) const;

	// N�mero de d�as de diferencia entre dos fechas
	int diff(const Date& date) const;

	// Operadores de lectura y escritura
	// (son amigos para poder acceder a los atributos de Date)
	friend std::istream& operator>>(std::istream& in, Date& d);
	friend std::ostream& operator<<(std::ostream& in, const Date& d);

private:
	int calculateValue() const;
	bool correctDate() const;

	// M�todos est�ticos (comprueban si un a�o es bisiesto y calculan
	// el n�mero de d�as de cada mes, pero no operan con una fecha)
	static bool leapYear(int y);
	static int daysInMonth(int m, int y);
};

#endif // DATE_H_
