#include "twpch.h"
#include "PreviewWindow.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "Core/Input/Input.h"
#include "Core/Input/KeyCodes.h"

#include "Editor/EditorLayer.h"
#include "Editor/EditorNames.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>


namespace TexWriter {


	struct QuadVertex
	{
		glm::vec3 Position;
		//glm::vec4 Color;
		glm::vec2 TexCoord;
	};


	PreviewWindow::PreviewWindow(EditorLayer* editor) : m_Editor(editor)
	{
		uint32_t* quadIndices = new uint32_t[6]{ 0, 1, 2, 2, 3, 0 };
		m_QuadIndexBuffer = IndexBuffer::Create(quadIndices, 6);
		delete[] quadIndices;

		m_QuadVertexBuffer = VertexBuffer::Create(4 * sizeof(QuadVertex));
	}

	void PreviewWindow::OnImGuiRender(bool* show)
	{
		ImGui::Begin(EditorNames::Windows::PREVIEW, show);
		{
			Ref<RenderTarget>& rt = m_Editor->GetContent()->GetRenderPass()->GetSpecification().Target;

			ImVec2 region = ImGui::GetContentRegionAvail();
			float size = glm::min(region.x, region.y);

			ImVec2 viewportSize = { size, size };
			ImVec2 uv00 = ImVec2{ 0, 1 }; // Flipped Y
			ImVec2 uv11 = ImVec2{ 1, 0 }; // Flipped Y
			ImGui::Image((void*)rt->GetColorRendererID(), viewportSize, uv00, uv11);
		}
		ImGui::End();
	}



	void PreviewWindow::RenderImage()
	{
		auto& proj = m_Editor->GetContent();

		QuadVertex* vertices = new QuadVertex[4]
		{
			// Vertex 0
			{ { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
			// Vertex 1
			{ { 1.0f, -1.0f, 0.0f },  { 1.0f, 0.0f } },
			// Vertex 2
			{ { 1.0f,  1.0f, 0.0f },  { 1.0f, 1.0f } },
			// Vertex 3
			{ { -1.0f,  1.0f, 0.0f }, { 0.0f, 1.0f } }
		};

		Ref<RenderTarget>& rt = proj->GetRenderPass()->GetSpecification().Target;
		Ref<Shader>& shader = proj->GetRenderPass()->GetSpecification().Shader;

		proj->GetRenderPass()->Bind();
		{
			m_QuadVertexBuffer->SetData(vertices, sizeof(QuadVertex) * 4);
			m_QuadIndexBuffer->Bind();

			// BIND UNIFORMS
			m_Editor->GetWindowShaderUniforms()->BindUniforms(shader);

			// DRAW INDEXED
			glDisable(GL_DEPTH_TEST);
			glDepthMask(GL_FALSE);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);

		}
		proj->GetRenderPass()->Unbind();

		delete[] vertices;
	}


}