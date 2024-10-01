#pragma once

#include "GameObject.h"

class Mothership : public GameObject
{
private:
	enum state { left = -1, right = 1, down };		//Enumerado para los estados del juego
	static const int ALIENS_UPDATE = 60 * 1;

	int dir = left;									//Dirección que siguen los aliens
	int alienCount = 0;								//Contador de aliens
	double level = 1;								//Nivel en el que se encuentran los aliens (Altura)
	int alienTimer = ALIENS_UPDATE;					//Temporizador para el movimiento de los aliens

	bool shouldMove = false;

	//Booleanos del estado de los aliens
	bool cannotMove = false;						//Indica si el alien ha llegado al borde de la pantalla
	bool alienDied = false;							//Indica si el alien ha muerto
	bool alienLanded = false;						//Indica si algún alien ha llegado a la fila del cañón

public:

	Mothership(Game* gam) : GameObject(gam) {
		dir = left;
		level = 1;
	}

	Mothership(Game* gam, int e, double l) : GameObject(gam) {
		dir = e;
		level = l;
	}

	void Render() const override;

	void Update() override;

	void save(std::ostream& out) const override;

	//Define la dirección del mov que deben seguir los aliens
	int GetDirection() { return dir; }

	//Indica si los aliens deben moverse en el siguiente ciclo o no
	void ShouldMove();

	bool GetShouldMove() { return shouldMove; }

	//Métodos llamados por los aliens para informar al MotherShip
	//No se si deberían ser booleanos, depende de donde y como los vayamos a usar
	void CannotMove() { cannotMove = true; }

	void AlienDied();

	void AlienLanded() { alienLanded = true; }

	//Métodos para informar al juego
	bool HaveLanded() { return alienLanded; }

	int GetAlienCount() { return alienCount; }

	int Level() { return level; }

	void SetAlienCount(int c) { alienCount = c; }
};

