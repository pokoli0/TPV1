#include "InfoBar.h"

InfoBar::InfoBar(Texture* ts, Texture* tv, int s, int v) : textScore(ts), textVidas(tv), vidas(v), posScore(0,10), posVidas (0,550)
{
	rectScore.h = textScore->getFrameHeight();
	rectScore.w = textScore->getFrameWidth();
	rectScore.y = posScore.getY();
	rectScore.x = posScore.getX();
	
	rectVidas.h = textVidas->getFrameHeight();
	rectVidas.w = textVidas->getFrameWidth();
	rectVidas.x = posVidas.getX();
	rectVidas.y = posVidas.getY();

	UpdateScore(s);
}

void InfoBar::Render()
{
	RenderVidas();
	RenderScore();
}

void InfoBar::RenderScore()
{
	for (int i = 0; i < SCORE_SIZE; i++)
	{
		textScore->renderFrame(rectScore, 0, score[i]);
		rectScore.x += textScore->getFrameWidth() + 5;
	}
	rectScore.x = 0;
}

void InfoBar::RenderVidas()
{
	for (int i = 0; i < vidas; i++)
	{
		textVidas->renderFrame(rectVidas, 0, 0);
		rectVidas.x += textVidas->getFrameWidth() + 5;
	}
	rectVidas.x = 0;
}

void InfoBar::UpdateScore(int scoreToAdd)
{
	//esto hay q convertirlo en un bucle
	int i = 3;
	while (scoreToAdd > 0 && i >= 0)
	{
		score[i] = scoreToAdd % 10; 
		scoreToAdd = scoreToAdd / 10;
		i--;
	}
}

void InfoBar::UpdateVidas()
{
	vidas--;
}

void InfoBar::SetInfo(const int vid, int scor)
{
}
