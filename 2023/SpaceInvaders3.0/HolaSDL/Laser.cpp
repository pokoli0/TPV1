#include "Laser.h"
#include "PlayState.h"

void Laser::Render() const
{
	//Dependiendo de quien dispare cambia el color
	if (color == blue) {	//Dispara un alien
		SDL_SetRenderDrawColor(renderer, 160, 252, 233, opacidad);		//VerdeAgua
	}
	else if (color == red) {	//Dispara el jugador
		SDL_SetRenderDrawColor(renderer, 252, 160, 217, opacidad);		//Rosa
	}
	//dibujamos el laser
	SDL_RenderFillRect(renderer, &rect);
}

void Laser::Update()
{
	//Dispara un alien (Se mueven abajo)
	if (color == blue) { pos = pos + vel; }

	//Dispara el cañón (Se mueven arriba)
	else { pos = pos - vel; }

	//Actualizamos el rect
	rect.x = pos.LeerPosX();
	rect.y = pos.LeerPosY();

	//Si colisiona o se salen de la pantalla destruimos el laser
	if (_playState->Colisiones(this) 
		|| (pos.LeerPosY() < 0 )){
		_playState->hasDied(sceneanc);
	}
}

void Laser::save(std::ostream& out) const
{
	out << "6 ";
	SceneObject::save(out);
	out << " " << color << std::endl;
}

bool Laser::Hit(const SDL_Rect* r, bool o)
 {
	if (SDL_HasIntersection(r, GetRect())) {
		if ((color == blue && !o) || (color == red && o))
		{
			SceneObject::Hit(r, o);
			_playState->hasDied(sceneanc);
			return true;
		}
	}
	return false;
}
