#pragma once
#include <fstream>
#include <SDL.h>
#include "Game.h"
#include "gameList.h"
using namespace std;


class GameObject
{
protected: 
	Game* game; 
	GameList<GameObject, true>::anchor Anchor;


public: 
	GameObject(Game* g);
	void setListAnchor(GameList<GameObject, true>::anchor a);
	virtual void Render();
	virtual void Update();
	virtual void Save(ostream& in) const;
	virtual ~GameObject();
};

