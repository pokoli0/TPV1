#include "GameObject.h"
#include "GameState.h"
#include "PlayState.h"
#include "SDLApplication.h"


GameObject::GameObject(SDLApplication* g, GameState* stat) {
	game = g;
	_gameState = stat; 
}

GameObject::GameObject(SDLApplication* g, PlayState* ps) { 
	game = g;
	_gameState = ps; }

