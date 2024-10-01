#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include "SDLApplication.h"
#include "checkML.h"

#include <functional> 

// Tipo de funci�n que recibe un evento SDL por referencia
using callBack = std::function<void(void)>;


class Button : public GameObject,
			   public EventHandler
{
private:

	//Datos del raton
	int x, y;							//Posici�n del rat�n
	SDL_Point point;					//Posici�n del rat�n al pulsar

	Texture* textura = nullptr;			//Puntero a la textura

	//Dibujo del boton
	const int opacidad = 255;			//Opacidad completa
	SDL_Renderer* renderer = nullptr;
	SDL_Rect Rect;						//Rect del boton

	//Animaci�n del boton
	int currentFrame;
	enum ButtonState { MouseOut, MouseOver, MouseClick };

	//Callback para las funciones que se tengan que hacer al ser pulsado
	std::list<callBack> callbacks;

	//Hay un m�todo privado porque el �nico que debe ser capaz de emitir el evento de bot�n pulsado es el propio bot�n
	void emit() const;

public:

	//Constructora
	//GameState para el game object??
	Button(SDLApplication* a, GameState* g, Texture* t, SDL_Renderer* r, Vector2D<double> pos )
	: GameObject(a, g)
	{
		textura = t;
		renderer = r;
		Rect.x = pos.LeerPosX();
		Rect.y = pos.LeerPosY();

		//Dimensiones del bot�n
		Rect.w = textura->getFrameWidth();
		Rect.h = textura->getFrameHeight();

		//Inicializamos el estado del raton como fuera dek bot�n
		currentFrame = MouseOut;
		
	}

	void Render() const override;

	void Update() override;

	void save(std::ostream& out) const override;

	void HandleEvent(const SDL_Event& event) override;

	//Asocia los callBacks
	void Connect(callBack cb);

};

