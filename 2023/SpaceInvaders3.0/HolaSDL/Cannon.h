#pragma once
#include "SceneObject.h"
#include "EventHandler.h"
#include "checkML.h"

class Cannon : public SceneObject,
	public EventHandler
{
private:
	enum dir { still, left, right };

	const int maxCooldown = 7;		//Cooldown 
	int cooldown;					//Contador del cooldown

	int maxVidas;					//Vidas máximas del jugador

	int dirC = still;				//Direccion en la que se mueve el jugador
	const double speed = 2;			//Velocidad a la que se mueve el jugador
	int margenCannon;				//Ancho del sprite

	bool invencible = false;		//Booleano para el escudo

	const int derecha = 2,
		izquierda = 1;
	const int _maxVidas = 3;

public:

	//Constructora vacía
	Cannon() : SceneObject()
	{
		maxVidas = _maxVidas;
	}

	//Constructora 
	Cannon(SDLApplication* j, PlayState* ps, Point2D<double> p, Texture* t, int v, int c)
		: SceneObject(j, ps, p, t, v)
	{
		maxVidas = v;
		margenCannon = textura->getFrameWidth() / 2;

		cooldown = c;
	}

	void Render() const override;

	void Update() override;

	void save(std::ostream& out) const override;

	bool Hit(const SDL_Rect* r, bool o) override;

	void HandleEvent(const SDL_Event& evento) override;

	void ImInvencible() { invencible = true; }
};

