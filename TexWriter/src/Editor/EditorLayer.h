#pragma once

#include "Core/Layer.h"
#include "Core/Application.h"
#include "Core/Log.h"

#include "Project/TWriterProject.h"

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "Panels/LanguageListPanel.h"

#include "Windows/DashboardWindow.h"
#include "Windows/PreviewWindow.h"
#include "Windows/TextEditorWindow.h"

#include "imgui.h"

namespace TexWriter {


	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float ts) override;
		virtual void OnEvent(Event& e) override;

		virtual void OnImGuiRender() override;

		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);

		inline bool IsContentActive() const { return m_ContentActive; }
		const Ref<TWriterProject>& GetContent() const { return m_Content; }

		void ResetDockSpace();
		void ResetLayout();
		
		//void ShowLanguageWindow(LanguageIso iso);

	public:
		inline const Ref<PreviewWindow> GetWindowPreview() const { return m_PreviewWindow; }
		inline const Ref<TextEditorWindow> GetWindowTextEditor() const { return m_TextEditorWindow; }


	private:
		bool m_ContentActive = false;
		Ref<TWriterProject> m_Content;
		
		Ref<LanguageListPanel> m_LanguageListWindow;
		bool m_ShowLanguageListWindow = false;

		Ref<DashboardWindow> m_DashboardWindow;
		bool m_ShowDashboardWindow = false;

		Ref<PreviewWindow> m_PreviewWindow;
		bool m_ShowPreviewWindow = true;

		Ref<TextEditorWindow> m_TextEditorWindow;
		bool m_ShowTextEditorWindow = true;


		//std::unordered_map<LanguageIso, Ref<LanguageWindow>> m_LanguageWindows;

		bool m_ShowAboutWindow = false;

		ImGuiID m_DockspaceId;
		bool m_DockspaceReady = false;
	};

}
