#pragma once
#include "GameState.h"
#include "checkML.h"

#include <stack>

class GameStateMachine
{
private:

	//Usamos una pila para almacenar los estados
	std::stack <GameState*> _pilaGameStates;

public:
	//Destructora
	~GameStateMachine();
	//Métodos para intercambiar estados
	void PushState(GameState* pState);				//Inserta un estado

	void ReplaceState(GameState* pState);			//cambia el estado actual

	void PopState();								//Elimina un estado

	void Update();

	void Render();

	void HandleEvent(SDL_Event& event);


};



