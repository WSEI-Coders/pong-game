#pragma once
#include "Paddle.h"
#include "Vector2.h"
#include <iostream>

class Ball
{
public:

	Ball(int x, int y, int velX, int velY, int radius);

	Ball();

	void drawFilledCircle(SDL_Renderer* renderer);


	void changePos(int screenHeight);

	void checkCollision(Paddle& leftPaddle, Paddle& rightPaddle, int screenWidth);

	/*void drawBall(Color color)
	{
		DrawCircleV(position, radius, color);
	}*/

	int getVelocityX();
	bool getIsInGame();

	void resetBall(int screenWidth, int screenHeight);

	void printPosition();

private:
	Vector2 position;
	Vector2 velocity;
	int radius;
	bool isInGame;
};