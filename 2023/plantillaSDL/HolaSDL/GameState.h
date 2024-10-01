#pragma once
#include <SDL.h>
#include <list>
#include "EventHandler.h"
#include "gameList.h"

//declaraciones anticipadas
class Game;
class GameObject; 

class GameState
{
protected:
	GameList <GameObject, true> objects;
	std::list <EventHandler*> eventHandlers;
	Game* game;

public: 
	GameState(Game* g);
	virtual void update();
	virtual void render();
	void handleEvent(const SDL_Event&);
	void addEventListener(EventHandler* listener);
	void addObjects(GameObject* object);
	//virtual void save() const;	esto lo voy a meter en el playstate xq no tiene sentido q este
};

