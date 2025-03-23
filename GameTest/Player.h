#pragma once
#include <GameObject.h>

class GameEngine;
class Player : public nGameEngine::GameObject
{
private:
	void Init();
public:
	Player(nWindow::Vector3 pos, nWindow::Vector3 size, nGameEngine::GameEngine* game) : nGameEngine::GameObject(pos, size, game) { this->Init(); }
	void Update() override;
	void Draw() override;
};

