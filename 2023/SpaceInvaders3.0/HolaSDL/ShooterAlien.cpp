#include "ShooterAlien.h"
#include "PlayState.h"

void ShooterAlien::Update()
{
	Alien::Update();
	//Si llega a 0 disparamos y reiniciamos el coolDown
	if (coolDown <= 0) {
		_playState->FireLaser(this->pos, true);
		coolDown = _playState->getRandomRange(minCoolDown, maxCoolDown);
	}
	else { coolDown--; }
}

void ShooterAlien::save(std::ostream& out) const
{
	out << "2 ";
	SceneObject::save(out);
	out << " " << indice << " " << coolDown << std::endl;
}
