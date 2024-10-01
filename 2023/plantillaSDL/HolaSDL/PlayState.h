#pragma once
#include "GameState.h"
#include "Cannon.h"
#include "InfoBar.h"
#include "ShooterAlien.h"
#include "Bunker.h"
#include "Ufo.h"
#include "Laser.h"


class PlayState: public GameState
{
private:
	GameList<SceneObject, false> sceneObjects;

	Cannon* cannon;
	MotherShip* motherShip;
	InfoBar* infobar;

	int score = 0;
	mt19937_64 randomGenerator;


public:

	//implementados:
	PlayState(Game* g, ifstream& in);



	void ReadObject(ifstream& in);
	void render() override;
	void update() override;

	//pendientes:
	void UpdateVidas();
	void hasDied(list<SceneObject*>::iterator iterator);
	bool Attack(SDL_Rect* rect, char origin);
	void addScore(const int scoreToAdd);
	void fireLaser(const int x, const int y, const int dir, const char fromAlien);
	int RandomGenerator(int min, int max);
	//y la destructora tuneada
	void handleEvents();
	void save(const string);
	void load(const string filename);
};

