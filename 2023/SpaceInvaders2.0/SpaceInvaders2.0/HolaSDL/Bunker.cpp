#include "checkML.h"
#include "Bunker.h"
#include "Game.h"

void Bunker::Render() const
{
	texture->renderFrame(rect, texture->getNumRows() - 1, 4 - vida);
}

//Comprueba si el bunker sigue con vida
void Bunker::Update()
{
	if (vida == 0) {
		game->hasDied(it);
	}
}

void Bunker::save(std::ostream& out) const
{
	out << "4 ";
	SceneObject::save(out);
	out << " " << vida << endl;
}

