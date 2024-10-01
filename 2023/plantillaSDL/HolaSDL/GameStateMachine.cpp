#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* newState)
{
	StateStack.push(newState);
}

void GameStateMachine::popState()
{
	StateStack.pop();
}

void GameStateMachine::replaceState(GameState* newState)
{
	popState();
	pushState(newState);
}

void GameStateMachine::update()
{
	//StateStack.front()-> update();
}

void GameStateMachine::render() const
{
	//StateStack.front()-> render();
}
