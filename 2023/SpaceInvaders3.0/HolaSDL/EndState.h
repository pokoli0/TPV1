#pragma once
#include "GameState.h"
#include "texture.h"
#include "checkML.h"

class Button;
class EndState : public GameState
{
private:
	static const std::string _endID;			//ID del endState

	Texture* textura = nullptr;					//Textura del texto
	SDL_Rect rect;

	//Posición
	
	const int columna = 250,
		fila = 100,
		margen = 100;

	//Botones
	Button* _exitButton;					//Boton para salir del juego
	Button* _homeButton;					//Boton para cargar partida

	//callbacks para los botones
	void Home();
	void Exit();

public:

	EndState(SDLApplication* g, Texture* t);

	//Todos los métodos sobrescriben los de la clase padre
	void Render() override;

	bool OnEnter() override;
	bool OnExit() override;
};

