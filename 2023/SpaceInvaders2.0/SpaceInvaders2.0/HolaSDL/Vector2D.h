#pragma once

template <typename T>

class Vector2D
{
private:
	T x, y; //Puntos del vector

public:
	//Constructora
	Vector2D(T X, T Y) { x = X, y = Y; }
	//Constructora vacía
	Vector2D() { x = 0, y = 0; }

	//Consulta las variables de posición
	T LeerPosX()const { return x; }
	T LeerPosY()const { return y; }

	//Operador de asignación
	Vector2D <T>& operator=(Vector2D<T> const& other) {
		x = other.x;
		y = other.y;

		return *this;
	}

	//Al final creo que no se usa en ningún sitio
	bool operator!=(Vector2D<T> const& other) {
		if (x != other.x && y != other.y)
		{
			return true;
		}
		else { return false; }
	}

	//Operadores de suma y resta 
	Vector2D<T> operator+(const Vector2D<T> other) const {
		Vector2D NewVector(0, 0);
		NewVector.x = x + other.x;
		NewVector.y = y + other.y;

		return NewVector;
	}

	Vector2D <T> operator-(const Vector2D<T> other) const {
		Vector2D NewVector(0, 0);
		NewVector.x = x - other.x;
		NewVector.y = y - other.y;

		return NewVector;
	}

	//Producto escalar
	T operator*(Vector2D<T> other) const {
		T sol = x * other.x + y * other.y;
		return sol;
	}

	//Vector por un escalar
	//Es importante el orden 1.vector 2.escalar
	Vector2D<T> operator*(const T esc) const {
		Vector2D NewVector(0, 0);
		NewVector.x = x * esc;
		NewVector.y = y * esc;
		return NewVector;
	}

};

template <typename T> using Point2D = Vector2D<T>;

