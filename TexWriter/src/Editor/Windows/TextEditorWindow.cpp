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

			if (m_HasCompileErrors && m_TextEditor->IsTextChanged())
			{
				ClearFeedback();
			}
		}
		ImGui::End();
	}






	static std::vector<std::string> StringToLines(std::string string)
	{
		std::vector<std::string> result;
		std::string temp;
		int markbegin = 0;
		int markend = 0;

		for (int i = 0; i < string.length(); ++i) {
			if (string[i] == '\n') {
				markend = i;
				result.push_back(string.substr(markbegin, markend - markbegin));
				markbegin = (i + 1);
			}
		}
		return result;
	}


	static std::pair<int, std::string> ProcessShaderError(std::string line, TextEditor::ErrorMarkers& markers)
	{
		std::pair<int, std::string> result;

		//   "ERROR: 0:11: 'aaaaa' : undeclared identifier"

		uint16_t columnCount = 0;
		uint16_t charIndex_Line = 0;

		int resultLine = 0;
		std::string errMsg;

		for (int i = 0; i < line.length(); ++i)
		{
			if (line[i] == ':') columnCount++;

			if (columnCount == 2 && charIndex_Line == 0) // We're past the col token in "col:line". Line is next token
			{
				charIndex_Line = i + 1;
			}
			if (columnCount == 3) // We're past the col token in "col:line". Line is next token
			{
				std::string strLine = line.substr(charIndex_Line, i - charIndex_Line);
				
				result.first = std::stoi(strLine);
				result.second = line.substr(i+2, line.length() - (i+2));
				break;
			}
		}
		return result;
	}




	void TextEditorWindow::SetFeedback(const OpenGLShaderCompiler::Result compileResult)
	{
		m_HasCompileErrors = compileResult.Success == false;

		TextEditor::ErrorMarkers markers;

		if (m_HasCompileErrors)
		{
			std::vector<std::string> lines = StringToLines(compileResult.InfoLog);

			for (uint16_t i = 0; i < lines.size() - 2; i++) // Last 2 lines are garbage
			{
				std::string line = lines[i];
				markers.insert(ProcessShaderError(lines[i], markers));

				//markers.insert(std::make_pair<int, std::string>(6, "Example error here:\nInclude file not found: \"TextEditor.h\""));
			}
		}
		m_TextEditor->SetErrorMarkers(markers);
	}

	void TextEditorWindow::ClearFeedback()
	{
		m_HasCompileErrors = false;

		TextEditor::ErrorMarkers markers;
		m_TextEditor->SetErrorMarkers(markers);
	}

}