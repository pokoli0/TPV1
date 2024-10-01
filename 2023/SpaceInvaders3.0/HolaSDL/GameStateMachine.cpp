#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine()
{
	while (!_pilaGameStates.empty()) {
		PopState();
	}
}

//No estamos comprobando si la pila está llena o vacía en ningún momento, podría dar problemas
void GameStateMachine::PushState(GameState* _state)
{
	//Introduce un nuevo elemento en lo alto de la pila
	_pilaGameStates.push(_state);

	//Hacemos el onEnter del estado que entre
	_pilaGameStates.top()->OnEnter();
}

void GameStateMachine::ReplaceState(GameState* _state)
{
	//Hacemos una fusión

	//Eliminamos el elemento que está actualmente en la cima
	//Puede que para eliminarlos haya que hacer una lista de punteros como la última vez
	PopState();

	//Añadimos el nuevo estado
	PushState(_state);

}

void GameStateMachine::PopState()
{
	//Hacemos el onExit del elemento que esté en la cima
	_pilaGameStates.top()->OnExit();

	//Lo sacamos de la pila
	_pilaGameStates.pop();

}

//Hace el update del estado que esté en la cima
void GameStateMachine::Update()
{
	_pilaGameStates.top()->Update();
}

void GameStateMachine::Render()
{
	_pilaGameStates.top()->Render();
}

void GameStateMachine::HandleEvent(SDL_Event& event)
{
	_pilaGameStates.top()->HandleEvent(event);
	
}
