#pragma once
#include "GameObject.h"
#include "checkML.h"

class MotherShip : public GameObject
{
	enum state { left = -1, right = 1, down };		//Enumerado para los estados del juego
	static const int ALIENS_UPDATE = 60 * 1;

	int dir = left;									//Dirección que siguen los aliens
	int alienCount = 0;								//Contador de aliens
	double level = 1;								//Nivel en el que se encuentran los aliens (Altura)
	const double aumentoLevel = 0.5;
	int alienTimer = ALIENS_UPDATE;					//Temporizador para el movimiento de los aliens

	bool shouldMove = false;

	//Booleanos del estado de los aliens
	bool cannotMove = false;						//Indica si el alien ha llegado al borde de la pantalla
	bool alienDied = false;							//Indica si el alien ha muerto
	bool alienLanded = false;						//Indica si algún alien ha llegado a la fila del cañón

public:

	//Constructoras
	MotherShip(SDLApplication* g, GameState* sta)
		: GameObject(g, sta) {
		dir = left;
		level = 1;
	}

	MotherShip(SDLApplication* g, GameState* sta, int e, double l)
		: GameObject(g, sta) {
		dir = e;
		level = l;
	}

	void Render() const override;

	void Update() override;

	void save(std::ostream& out) const override;

	//Define la dirección del mov que deben seguir los aliens
	const int GetDirection() { return dir; }

	//Indica si los aliens deben moverse en el siguiente ciclo o no
	void ShouldMove();

	const bool GetShouldMove() { return shouldMove; }

	void SetMove(int i) { dir = i; }

	//Métodos llamados por los aliens para informar al MotherShip
	void CannotMove() { cannotMove = true; }

	void AlienDied();

	void AlienLanded() { alienLanded = true; }

	//Métodos para informar al juego
	const bool HaveLanded() { return alienLanded; }

	const int GetAlienCount() { return alienCount; }

	const int Level() { return level; }

	void SetLevel(int i) { level = i; }

	void SetAlienCount(int c) { alienCount = c; }
};

