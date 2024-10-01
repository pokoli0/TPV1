#pragma once
#include <string>
#include <iostream>
#include <list>

#include "gameList.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "checkML.h"

//Declaraciones anticipadas
class GameObject;
class SDLApplication;
class GameState
{
protected:
	SDLApplication* game;						//Puntero al juego
	GameList<GameObject, true> gameList;		//Lista de objetos del juego
	std::list<EventHandler*> listenerList;			//Manejadores de eventos

public:
	//Destructora
	virtual ~GameState() = default;

	//Constructora
	GameState(SDLApplication* g) { game = g; }

	//Funciones necesarias para todas las clases hijas de GameState
	virtual void Update();
	virtual void Render() = 0;
	virtual void HandleEvent(const SDL_Event& event);


	//Funciones de transición entre estados
	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;

	//Metodos para añadir 
	virtual void AddEventListener(EventHandler* lis);
	void AddObject(GameObject* obj);
};

