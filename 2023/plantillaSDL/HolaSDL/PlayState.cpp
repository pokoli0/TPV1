#include "PlayState.h"

PlayState::PlayState(Game* g, ifstream& in): GameState(g), motherShip(new MotherShip(g)), randomGenerator(time(nullptr))
{
	while (!in.fail())
	{
		ReadObject(in);
	}

	infobar = new InfoBar(game->GetTexture(Game::NUMEROS), game->GetTexture(Game::SPACESHIP), score, cannon->getLives());
}

void PlayState::ReadObject(ifstream& in)
{
	int numObjecto; 
	in >> numObjecto;

	if (!in.fail()) {

		SceneObject* aux = nullptr;
		switch (numObjecto) {
		case 0:		//cannon
			cannon = new Cannon(in, game->GetTexture(Game::SPACESHIP), game);
			GameState::addObjects(cannon);
			sceneObjects.push_back(cannon);
			GameState::addEventListener(cannon);
			break;

		case 1:		//alien
			motherShip->addAlien();
			aux = new Alien(in, game->GetTexture(Game::ALIEN), game, motherShip);
			GameState::addObjects(aux);
			sceneObjects.push_back(aux);
			break;

		case 2:		//shooter Alien
			motherShip->addAlien();
			aux = new ShooterAlien(in, game->GetTexture(Game::ALIEN), game, motherShip);
			GameState::addObjects(aux);
			sceneObjects.push_back(aux);
			break;

		case 3:		//mothership
			motherShip->SetMotherData(in);
			GameState::addObjects(motherShip);
			break;

		case 4:		//bunker
			aux = new Bunker(in, game->GetTexture(Game::BUNKER), game);
			GameState::addObjects(aux);
			sceneObjects.push_back(aux);
			break;

		case 5:		//alien
			aux = new Ufo(game->GetTexture(Game::UFO), game, in);
			GameState::addObjects(aux);
			sceneObjects.push_back(aux);
			break;

		case 6:		//laser
			aux = new Laser(game, in);
			GameState::addObjects(aux);
			sceneObjects.push_back(aux);

		case 7:		//score
			in >> score;
		}
	}
}

void PlayState::addScore(const int scoreToAdd)
{
	score += scoreToAdd;
	infobar->UpdateScore(score);
}

int PlayState::RandomGenerator(int min, int max)
{
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

void PlayState::render()
{
	GameState::render();
	infobar->Render();
}

void PlayState::update()
{
	GameState::update();

	if (cannon->getLives() <= 0 || motherShip->getAlienCount() == 0 || motherShip->haveLanded())
		game->quit();
}
