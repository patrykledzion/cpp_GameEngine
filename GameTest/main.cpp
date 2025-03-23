#include <iostream>
#include "Game.h"

int main()
{ 
	Game* game = new Game(800,600, "Test", nGameEngine::GameRect{4 / 3});
	game->Init();
	while (true)
	{
		game->Update();
		game->Draw();
	}
	return 0;
}