#include "PlayState.h"

const std::string PlayState::_playID = "PLAY";

void PlayState::Update()
{
	if (mothership->GetAlienCount() == 0) {
		YouWin();
	}
	else {
		// Si aun quedan aliens seguimos jugando
		mothership->ShouldMove();
		//recorremos la lista de elementos del juego
		for (SceneObject& a : sceneObjectsList) {
			a.Update();
		}
	}
	
}

void PlayState::Render()
{
	//recorremos la lista de elementos del juego
	for (SceneObject& a : sceneObjectsList) {
		a.Render();
	}
}

void PlayState::Mapas(std::string file)
{
#pragma region Incio

	//Inicializamos todos los elementos para los objetos a crear
	int elem,							//Indica que vamos a crear
		posX, posY,						//Indica la posicion en la que se encuentra
		indice,							//Tipo de alien a crear
		aux,
		frame = 0;						//Para la animación de los aliens

	SceneObject* o = nullptr;			//objeto a crear
#pragma endregion

	//Abrimos el archivo a leer
	std::ifstream Mapa(file);

	//Si no encuentra el archivo lanzamos una excepción
	if (Mapa.fail()) {
		//throw FileNotFoundError("No se ha podido encontrar el archivo llamado "s + file);
	}

	//Mientras no haya terminado el archivo
	while (!Mapa.eof()) {

		//Leemos que tenemos que crear y su pos
		Mapa >> elem;
		Mapa >> posX;
		Mapa >> posY;
		Point2D<double> pos(posX, posY);		//Creamos la pos del objeto

		if (elem == bunker) {
			//para leer las vidas
			Mapa >> aux;
			o = new Bunker(game, this, pos, game->GetTexture(BUNKERS), aux);
		}
		else if (elem == laser) {
			Mapa >> aux;
			o = new Laser(game, this, pos, nullptr, 1, game->GetRenderer(), aux);
		}
		else if (elem == alien || elem == shooterAlien) {
			Mapa >> indice;
			if (elem == shooterAlien) {
				//Lo utilizamos para el coolDown
				Mapa >> aux;
				o = new ShooterAlien(game, this, pos, game->GetTexture(ALIENS), mothership, 1, indice, frame, aux);
			}
			else {
				o = new Alien(game, this, pos, game->GetTexture(ALIENS), mothership, 1, indice, frame);
			}
			frame++;
		}
		else if (elem == ufo) {
			//Usamos indice para guardar el estado
			Mapa >> indice;
			//Usamos aux para guardar la espera
			Mapa >> aux;
			o = new Ufo(game, this, pos, game->GetTexture(UFO), 1, indice, aux);
		}
		else if (elem == cannon) {
			//Lo usamos para guardar las vidas de la nave
			Mapa >> indice;
			//Lo usamos para guardar el cooldown
			Mapa >> aux;
			nave = new Cannon(game, this, pos, game->GetTexture(NAVE), indice, aux);
			o = nave;
			//Añadimos el canon a los oyentes de eventos
			AddEventListener(nave);
		}
		sceneObjectsList.push_back(o);

		//Elementos que no se añaden a la lista
		if (elem == mother) {
			//Sirve para indicar la dirección del mov
			Mapa >> elem;
			//Sirve para indicar el nivel
			Mapa >> aux;
			mothership->SetMove(elem);
			mothership->SetLevel(aux);
		}
		//También contamos la puntuación
		if (elem == puntos) {
			//Guardamos los puntos actuales
			Mapa >> ScorePlayer;
		}
	}
	//Le decimos a mothership cuantos aliens hay
	mothership->SetAlienCount(frame);

	Mapa.close();
}

void PlayState::Save(const std::string& saveFileName) const
{
	//Creamos un archivo donde vayamos a guardar los datos
	std::ofstream save(guardadoRoot + saveFileName);
	//si no se encuentra el archivo
	if (save.fail())
		//throw FileNotFoundError("No se puede leer el archivo llamado"s + saveFileName);

	//Guardamos el mothership
	mothership->save(save);

	//Guardamos los diferentes datos en el archivo
	for (GameList<SceneObject, true>::forward_iterator i = sceneObjectsList.begin(); i != sceneObjectsList.end(); ++i) {
		(*i).save(save);
	}

	//Guardamos los puntos
	save << "7 " << ScorePlayer << std::endl;

	save.close();
}

int PlayState::getRandomRange(int min, int max)
{
	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}

void PlayState::HandleEvent(const SDL_Event& event)
{
	//Llamamos a los eventos adscritos al gameState
	GameState::HandleEvent(event);

	if (SDL_SCANCODE_ESCAPE == event.key.keysym.scancode) {
		//Si el estado es igual a play permitimos entrar al menú de pausa
		game->GetMachine()->PushState(new PauseState(game, this));
	}
}

void PlayState::SetScore(int s)
{
	//Sumamos a la puntuación actual los puntos que se consigan
	ScorePlayer += s;

	//Hacemos que escriban los puntos en consola
	std::cout << "Score: " << ScorePlayer << std::endl;
}

void PlayState::FireLaser(Point2D<double> p, bool origen)
{
	SceneObject* l = new Laser(game, this, p, nullptr, 1, game->GetRenderer(), origen);

	sceneObjectsList.push_back(l);
}

bool PlayState::Colisiones(Laser* laser)
{
	for (SceneObject& a : sceneObjectsList) {
		if ((&a)->Hit(laser->GetRect(), laser->Origen())) {
			return true;
		}
	}
	return false;
}

void PlayState::hasDied(GameList<SceneObject, true>::anchor i)
{
	sceneObjectsList.erase(i);
}

void PlayState::isGameOver()
{
	gameOver = true;
	std::cout << "Has perdido :(";
	//game->ChangeState(0);
	//game->GetMachine()->ReplaceState(new MenuState(game));
	game->GetMachine()->ReplaceState(new EndState(game, game->GetTexture(GAMEOVER)));
}

void PlayState::YouWin()
{
	gameOver = true;
	std::cout << "Has ganado!!! :D";
	//game->ChangeState(0);
	//game->GetMachine()->ReplaceState(new MenuState(game));
	game->GetMachine()->ReplaceState(new EndState(game, game->GetTexture(HASGANADO)));
}

bool PlayState::MayGrantReward(SDL_Rect r) const
{
	return SDL_HasIntersection(&r, nave->GetRect());
}

void PlayState::DropReward(Point2D<double> pos)
{
	//Creamos el premio
	Reward* premio = new Reward(game, this, pos, game->GetTexture(S_REWARD), 1);

	//Le ponemos el callback
	premio->Connect([this]() {ShieldReward(); });

	//Lo añdimos a la lista de objetos
	sceneObjectsList.push_back(premio);
}

void PlayState::ShieldReward()
{
	std::cout << "Invencibleeee";
	nave->ImInvencible();
}

void PlayState::FireBomb(Point2D<double> pos)
{
	//Crea la bomba
	Bomb* bomba = new Bomb(game, this, pos, game->GetTexture(BOMB), 2);

	sceneObjectsList.push_back(bomba);
}

bool PlayState::OnEnter()
{
	std::cout << "Entrando en PlayState" << std::endl;
	return true;
}

bool PlayState::OnExit()
{
	std::cout << "Saliendo de PlayState" << std::endl;
	
	return true;
}

