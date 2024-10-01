#pragma once
#include "vector2D.h"
#include "texture.h"

class InfoBar
{
private:
	Texture* textScore;
	Texture* textVidas;
	point2D posScore, posVidas;
	int vidas = 3;
	int score[4] = { 0, 0, 0, 0 };
	const int SCORE_SIZE = 4;
	SDL_Rect rectScore;
	SDL_Rect rectVidas;

public:
	InfoBar(Texture* ts, Texture* tv, int s, int v);
	void Render();
	void RenderVidas();
	void RenderScore();
	void UpdateScore(int scoreToAdd);
	void UpdateVidas();
	void SetInfo(const int vid, int scor);
};

