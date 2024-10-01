
#include "Game.h"
#include <SDL_image.h>
#include "ShooterAlien.h"
#include "Bunker.h"
#include "Laser.h"
#include "Cannon.h"
#include "Ufo.h"
#include <ctime>
#include <fstream>
//#include <filesystem>
//using uint = unsigned int;


//constructora. Carga las texturas, crea la ventana, el renderer y el randomGenerator, crea los objetos (en sus posiciones correctas)
Game::Game(): randomGenerator(time(nullptr)) {

	//las cosas de SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SPACE INVADERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)  //si no encuentra:
		throw string ("Error loading SDL window or renderer");

	
	//cargar texturas
	try {
		for (int i = 0; i < NUM_TEXTURES; i++) {
			textureArray[i] = new Texture(renderer, textInfo[i].name,			//renderer, nombre
				textInfo[i].framesVerticales, textInfo[i].framesHorizontales);  //numero de frames
		}
	} catch (string e) { throw string("archivo de textura no encontrado o no válido"); }
	catch (exception e) { throw string("problema al cargar la textura"); }
	
	motherShip = new MotherShip(this);
	readMap(MAPAS[0]);
	AsignIterator();
	infoBar = new InfoBar(textureArray[NUMEROS], textureArray[SPACESHIP], score, cannon->getLives());
	
}

//lee la informacion de un mapa (no una partida guardada)
void Game::readMap(const string filename)
{
	ifstream entradaMapa; entradaMapa.open(filename);	
	if(!entradaMapa.is_open())
		throw string("fichero de mapa no encontrado");


	int numObjeto;
	entradaMapa >> numObjeto;

	//cañón
	textureIndex = SPACESHIP;
	if (numObjeto == 0)
	{
		cannon = new Cannon(entradaMapa, textureArray[textureIndex], this);
		Objects.push_back(cannon);
	}
	else
		throw string("como vas a tener un mapa sin cañón alma de cántaro");
	
	//aliens
	entradaMapa >> numObjeto;
	textureIndex = ALIEN; 
	int alienNum = 0; //para pasarle el número de aliensa a mothership
	while (numObjeto == 1)
	{
		alienNum++;
		Objects.push_back(new Alien(entradaMapa, textureArray[textureIndex], this, motherShip));
		motherShip->addAlien();
		entradaMapa >> numObjeto;
	}
	while (numObjeto == 2)
	{
		alienNum++;
		Objects.push_back(new ShooterAlien(entradaMapa, textureArray[textureIndex], this, motherShip));
		motherShip->addAlien();
		entradaMapa >> numObjeto;
	}
	
	
	//bunkers
	textureIndex = BUNKER;
	while (numObjeto == 4)
	{
		Objects.push_back(new Bunker(entradaMapa, textureArray[textureIndex], this));
		entradaMapa >> numObjeto;
	}

	//UFO (si hay)
	textureIndex = UFO;
	if (numObjeto == 5)
	{
		Objects.push_back(new Ufo(textureArray[textureIndex], this, entradaMapa));
		entradaMapa >> numObjeto;
	}
	else
		Objects.push_back(new Ufo(textureArray[textureIndex], this, WINDOW_WIDTH, 40));

	//laseres (si hay)
	if (numObjeto == 6)
	{
		Objects.push_back(new Laser(this, entradaMapa));
		entradaMapa >> numObjeto;
	}

	//motherShip (si hay)
	if (numObjeto == 3)
	{
		motherShip->SetMotherData(entradaMapa);
	}

	//score (si hay)
	if (numObjeto == 7)
		entradaMapa >> score;
}

void Game::Render() {
	try {
		SDL_RenderClear(renderer);

		//fondo
		textureIndex = STARS;
		textureArray[textureIndex]->render();


		// los objetos
		for (SceneObject* SO : Objects)
			SO->Render();

		infoBar->Render();

		//mostrarlo
		SDL_RenderPresent(renderer);
	}
	catch (exception e) { throw string("ha ocurrido un problema con el render. Probablemente culpa de SDL."); }
}

