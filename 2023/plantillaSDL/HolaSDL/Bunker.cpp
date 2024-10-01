#include "Bunker.h"
#include "checkML.h"
using namespace std;

Bunker::Bunker(ifstream& in, Texture* tx, Game* g) : SceneObject(g, tx, in)
{
	//como el bunker no se mueve, podemos definirlo en la constructora
	rect.w = text->getFrameWidth();
	rect.h = text->getFrameHeight();
	rect.x = pos.getX();
	rect.y = pos.getY();

	in >> vidas;
}

void Bunker::Render() {
	//llama al render de texture.h
	text->renderFrame(rect, 0, text->getNumColumns() - vidas);
}

bool Bunker::Hit(SDL_Rect* otherRect, char origin) {

	//se comprueba si da
	if (SceneObject::Hit(otherRect, origin))
	{
		vidas--;
		if (vidas == 0)
			game->hasDied(iterator);
		return true;
	}
	else
		return false;
	
}

void Bunker::Save(ostream& out) const
{
	out<< "4 " << pos.getX() << " " << pos.getY() << " " << vidas << endl;
}

SDL_Rect* Bunker::getSDLRect() //devuelve puntero al rect de bunker
{
	return &rect;
}

//returns false si ha perdido todas sus vidas
void Bunker::Update() {
	if (vidas <= 0)
	{
		game->hasDied(iterator);
	}
}

