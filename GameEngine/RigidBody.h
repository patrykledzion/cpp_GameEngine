#pragma once
#include "Component.h"
#include "Drawing.h"

namespace nGameEngine { 
	class RigidBody : public Component {
	private:
		void _Gravity();
	public:
		nWindow::Vector2 speedX = { 0,0 };
		nWindow::Vector2 speedY = { 0,0 };
		bool gravity = false;
		RigidBody(GameObject* gameObject) : Component(gameObject) {}
		void Update() override;
	};
}