#include "GameState.h"
#include "GameObject.h"

//vale poli guapa te digo
//aqui hay mucha abstracción. la mayoria de metodos simplemente recorren bucles llamando a los metodos de esos objetos
//o añaden/ borran objetos de metodos específicos.
//poco mas tbh

GameState::GameState(Game* g) : game(g), objects(), eventHandlers() {}

void GameState::update()
{
	for (auto SO : objects)
		SO.Update();
}

void GameState::render()
{
	for (auto SO : objects)
		SO.Render();
}

void GameState::handleEvent(const SDL_Event& event)
{
	for (auto SO : eventHandlers)
		SO->handleEvent(event);
}

void GameState::addEventListener(EventHandler* listener)
{
	eventHandlers.push_back(listener);
}

void GameState::addObjects(GameObject* object)
{
	objects.push_back(object);
}
