#include "twpch.h"
#include "TextEditorWindow.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "Editor/EditorLayer.h"
#include "Editor/EditorNames.h"

namespace TexWriter {

	TextEditorWindow::TextEditorWindow(EditorLayer* editor) : m_Editor(editor)
	{
		m_TextEditor = CreateRef<TextEditor>();

		TextEditor::LanguageDefinition lang = TextEditor::LanguageDefinition::GLSL();
		m_TextEditor->SetLanguageDefinition(lang);

		m_TextEditor->SetText(R""(#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Textures[32];

in vec2 v_TexCoord;

void main()
{
	//color = vec4(v_TexCoord.r, v_TexCoord.g, 0.0f, 1.0f);
	color = texture(u_Textures[0], v_TexCoord);
}
)"");
	}


	void TextEditorWindow::OnImGuiRender(bool* show)
	{
		ImGui::Begin(EditorNames::Windows::TEXT_EDITOR, show);
		{
			if (ImGui::Button("Compile"))
			{
				m_Editor->GetContent()->CompileShader(m_Editor);
			}

			m_TextEditor->Render(EditorNames::Windows::TEXT_EDITOR);
		}
		ImGui::End();
	}

}