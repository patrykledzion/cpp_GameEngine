#include "GameObject.h"
#include "GameEngine.h"
#include "Transform.h" 

namespace nGameEngine {
	 
	GameObject::GameObject(Vector3 pos, Vector3 size, nGameEngine::GameEngine* game)
		: game(game)
	{ 
		this->transform = std::make_shared<Transform>(this);
		this->transform->pos = pos;
		this->transform->size = size;
		this->components.push_back(this->transform);
		this->Init();
	}

	void GameObject::Init()
	{	   
	}

	void GameObject::Update()
	{
		for (auto& component : this->components)
		{
			component->Update();
		}
	}

	void GameObject::Draw()
	{
		for (auto& component : this->components)
		{
			component->Draw();
		}
	}

	void GameObject::AddComponent(std::shared_ptr<Component> component)
	{
		if (component == nullptr)return;
		this->components.push_back(component);
	}
}
