#include "Laser.h"
using namespace std;

bool Laser::Attack()
{
	return game->Attack(&rect, color);
}

Laser::Laser(Game* g, int x, int y, int dir, char c) :
	SceneObject(g, x, y, nullptr), color(c), velocidad(0, 20*dir){

	renderer = game->GetRenderer();
	rect.w = LASER_WIDTH;			//el tamaño no varía, por lo que lo podemos definir en la constructora
	rect.h = LASER_HEIGHT;

}

Laser::Laser(Game* g, ifstream& in) : SceneObject(game, nullptr, in)
{
	renderer = game->GetRenderer();

	in >> color;
	if (color == 'r')
		velocidad = Vector2D(0, -20);
	else
		velocidad = Vector2D(0, 20);

}

void Laser::Render() {
	SceneObject::Render();
	//Poli borracha putera estafadora esto esta al reves (Luis) Se te quiere mucho <3
	//def: int SDL_SetRenderDrawColor(SDL_Renderer * renderer, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	if (color == 'r')
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //green
		
	else
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 50); //red
		 
	

	SDL_RenderFillRect(renderer, &rect); //lo dibuja como un rectángulo
}

void Laser::Update() {
	//avanza de acuerdo a su velocidad
	pos = pos + velocidad;
	if (game->Attack(&rect, color))
	{
		game->hasDied(iterator);
	}
		
		

	else if (pos.getY() < 0 || pos.getY() > game->GetWindowHeight())
		game->hasDied(iterator); //para q no se salga
}

bool Laser::Hit(SDL_Rect* OtherRect, char origin)
{
	if (color != origin && SceneObject::Hit(OtherRect, origin))
	{
		//como se elimina el solo cuando da con algo, no tenemos q hacer el hasDied()
		return true;
	}
	return false;
}

void Laser::Save(ostream& in) const 
{
	in << "3 " + to_string(pos.getX()) + " " + to_string(velocidad.getY()/20) +
		" " + to_string(velocidad.getY()) + " " + color << endl;
}


