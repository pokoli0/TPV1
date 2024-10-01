#include "PauseState.h"
#include "Button.h"

const std::string PauseState::_pauseID = "PAUSE";

void PauseState::Save()
{
	//Guarda la partida actual
	std::cout << "Ingrese el numero de la partida: " << std::endl;

	//Si se escribe algo distinto a un int, lanzar una excepción
	int k;
	std::cin >> k;

	//Ahora mismo si le pone un character distinto a un int lo guarda como 0
	std::string fileName = "saved" + std::to_string(k) + ".txt";

	_playState->Save(fileName);

	std::cout << "Su partida se ha guardado con el nombre " << fileName << std::endl;
	
}

void PauseState::Load()
{
	//Llama al método de change State para cambiar a playState pero tiene que cargar una partida nueva
	std::cout << "Escriba el numero de partida que desea cargar: " << std::endl;

	int k;
	std::cin >> k;
	if (k >= 0) {
		std::string fileName = "..\\mapas\\saved" + std::to_string(k) + ".txt";
		game->ChangeState(1);
		game->GetMachine()->ReplaceState(new PlayState(game, fileName));
	}
	else {
		std::cout << "El caracter no es válido, se reaunuda la partida" << std::endl;
	}
}

void PauseState::Home()
{
	game->GetMachine()->PopState();
	game->ChangeState(0);
	game->GetMachine()->ReplaceState(new MenuState(game));
}

void PauseState::Return()
{
	game->GetMachine()->PopState();
}

PauseState::PauseState(SDLApplication* game, PlayState* p)
	: GameState(game)
{
	_playState = p;
	
	_saveButton = new Button(game, this, game->GetTexture(GUARDARPARTIDA), game->GetRenderer(), Point2D<double>(columna, fila));
	_loadButton = new Button(game, this, game->GetTexture(CARGARPARTIDA), game->GetRenderer(), Point2D<double>(columna, fila + margen));
	_homeButton = new Button(game, this, game->GetTexture(VOLVERALMENU), game->GetRenderer(), Point2D<double>(columna, fila + margen * 2));
	_returnButton = new Button(game, this, game->GetTexture(CONTINUAR), game->GetRenderer(), Point2D<double>(columna, fila + margen * 3));

	AddObject(_saveButton);
	AddObject(_loadButton);
	AddObject(_homeButton);
	AddObject(_returnButton);

	AddEventListener(_saveButton);
	AddEventListener(_loadButton);
	AddEventListener(_homeButton);
	AddEventListener(_returnButton);

	_saveButton->Connect([this]() {Save(); });
	_loadButton->Connect([this]() {Load(); });
	_homeButton->Connect([this]() {Home(); });
	_returnButton->Connect([this]() {Return(); });
}

void PauseState::Render()
{
	//Hacemos el render de todos los botones en escena
	for (GameObject& g : gameList) {
		g.Render();
	}
}

bool PauseState::OnEnter()
{
	std::cout << "Entrando al PauseState" << std::endl;
	return true;
}

bool PauseState::OnExit()
{
	std::cout << "Saliendo del PauseState" << std::endl;
	return true;
}


