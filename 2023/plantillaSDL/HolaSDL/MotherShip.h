#pragma once;
#include "GameObject.h"
using uint = unsigned int;


//enum state {}; //estado de movimiento , ser� c�clico ?�?�

class MotherShip : public GameObject
{
private: 
	uint frameRate = 1000, starTime;
	int direction = 1;
	bool shouldMove = true, canMove = true, hasLanded = false, lower = false;
	int alienNum = 0;

	//0=derecha, 1=cambiando, 2=izquierda
	int state;

	int level= 1; //nivel de descenso, que afectar a la velocidad de los alien�genas

public: 
	MotherShip(Game* g);
	void SetMotherData(ifstream& entrada);
	void SetAlienNum(const int num);
	int getDirection() const;
	bool ShouldMove() const;
	void cannotMove();
	void aliendDied();
	void addAlien();
	void alienLanded();
	bool haveLanded() const;

	int getAlienCount() const;
	bool shouldLower() const;
	void Render() override;
	void Update() override;
	void Save(ostream& in) const override;
};
