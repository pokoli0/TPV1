//
// Declaración de la clase Date
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
	Date() : day(0), month(0), year(0) {};
	Date(int d, int m, int y);
	Date(const Date& date);

	// Operadores aritméticos
	void operator++();
	void operator+=(int n);

	// Operador de comparación
	bool operator<(const Date& date) const;

	// Número de días de diferencia entre dos fechas
	int diff(const Date& date) const;

	// Operadores de lectura y escritura
	// (son amigos para poder acceder a los atributos de Date)
	friend std::istream& operator>>(std::istream& in, Date& d);
	friend std::ostream& operator<<(std::ostream& in, const Date& d);

private:
	int calculateValue() const;
	bool correctDate() const;

	// Métodos estáticos (comprueban si un año es bisiesto y calculan
	// el número de días de cada mes, pero no operan con una fecha)
	static bool leapYear(int y);
	static int daysInMonth(int m, int y);
};

#endif // DATE_H_
