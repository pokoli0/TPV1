#pragma once
#include "Alien.h"
#include "checkML.h"

class SDLApplication;		//Declaración anticipada
class ShooterAlien: public Alien
{
private:

	int minCoolDown = 50, maxCoolDown = 200;
	int coolDown = 100;		//Contador para el cooldown

public:

	//Constructora vacía
	ShooterAlien() : Alien() { }

	//Constructora
	ShooterAlien(SDLApplication* gam, PlayState* ps, Point2D<double> p, Texture* t, MotherShip* m, int v, int i, int f, int c)
		: Alien(gam, ps, p, t, m, v, i, f)
	{
		//Iniciamos con un valor random
		coolDown = c;
	}

	void Update() override;

	void save(std::ostream& out) const override;

};

