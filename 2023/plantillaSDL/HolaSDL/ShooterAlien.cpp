#include "ShooterAlien.h"



ShooterAlien::ShooterAlien(ifstream& Entrada, Texture* t, Game* g, MotherShip* m): Alien(Entrada, t, g, m), lastTimeShot(SDL_GetTicks())
{
	Entrada >> tiempoRecarga;
	
}

void ShooterAlien::Update()
{
	Alien::Update();
	if (SDL_GetTicks() - lastTimeShot > tiempoRecarga)
		TryShoot();
}
void ShooterAlien::Save(ostream& out) const
{
	out << "2 " << pos.getX() << " " << pos.getY() << " " << subtipo << " " << tiempoRecarga - (SDL_GetTicks() - lastTimeShot)  << endl;
}
void ShooterAlien::TryShoot()
{
	//game->fireLaser(new Laser(game, pos.getX() + text.getFrameWidth/2, pos.getY(), 1, 'b'));
	tiempoRecarga = game->RandomGenerator(700, 2000);
	game->fireLaser(pos.getX() + text->getFrameWidth() / 2, pos.getY(), 1, 'b');

	lastTimeShot = SDL_GetTicks();
}
