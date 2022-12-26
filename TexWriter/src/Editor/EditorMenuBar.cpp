#include "twpch.h"
#include "EditorMenuBar.h"

#include "EditorLayer.h"

#include "Files/ContentSerializer.h"
#include "Files/FilesUtil.h"

#include "Core/Input/Input.h"

#include "Core/ImGui/ImGuiUtil.h"

#include "imgui_internal.h"

namespace TexWriter {


	EditorMenuBar::EditorMenuBar(EditorLayer* editorLayer)
		: m_EditorLayer(editorLayer)
	{
	}



	void EditorMenuBar::OnImGuiRender()
	{
		if (ImGui::BeginMenuBar())
		{
			DoMenuFile();
			DoMenuView();
			DoMenuHelp();

			ImGui::EndMenuBar();
		}
	}



	void EditorMenuBar::DoMenuFile()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGuiUtil::MenuItem("New Project...", false))
			{
				std::string filename = FilesUtil::SaveFile("TexWriter Project\0*.texwriter\0 All files\0*.*\0");
				if (filename != "")
				{
					if (filename.substr(filename.find_last_of(".") + 1) != "texwriter")
						filename = filename + ".texwriter";

					std::string name = FilesUtil::SplitFileName(filename);
					m_EditorLayer->m_Content = CreateRef<TWriterProject>(name, filename);
					m_EditorLayer->m_ContentActive = true;
					ContentSerializer::Serialize(m_EditorLayer->m_Content, filename);
					m_EditorLayer->ResetLayout();
				}
			}
			if (ImGuiUtil::MenuItem("Open Project...", false))
			{
				std::string filename = FilesUtil::OpenFile("TexWriter Project\0*.texwriter\0 All files\0*.*\0");
				if (filename != "")
				{
					if (filename.substr(filename.find_last_of(".") + 1) == "texwriter")
					{
						if (m_EditorLayer->m_Content)
							m_EditorLayer->m_Content.reset();
						m_EditorLayer->m_Content = ContentSerializer::Deserialize(filename);
						m_EditorLayer->m_ContentActive = true;
						m_EditorLayer->ResetLayout();
					}
					else
					{
						TW_LOG_ERROR("Please, select a .mbsloc file");
					}
				}
			}

			ImGui::Separator();

			if (ImGuiUtil::MenuItem("Save", false && m_EditorLayer->m_ContentActive))
			{
				ContentSerializer::Serialize(m_EditorLayer->m_Content, m_EditorLayer->m_Content->GetPath());
			}
			if (ImGuiUtil::MenuItem("Save as...", false && m_EditorLayer->m_ContentActive))
			{
				std::string filename = FilesUtil::SaveFile("TexWriter Project\0*.texwriter");
				if (filename != "")
				{
					ContentSerializer::Serialize(m_EditorLayer->m_Content, filename);
				}
			}


			ImGui::Separator();

			if (ImGuiUtil::MenuItem("Export...", m_EditorLayer->m_ContentActive))
			{
				std::string filename = FilesUtil::SaveFile("PNG\0*.png\0 JPG\0*.jpg\0 All files\0*.*\0");
				if (filename != "")
				{
					Ref<RenderTarget> rt = m_EditorLayer->m_Content->GetRenderPass()->GetSpecification().Target;
					rt->SaveToFile(filename);
				}
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Exit"))
			{
				TexWriter::Application::Get().Close();
			}

			ImGui::EndMenu();
		}
	}


	void EditorMenuBar::DoMenuView()
	{
		if (ImGui::BeginMenu("View"))
		{
			if (ImGuiUtil::MenuItem("Dashboard", false && !m_EditorLayer->m_ContentActive))
			{
				m_EditorLayer->m_ShowDashboardWindow = true;
			}

			ImGui::Separator();

			if (ImGuiUtil::MenuItem("Preview", m_EditorLayer->m_ContentActive))
			{
				m_EditorLayer->m_ShowPreviewWindow = true;
			}

			if (ImGuiUtil::MenuItem("Shader Editor", m_EditorLayer->m_ContentActive))
			{
				m_EditorLayer->m_ShowTextEditorWindow = true;
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Console"))
			{
				Application::Get().GetImGuiLayer()->ShowConsole();
			}
			ImGui::EndMenu();
		}
	}

	void EditorMenuBar::DoMenuHelp()
	{
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				m_EditorLayer->m_ShowAboutWindow = true;
			}
			ImGui::EndMenu();
		}
	}

}
