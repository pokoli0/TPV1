#include "Ufo.h"

using namespace std;


Ufo::Ufo(Texture* texture, Game* game, int x, int y)
	: SceneObject(game, x, y, texture), startTime (SDL_GetTicks()) {

	rect.w = text->getFrameWidth();
	rect.h = text->getFrameHeight();
	rect.y = pos.getY();
	waitTime = game->RandomGenerator(2000, 5000);
}

Ufo::Ufo(Texture* texture, Game* game, ifstream& in): SceneObject(game, texture, in), startTime(SDL_GetTicks())
{
	rect.w = text->getFrameWidth();
	rect.h = text->getFrameHeight();
	rect.y = pos.getY();


	int st; in >> st;
	state = (states)st; //esto es un parse de int a state.

	in >> waitTime;
}


void Ufo::Render()
{
	if (state != hidden)
	{
		rect.x = pos.getX();
		text->renderFrame(rect, 0, (int)state - 1);
	}
	
}

bool Ufo::Hit(SDL_Rect* otherRect, char origin) {
	
	if (state == visible && origin == 'r' && SDL_HasIntersection(getRect(), otherRect))
	{
		game->addScore(100); //no se si hay q hacer una constante para este 100
		UfoDestroyed();
		return true;
	}
	return false;
}

void Ufo::Save(ostream& out) const
{
	out << "5 " << pos.getX() << " " << pos.getY() << " " << (int)state << " " << waitTime - (SDL_GetTicks() - startTime);
}

void Ufo::Update()
{
	if (state == visible)			//si está visible, se mueve
	{
		pos = pos - Vector2D(velocidad, 0);
		if (pos.getX() < 0)			//si se sale, se esconde
			UfoHidden();
	}
	else if (SDL_GetTicks() - startTime >= waitTime)	//si está destruido o invisible, espera
	{
		if (state == hidden)
			state = visible;
		else
			UfoHidden();
		startTime = SDL_GetTicks();
	}
}

void Ufo::UfoDestroyed()
{
	state = destroyed;
	waitTime = 60; //tiempo de espera en el q es visible antes de destruirse
	startTime = SDL_GetTicks();
}

void Ufo::UfoHidden()
{
	state = hidden;
	pos = point2D(game->GetWindowWidth(), pos.getY());
	waitTime = game->RandomGenerator(2000, 5000);
	startTime = SDL_GetTicks();
}

