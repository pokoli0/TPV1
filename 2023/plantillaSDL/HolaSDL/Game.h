/*Clase Game: contiene, al menos, el tama�o de la ventana, punteros a la ventana y al renderer, a los
elementos del juego (usa el tipo vector), el booleano exit, y el array de texturas (ver m�s abajo). Define
tambi�n las constantes que sean necesarias. Implementa m�todos p�blicos para inicializarse y destruirse,
el m�todo run con el bucle principal del juego, m�todos para dibujar el estado actual del juego (m�todo
render), actualizar (m�todo update), manejar eventos (m�todo handleEvents), obtener la direcci�n de
movimiento de los alien�genas (m�todo getDirection), informar de que no es posible moverse otra iteraci�n
m�s en la direcci�n actual (m�todo cannotMove) y disparar l�seres (m�todo fireLaser).
*/
#pragma once
#include "checkML.h"
#include <SDL.h>
#include <vector>
#include "texture.h"
#include <string>
#include <array> 
#include <random>
#include "InfoBar.h"
#include <list>
#include <queue>

using namespace std;

class SceneObject;
class Cannon;
class MotherShip;


class Game
{

public:
	//para q pueda usarse desde fuera
	enum textureName { STARS, MAINMENU,															       	   //fondos
					   SPACESHIP, BUNKER, ALIEN, UFO, SHIELD, SHIELD_EFFECT, BOMB,						   //objetos
					   NUMEROS, CARGAR_PARTIDA, CODIGO, CONTINUAR, GAMEOVER, GUARDAR_PARTIDA, HAS_GANADO,  //textos
					   NUEVA_PARTIDA, SALIR, VOLVER_AL_MENU}; 


private:
	//constantes
	static const int NUM_TEXTURES = 19, WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
	//const char* textRoot = "../images/"; //nos da error y no funciona. No es estrictamente necesaria asiq preferimos no usarla
	const string MAPAS [3] = {"../mapas/original.txt","../mapas/trinchera.txt","../mapas/lluvia.txt"};

	//cosas de SDL
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;



#pragma region cosas q van a ser de playstate (pero todavia no he borrado)
	mt19937_64 randomGenerator;
	std::list <SceneObject*> Objects;
	Cannon* cannon;
	MotherShip* motherShip;
	InfoBar* infoBar;
	bool exit = false;
	int score = 0;
#pragma endregion

	//cosas q borrar:
	queue <list<SceneObject*>::iterator> deadObjects;


#pragma region cosas de textura
	struct TextureInfo {
		const char* name;
		int framesVerticales;
		int framesHorizontales;
	};
	textureName textureIndex; //no, no hace falta. pero nos dice q lo usemos de todas maneras.

	TextureInfo textInfo[NUM_TEXTURES]{
		//fondos
		TextureInfo {"../images/fondos/stars.png", 1, 1},
		TextureInfo {"../images/fondos/mainMenu.png", 1, 1},
		//objetos
		TextureInfo {"../images/spaceship.png", 1, 1},
		TextureInfo {"../images/bunker.png", 1, 4},
		TextureInfo {"../images/aliens.png", 3, 2},
		TextureInfo {"../images/ufo.png", 1, 2},
		TextureInfo {"../images/shield.png", 1, 1},
		TextureInfo {"../images/shield_effect.png", 1, 1},
		TextureInfo {"../images/bomb.png", 1, 1},
		//textos
		TextureInfo {"../images/textos/numbers.png", 1, 10},
		TextureInfo {"../images/textos/cargarPartida.png", 1, 1},
		TextureInfo {"../images/textos/codigo.png", 1, 1},
		TextureInfo {"../images/textos/continuar.png", 1, 1},
		TextureInfo {"../images/textos/gameOver.png", 1, 1},
		TextureInfo {"../images/textos/guardarPartida.png", 1, 1},
		TextureInfo {"../images/textos/hasGanado.png", 1, 1},
		TextureInfo {"../images/textos/nuevaPartida.png", 1, 1},
		TextureInfo {"../images/textos/salir.png", 1, 1},
		TextureInfo {"../images/textos/volverAlMenu.png", 1, 1},
	};

	Texture* textureArray[NUM_TEXTURES]; //array est�tico
#pragma endregion


public:
	Game();
	~Game();
	

	int GetWindowWidth() const {return WINDOW_WIDTH;} 
	int GetWindowHeight() const { return WINDOW_HEIGHT;}
	SDL_Renderer* GetRenderer() const { return renderer;}
	Texture* GetTexture(textureName indx);
	void quit();
	void Run();
	
	




	//metodos del playstate:
	void UpdateVidas();
	void hasDied(list<SceneObject*>::iterator iterator);
	bool Attack(SDL_Rect* rect, char origin);
	void addScore(const int scoreToAdd);
	void fireLaser(const int x, const int y, const int dir, const char fromAlien);
	int RandomGenerator(int min, int max);
	//y la creadora y destructora pero tuneadas.
	void Render();
	void Update();
	void handleEvents();
	void readMap(const string filename);
	void save(const string);
	void AsignIterator();
	void DeleteDEadObjects();
	void load(const string filename);
	
};

