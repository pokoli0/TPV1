#pragma once
#include "GameObject.h"
#include "texture.h"
#include "Vector2D.h"
#include "list"

using namespace std;
class SceneObject : public GameObject
{
protected: 
	Point2D<double> pos;				//Posición

	SDL_Rect rect;						//Dimensiones de la imagen
	Texture* texture = nullptr;			//Puntero a la textura
	int vida;							//Vida restante
	list<SceneObject*>::iterator it;	//Crea a vector iterator
	
	
public:
	//Constructora vacía
	SceneObject()
	{
		pos = Point2D<double>(0, 0);
		rect.h = rect.w = rect.x = rect.y = 0;
		vida = 1;
	};

	//Constructora
	SceneObject(Game* j, Point2D<double> p, Texture* t, int v)
		: GameObject(j) 
	{
		pos = p;
		texture = t;

		//Inicializamos el rect en la constructora
		if (t != nullptr) {
			rect.w = texture->getFrameWidth();
			rect.h = texture->getFrameHeight();
		}
		else {	//Tamaño de los láseres
			rect.w = 5;
			rect.h = 25;
		}
			rect.x = pos.LeerPosX();
			rect.y = pos.LeerPosY();
		vida = v;
	}

	//Poner el virtual cuando vaya a usarlo en alguna clase
	virtual bool Hit(const SDL_Rect* r, bool o);

	void save(std::ostream& out) const override;

	//Getters para las coordenadas
	int LeerPosX() { return pos.LeerPosX(); }

	//Devuelve un puntero al rect del objeto
	const SDL_Rect* GetRect() const { return &rect; }

	//Iterador a una lista
	//setea el iterador de la posición del objeto en la lista
	void setListIterator(list<SceneObject*>::iterator& newit) { it = newit; }

};

