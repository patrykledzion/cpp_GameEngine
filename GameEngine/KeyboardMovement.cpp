#include "KeyboardMovement.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "GameEngine.h"

void nGameEngine::KeyboardMovement::_KeyboardUpHandle(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	this->keys[(char)wParam] = false;
}

void nGameEngine::KeyboardMovement::_KeyboardDownHandle(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	this->keys[(char)wParam] = true;
}

void nGameEngine::KeyboardMovement::_Move()
{

	RigidBody* rigidBody = this->gameObject->GetComponent<RigidBody>();

	if (rigidBody == nullptr)return;

	switch (movementType)
	{
	case MovementType::TOPDOWN:
		if (this->keys[this->UP_KEY])rigidBody->speedY.x = std::min<float>(rigidBody->speedY.x + slide, maxSpeed);
		if (this->keys[this->DOWN_KEY])
		{ 
			rigidBody->speedY.y = std::min<float>(rigidBody->speedY.y + slide, maxSpeed);
		}
		if (this->keys[this->LEFT_KEY])rigidBody->speedX.x = std::min<float>(rigidBody->speedX.x + slide, maxSpeed);
		if (this->keys[this->RIGHT_KEY])rigidBody->speedX.y = std::min<float>(rigidBody->speedX.y + slide, maxSpeed);

		if (!this->keys[this->UP_KEY])rigidBody->speedY.x = std::max<float>(rigidBody->speedY.x - slide, 0);
		if (!this->keys[this->DOWN_KEY])rigidBody->speedY.y = std::max<float>(rigidBody->speedY.y - slide, 0);
		if (!this->keys[this->LEFT_KEY])rigidBody->speedX.x = std::max<float>(rigidBody->speedX.x - slide, 0);
		if (!this->keys[this->RIGHT_KEY])rigidBody->speedX.y = std::max<float>(rigidBody->speedX.y - slide, 0);
		break;
	case MovementType::PLATFORM:
		std::cout << "TODO PLATFORM MOVEMENT\n";
		break;
	}
}

nGameEngine::KeyboardMovement::KeyboardMovement(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject->GetGame()->GetWindow()->keyboardUpHandle.push_back([this](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {this->_KeyboardUpHandle(hWnd, uMsg, wParam, lParam); });
	this->gameObject->GetGame()->GetWindow()->keyboardDownHandle.push_back([this](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {this->_KeyboardDownHandle(hWnd, uMsg, wParam, lParam); });
}

void nGameEngine::KeyboardMovement::Update()
{
	_Move();
}