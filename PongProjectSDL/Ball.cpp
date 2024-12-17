#pragma once
#include "Paddle.h"
#include "Vector2.h"
#include "Ball.h"
#include <iostream>



	Ball::Ball(int x, int y, int velX, int velY, int radius)
	{
		position.x = x;
		position.y = y;
		velocity.x = velX;
		velocity.y = velY;
		this->radius = radius;
		isInGame = true;
	}

	Ball::Ball()
	{
		position.x = 400;
		position.y = 315;
		velocity.x = 5;
		velocity.y = 5;
		this->radius = 10;
		isInGame = true;
	}

	void Ball::drawFilledCircle(SDL_Renderer* renderer)
	{
		int x = 0;
		int y = radius;
		int decision = 1 - radius;
		int centerX = position.x, centerY = position.y;

		while (y >= x)
		{
			SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
			SDL_RenderDrawLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x);
			SDL_RenderDrawLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
			SDL_RenderDrawLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);

			x++;
			if (decision <= 0)
			{
				decision += 2 * x + 1;
			}
			else
			{
				y--;
				decision += 2 * (x - y) + 1;
			}
		}
	}


	void Ball::changePos(int screenHeight)
	{
		position.y += velocity.y;
		position.x += velocity.x;

		if ((position.y <= radius / 2) || position.y >= screenHeight - radius / 2)
		{
			velocity.y *= -1;
		}

		printPosition();
	}

	void Ball::checkCollision(Paddle& leftPaddle, Paddle& rightPaddle, int screenWidth)
	{
		int paddlePosY = rightPaddle.getPos(screenWidth).second;
		int paddlePosX = rightPaddle.getPos(screenWidth).first;
		int paddleHeight = rightPaddle.getHeight();

		//right paddle collision check
		if ((position.x + radius / 2 >= paddlePosX && position.x - radius / 2 <= paddlePosX + 5) && (position.y >= paddlePosY && position.y <= paddlePosY + paddleHeight))
		{
			velocity.x *= -1;
		}
		else if ((position.x + radius / 2 >= screenWidth))
		{
			isInGame = false;
		}

		paddlePosY = leftPaddle.getPos(screenWidth).second;
		paddlePosX = leftPaddle.getPos(screenWidth).first;
		paddleHeight = rightPaddle.getHeight();

		//left paddle collision check
		if ((position.x - radius / 2 <= paddlePosX && position.x - radius/2 >= paddlePosX - 5) && (position.y >= paddlePosY && position.y <= paddlePosY + paddleHeight))
		{
			velocity.x *= -1;
		}
		else if ((position.x - radius / 2 <= 0))
		{
			isInGame = false;
		}

	}

	/*void drawBall(Color color)
	{
		DrawCircleV(position, radius, color);
	}*/

	int Ball::getVelocityX()
	{
		return velocity.x;
	}

	bool Ball::getIsInGame()
	{
		return isInGame;
	}


	void Ball::resetBall(int screenWidth, int screenHeight)
	{
		position.x = screenWidth / 2;
		position.y = screenHeight / 2;
		velocity.x *= -1;
		isInGame = true;
	}

	void Ball::printPosition()
	{
		std::cout << "pos X: " << position.x << "pos Y: " << position.y << std::endl;

	}

