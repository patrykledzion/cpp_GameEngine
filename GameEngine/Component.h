#pragma once
#include "Drawing.h"
#include "Window.h" 

namespace nGameEngine { 
	class GameObject; 
	class Component
	{
	protected:
		std::unique_ptr<GameObject> gameObject;
	public: 
		Component(GameObject* gameObject) { this->gameObject.reset(gameObject); }
		virtual ~Component() = default;
		virtual void Update() {};
		virtual void Draw() {};
	};

	enum class COMPONENTS {
		Transform,
		RigidBody,
		KeyboardMovement,
		Sprite
	};

}


 

