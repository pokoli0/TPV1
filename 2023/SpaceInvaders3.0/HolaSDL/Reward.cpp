#include "Reward.h"
#include "PlayState.h"

void Reward::emit() const
{
	//LLama al HandleEvent de cada oyente
	for (callBack objectCallback : Objectscallbacks) {
		objectCallback();
	}
}

void Reward::Render() const
{
	//renderizamos el premio
	textura->renderFrame(rect, textura->getNumRows() - 1, textura->getNumColumns() - 1);
}

void Reward::Update()
{
	//Se mueve hacia abajo mientras pueda
	pos = pos + vel;

	//Actualizamos el rect
	rect.x = pos.LeerPosX();
	rect.y = pos.LeerPosY();

	//Colision
	//Se destruye si desaparece por abajo
	if (pos.LeerPosY() >= game->GetWinHeight()) {
		_playState->hasDied(sceneanc);
	}

	// le pregunta si hay alguien a quien dar reward
	if (_playState->MayGrantReward(rect)) {

		// llama al callback de la reward
		emit();

		// elimina reward después de colisionar
		_playState->hasDied(sceneanc);
	}
}

void Reward::save(std::ostream& out) const
{ }

bool Reward::Hit(const SDL_Rect* r, bool o)
{
	return false;
}

void Reward::Connect(callBack cb)
{
	//Añadimos el callback al vector
	Objectscallbacks.push_back(cb);
}
