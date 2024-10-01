//Clase Alien : contiene al menos la posición actual del alienígena(tipo Point2D), el índice de su subtipo(de
//tipo int), un puntero a su textura y un puntero al juego.Este último es necesario para que el alienígena
//conozca la dirección común de movimiento de todos sus semejantes y pueda informar de que ya no se
//puede desplazar más en ella(ver más abajo cómo se maneja el desplazamiento).Implementa además
//métodos para construirse, dibujarse(método render), actualizarse(método update), y recibir daño.En la
//actualización, además de moverse, el alienígena podrá disparar aleatoriamente un láser una vez trascurrido
//el periodo de recarga de su disparo anterior.El método update devolverá false si el alienígena ha sido
//alcanzado por un láser del cañón

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

