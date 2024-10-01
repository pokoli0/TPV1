#include "checkML.h"
#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	try {
		//Creamos el juego
		Game game;

		//Bucle principal del juego
		game.Run();
		SDL_Delay(500);
	}
	catch (FileNotFoundError& fileError)
	{
		std::cout << fileError.what() << std::endl;
	}
	catch (SDLError& SDLError)
	{
		std::cout << SDLError.what() << std::endl;
	}
	catch (FileFormatError& fileError)
	{
		std::cout << fileError.what() << std::endl;
	}
	

	
	return 0;
}


