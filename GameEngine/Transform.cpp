#include "Transform.h"

nGameEngine::Transform::Transform(GameObject* gameObject) : Component(gameObject)
{
	this->pos = { 0,0,0 };
	this->size = { 0,0,0 };
}

