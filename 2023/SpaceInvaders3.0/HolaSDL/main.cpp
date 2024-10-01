#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDLApplication.h"
#include <iostream>


using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[])
{
	const int delay = 500;
	try {
		//Creamos el juego
		SDLApplication game;
		//Bucle principal
		game.Run();
		SDL_Delay(delay);
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
