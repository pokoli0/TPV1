//Clase Bunker: contiene la posici�n del b�nker(tipo Point2D), el n�mero de vidas restantes y un puntero a
//su textura.Implementa un constructor, m�todos para dibujarse(m�todo render), para actualizarse(m�todo
//update) y para recibir da�o(m�todo hit).Cada vez que reciba da�o el n�mero de vidas ha de disminuir y
//la apariencia se ha de ajustar en consecuencia.El m�todo update devolver� false si el b�nker ha perdido
//todas sus vidas y eso provocar� que el juego lo elimine.

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

