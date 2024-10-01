//#include "Alien.h"
//#include "Game.h"
#include "MotherShip.h"

MotherShip::MotherShip(Game* game)
	:  GameObject(game), starTime(SDL_GetTicks()) { }

void MotherShip::SetMotherData(ifstream& entrada)
{
	entrada >> state >> level >> frameRate;
}


int MotherShip::getDirection() const
{
	return direction;
}

bool MotherShip::ShouldMove() const
{
	return shouldMove;
}

void MotherShip::cannotMove()
{
	canMove = false;
	state = 1;
}

void MotherShip::aliendDied()
{
	alienNum--;
}
void MotherShip::addAlien()
{
	alienNum++;
}
void MotherShip::SetAlienNum(const int num)
{
	alienNum = num;
}
void MotherShip::alienLanded()
{
	hasLanded = true; 
}

bool MotherShip::haveLanded() const
{
	return hasLanded;
}

int MotherShip::getAlienCount() const
{
	return alienNum;
}

void MotherShip::Render()
{}

void MotherShip::Update()
{

	if (shouldMove) //solo pueden moverse un frame.
		shouldMove = false;

	else if (SDL_GetTicks() - starTime >= frameRate)
	{
		shouldMove = true;
		starTime = SDL_GetTicks();

		if (!canMove)
		{
			direction = direction * (-1);
			canMove = true;
			level++;
			frameRate -= 70;
			lower = true;
		}

		else if (lower)
			lower = false;

	}




}

void MotherShip::Save(ostream & in) const
{
	in << "3 " << state << " " << level << " " << frameRate << endl;

}

bool MotherShip::shouldLower() const
{
	return lower;
}
