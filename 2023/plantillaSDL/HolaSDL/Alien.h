//Clase Alien : contiene al menos la posici�n actual del alien�gena(tipo Point2D), el �ndice de su subtipo(de
//tipo int), un puntero a su textura y un puntero al juego.Este �ltimo es necesario para que el alien�gena
//conozca la direcci�n com�n de movimiento de todos sus semejantes y pueda informar de que ya no se
//puede desplazar m�s en ella(ver m�s abajo c�mo se maneja el desplazamiento).Implementa adem�s
//m�todos para construirse, dibujarse(m�todo render), actualizarse(m�todo update), y recibir da�o.En la
//actualizaci�n, adem�s de moverse, el alien�gena podr� disparar aleatoriamente un l�ser una vez trascurrido
//el periodo de recarga de su disparo anterior.El m�todo update devolver� false si el alien�gena ha sido
//alcanzado por un l�ser del ca��n

#pragma once
#include <string>
#include "MotherShip.h"
#include "SceneObject.h"


using uint = unsigned int;
using namespace std;

class Alien : public SceneObject
{
protected:
	const int SCORES[3] = { 30, 20, 10 }; //los disparadores valen 30, los verdes 20 y los rojos 10
	
	int subtipo;
	MotherShip* motherShip;
	bool posture = false; //para cambiar la postura
	int velocidad = 20;
	

public:
	

	void Lower();

	//finikitaos
	Alien(ifstream& in, Texture* t, Game* g, MotherShip* m);
	void Save(ostream& in) const override;
	bool Hit(SDL_Rect* OtherRect, char origin) override;

	//creo q finikitaos
	void Render() override;
	void Update() override;
};

