#include <iostream>
#include "GameManager.h"

int main(int argc, char* args[])
{
	const int SCREEN_WIDTH{ 800 };
	const int SCREEN_HEIGHT{ 600 };

	GameManager gameMan(9, 10, 100, 7, 7, 10, SCREEN_WIDTH, SCREEN_HEIGHT, 50, 1);

	gameMan.initWindow();
	gameMan.initializeGame();

	return 0;
}
