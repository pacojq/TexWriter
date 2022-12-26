#include "twpch.h"
#include "EditorLayer.h"

#include "Files/ContentSerializer.h"
#include "Files/FilesUtil.h"

#include "Core/Input/Input.h"

#include "Core/ImGui/ImGuiUtil.h"

#include "imgui_internal.h"

namespace TexWriter {


	EditorLayer::EditorLayer() : Layer("Editor Layer")
	{
		m_MenuBar = CreateRef<EditorMenuBar>(this);

		m_DashboardWindow = CreateRef<DashboardWindow>(this);
		m_PreviewWindow = CreateRef<PreviewWindow>(this);
		m_TextEditorWindow = CreateRef<TextEditorWindow>(this);
	}

	EditorLayer::~EditorLayer()
	{
	}


	void EditorLayer::OnAttach()
	{
		m_Content = CreateRef<TWriterProject>("Blank Project", "");
		m_ContentActive = true;

		// TODO: update data in each window

		m_PreviewWindow->RenderImage();

		ResetLayout();
	}

	void EditorLayer::OnDetach()
	{
	}


	void EditorLayer::OnUpdate(float ts)
	{
		
	}



	void EditorLayer::OnImGuiRender()
	{
		static bool p_open = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		m_DockspaceId = ImGui::GetID("MyDockSpace");

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGui::DockSpace(m_DockspaceId, ImVec2(0.0f, 0.0f), dockspace_flags);
			if (!m_DockspaceReady)
				ResetDockSpace();
		}

		m_MenuBar->OnImGuiRender();

		// ============================================= WINDOWS ============================================= //

		if (m_ShowDashboardWindow)
		{
			m_DashboardWindow->OnImGuiRender(&m_ShowDashboardWindow);
		}
		
		if (m_ShowPreviewWindow)
		{
			m_PreviewWindow->OnImGuiRender(&m_ShowPreviewWindow);
		}

		if (m_ShowTextEditorWindow)
		{
			m_TextEditorWindow->OnImGuiRender(&m_ShowTextEditorWindow);
		}

		

		// ============================================= MISC WINDOWS ============================================= //

		if (m_ShowAboutWindow)
		{
			ImGui::Begin("About", &m_ShowAboutWindow, ImGuiWindowFlags_NoResize);

			ImGui::Text("TEX-WRITER - Shader-based image generation tool");
			ImGui::Separator();
			ImGui::Text("Version: v.0.0.1");
			ImGui::Text(u8"Author: Paco Juan Quirós");
			ImGui::Text("Year: 2022");
			
			ImGui::End();
		}


		
		ImGui::End();

	}

	void EditorLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(TW_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<KeyPressedEvent>(TW_BIND_EVENT_FN(EditorLayer::OnKeyPressed));

		/*
		for (auto kvp : m_LanguageWindows)
		{
			auto window = kvp.second;
			// TODO if active
			window->OnEvent(e);
		}
		*/
	}


	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		return false;
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts

		if (e.GetRepeatCount() > 0)
			return false;

		if (m_ContentActive)
		{
			if (Input::IsKeyPressed(TW_KEY_LEFT_CONTROL) || Input::IsKeyPressed(TW_KEY_RIGHT_CONTROL))
			{
				switch (e.GetKeyCode())
				{
				case (int)TW_KEY_S:
				{
					// Save content
					ContentSerializer::Serialize(m_Content, m_Content->GetPath());
					return false;
				}
				}
			}
		}


		return false;
	}




	

	void EditorLayer::ResetLayout()
	{
		if (m_ContentActive)
		{
			m_ShowDashboardWindow = false;
			Application::Get().GetImGuiLayer()->ShowConsole();

			m_ShowPreviewWindow = true;
			m_ShowTextEditorWindow = true;

			m_ShowAboutWindow = false;
		}
		else
		{
			m_ShowDashboardWindow = false;
			Application::Get().GetImGuiLayer()->ShowConsole();

			m_ShowPreviewWindow = false;
			m_ShowTextEditorWindow = false;

			m_ShowAboutWindow = false;
		}
	}

	void EditorLayer::ResetDockSpace()
	{
		m_DockspaceReady = true;
		ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGui::DockBuilderRemoveNode(m_DockspaceId); // Clear out existing layout
		ImGui::DockBuilderAddNode(m_DockspaceId, ImGuiDockNodeFlags_DockSpace); // Add empty node
		ImGui::DockBuilderSetNodeSize(m_DockspaceId, viewport->Size);

		ImGuiID dock_main_id = m_DockspaceId; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.

		ImGuiID dock_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
		ImGuiID dock_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, NULL, &dock_main_id);
		ImGuiID dock_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

		ImGui::DockBuilderDockWindow("Console", dock_bottom);
		ImGui::DockBuilderDockWindow(IMGUI_DASHBOARD_NAME, dock_main_id);

		ImGui::DockBuilderDockWindow(IMGUI_TEXT_EDITOR_WINDOW_NAME, dock_main_id);
		ImGui::DockBuilderDockWindow(IMGUI_PREVIEW_WINDOW_NAME, dock_right);

		/*
		for (int i = 0; i < LanguageIso::Unknown; i++)
		{
			std::string lang = Language::GetName((LanguageIso)i);
			ImGui::DockBuilderDockWindow(lang.c_str(), dock_main_id);
		}
		*/

		//ImGui::DockBuilderDockWindow("Mesh", dock_left);
		//ImGui::DockBuilderDockWindow("Extra", dock_left);
		ImGui::DockBuilderFinish(m_DockspaceId);
	}




}
