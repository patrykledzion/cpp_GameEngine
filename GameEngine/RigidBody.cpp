#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"

void nGameEngine::RigidBody::_Gravity()
{
	if (!this->gravity) {
		return;
	}
	this->speedY.y++;
}

void nGameEngine::RigidBody::Update()
{
	this->_Gravity();

	Transform* transform = this->gameObject->GetComponent<Transform>();

	if (transform == nullptr)return;

	transform->pos.x += this->speedX.y;
	transform->pos.x -= this->speedX.x;
	transform->pos.y += this->speedY.y;
	transform->pos.y -= this->speedY.x;
}