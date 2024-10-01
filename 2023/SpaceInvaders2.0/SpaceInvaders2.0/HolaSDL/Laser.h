#pragma once

#include "SceneObject.h"

class Laser: public SceneObject
{
private:
	enum color {red, blue};
	Vector2D<double> vel;				//Vector velocidad del l�ser
	double v = 5;						//Velocidad del l�ser
	int color = red;					//Puede ser r o b dependiendo de quien lance el l�ser

	//Dibujo del l�ser
	SDL_Renderer* renderer = nullptr;	//Puntero al renderer
	const int laserW = 5;				//Ancho del laser
	const int laserH = 25;				//largo del laser
		
public:
	//Constructora vac�a
	Laser() : SceneObject() {}

	//Constructora - Mirar que pasa cuando utiliza la constructora de la clase padre
	Laser(Game* j, Point2D<double> p, Texture* t, int vida, SDL_Renderer* render, bool origen)
		: SceneObject(j, p, t, vida) {

		renderer = render;
		vel = Vector2D<double>(0, v);
		if (origen) { color = blue; }
	}

	void Render() const override;
	
	void Update() override;
	
	void save(std::ostream& out) const override;

	bool Hit(const SDL_Rect* r, bool o) override;
	
	int Origen() { return color; }

};

