#include "Paddle.h"


	Paddle::Paddle(int vely, int posy, int posx, int width, int height)
	{
		paddle = std::make_unique<SDL_Rect>();
		velY = vely;
		posY = posy;
		posX = posx;
		paddle->w = width;
		paddle->h = height;
		paddle->x = posX;
		paddle->y = posY;
	}

	Paddle::Paddle() : paddle(std::make_unique<SDL_Rect>())
	{
		velY = 5;
		posY = 270;
		posX = 50;
		paddle->w = 10;
		paddle->h = 100;
		paddle->x = posX;
		paddle->y = posY;
	}

	void Paddle::movePaddle(const int screenHeight)
	{
		
		if (dir > 0 && posY <= screenHeight - paddle->h || dir < 0 && posY >= 0)
		{
			posY += dir * velY;
		}
		paddle->y = posY;
	}

	std::pair<int, int> Paddle::getPos(int screenWidth)
	{
		int pX{ 0 };
		if (posX > screenWidth / 2)
		{
			pX = posX;
		}
		else
		{
			pX = posX + paddle->w;
		}
		std::pair<int, int> pair = std::make_pair(pX, posY);
		return pair;
	}

	int Paddle::getHeight()
	{
		return paddle->h;
	}

	int Paddle::getWidth()
	{
		return paddle->w;
	}

	void Paddle::drawPaddle(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 224, 66, 245, 255);
		SDL_RenderFillRect(renderer, paddle.get());
	}

	void Paddle::setDirection(int dir)
	{
		this->dir = dir;
	}

