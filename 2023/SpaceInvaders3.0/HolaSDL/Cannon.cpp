#include "Cannon.h"
#include "PlayState.h" 

//Mueve el cañón y comprueba las vidas
void Cannon::Update()
{
	//Si no está en el margen izquierdo se mueve a la izquierda
	if (dirC == left && LeerPosX() >= margenCannon) {
		pos = pos - Vector2D<double>(speed, 0);
	}

	//Si no está en el margen derecho se mueve a la derecha
	else if (dirC == right && LeerPosX() <= game->GetWinWidth() - 3 * margenCannon) {
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
	out << " " << vida << " " << cooldown << std::endl;
}

//Si el disparo es de un alien y colisionan
bool Cannon::Hit(const SDL_Rect* r, bool o) {

	//Si dispara un alien y se chocan
	if (o && SDL_HasIntersection(r, GetRect()))
	{
		if (!invencible) {
			SceneObject::Hit(r, o);

			if (vida == 0) {
				//Fin de la partida
				_playState->isGameOver();
			}
		}
		else {
			//La invencibilidad dura un golpe
			invencible = false;
			std::cout << "No invencible";
		}
		return true;
	}

	return false;
}

//Renderiza la nave
void Cannon::Render() const
{
	textura->renderFrame(rect, textura->getNumRows() - 1, textura->getNumColumns() - 1);
}

void Cannon::HandleEvent(const SDL_Event& evento)
{
	//Cuando se pulsa la tecla
	if (SDL_KEYDOWN == evento.type) {

		//Se mueve hacia la izquierda
		if (SDLK_LEFT == evento.key.keysym.sym) { dirC = izquierda; }

		//Se mueve hacia la derecha
		else if (SDLK_RIGHT == evento.key.keysym.sym) { dirC = derecha; }

		//Disparamos si se pulsa el espacio y ha pasado el tiempo de enfriamiento
		else if (SDLK_SPACE == evento.key.keysym.sym && cooldown == maxCooldown) {
			//Disparamos y ponemos el contador a 0
			_playState->FireLaser(this->pos, false);
			cooldown = 0;
		}

	}	//Cuando se levanta la tecla
	else if (SDL_KEYUP == evento.type) { dirC = 0; }

	//Controlamos el contador para disparar
	if (cooldown < maxCooldown) { cooldown++; }
}
