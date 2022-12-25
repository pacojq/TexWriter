#include "twpch.h"
#include "OpenGLRenderPass.h"

#include <glad/glad.h>

namespace TexWriter {


	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;

		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;

		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;

		case ShaderDataType::Bool:		return GL_BOOL;
		}

		TW_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}



	OpenGLRenderPass::OpenGLRenderPass(const RenderPassSpecification& spec)
		: m_Specification(spec)
	{
		Invalidate();
	}

	OpenGLRenderPass::~OpenGLRenderPass()
	{
		GLuint rendererID = m_VertexArrayRendererID;
		glDeleteVertexArrays(1, &rendererID);
	}


	void OpenGLRenderPass::Invalidate()
	{
		TW_ASSERT(m_Specification.VertexLayout.GetElements().size(), "Layout is empty!");


		if (m_VertexArrayRendererID)
			glDeleteVertexArrays(1, &m_VertexArrayRendererID);

		glGenVertexArrays(1, &m_VertexArrayRendererID);
		glBindVertexArray(m_VertexArrayRendererID);

		// TODO Bind() ?

		glBindVertexArray(0);
	}


	void OpenGLRenderPass::Bind()
	{
		// ======== BIND TARGET TEXTURE AND CLEAR
		{
			m_Specification.Target->Bind();

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		// ======== BIND VERTEX LAYOUT
		{
			TW_ASSERT(m_Specification.VertexLayout.GetElements().size(), "Vertex buffer has no layout!");

			glBindVertexArray(m_VertexArrayRendererID);
			//vertexBuffer->Bind();

			const auto& layout = m_Specification.VertexLayout;

			uint32_t attribIndex = 0;
			for (auto& element : layout)
			{
				glEnableVertexAttribArray(attribIndex);
				glVertexAttribPointer(
					attribIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)(intptr_t)element.Offset
				);
				attribIndex++;
			}
		}

		// ======== BIND SHADER
		{
			m_Specification.Shader->Bind();
		}
	}


	void OpenGLRenderPass::Unbind()
	{
		m_Specification.Shader->Unbind();

		m_Specification.Target->Unbind();
	}

}