//Clase Bunker: contiene la posición del búnker(tipo Point2D), el número de vidas restantes y un puntero a
//su textura.Implementa un constructor, métodos para dibujarse(método render), para actualizarse(método
//update) y para recibir daño(método hit).Cada vez que reciba daño el número de vidas ha de disminuir y
//la apariencia se ha de ajustar en consecuencia.El método update devolverá false si el búnker ha perdido
//todas sus vidas y eso provocará que el juego lo elimine.

#pragma once
#include "SceneObject.h"
#include <string>
using namespace std;

class Bunker : public SceneObject
{
private:
	int vidas;


public:
	Bunker(ifstream& in, Texture* tx, Game* g); //para inicializar

	void Render() override;
	void Update() override;
	bool Hit(SDL_Rect* otherRect, char origin) override;
	void Save(ostream& out) const override;
	SDL_Rect* getSDLRect();
};

