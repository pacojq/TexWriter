#include "twpch.h"
#include "DashboardWindow.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "Editor/EditorLayer.h"

namespace TexWriter {

	DashboardWindow::DashboardWindow(EditorLayer* editor) : m_Editor(editor)
	{
	}


	void DashboardWindow::OnImGuiRender(bool* show)
	{
		ImGui::Begin(IMGUI_DASHBOARD_NAME, show);
		{


		}
		ImGui::End();
	}

}