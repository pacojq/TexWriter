#pragma once

#include "Core/Core.h"

#include "imgui.h"

namespace TexWriter {

	class EditorLayer;

	class EditorMenuBar
	{
	public:
		EditorMenuBar(EditorLayer* editorLayer);
		
		void OnImGuiRender();

	private:
		void DoMenuFile();
		void DoMenuView();
		void DoMenuHelp();


	private:
		EditorLayer* m_EditorLayer;
	};

}
