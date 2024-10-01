#include "checkML.h"
#include "Cannon.h"
#include "Game.h"

//Mueve el cañón y comprueba las vidas
void Cannon::Update()
{
	//Si se acaban las vidas devuelve false
	if (vida == 0) { 
		game->IsGameOver();
	}

	//Si no está en el margen izquierdo se mueve a la izquierda
	if (dirC == left && LeerPosX() >= margenCannon) {
		pos = pos - Vector2D<double>(speed, 0);
	}

	//Si no está en el margen derecho se mueve a la derecha
	else if (dirC == right && LeerPosX() <= game -> GetWinWidth() - 3 * margenCannon) {
		pos = pos + Vector2D<double>(speed, 0);
	}

	//Actualizamos la pos rel rect
	rect.x = pos.LeerPosX();
	rect.y = pos.LeerPosY();

}

void Cannon::save(std::ostream& out) const
{
	out << "0 ";
	SceneObject::save(out);
	out << " " << vida << " " << cooldown << endl;
}

//Si el disparo es de un alien y colisionan
bool Cannon::Hit(const SDL_Rect* r, bool o) {
	
	//Si dispara un alien y se chocan
	if (o && SDL_HasIntersection(r, GetRect()))
	{ 
		vida--; 
		return true;
	}

	return false;
}

//Renderiza la nave
void Cannon::Render() const
{
	//Renderizamos la nave	
	texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - 1);
}

void Cannon::HandleEvent(SDL_Event evento)
{
	//Cuando se pulsa la tecla
	if (SDL_KEYDOWN == evento.type) {

		//Se mueve hacia la izquierda
		if (SDLK_LEFT == evento.key.keysym.sym) { dirC = 1; }

		//Se mueve hacia la derecha
		else if (SDLK_RIGHT == evento.key.keysym.sym) { dirC = 2; }

		//Disparamos si se pulsa el espacio y ha pasado el tiempo de enfriamiento
		else if (SDLK_SPACE == evento.key.keysym.sym && cooldown == maxCooldown) {
			//Disparamos y ponemos el contador a 0
			game->FireLaser(this->pos, false);
			cooldown = 0;
		}

	}	//Cuando se levanta la tecla
	else if (SDL_KEYUP == evento.type) { dirC = 0; }

	//Controlamos el contador para disparar
	if (cooldown < maxCooldown) { cooldown++; }
}
