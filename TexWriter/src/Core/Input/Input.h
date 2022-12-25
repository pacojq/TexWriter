#pragma once

#include "Core/Core.h"
#include "KeyCodes.h"

namespace TexWriter {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keyCode);
		static bool IsKeyHeld(KeyCode keyCode);
		static bool IsKeyReleased(KeyCode keyCode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}