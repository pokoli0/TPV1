#pragma once
#include <stack>
#include "GameState.h"
class GameStateMachine
{
private: 
	std::stack <GameState*> StateStack;

public:
	void pushState(GameState* newState);
	void popState();
	void replaceState(GameState*);
	void update();
	void render() const;
	void handleEvent(const SDL_Event&);
};

