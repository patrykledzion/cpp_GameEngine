#include "CircleCollision.h"
#include "GameObject.h"
#include "GameEngine.h"

void nGameEngine::CircleCollision::Update()
{
	if (!gameObjects || !gameObject)return;
	this->collisions.clear();

	auto transform = this->gameObject->GetComponent<Transform>();
	if (!transform)return;

	int radius = this->relativeRadius * std::min<float>(transform->size.x, transform->size.y) / 2;
	nWindow::Vector2 center = { transform->pos.x + relativeCenter.x, transform->pos.y + relativeCenter.y };

	for (auto& go : *this->gameObjects)
	{
		if (go == this->gameObject.get())continue;
		auto goCircleCollision = go->GetComponent<CircleCollision>();
		if (!goCircleCollision)continue;
		auto goTransform = go->GetComponent<Transform>();
		if (!goTransform)continue;

		int goRadius = goCircleCollision->relativeRadius * std::min<float>(goTransform->size.x, goTransform->size.y) / 2;
		nWindow::Vector2 goCenter = { goTransform->pos.x + goCircleCollision->relativeCenter.x, goTransform->pos.y + goCircleCollision->relativeCenter.y };
		
		float distanceX = center.x - goCenter.x;
		float distanceY = center.y - goCenter.y;
		float distance = std::sqrt(std::pow(distanceX,2) + std::pow(distanceY, 2));

		if (distance > goRadius + radius)continue;;

		DetectedCollision collision;
		float offset = distance - (goRadius + radius);
		if (distanceY == 0)distanceY = 1;
		float proportion = offset / distance;
		float offsetX = distanceX * proportion;
		float offsetY = distanceY * proportion;
		
		collision.target = go;
		collision.diff = { offsetX, offsetY };
		this->collisions.push_back(collision);
	}
}
