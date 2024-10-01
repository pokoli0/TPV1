#include "EndState.h"
#include "Button.h"

const std::string EndState::_endID = "END";

void EndState::Home()
{
	game->ChangeState(0);
	game->GetMachine()->ReplaceState(new MenuState(game));
}

void EndState::Exit()
{
	//Hacemos que salir sea igual a true
	game->SetExit(true);
}

EndState::EndState(SDLApplication* g, Texture* t): GameState(g)
{
	textura = t;

	rect.x = columna;
	rect.y = fila;

	rect.w = textura->getFrameWidth();
	rect.h = textura->getFrameHeight();

	_exitButton = new Button(game, this, game->GetTexture(SALIR), game->GetRenderer(), Vector2D<double>(columna, fila + margen * 2));
	_homeButton = new Button(game, this, game->GetTexture(VOLVERALMENU), game->GetRenderer(), Vector2D<double>(columna, fila + margen));

	//Añadimos los botones a la lista de objetos
	AddObject(_exitButton);
	AddObject(_homeButton);

	//Lo añadimos a la lista de oyentes
	AddEventListener(_exitButton);
	AddEventListener(_homeButton);

	//Añadimos los callbacks de los botones
	_homeButton->Connect([this]() {Home(); });
	_exitButton->Connect([this]() {Exit(); });
}

void EndState::Render()
{
	//Texto de ganar o perder
	textura->renderFrame(rect, textura->getNumRows() - 1, textura->getNumColumns() - 1);

	//Hacemos el render de todos los botones en escena
	for (GameObject& g : gameList) {
		g.Render();
	}
}

bool EndState::OnEnter()
{
	std::cout << "Entrando al EndState" << std::endl;
	return true;
}

bool EndState::OnExit()
{
	std::cout << "Saliendo del EndState" << std::endl;
	return true;
}
