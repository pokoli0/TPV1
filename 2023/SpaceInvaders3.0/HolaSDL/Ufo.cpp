#include "Ufo.h"
#include "PlayState.h"

void Ufo::Render() const
{
	textura->renderFrame(rect, textura->getNumRows() - 1, textura->getNumColumns() - estado);
}

void Ufo::Update()
{
	if (estado != destruido) {
		//Se mantiene oculto mientras se decrementa el contador
		if (cont > 0) {
			cont--;
		}
		else if (cont == 0) {
			estado = visible;
			//Paramos y reiniciamos el movimiento si llegamos al final
			if (pos.LeerPosX() <= 0) {
				//Pasamos el estado a oculto
				estado = oculto;

				//Actualizamos el cooldown
				cont = _playState->getRandomRange(minCoolDown, maxCoolDown);
				pos = Vector2D<double>(originalX, originalY);
			}
			else {
				//Siempre se mueve de derecha a izquierda
				pos = pos - Vector2D<double>(speed, 0);
			}

			rect.x = pos.LeerPosX();
			rect.y = pos.LeerPosY();
		}
	}
	else {
		//Pasamos el estado a oculto
		estado = oculto;

		//Actualizamos el cooldown
		cont = _playState->getRandomRange(minCoolDown, maxCoolDown);
		pos = Vector2D<double>(originalX, originalY);
		rect.x = pos.LeerPosX();
		rect.y = pos.LeerPosY();
	}

}

void Ufo::save(std::ostream& out) const
{
	out << "5 ";
	SceneObject::save(out);
	out << " " << estado << " " << cont << std::endl;
}

bool Ufo::Hit(const SDL_Rect* r, bool o)
{
	//Si le golpean y no está destruido pasamos el estado pasa a destruido y hacemos la animación
	if (!o && SDL_HasIntersection(r, GetRect())) {
		estado = destruido;
		_playState->SetScore(UFOScore);

		// gestion de dropeo de reward
		rewardProb = _playState->getRandomRange(minProbReward, maxProbReward);
		if (rewardProb == 1) {
			_playState->FireBomb(pos);
		}
		else {
			_playState->DropReward(pos);
		}
		return true;
	}
	return false;
}
