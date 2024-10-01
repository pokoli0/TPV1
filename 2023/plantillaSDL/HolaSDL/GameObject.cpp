#include "GameObject.h"
#include "GameObject.h"
#include <iostream>

using namespace std;


GameObject::GameObject(Game* g) : game (g), Anchor() {}

void GameObject::setListAnchor(GameList<GameObject, true>::anchor a)
{
	Anchor = a;
}

void GameObject::Render()
{}

void GameObject::Update() 
{}

void GameObject::Save(ostream& in) const
{}

GameObject::~GameObject()
{}
