#pragma once
#include "SceneObject.h"
#include "checkML.h"

class Bomb: public SceneObject
{
private:
	Vector2D<double> vel;				//Vector velocidad de la bomba
	double v = 5;						//Velocidad del láser
	int color = 1;						//Para el origen

	//Dibujo del láser
	SDL_Renderer* renderer = nullptr;	//Puntero al renderer
	const int laserW = 5;				//Ancho del laser
	const int laserH = 25;				//largo del laser

public:
	//Constructora vacía
	Bomb() : SceneObject() {}

	//Constructora 
	Bomb(SDLApplication* g, PlayState* j, Point2D<double> p, Texture* t, int vida)
		: SceneObject(g, j, p, t, vida) {

		vel = Vector2D<double>(0, v);
	}

	void Render() const override;

	void Update() override;

	void save(std::ostream& out) const override;

	bool Hit(const SDL_Rect* r, bool o) override;

	const int Origen() { return color; }
};

