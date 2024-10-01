#include "SceneObject.h"

SceneObject::SceneObject(Game* g, int x, int y, Texture* t) : 
	GameObject(g), pos(x,y), text(t)
{}

SceneObject::SceneObject(Game * g, Texture * t, ifstream& in): GameObject(g), text(t)
{
	int x, y;
	in >> x >> y;
	pos = point2D(x, y);
	
}

bool SceneObject::Hit(SDL_Rect* OtherRect, char origin)
{
	if (SDL_HasIntersection(OtherRect, &rect))
	{
		return true;
	}
	return false;
}

void SceneObject::Render() 
{
	rect.x = pos.getX();
	rect.y = pos.getY();
}

void SceneObject::Update()
{}

void SceneObject::Save(ostream& in) const
{}

void SceneObject::SetListIterator(list<SceneObject*>::iterator i)
{
	iterator = i;
}

void SceneObject::setListAnchor(GameList<SceneObject, false>::anchor a)
{
	SceneAnchor = a; //o algo ns
}
