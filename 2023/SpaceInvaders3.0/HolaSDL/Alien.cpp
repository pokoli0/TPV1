#include "Alien.h"
#include "PlayState.h"

//Renderiza el alien
void Alien::Render() const
{
	//Renderiza el frame que toque
	textura->renderFrame(rect, indice, frame % 2);
}

//Mueve al alien y comprueba si sigue vivo
void Alien::Update()
{
	//Si toca moverse se mueven
	if (mother->GetShouldMove()) {
		//Para que solo cambie de frame cuando se mueve el alien
		frame++;

		//Se mueven a la derecha
		if (mother->GetDirection() == 1)
		{
			pos = pos + Vector2D<double>(speed, 0) * (mother->Level() + 1);
		}
		else if (mother->GetDirection() == -1) { //Se mueven hacia la izquierda
			pos = pos - Vector2D<double>(speed, 0) * (mother->Level() + 1);
		}
		else {	//Se mueven hacia abajo
			pos = pos + Vector2D<double>(0, textura->getFrameHeight());

			//Si llega a la fila del cannon avisa a la mothersip
			if (pos.LeerPosY() >= alienHigh) { mother->AlienLanded(); }
		}

		//Comprobamos si en el siguiente ciclo se pueden seguir moviendo
		if (pos.LeerPosX() <= margenAlien || pos.LeerPosX() >= game->GetWinWidth() - 3 * margenAlien) {
			mother->CannotMove();
		}

		//Actualizamos  la posición de la textura
		rect.x = pos.LeerPosX();
		rect.y = pos.LeerPosY();

	}

}

//Guarda la posición del alien y su tipo
void Alien::save(std::ostream& out) const
{
	out << "1 ";
	SceneObject::save(out);
	out << " " << indice << std::endl;;
}

//Controla la colision
bool Alien::Hit(const SDL_Rect* r, bool o)
{
	//Si el disparo es de una nave y colisionan
	if (!o && SDL_HasIntersection(r, GetRect()))
	{
		SceneObject::Hit(r, o);
		mother->AlienDied();
		_playState->SetScore(AlienScore - minScore * indice);
		_playState->hasDied(sceneanc);
		return true;
	}
	return false;
}