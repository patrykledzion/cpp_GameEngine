#pragma once
#include "Component.h"
#include "Drawing.h"

namespace nGameEngine {
	class Transform : public Component {
	public:
		nWindow::Vector3 pos;
		nWindow::Vector3 size;
		Transform(GameObject* gameObject);
	};

}
