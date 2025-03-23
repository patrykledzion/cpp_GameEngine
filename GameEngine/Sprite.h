#pragma once
#include "Component.h"

namespace nGameEngine {
	class Sprite : public Component {
	private:
	public:
		nWindow::Texture* texture;
		nWindow::Color color;
		Sprite(GameObject* gameObject) : Component(gameObject), texture(nullptr), color({ 1,1,1,1 }) {}
		Sprite(nWindow::Color color, GameObject* gameObject) : Component(gameObject), texture(nullptr), color(color) {}
		Sprite(nWindow::Texture* texture, GameObject* gameObject) : Component(gameObject), texture(texture), color({1,1,1,1}) {}
		Sprite(nWindow::Color color, nWindow::Texture* texture, GameObject* gameObject) : Component(gameObject), texture(texture), color(color) {}
		~Sprite() = default;
		void Update() override;
		void Draw() override;
	};
}
