#include "Bunker.h"
#include "PlayState.h"


void Bunker::Render() const
{
	textura->renderFrame(rect, textura->getNumRows() - 1, maxVida - vida);
}

 bool Bunker::Hit(const SDL_Rect* r, bool o)
{
	//Al ser un bunker nos da igual el origen del laser
	 if (SDL_HasIntersection(r, GetRect())) { 
		 SceneObject::Hit(r, o);
		 //Si se queda sin vidas llama al hasDied del estado en el que está
		 if (vida == 0) { _playState->hasDied(sceneanc); }
		 return true; 
	 }

	return false;
	
}

void Bunker::save(std::ostream& out) const
{
	out << "4 ";
	SceneObject::save(out);
	out << " " << vida << std::endl;
}
