#include "Bomb.h"
#include "PlayState.h"

void Bomb::Render() const
{
	//renderizamos la bomba
	textura->renderFrame(rect, textura->getNumRows() - 1, textura->getNumColumns() - 1);
}

void Bomb::Update()
{
	//Se mueven abajo
	pos = pos + vel;

	//Actualizamos el rect
	rect.x = pos.LeerPosX();
	rect.y = pos.LeerPosY();

	//Si colisiona o se salen de la pantalla destruimos el laser
	if (pos.LeerPosY() < 0) {
		_playState->hasDied(sceneanc);
	}
}

void Bomb::save(std::ostream& out) const
{
	
}

bool Bomb::Hit(const SDL_Rect* r, bool o)
{
	if (SDL_HasIntersection(r, GetRect()) && !o && o) {
			SceneObject::Hit(r, o);
			if(vida == 0) _playState->hasDied(sceneanc);
			return true;
	}
	return false;
}

