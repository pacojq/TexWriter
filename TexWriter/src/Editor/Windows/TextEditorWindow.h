#pragma once

#include "TextEditor/TextEditor.h"

#include "Core/Core.h"
#include "Core/Platform/OpenGL/OpenGLShaderCompiler.h"

namespace TexWriter {

	class EditorLayer;

	class TextEditorWindow
	{
	public:
		TextEditorWindow(EditorLayer* editor);
		~TextEditorWindow() = default;

		void OnImGuiRender(bool* show);

	public:
		std::string GetContent() const { return m_TextEditor->GetText(); }

		void SetFeedback(const OpenGLShaderCompiler::Result compileResult);
		void ClearFeedback();

	private:
		EditorLayer* m_Editor;

		Ref<TextEditor> m_TextEditor;
		bool m_HasCompileErrors;
	};

}