/*Clase Cannon : al igual que los anteriores, sus atributos incluyen su posición actual, un puntero a su textura y
un puntero al juego(que utilizará para lanzar láseres).Además, mantiene la dirección actual del movimiento,
el número de vidas que le quedan y el tiempo restante de recarga del láser.Implementa también métodos
para construirse, dibujarse(render), actualizarse, es decir, moverse(método update), recibir daño(método
hit) y manejar eventos del teclado(método handleEvent), que determinan el estado de movimiento y
permiten lanzar el láser(barra espaciadora).*/

#pragma once
#include "SceneObject.h"
#include "EventHandler.h"
#include <string>
using uint = unsigned int;
using namespace std;

//class Game;

class Cannon : public SceneObject, public EventHandler
{
private:
	int direccion = 0;
	int vidas = 3;
	int TiempoRecarga = 700;
	uint lastTimeShoot;

	const int VELOCIDAD = 30;

public:
	Cannon(ifstream& in, Texture* tx, Game* g);
	//este creo q lo tenemos
	void handleEvent(SDL_Event event);
	

	//metodos q ya tenemos:
	int getLives() const { return vidas; }
	void Update() override;
	void Render() override;
	bool Hit(SDL_Rect* OtherRect, char origin) override;
	void Save(ostream& out) const  override;

private: //metodos privados
	//este hay q ver q hacemos
	void TryToShoot();
};

