#pragma once

#include <vector>

#include "Drawing.h"
#include "Component.h" 
#include "Transform.h"

using namespace nWindow;

namespace nGameEngine {
	class GameEngine;

	class GameObject
	{
	private:
		virtual void Init();
	protected:
		std::unique_ptr<std::vector<std::unique_ptr<Component>>> components; 
		std::unique_ptr<GameEngine> game; 
	public:
		Transform* transform;
		GameObject(Vector3 pos, Vector3 size, nGameEngine::GameEngine* game); 
		virtual ~GameObject() = default;
		virtual void Update();
		virtual void Draw();  

		nGameEngine::GameEngine* GetGame() { return this->game.get(); };
		std::vector<std::unique_ptr<Component>>* GetComponents() { return this->components.get(); }
		virtual void AddComponent(std::unique_ptr<Component> component);
		template <typename T>
		T* GetComponent();
	};
	template<typename T>
	inline T* GameObject::GetComponent()
	{
		T* searched = nullptr;
		for (auto& component : *this->components.get())
		{
			searched = dynamic_cast<T*>(component.get());
			if (searched != nullptr)break;
		}
		return searched;
	}
}


