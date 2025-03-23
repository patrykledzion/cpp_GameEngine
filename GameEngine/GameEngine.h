#pragma once
#include <vector>
#include "Window.h"
#include "Image.h"
#include "Drawing.h"

#include "GameObject.h"

namespace nGameEngine {

	typedef struct {
		float aspectRatio;
	} GameRect;

	class GameEngine
	{
	private:
		std::unique_ptr<nWindow::Window> window; 
		GameRect gameRect;
		void Init();
	protected:
		std::unique_ptr<std::vector<GameObject*>> gameObjects; 
	public:
		GameEngine(int width, int height, const char* title, nGameEngine::GameRect rect) : gameRect(gameRect) { 
			this->window = std::make_unique<Window>(title, width, height); 
			this->Init();
		};
		virtual void Update();
		virtual void Draw();

		Window* GetWindow() { return this->window.get(); }
		std::vector<GameObject*>* GetGameObjects() { return this->gameObjects.get(); };
	};
}