void Game::Run() { 
	while (!exit)
	{
		Render();
		Update();
		handleEvents();

		SDL_Delay(50);
	}
}

void Game::UpdateVidas()
{
	infoBar->UpdateVidas();
}

void Game::Update() {

	for (auto const& SO : Objects)
		SO->Update();
	motherShip->Update();


	if (cannon->getLives() == 0 || motherShip->haveLanded() ||motherShip->getAlienCount() == 0) //pierdes el cañón, mueres. aliens landed= mueres. aliens 0, acaba el juego
		quit();

	DeleteDEadObjects();
}

//si el evento es alguno de los que nos interesan, se lo pasa a cannon o lo ejecuta
void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		
		//si se ha pulsado una tecla
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) quit();//si es esc se cierra
			else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT //si son las flechas
				|| event.key.keysym.sym == SDLK_SPACE) //o el espacio, se lo pasas a cannon
				cannon->handleEvent(event);

			else if (event.key.keysym.sym == SDLK_s) //guardar
			{
				int num;
				cin >> num;
				if (!cin.fail())
					save("saved" + to_string(num) + ".txt");
			}	

			else if (event.key.keysym.sym == SDLK_l) //leer partida
			{
				int num;
				cin >> num;
				if (!cin.fail())
					load("saved" + to_string(num) + ".txt");

			}
		}

		//si se suelta una tecla
		else if (event.type = SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT) //si son las flechas te dejas de mover
				cannon->handleEvent(event);
		}
	}
}

//suma scoretoadd a la score y se la pasa a infobar para q la actualice
void Game::addScore(const int scoreToAdd)
{
	score += scoreToAdd; 
	infoBar->UpdateScore(score);

}

void Game::hasDied(list<SceneObject*>::iterator iterator)
{
	deadObjects.push(iterator);
}

bool Game::Attack(SDL_Rect* rect, char origin)
{
	bool hasHit = false;
	

	for (list<SceneObject*>::iterator it = Objects.begin();!hasHit && it != Objects.end() ;it++) {
		hasHit = (*it)->Hit(rect, origin);
	}

	return hasHit;
}



void Game::fireLaser(const int x, const int y, const int dir, const char fromAlien) {

	Objects.push_back(new Laser(this, x, y, dir, fromAlien));

	list<SceneObject*>::iterator it = Objects.end();
	it--;
	(*it)->SetListIterator(it);
}

//genera un entero aleatorio entre min y max
int Game::RandomGenerator(int min, int max)
{
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

Texture* Game::GetTexture(textureName indx)
{
	return textureArray[(int) indx];
}

//cambia exit a false para que se acabe el bucle de juego
void Game::quit() {

	exit = true;
}

//destructora
Game::~Game()
{
	for (SceneObject* SO : Objects)
		delete SO;

	delete infoBar;
	delete motherShip;

	for (int i = 0; i < NUM_TEXTURES; i++)
		delete textureArray[i];

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::save(const string filename) {
	fstream out; 

	out.open(filename, std::ios_base::out); 
	if (!out.is_open()) {
		throw string("failed to save");
	}

	for (auto const& SO : Objects)
		SO->Save(out);

	motherShip->Save(out);
	
	//puntuacion
	out << "7 " << score << endl;

	out.close();
}

void Game::AsignIterator()
{
	for (list<SceneObject*>::iterator it = Objects.begin();it != Objects.end(); it++ ) {
		(*it) -> SetListIterator(it);
	}
}

void Game::DeleteDEadObjects()
{
	// eri terrotista
	while (deadObjects.size() > 0)
	{
		delete (*(deadObjects.front()));
		Objects.erase(deadObjects.front());
		deadObjects.pop();

	}
	
}

void Game::load(const string filename)
{

	list<SceneObject*>::iterator it = Objects.begin();
	while (it != Objects.end())
	{
		delete* it;
		it = Objects.erase(it);
	}

	readMap(filename);
	AsignIterator();
	infoBar->SetInfo(cannon->getLives(), score);

}
