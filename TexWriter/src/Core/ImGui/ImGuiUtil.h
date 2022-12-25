#pragma once

namespace TexWriter {

	class ImGuiUtil
	{
	public:
		static bool MenuItem(const std::string& text, bool enabled);
		static bool InputText(const std::string& label, std::string& value, bool error);
		static bool Checkbox(const std::string& text, bool* value, bool enabled);
		static bool ArrowButton(const std::string& id, int dir, std::string tooltip);

		static void HelpMarker(const char* description);
	};
	
}