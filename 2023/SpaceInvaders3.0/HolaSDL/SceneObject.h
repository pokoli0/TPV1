#pragma once
#include "GameObject.h"
#include "texture.h"
#include "checkML.h"

class PlayState;
class SceneObject: public GameObject
{
protected:
	Point2D<double> pos;						//Posición del objeto instanciado

	SDL_Rect rect;								//Rect de la imagen
	Texture* textura = nullptr;					//Puntero a la textura
	int vida;									//Vida del objeto

	PlayState* _playState = nullptr;			//Puntero al playState

	//Tamaño laser
	const int anchoLaser = 5,
		largoLaser = 25;

	//anchor
	GameList<SceneObject, true>::anchor sceneanc = nullptr;

public:

	//Constructora vacía
	SceneObject() {
		pos = Point2D<double>(0, 0);
		rect.h = rect.w = rect.x = rect.y = 0;
		vida = 1;
	}

	//Constructora
	SceneObject(SDLApplication* g, PlayState* ps, Point2D<double> p, Texture* t, int v)
	: GameObject(g, ps)
	{
		_playState = ps;
		pos = p;
		textura = t;
		vida = v;

		//inicializamos el rect dependiendo de la textura
		if (textura != nullptr) {
			rect.w = textura->getFrameWidth();
			rect.h = textura->getFrameHeight();
		}
		else {	//Si no tiene textura significa que es un laser
			rect.w = anchoLaser;
			rect.h = largoLaser;
		}
		
		//El objeto se dibuja en su posición
		rect.x = pos.LeerPosX();
		rect.y = pos.LeerPosY();
	}

	virtual bool Hit(const SDL_Rect* r, bool o);

	void save(std::ostream& out) const override;

	//Getters para las coordenadas
	const int LeerPosX() { return pos.LeerPosX(); }

	//Devuelve un puntero al rect del objeto
	const SDL_Rect* GetRect() const { return &rect; }

	void setListAnchor(GameList<SceneObject, true>::anchor newanc) // list<SceneObject*>::iterator& newit
	{
		// setea el iterador de la posicion del objeto en la lista
		sceneanc = newanc;
	};
};

