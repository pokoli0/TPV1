#include "Button.h"

void Button::emit() const
{
	//LLama al HandleEvent de cada oyente
	for (callBack buttonCallback : callbacks) {

		buttonCallback();
	}
}

void Button::Render() const
{
	//renderizamos el botón
	textura->renderFrame(Rect, textura->getNumRows() - 1, textura->getNumColumns() - 1);

	//Dependiendo del estado del ratón lo ponemos de un color u otro
	if (currentFrame == MouseOver) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, opacidad);	//Amarillo clarito
		//dibujamos el boton
		SDL_RenderFillRect(renderer, &Rect);
	}

	//Restablece el color de fondo (para el SDL_RenderClear)
	SDL_SetRenderDrawColor(game->GetRenderer(), 0, 0, 0, opacidad);
}

void Button::Update()
{
	SDL_GetMouseState(&point.x, &point.y);

	//Comprobamos si el ratón está sobre el rectángulo
	if (SDL_PointInRect(&point, &Rect)) {
		currentFrame = MouseOver;
	}
	else { currentFrame = MouseOut; }
}

void Button::save(std::ostream& out) const
{

}

void Button::HandleEvent(const SDL_Event& event)
{
	//Comprueba si se hace el click izquierdo del raton
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		//posición del ratón cuando se pulsa
		SDL_Point point{ event.button.x, event.button.y };

		//Vemos si el punto está en el mismo sitio que el botón
		if (SDL_PointInRect(&point, &Rect)) {
			emit();
		}
	}
}

void Button::Connect(callBack cb)
{
	//Añadimos el callback al vector
	callbacks.push_back(cb);
}
