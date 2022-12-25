#pragma once

#include "Core/Application.h"


namespace TexWriter {

	#define IMGUI_DASHBOARD_NAME "Dashboard"

	class EditorLayer;

	class DashboardWindow
	{
	public:
		DashboardWindow(EditorLayer* editor);
		~DashboardWindow() = default;

		void OnImGuiRender(bool* show);

	private:
		EditorLayer* m_Editor;
	};

}