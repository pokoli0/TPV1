/*Clase Laser: contiene su posici�n (tipo Point2D), una velocidad (tipo Vector2D) y un booleano que indica
si procede de un alien�gena o de la nave que controla el jugador. Implementa m�todos para construirse,
dibujarse (render) y actualizarse (m�todo update). La actualizaci�n consiste en avanzar de acuerdo a
su velocidad y comprobar si ha acertado a alg�n objetivo. Los l�seres lanzados por el jugador hieren a
los alien�genas, mientras que los lanzados por los alien�genas da�an al jugador. Los l�seres hieren a los
b�nkeres independientemente de su origen. Cuando dos disparos de origen distinto se cruzan se anulan
mutuamente. Se pueden dibujar como un rect�ngulo de color con SDL_RenderFillRect.
*/
#pragma once
#include "SceneObject.h"
#include <string>
using namespace std;

//class Game;


class Laser : public SceneObject
{
private:
	static const int LASER_WIDTH = 5, LASER_HEIGHT = 20; //para el rectangulo
	Vector2D<> velocidad;
	char color; //r for cannon, b for alien

	SDL_Renderer* renderer;
	bool Attack();



public:
	Laser(Game* g, int x, int y, int dir, char color);
	Laser(Game* g, ifstream& in);

	void Render();
	void Update() override;
	bool Hit(SDL_Rect* OtherRect, char origin) override;


	void Save(ostream& in) const override;
};

