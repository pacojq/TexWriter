#include "twpch.h"
#include "ShaderUniformsWindow.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "Editor/EditorNames.h"
#include "Editor/EditorLayer.h"

#include "Files/FilesUtil.h"


namespace TexWriter {

	static const uint32_t MAX_TEXTURE_SLOTS = 32;
	static int32_t s_Samplers[MAX_TEXTURE_SLOTS];


	static uint32_t s_TextureBindingIndex; // Used to draw the slot of each texture binding
	

	ShaderUniformsWindow::ShaderUniformsWindow(EditorLayer* editor) : m_Editor(editor)
	{
	}


	void ShaderUniformsWindow::BindUniforms(const Ref<Shader>& shader) const
	{
		for (uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++)
			s_Samplers[i] = i;

		ShaderUniformTextureBinding::s_SlotCount = 0;
		shader->SetIntArray("u_Textures", s_Samplers, MAX_TEXTURE_SLOTS);

		for (auto& binding : m_Bindings)
		{
			binding->Bind(shader);
		}
	}




	void ShaderUniformsWindow::OnImGuiRender(bool* show)
	{
		s_TextureBindingIndex = 0;

		ImGui::Begin(EditorNames::Windows::SHADER_UNIFORMS, show);
		{
			uint16_t index = -1;
			for (Ref<ShaderUniformBinding>& binding : m_Bindings)
			{
				index++;

				const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

				ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

				ImGui::Separator();

				std::string name = binding->GetName();
				if (binding->GetType() == UniformType::Texture)
					name = fmt::format("u_Textures[{0}]", s_TextureBindingIndex++);

				bool open = ImGui::TreeNodeEx((void*)index, treeNodeFlags, name.c_str());
				bool willRemove = false;

				ImGui::PopStyleVar();
				ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
				if (ImGui::Button("-", ImVec2{ lineHeight, lineHeight }))
				{
					willRemove = true;
				}

				if (open) 
				{
					binding->Accept(this);
					ImGui::TreePop();
				}

				if (willRemove)
				{
					binding.reset();
					m_Bindings.erase(m_Bindings.begin() + index, m_Bindings.begin() + (index + 1));
					break;
				}
			}

			if (m_Bindings.size() > 0)
				ImGui::Separator();

			if (ImGui::Button("Add"))
			{
				ImGui::OpenPopup("AddShaderUniformBinding");
			}
			if (ImGui::BeginPopup("AddShaderUniformBinding"))
			{
				if (ImGui::MenuItem("Texture")) AddBinding<ShaderUniformTextureBinding>("u_NewTexture");
				if (ImGui::MenuItem("Vector")) AddBinding<ShaderUniformVectorBinding>("u_NewVec4");
				//if (ImGui::MenuItem("Int")) AddBinding<ShaderUniformTextureBinding>("u_NewInt");
				if (ImGui::MenuItem("Color")) AddBinding<ShaderUniformColorBinding>("u_NewColor");

				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}





	void ShaderUniformsWindow::DrawBindingName(ShaderUniformBinding* binding)
	{
		char buffer[256];
		std::string id = fmt::format("##{0}", binding->GetName());

		if (binding->IsEditingName())
		{
			strcpy(buffer, binding->GetEditorTempName().c_str());

			if (ImGui::InputText(id.c_str(), buffer, 256))
			{
				binding->SetEditorTempName(buffer);
			}

			ImGui::SameLine();

			if (ImGui::Button("Apply")) // TODO: just "pencil icon"
			{
				binding->SetName(binding->GetEditorTempName());
				binding->SetEditingName(false);
			}
		}
		else 
		{
			strcpy(buffer, binding->GetName().c_str());
			ImGui::BeginDisabled();
			ImGui::InputText(id.c_str(), buffer, 256, ImGuiInputTextFlags_ReadOnly);
			ImGui::EndDisabled();

			ImGui::SameLine();

			if (ImGui::Button("Rename")) // TODO: just "pencil icon"
			{
				binding->SetEditingName(true);
			}
		}
		/*
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
		ImGui::InputText("##text1", txt_green, sizeof(txt_green));
		ImGui::PopStyleColor();
		*/
	}





	void ShaderUniformsWindow::DrawBinding(ShaderUniformTextureBinding* binding)
	{
		ImGui::Text(binding->GetName().c_str());

		ImGui::SameLine();

		if (ImGui::Button("Open..."))
		{
			std::string path = FilesUtil::OpenFile("PNG\0*.png\0");
			if (path.length() > 0)
			{
				binding->SetTexture(path);
			}
		}

		if (binding->GetTexture().get())
		{
			ImVec2 viewportSize = { 200, 200 };
			ImVec2 uv00 = ImVec2{ 0, 1 }; // Flipped Y
			ImVec2 uv11 = ImVec2{ 1, 0 }; // Flipped Y
			ImGui::Image((void*)binding->GetTexture()->GetRendererID(), viewportSize, uv00, uv11);
		}
	}


	void ShaderUniformsWindow::DrawBinding(ShaderUniformVectorBinding* binding)
	{
		DrawBindingName(binding);

		glm::vec4 value = binding->GetValue();

		std::string id = fmt::format("##vec4_{0}", binding->GetName());
		ImGui::DragFloat4(id.c_str(), (float*)&value);

		binding->SetValue(value);
	}


	void ShaderUniformsWindow::DrawBinding(ShaderUniformColorBinding* binding)
	{
		DrawBindingName(binding);

		glm::vec4 color = binding->GetValue();

		std::string id = fmt::format("##color_{0}", binding->GetName());
		ImGui::ColorEdit4(id.c_str(), (float*)&color);

		binding->SetValue(color);
	}
}