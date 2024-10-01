#pragma once
#include "SceneObject.h"

// El tiempo aleatorio que permanece oculto se puede determinar
//de la misma forma que el tiempo de disparo de los alienígenas en la práctica anterior.



class Ufo : public SceneObject
{
	enum states {hidden, visible, destroyed};
	states state = hidden;
	int waitTime, startTime;
	int velocidad = 10;

public:
	Ufo(Texture* texture, Game* game, int x, int y); 
	Ufo(Texture* texture, Game* game, ifstream& in);
	void Render() override;
	bool Hit(SDL_Rect* otherRect, char origin) override;
	void Save(ostream& out) const override;
	void Update() override;

private:
	void UfoDestroyed();
	void UfoHidden();
	
};

