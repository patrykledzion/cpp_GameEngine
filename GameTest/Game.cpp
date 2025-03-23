#include "Game.h" 
#include "Player.h"
#include <KeyboardMovement.h>
#include <Sprite.h>
#include <CircleCollision.h>
#include <RigidBody.h>

using namespace nGameEngine;
using namespace nWindow;

void Game::Init()
{
	std::cout << "TODO: Collision Component\n";
	Player* player = new Player(Vector3{ 50,50,0 }, Vector3{ 100,100,0 }, this);
	Player* player2 = new Player(Vector3{ 300,50,0 }, Vector3{ 100,100,0 }, this);
	
	player2->GetComponent<KeyboardMovement>()->UP_KEY = 'S';
	player2->GetComponent<KeyboardMovement>()->DOWN_KEY = 'W';
	player2->GetComponent<KeyboardMovement>()->LEFT_KEY = 'D';
	player2->GetComponent<KeyboardMovement>()->RIGHT_KEY = 'A';

	player->AddComponent(std::make_shared<CircleCollision>(player, this->GetGameObjects()));
	player2->AddComponent(std::make_shared<CircleCollision>(player2, this->GetGameObjects()));

	//player->GetComponent<CircleCollision>()->relativeRadius = 2.;
	this->gameObjects->push_back((GameObject*)player);
	this->gameObjects->push_back((GameObject*)player2);
	
}

void Game::Update()
{
	GameEngine::Update();
	std::cout << this->gameObjects->at(0)->GetComponent<Transform>()->pos.x << std::endl;
}

void Game::Draw()
{
	GameEngine::Draw();
}
