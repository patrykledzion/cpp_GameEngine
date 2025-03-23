#include "GameEngine.h"
#include "Sprite.h"

void nGameEngine::GameEngine::Init()
{
    this->gameObjects = std::make_unique<std::vector<nGameEngine::GameObject*>>();
}

void nGameEngine::GameEngine::Update()
{
	this->window->Update();
    for (auto& gameObject : *this->gameObjects)
    {
        gameObject->Update();
    }
}

void nGameEngine::GameEngine::Draw()
{
    nWindow::Drawing::Begin();

    for (auto& gameObject : *this->gameObjects)
    {
        gameObject->Draw();
    }

    nWindow::Drawing::End(this->window.get());
    
}
