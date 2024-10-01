#include "MotherShip.h"

void MotherShip::Render() const { }

void MotherShip::Update() { }

void MotherShip::save(std::ostream& out) const
{
	out << "3 ";
	out << " " << dir << " " << level << std::endl;

}

void MotherShip::ShouldMove()
{
	//Si el temporizador llega a 0 les toca moverse -> return true
	if (alienTimer <= 0)
	{
		//Si se han movido hacia abajo
		if (dir == down || dir == -down) {
			cannotMove = false;
			//Vuelve dir a la dirección que tenía al bajar y la cambia
			dir = (dir / down) * -1;

			//A lo mejor es demasiado aumento
			level += aumentoLevel;
		}
		//Si no se pueden mover hacemos que vaya hacia abajo
		if (cannotMove) {
			dir *= down;
		}
		//Si es menor o igual a 0 se mueven
		alienTimer = ALIENS_UPDATE;
		shouldMove = true;
	}
	else {
		alienTimer--;
		shouldMove = false;
	}
}

void MotherShip::AlienDied() {

	alienCount--; 
}
