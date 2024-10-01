#include "Cannon.h"
using namespace std;
using uint = unsigned int;


Cannon::Cannon(ifstream& in, Texture* tx, Game* g) : SceneObject(g, tx, in), lastTimeShoot(SDL_GetTicks()) {
	rect.w = text->getFrameWidth();
	rect.h = text->getFrameHeight();

	in >> vidas >> TiempoRecarga;
}

void Cannon::Render()
{
	SceneObject::Render();
	text->renderFrame(rect, 0, 0);
}


void Cannon::Update()
{
	if ((direccion == -1 && pos.getX() > 0) ||												//si no te sales por la izquierda
		(direccion == 1 && pos.getX() < (game->GetWindowWidth() - text->getFrameWidth())))  //ni por la derecha
	{
		pos = pos + Vector2D((direccion * VELOCIDAD), 0);
	}
}

void Cannon::TryToShoot()
{
	if (SDL_GetTicks() - lastTimeShoot > TiempoRecarga) //disparar cada x tiempo
	{
		game->fireLaser(pos.getX() + text->getFrameWidth()/2, pos.getY(), - 1, 'r'); //el getframewidth es para q salga del centro y no de la esquina
		lastTimeShoot = SDL_GetTicks();
	}
}

void Cannon::handleEvent(SDL_Event event) {

	if (event.type == SDL_KEYDOWN) //si se ha pulsado una tecla
	{
		if (event.key.keysym.sym == SDLK_SPACE)
			TryToShoot();

		else if (direccion == 0) //para moverte en una direccion, tienes q estar no moviendote en la otra
		{
			if (event.key.keysym.sym == SDLK_RIGHT)
				direccion = 1;

			else
				direccion = -1;
		}
	}
	
	else if (event.type == SDL_KEYUP) //si se suelta una tecla, la dirección cambia a 0
	{
		direccion = 0; 
	}
}


bool Cannon::Hit(SDL_Rect* OtherRect, char origin)
{	
	if (origin == 'b' && SceneObject::Hit(OtherRect, origin))
	{
		vidas--;
		/*if (vidas <= 0)
			game->hasDied(iterator);*/

		game->UpdateVidas();
		return true;
	} 
	return false;
}

void Cannon::Save(ostream& out) const
{
	out << "0 " << pos.getX() << " " << pos.getY() << " " << vidas << " " << TiempoRecarga << endl;
}



