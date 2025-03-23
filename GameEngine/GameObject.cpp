#include "GameObject.h"
#include "GameEngine.h"
#include "Transform.h" 

namespace nGameEngine {
	 
	GameObject::GameObject(Vector3 pos, Vector3 size, nGameEngine::GameEngine* game)
		: game(game)
	{ 
		this->components = std::make_unique<std::vector<std::unique_ptr<Component>>>();

		std::unique_ptr<Transform> _transform = std::make_unique<Transform>(this);
		_transform->pos = pos;
		_transform->size = size;
		this->components->push_back(std::move(_transform)); 
		this->transform = this->GetComponent<Transform>();
		this->Init();
	}

	void GameObject::Init()
	{	   
	}

	void GameObject::Update()
	{
		for (auto& component : *this->components.get())
		{
			component->Update();
		}
	}

	void GameObject::Draw()
	{
		for (auto& component : *this->components.get())
		{
			component->Draw();
		}
	}

	void GameObject::AddComponent(std::unique_ptr<Component> component)
	{
		if (component == nullptr)return;
		this->components->push_back(std::move(component));
	}
}
