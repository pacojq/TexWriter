#include "twpch.h"
#include "LanguageListPanel.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "Editor/EditorLayer.h"

namespace TexWriter {


	LanguageListPanel::LanguageListPanel(EditorLayer* editor)
		: m_Editor(editor)
	{
	}


	void LanguageListPanel::OnUpdate()
	{
		/*
		if (!m_Editor->IsContentActive())
		{
			show = false;
			return;
		}
		
		ImGui::SetNextWindowSize(ImVec2(320, 480), ImGuiCond_FirstUseEver);
		ImGui::Begin(IMGUI_LANGUAGE_LIST_NAME, show);
		{
			uint32_t count = 0;
			for (uint32_t i = 0; i < LanguageIso::Unknown; i++)
			{
				LanguageIso iso = (LanguageIso)i;
				if (m_Editor->GetContent()->LanguageExists(iso))
				{
					DrawLanguage((LanguageIso)i);
					count++;
				}
			}

			if (count > 0)
				ImGui::Separator();			

			if (ImGui::Button("Add language"))
			{
				m_PopupItems.clear();
				for (uint32_t i = 0; i < LanguageIso::Unknown; i++)
				{
					LanguageIso iso = (LanguageIso)i;
					if (!m_Editor->GetContent()->LanguageExists(iso))
						m_PopupItems.push_back(iso);
				}
				
				m_PopupSelectedItem = Unknown;
				
				ImGui::OpenPopup("Add new language");
			}

			bool showModal = true;
			DrawNewLanguageModal(&showModal);
		}
		ImGui::End();
		 */
	}

	

	void LanguageListPanel::OnImGuiRender(bool* show)
	{
		if (!m_Editor->IsContentActive())
		{
			show = false;
			return;
		}
		
		ImGui::Begin(IMGUI_LANGUAGE_LIST_NAME, show);
		{
			ImGui::Columns(3);
			for (uint32_t i = 0; i < 16; i++)
			{				
				ImGui::PushID((void*)(uint32_t)i);
				
				int value = i;
				std::string id = fmt::format("##{0}", i);
				std::string label = fmt::format("Entry {0}", i);

				// Language name
				ImGui::Text(label.c_str());
				ImGui::NextColumn();

				// Path
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
				ImGui::InputInt(id.c_str(), &value);
				ImGui::PopStyleVar();
				ImGui::NextColumn();

				// Edit button
				if (ImGui::Button("Open"))
				{
					TW_LOG_WARN("Clicked on {}", i);
				}
				ImGui::NextColumn();
				ImGui::PopID();
			}
			ImGui::Columns(1);
		}
		ImGui::End();
	}



	

}

/*
void SceneHierarchyPanel::DrawEntityNode(Entity entity)
{
	const char* name = "Unnamed Entity";
	if (entity.HasComponent<TagComponent>())
		name = entity.GetComponent<TagComponent>().Tag.c_str();

	ImGuiTreeNodeFlags node_flags = (entity == m_SelectionContext ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
	bool opened = ImGui::TreeNodeEx((void*)(uint32_t)entity, node_flags, name);
	if (ImGui::IsItemClicked())
	{
		m_SelectionContext = entity;
		m_ShowProperties = true;
	}

	bool entityDeleted = false;
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Delete"))
			entityDeleted = true;

		ImGui::EndPopup();
	}
	if (opened)
	{
		ImGui::TreePop();
	}

	// Defer deletion until end of node UI
	if (entityDeleted)
	{
		m_Scene->DestroyEntity(entity);
		if (entity == m_SelectionContext)
		{
			m_SelectionContext = {};
			m_ShowProperties = false;
		}
	}
}
*/