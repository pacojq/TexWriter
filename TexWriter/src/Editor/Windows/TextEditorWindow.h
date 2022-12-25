#pragma once

#include "Core/Application.h"
#include "TextEditor/TextEditor.h"

namespace TexWriter {

#define IMGUI_TEXT_EDITOR_WINDOW_NAME "Text Editor"

	class EditorLayer;

	class TextEditorWindow
	{
	public:
		TextEditorWindow(EditorLayer* editor);
		~TextEditorWindow() = default;

		void OnImGuiRender(bool* show);

		std::string GetContent() const { return m_TextEditor->GetText(); }

	private:
		EditorLayer* m_Editor;

		Ref<TextEditor> m_TextEditor;
	};

}