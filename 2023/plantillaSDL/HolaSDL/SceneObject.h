#pragma once
#include "checkML.h"
#include "vector2D.h"
#include "texture.h"
#include "GameObject.h"
#include <ostream>


class SceneObject: public GameObject
{
protected: 
	point2D pos;
	int width, height, vidas;
	SDL_Rect rect; 
	Texture* text; 
	list<SceneObject*>::iterator iterator; //iterador time D:
	GameList<SceneObject, false>::anchor SceneAnchor;

	

public: 
	//constructoras
	SceneObject(Game* g, int x, int y, Texture* t);
	SceneObject(Game* g, Texture* t, ifstream& in);

	//metodos
	virtual bool Hit(SDL_Rect* OtherRect, char origin);
	virtual void Render() override;
	virtual void Update() override;
	virtual void Save(ostream& in) const override;

	//SETTER HAY Q BORRARLO
	void SetListIterator(list<SceneObject*>::iterator i);
	void setListAnchor(GameList<SceneObject, false>::anchor a);

	//GETTERS
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getLives() const { return vidas; }
	Texture* getTexture() const { return text; }
	SDL_Rect* getRect() { return &rect; }

};

