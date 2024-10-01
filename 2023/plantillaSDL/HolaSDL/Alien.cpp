#include "Alien.h"
#include "Laser.h"


Alien::Alien(ifstream& in, Texture* t, Game* g, MotherShip* m) : SceneObject(g, t, in), posture(pos.getX()%2 == 0), motherShip(m)
{
	rect.w = text->getFrameWidth();
	rect.h = text->getFrameHeight();
	in >> subtipo;
}

void Alien::Render()
{
	SceneObject::Render();
	text->renderFrame(rect, subtipo, (int) posture);
}
void Alien::Update()
{
	if (motherShip->ShouldMove())
	{
		if (!motherShip->shouldLower())		//si este turno no nos toca bajar
		{
			int direction = motherShip->getDirection();
			posture = !posture;					//cambiamos de postura en cada iteraccion
			pos = pos + Vector2D<>(direction * velocidad, 0);

			//bienvenido profe al mayor if del mundo
			if ((direction < 0 && pos.getX() <= velocidad)						//si van hacia la izquierda y no cabrian en la siguiente iteracion
				|| (direction > 0 && pos.getX() > game->GetWindowWidth() - text->getFrameWidth() - velocidad)) //o hacia la derecha
				motherShip->cannotMove();

		}
		else
			Lower();
		

	}
}
bool Alien::Hit(SDL_Rect* OtherRect, char origin) {

	if (origin == 'r' && SceneObject::Hit(OtherRect, origin))
	{
		game->hasDied(iterator);
		motherShip->aliendDied();
		game->addScore(SCORES[subtipo]);
		return true;
	}

	return false;
}


void Alien::Lower()
{
	pos = pos + Vector2D<>(0, text->getFrameHeight());
	if (pos.getY() >= 500)
		motherShip->alienLanded();
}

void Alien::Save(ostream& in) const
{
	in << "1 " << pos.getX() << " " << pos.getY() << " " << subtipo << endl;
}
