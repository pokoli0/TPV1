#pragma once
#include "Alien.h"
#include <random>

class ShooterAlien : public Alien
{
private:

		std::mt19937_64 random;	//Generador de randoms
		int minCoolDown = 250, maxCoolDown = 750;
		int coolDown = 100;		//Contador para el cooldown
	
	public:
		//Constructora vacía
		ShooterAlien() : Alien() { }
		
		//Constructora
		ShooterAlien(Game* gam, Point2D<double> p,Texture* t, Mothership* m, int v, int i, int f, int c)
			: Alien(gam, p, t, m, v, i, f) 
		{
			//Iniciamos con un valor random
			coolDown = c;
		}
	
		void Update() override;

		void save(std::ostream& out) const;

		int getRandomRange(int min, int max);
};

