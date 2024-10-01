#pragma once
#include "Alien.h"
using uint = unsigned int;


class ShooterAlien : public Alien
{
private:
	uint tiempoRecarga, lastTimeShot;


	void TryShoot();
	

public:
	ShooterAlien(ifstream& Entrada, Texture* t, Game* g, MotherShip* m);
	void Update() override;
	void Save(ostream& out) const override;

};

