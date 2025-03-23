#include "Sprite.h"
#include "Transform.h"
#include "GameObject.h"

void nGameEngine::Sprite::Draw()
{
	Transform* transform = this->gameObject->GetComponent<Transform>();

	if (transform == nullptr)return;

	if (this->texture != nullptr)
		Drawing::DrawRectangle(&transform->pos, &transform->size, &this->color, this->texture);
	else
		Drawing::DrawRectangle(&transform->pos, &transform->size, &this->color);
}

void nGameEngine::Sprite::Update()
{
}
