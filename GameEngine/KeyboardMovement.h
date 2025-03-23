#pragma once
#include "Window.h"
#include "Component.h"

namespace nGameEngine {
	enum class MovementType {
		PLATFORM,
		TOPDOWN,
	};

	class KeyboardMovement : public Component {
	private:
		void _KeyboardUpHandle(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void _KeyboardDownHandle(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void _Move();
		bool keys[256] = { false };
	public:
		

		MovementType movementType = MovementType::TOPDOWN;
		float maxSpeed = 3;
		float slide = 0.5;
		char UP_KEY = 'W';
		char DOWN_KEY = 'S';
		char LEFT_KEY = 'A';
		char RIGHT_KEY = 'D';

		KeyboardMovement(GameObject* gameObject);
		void Update() override;
	};
}