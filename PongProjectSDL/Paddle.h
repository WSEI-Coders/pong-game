#pragma once
#include <SDL2/SDL.h>
#include<SDL2/SDL_render.h>
#include <memory>
#include <SDL2/SDL_ttf.h>


class Paddle
{
public:

	Paddle(int vely, int posy, int posx, int width, int height);

	Paddle();
	
	void movePaddle(const int screenHeight);
	
	std::pair<int, int> getPos(int screenWidth);

	int getHeight();
	int getWidth();
	void drawPaddle(SDL_Renderer* renderer);

	void setDirection(int dir);

private:
	std::unique_ptr<SDL_Rect> paddle;
	int velY;
	int posY;
	int posX;
	int dir{ 0 };

};