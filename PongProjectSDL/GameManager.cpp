#pragma once
#include "GameManager.h"


GameManager::GameManager(int paddleVelocity,
	int paddleWidth, int paddleHeight,
	int ballVelX, int ballVelY,
	int ballRadius, int screenWidth,
	int screenHeight, int paddleOffset, int maxScore)
	:
	leftPaddle(paddleVelocity, (screenHeight / 2) - paddleHeight / 2, paddleOffset, paddleWidth, paddleHeight),
	rightPaddle(paddleVelocity, (screenHeight / 2) - paddleHeight / 2, screenWidth - paddleOffset - paddleWidth, paddleWidth, paddleHeight),
	ball(screenWidth / 2, screenHeight / 2, ballVelX, ballVelY, ballRadius),
	score(0, 0), scrWidth(screenWidth), scrHeight(screenHeight), window(nullptr, SDL_DestroyWindow), renderer(nullptr, SDL_DestroyRenderer), 
	quit(false), font(nullptr, TTF_CloseFont), textSurface(nullptr, SDL_FreeSurface), textTexture(nullptr, SDL_DestroyTexture), 
	textW (0), textH(0), textRect({0,0,0,0}), text(std::to_string(score.first) + "          " + std::to_string(score.second)), maxScore(maxScore)
	{
	}

	void GameManager::initWindow()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		{
			std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}

		window.reset(SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scrWidth, scrHeight, SDL_WINDOW_SHOWN));
		if (!window)
		{
			throw std::runtime_error("Failed to create SDL Window: " + std::string(SDL_GetError()));
		}

		renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
		if (!renderer)
		{
			throw std::runtime_error("Failed to create SDL Renderer: " + std::string(SDL_GetError()));
		}

		if (TTF_Init() == -1)
		{
			std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
		}
	}

	void GameManager::handleInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN &&  e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_w:
						if (leftPaddle.getPos(scrHeight).second > 0) leftPaddle.setDirection(-1);
						break;

					case SDLK_s:
						if (leftPaddle.getPos(scrHeight).second < scrHeight - leftPaddle.getHeight()) leftPaddle.setDirection(1);
						break;

					case SDLK_UP:
						if (rightPaddle.getPos(scrHeight).second > 0) rightPaddle.setDirection(-1);
						break;

					case SDLK_DOWN:
						if (rightPaddle.getPos(scrHeight).second < scrHeight - rightPaddle.getHeight()) rightPaddle.setDirection(1);
						break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_w:
					case SDLK_s:
						leftPaddle.setDirection(0);
						break;
					case SDLK_UP:
					case SDLK_DOWN:
						rightPaddle.setDirection(0);
						break;

				}
			}
		}
	}

	void GameManager::initializeGame()
	{
		
		initFont();
		const int FPS = 60;
		const int frameDelay = 1000 / FPS;

		Uint32 frameStart;
		int frameTime;

		while (!quit)
		{
			frameStart = SDL_GetTicks();

			if (score.first < maxScore && score.second < maxScore)
			{
				handleInput();

				SDL_SetRenderDrawColor(renderer.get(), 10, 10, 10, 255);
				SDL_RenderClear(renderer.get());

				leftPaddle.drawPaddle(renderer.get());
				rightPaddle.drawPaddle(renderer.get());
				leftPaddle.movePaddle(scrHeight);
				rightPaddle.movePaddle(scrHeight);

				ball.drawFilledCircle(renderer.get());
				ball.changePos(scrHeight);
				ball.checkCollision(leftPaddle, rightPaddle, scrWidth);

				displayText();

				SDL_RenderPresent(renderer.get());

				trackScore();
			}
			else
			{
				SDL_Event e;
				SDL_SetRenderDrawColor(renderer.get(), 10, 10, 10, 255);
				SDL_RenderClear(renderer.get());
				text = "Press any button to quit. Press 'Y' to play Again";
				initFont();
				displayText();
				SDL_RenderPresent(renderer.get());
				while (SDL_PollEvent(&e))
				{
					
					
					if (e.type == SDL_KEYDOWN)
					{
						if (e.key.keysym.sym == SDLK_y)
						{
							score.first = 0; score.second = 0;
							ball.resetBall(scrWidth, scrHeight);
						}
						else
						{
							quit = true;
						}
					}

				}
			}

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}

		}
		SDL_Quit();

	}

	void GameManager::initFont()
	{
		font.reset(TTF_OpenFont("C:/Users/ppusz/Desktop/Roboto-Light.ttf", 24));
		if (!font)
		{
			std::cerr << "Failed to initialize font: " << TTF_GetError() << std::endl;
			throw std::runtime_error("Font initialization failed");
		}
		
		updateText();
		
		if (!textSurface)
		{
			std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
			throw std::runtime_error("Text surface creation failed");
		}
	
		textTexture.reset(SDL_CreateTextureFromSurface(renderer.get(), textSurface.get()));
		if (!textTexture)
		{
			std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
			throw std::runtime_error("Text texture creation failed");
		}

		textSurface.reset();
	}

	void GameManager::displayText()
	{
		
		if(TTF_SizeText(font.get(), text.c_str(), &textW, &textH) != 0)
		{
			std::cerr << "failed to obtain text size: " << TTF_GetError() << std::endl;
		}
		textRect.x = scrWidth/2 - textW / 2;
		textRect.y = 30;
		textRect.w = textW;
		textRect.h = textH;

		SDL_RenderCopy(renderer.get(), textTexture.get(), nullptr, &textRect);
	
	}

	void GameManager::updateText()
	{
		SDL_Color color = { 255, 255, 255, 255 };
		textSurface.reset(TTF_RenderText_Solid(font.get(), text.c_str(), color));
	}

	void GameManager::trackScore()
	{
		if (!ball.getIsInGame())
		{

			if (ball.getVelocityX() < 0)
			{
				score.second += 1;

			}
			else if (ball.getVelocityX() > 0)
			{
				score.first += 1;

			}
			ball.resetBall(scrWidth, scrHeight);
			initFont();

		}
	}

