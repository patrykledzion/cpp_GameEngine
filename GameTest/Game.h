#pragma once 
#include <GameEngine.h>
#include <GameObject.h>
#include <vector>

class Game : nGameEngine::GameEngine
{
private: 
public:
	Game(int width, int height, const char* title, nGameEngine::GameRect rect) :
		GameEngine(width, height, title, rect) {}
	void Init();
	void Update();
	void Draw();
};

