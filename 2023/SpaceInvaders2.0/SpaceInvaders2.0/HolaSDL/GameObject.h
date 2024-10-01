#pragma once
#include <ostream>
class Game;

//Reune la funcionalidad común a todos los objetos del juego
class GameObject
{
protected:
	Game* game;		//Puntero al juego

public:
	//Constructora vacía
	GameObject() { game = nullptr; };

	//Constructora
	GameObject(Game* gam) { game = gam; }

	//Métodos virtuales puros
	virtual void Render() const = 0;

	virtual void Update() = 0;

	//Poner el ostream& cuando sepa hacerlo
	virtual void save(std::ostream& out) const = 0;

	//Destructora virtual
	virtual ~GameObject() = default;

};

