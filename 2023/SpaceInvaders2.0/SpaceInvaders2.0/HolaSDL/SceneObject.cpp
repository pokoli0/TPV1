#include "SceneObject.h"

bool SceneObject::Hit(const SDL_Rect* r, bool o)
{
	if (SDL_HasIntersection(r, GetRect()))
	{
		vida--;
		return true;
	}
	return false;
}

//Todos los objetos que se guarden van a guardar su posición
void SceneObject::save(std::ostream& out) const
{
	out << pos.LeerPosX() << " " << pos.LeerPosY();
}
