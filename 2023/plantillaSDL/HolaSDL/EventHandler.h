#pragma once
#include <SDL.h>
class EventHandler
{
public:
	virtual void handleEvent(const SDL_Event&) {};
};

//nada más tiene esta clase. Enonces, xq la hacemos??
//literalmente para decir "I pinky promise q esta clase va a manejar eventos" en las clases q hereden.
