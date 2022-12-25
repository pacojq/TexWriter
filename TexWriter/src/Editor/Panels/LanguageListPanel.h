#pragma once

#include "Core/Application.h"


namespace TexWriter {

	#define IMGUI_LANGUAGE_LIST_NAME "Language List"

	class EditorLayer;
	
	class LanguageListPanel
	{
	public:
		LanguageListPanel(EditorLayer* editor);
		~LanguageListPanel() = default;

		void OnUpdate();
		void OnImGuiRender(bool* show);


		
	private:
		EditorLayer* m_Editor;
	};

}