#include "SDLApplication.h"


void SDLApplication::Run()
{
	while (!exit) {

		//Controlamos el frame rate del juego
		int startLoop = SDL_GetTicks();

		//Bucle del propio juego
		HandleEvents();
		Update();
		Render();

		int delta = SDL_GetTicks() - startLoop;
		if (delta < desiredDelta) {
			SDL_Delay(desiredDelta - delta);
		}
	}
}

void SDLApplication::Render()
{
	

	//Dependiendo del estado en el que estemos ponemos un fondo u otro
	switch (_state) {
	case MENU: {
		//Ponemos el fondo del menú
		texturas[FONDOMENU]->render();
		break;
	}
	case PLAY: {
		//Ponemos el fondo del juego
		texturas[FONDOJUEGO]->render();
		break;
	}
	}

	_gameStateMachine->Render();
	SDL_RenderPresent(renderer);

	//Limpiamos la pantalla
	SDL_RenderClear(renderer);
}

SDLApplication::~SDLApplication()
{
	delete _gameStateMachine;
	for (const auto i : texturas) delete i;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Constructora
SDLApplication::SDLApplication()
{
	//Iniciamos todo
	SDL_Init(SDL_INIT_EVERYTHING);

	//Inicializa la ventana SDL
		window = SDL_CreateWindow("SpaceInvaders", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (window == nullptr || renderer == nullptr)
			throw "Error cargando SDL";

	if (!exit) {

		//Cargamos todo el estado inicial del juego
		Texturas();
		//Cambiamos a gameOver si no se han encontrado las texturas

		if (!exit) {
			//Inicializamos el estado actual al primer estado
			_state = MENU;

			//Creamos la máquina de estados
			_gameStateMachine = new GameStateMachine();

			//Le ponemos de estado inicial el menú de inciio
			_gameStateMachine->PushState(new MenuState(game));

			Render();
		}
	}
}

void SDLApplication::Texturas()
{
	//Raiz común de todas las texturas
	std::string textureRoot = "..\\images\\";
	std::string objectRoot = "..\\objetos\\";
	std::string textRoot = "..\\textos\\";
	std::string textura;

	//Struct con los datos de cada imagen a texturizar
	struct Imagen {
		std::string nombre;
		int filas;
		int columnas;
	};

	//Imagenes a texturizar
	//FONDOS
	Imagen _FondoMenu{ "..\\fondos\\mainMenu.png", 1, 1 };
	Imagen _FondoJuego{ textureRoot + "stars.png", 1, 1 };

	//OBJETOS
	Imagen _Nave{ textureRoot + "spaceship.png", 1, 1 };
	Imagen _Bunker{ textureRoot + "bunker.png", 1, 4 };
	Imagen _Alien{ textureRoot + "aliens.png", 3, 2 };
	Imagen _Ufo{ textureRoot + "ufo.png", 1, 2 };
	Imagen _Bomb{ objectRoot + "bomb.png", 1, 1 };
	Imagen _Shield{ objectRoot + "shield.png", 1, 1 };
	Imagen _S_Reward{ objectRoot + "shield_reward.png", 1, 1 };

	//TEXTOS
	Imagen _CargarPartida{ textRoot + "cargarPartida.png", 1, 1 };
	Imagen _Codigo{ textRoot + "codigo.png", 1, 1 };
	Imagen _Continuar{ textRoot + "continuar.png", 1, 1 };
	Imagen _GameOver{ textRoot + "gameOver.png", 1, 1 };
	Imagen _GuardarPartida{ textRoot + "guardarPartida.png", 1, 1 };
	Imagen _HasGanado{ textRoot + "hasGanado.png", 1, 1 };
	Imagen _NuevaPartida{ textRoot + "nuevaPartida.png", 1, 1 };
	Imagen _Salir{ textRoot + "salir.png", 1, 1 };
	Imagen _VolverAlMenu{ textRoot + "volverAlMenu.png", 1, 1 };

	//Creamos un array que contenga todas las imagenes (Para poder automatizarlo)
	std::array <Imagen, NUM_TEXTURES> Imagenes;
	//Fondos
	Imagenes[FONDOMENU] = _FondoMenu;
	Imagenes[FONDOJUEGO] = _FondoJuego;
	//Objetos
	Imagenes[NAVE] = _Nave;
	Imagenes[BUNKERS] = _Bunker;
	Imagenes[ALIENS] = _Alien;
	Imagenes[UFO] = _Ufo;
	Imagenes[BOMB] = _Bomb;
	Imagenes[SHIELD] = _Shield;
	Imagenes[S_REWARD] = _S_Reward;
	//Textos
	Imagenes[CARGARPARTIDA] = _CargarPartida;
	Imagenes[CODIGO] = _Codigo;
	Imagenes[CONTINUAR] = _Continuar;
	Imagenes[GAMEOVER] = _GameOver;
	Imagenes[GUARDARPARTIDA] = _GuardarPartida;
	Imagenes[HASGANADO] = _HasGanado;
	Imagenes[NUEVAPARTIDA] = _NuevaPartida;
	Imagenes[SALIR] = _Salir;
	Imagenes[VOLVERALMENU] = _VolverAlMenu;

	//Hacemos un array con las texturas
	for (int i = 0; i < NUM_TEXTURES; i++) {
		//Guardamos el nombre de la textura
		textura = Imagenes[i].nombre;
		texturas[i] = new Texture(renderer, textura.c_str(), Imagenes[i].filas, Imagenes[i].columnas);

		//Si no se puede crear la textura, lanzamos una excepción
		if (texturas[i] == nullptr) {
			throw "La textura " + textura + " no se ha encontrado";
		}
	}
}

void SDLApplication::Update() {

	_gameStateMachine->Update();
}

void SDLApplication::HandleEvents()
{
	SDL_Event evento;

	while (SDL_PollEvent(&evento) && !exit) {
		if (evento.type == SDL_QUIT) { exit = true; }
		else { _gameStateMachine->HandleEvent(evento); }
	}

}

void SDLApplication::ChangeState(int s) { _state = s; }
