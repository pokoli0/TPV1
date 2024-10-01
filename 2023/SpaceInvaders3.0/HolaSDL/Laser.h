#pragma once
#include "SceneObject.h"
#include "checkML.h"

class Laser : public SceneObject
{
private:
	enum color{ red, blue };			//Osigen del laser
	Vector2D<double> vel;				//Vector velocidad del laser
	double v = 5;						//Velocidad del láser
	int color = red;					//Puede ser r o b dependiendo de quien lance el láser

	//Dibujo del láser
	SDL_Renderer* renderer = nullptr;	//Puntero al renderer
	const int laserW = 5;				//Ancho del laser
	const int laserH = 25;				//largo del laser

	const int opacidad = 255;

public:
	//Constructora vacía
	Laser() : SceneObject() {}

	//Constructora 
	Laser(SDLApplication* g, PlayState* j, Point2D<double> p, Texture* t, int vida, SDL_Renderer* render, int origen)
		: SceneObject(g, j, p, t, vida) {

		renderer = render;
		vel = Vector2D<double>(0, v);
		color = origen;
	}

	void Render() const override;

	void Update() override;

	void save(std::ostream& out) const override;

	bool Hit(const SDL_Rect* r, bool o) override;

	const int Origen() { return color; }
};

