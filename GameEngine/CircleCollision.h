#pragma once
#include <vector>
#include "Component.h"


namespace nGameEngine {

	struct DetectedCollision {
		GameObject* target;
		nWindow::Vector2 diff;
	};

	class CircleCollision : public Component
	{
	private:
		std::unique_ptr<std::vector<GameObject*>> gameObjects;
		std::vector<DetectedCollision> collisions;
	public:
		nWindow::Vector2 relativeCenter;
		float relativeRadius;
		CircleCollision(GameObject* gameObject, std::vector<GameObject*>* gameObjects) : 
			Component(gameObject), gameObjects(gameObjects), relativeCenter(nWindow::Vector2{ 0,0 }), relativeRadius(1) {}

		CircleCollision(GameObject* gameObject, std::vector<GameObject*>* gameObjects, nWindow::Vector2 relativeCenter) :
			Component(gameObject), gameObjects(gameObjects), relativeCenter(relativeCenter), relativeRadius(1) {}

		CircleCollision(GameObject* gameObject, std::vector<GameObject*>* gameObjects, nWindow::Vector2 relativeCenter, float relativeRadius) :
			Component(gameObject), gameObjects(gameObjects), relativeCenter(relativeCenter), relativeRadius(relativeRadius) {}
		void Update() override;
		std::vector<DetectedCollision>* GetCollisions() { return &this->collisions; };
	};
}
