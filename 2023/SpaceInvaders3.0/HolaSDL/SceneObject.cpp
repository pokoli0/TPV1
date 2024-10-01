#include "SceneObject.h"
#include "PlayState.h"

//Le restamos vida si es golpeado
bool SceneObject::Hit(const SDL_Rect* r, bool o)
{
    vida--;
    return true;
}

//Guardamos la pos del objeto
void SceneObject::save(std::ostream& out) const
{
    out << pos.LeerPosX() << " " << pos.LeerPosY();
}
