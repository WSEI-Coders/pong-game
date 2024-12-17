#pragma once
#include "Ball.h"
#include <string>

using SDLWindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using SDLRendererPtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
using SDLTexturePtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
using TTFFontPtr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;
using SDLSurfacePtr = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;


class GameManager
{

public:
	GameManager(int paddleVelocity,
		int paddleWidth, int paddleHeight,
		int ballVelX, int ballVelY,
		int ballRadius, int screenWidth,
		int screenHeight, int paddleOffset, int maxScore);

	void initWindow();
	void handleInput();
	void initializeGame();
	void initFont();
	void displayText();
	void updateText();
	//void drawScore()
	//{
	//	DrawText(TextFormat(std::to_string(score.first).c_str()), scrWidth / 2 - MeasureText("   ", 50) * 2, scrHeight / 10, 50, col);
	//	DrawText(TextFormat(" - "), scrWidth / 2 - MeasureText("   ", 50), scrHeight / 10, 50, col);
	//	DrawText(TextFormat(std::to_string(score.first).c_str()), scrWidth / 2 + MeasureText("   ", 50) * 2, scrHeight / 10, 50, col);

	//}

	void trackScore();

private:
	SDLWindowPtr window;
	SDLRendererPtr renderer;
	SDLTexturePtr textTexture;
	TTFFontPtr font;
	SDLSurfacePtr textSurface;
	Paddle leftPaddle;
	Paddle rightPaddle;
	Ball ball;
	bool quit;
	std::pair<int, int> score;
	int scrWidth;
	int scrHeight;
	int textW;
	int textH;
	std::string text;
	SDL_Rect textRect;
	int maxScore;
};
