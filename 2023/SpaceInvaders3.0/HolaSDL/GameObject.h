#pragma once
#include <ostream>
#include "Vector2D.h"
#include "gameList.h"
#include "checkML.h"


//Reune la funcionalidad común a todos los objetos del juego
class SDLApplication;
class GameState;
class PlayState;
class GameObject
{
protected:
	//A lo mejor podemos quitar esto
	SDLApplication* game;		//Puntero al juego

	GameState* _gameState;		//Estado del juego, para el play state

	GameList<GameObject, true>::anchor anc = nullptr;

public:

	//Constructora vacía
	GameObject() { game = nullptr;  _gameState = nullptr; }

	//Contructora
	GameObject(SDLApplication* g, GameState* stat);

	GameObject(SDLApplication* g, PlayState* stat);

	//Métodos virtuales puros
	virtual void Render() const = 0;

	virtual void Update() = 0;

	virtual void save(std::ostream& out) const = 0;

	//Destructora virtual
	virtual ~GameObject() = default;

	void setListAnchor(GameList<GameObject, true>::anchor newanc) // list<SceneObject*>::iterator& newit
	{
		// setea el iterador de la posicion del objeto en la lista
		anc = newanc;
	};
};

