#include "GameState.h"

void GameState::Update()
{
	//Hacemos el update de todos los elementos de la lista
	for (GameObject& objects : gameList) {
		objects.Update();
	}
}

void GameState::HandleEvent(const SDL_Event& event)
{
	//hacemos el HandleEvent de todos los elementos de la lista
	for (EventHandler* listener : listenerList) {
		listener->HandleEvent(event);
	}
}

void GameState::AddEventListener(EventHandler* lis)
{
	listenerList.push_back(lis);
}

void GameState::AddObject(GameObject* obj)
{
	gameList.push_back(obj);
}
