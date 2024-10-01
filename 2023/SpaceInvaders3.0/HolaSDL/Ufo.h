#pragma once
#include "SceneObject.h"
#include "checkML.h"

class Ufo: public SceneObject
{
private:
	enum state { oculto, destruido, visible };
	int estado = oculto;			//Estado del ovni

	int minCoolDown = 250,
		maxCoolDown = 750;

	int cont = 0;					//Contador del tiempo en oculto
	const int speed = 3,
	 UFOScore = 100;				//Puntos que se consiguen cuando le das al ufo

	int rewardProb;					//Probabilidad de que te caiga un objeto
	int minProbReward = 1,
		maxProbReward = 4;

	//Posición original del ufo
	const int originalX = 800,
		originalY = 10;

public:
	//Constructora vacia
	Ufo() : SceneObject() {}

	//Constructora
	Ufo(SDLApplication* j, PlayState* ps, Point2D<double> p, Texture* t, int v, int e, int c)
		: SceneObject(j, ps, p, t, v) {
		estado = e;
		cont = c;
	}

	void Render() const override;

	void Update() override;

	void save(std::ostream& out) const override;

	bool Hit(const SDL_Rect* r, bool o) override;
};

