#pragma once

#include "imgui.h"

namespace TexWriter {

	class ImGuiStyles
	{
	public:
		static void ApplyDefaultStyle();

		static float GetFontSize();
		static ImFont* GetItalicFont();
	

		static ImFont* GetJapaneseFont();
		static ImFont* GetKoreanFont();
		static ImFont* GetCyrillicFont();
		static ImFont* GetPolishFont();
		static ImFont* GetChineseSimplifiedFont();
	};

}