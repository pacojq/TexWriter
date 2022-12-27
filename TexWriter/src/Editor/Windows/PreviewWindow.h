#pragma once

#include "Core/Application.h"
#include "Core/VertexBuffer.h"
#include "Core/IndexBuffer.h"

namespace TexWriter {

	class EditorLayer;

	class PreviewWindow
	{
	public:
		PreviewWindow(EditorLayer* editor);
		~PreviewWindow() = default;

		void OnImGuiRender(bool* show);

		void RenderImage();

	private:
		EditorLayer* m_Editor;

		Ref<IndexBuffer> m_QuadIndexBuffer;
		Ref<VertexBuffer> m_QuadVertexBuffer;
	};

}