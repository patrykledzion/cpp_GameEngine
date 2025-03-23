#include "Player.h"
#include "Game.h"
#include <GameObject.h>
#include <Drawing.h>
#include <Sprite.h>
#include <RigidBody.h>
#include <KeyboardMovement.h>
#include <CircleCollision.h>

using namespace nWindow;
using namespace nGameEngine;

void Player::Init()
{
	Image* image = new Image("D:\\cpp\\GameEngine\\WindowsLib\\WindowsLib\\src\\test3.bmp");
	Texture* texture = Drawing::LoadTexture(image); 
	this->AddComponent(std::make_shared<Sprite>(Color{ 1,1,1,1 }, texture, (GameObject*)(this)));
	this->AddComponent(std::make_shared<RigidBody>(this));
	this->AddComponent(std::make_shared<KeyboardMovement>(this));
}

void Player::Update()
{
	GameObject::Update();

	auto col = this->GetComponent<CircleCollision>();
	if (col == nullptr)return;

	if (col->GetCollisions()->size() > 0)
	{
		this->GetComponent<Sprite>()->color = { 1,0,0,1 };
	}
	else {
		this->GetComponent<Sprite>()->color = { 1,1,1,1 };
	}

	for (auto& colision : *col->GetCollisions())
	{
		this->GetComponent<Transform>()->pos.x -= colision.diff.x / 2;
		this->GetComponent<Transform>()->pos.y -= colision.diff.y / 2;

		colision.target->GetComponent<Transform>()->pos.x += colision.diff.x / 2;
		colision.target->GetComponent<Transform>()->pos.y += colision.diff.y / 2;
	}
}

void Player::Draw()
{
	GameObject::Draw();
}
