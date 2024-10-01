#pragma once
#include "GameState.h"
#include "checkML.h"


class Button;		//Declaración anticipada
//Todos los estados heredan de la clase base "GameState"
class MenuState : public GameState
{
private:
	static const std::string _menuID;			//ID del MenuState

	//Botones del menú
	Button* _playButton;
	Button* _loadButton;
	Button* _exitButton;

	//Posición botones
	const int columna = 250,
		fila = 150,
		margen = 50;

	//Callbacks para los botones
	void Play();
	void Load();
	void Exit();

public:

	//Contructora del menú con el renderer
	MenuState(SDLApplication* game);

	//Todos los métodos sobrescriben los de la clase padre
	void Render() override;

	bool OnEnter() override;
	bool OnExit() override;
};


