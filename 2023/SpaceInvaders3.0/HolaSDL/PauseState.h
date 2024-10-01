#pragma once
#include"GameState.h"
#include "checkML.h"

class Button;
class PauseState : public GameState
{
private:
	static const std::string _pauseID;			//ID del PauseState

	PlayState* _playState;						//Puntero a PlayState
	
	//Botones
	Button* _saveButton;						//Boton para guardar
	Button* _loadButton;						//Boton para cargar partida
	Button* _homeButton;						//Para volver al menu principal
	Button* _returnButton;						//Para reanudar la partida

	//Posiciones
	const int columna = 200,
		fila = 125,
		margen = 100;
	
	//callback del boton
	void Save();

	void Load();

	void Home();

	void Return();

public:

	PauseState(SDLApplication* game, PlayState* p);
	//Todos los métodos sobrescriben los de la clase padre
	virtual void Render() override;

	virtual bool OnEnter() override;
	virtual bool OnExit() override;

	virtual std::string GetStateID() const { return _pauseID; }
};

