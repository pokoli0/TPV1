#include "ShooterAlien.h"
#include "Game.h"

void ShooterAlien::Update()
{
	Alien::Update();
		//Si llega a 0 disparamos y reiniciamos el coolDown
		if (coolDown <= 0) {
			game->FireLaser(this->pos, true);
			coolDown = getRandomRange(minCoolDown, maxCoolDown);
		}
		else {
			coolDown--;
		}
  
}

void ShooterAlien::save(std::ostream& out) const
{
	out << "2 ";
	SceneObject::save(out);
	out << " " << indice << " " << coolDown << endl;
}

int ShooterAlien::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(random);
}
