#include "twpch.h"
#include "TWriterProject.h"

#include "Editor/EditorLayer.h"

#include "Core/Platform/OpenGL/OpenGLShaderCompiler.h"

#include "Files/ContentSerializer.h"
#include "Files/FilesUtil.h"

#include <filesystem>

namespace TexWriter {

	
	TWriterProject::TWriterProject(const std::string& name, const std::string& path)
		: m_Name(name), m_Path(path)
	{
		const std::string srcVertex = R""(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = vec4(a_Position, 1.0);
		}
		)"";

		const std::string srcFragment = R""(
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec2 v_TexCoord;

		void main()
		{
			color = vec4(v_TexCoord.r, v_TexCoord.g, 0.0f, 1.0f);
		}
		)"";


		RenderPassSpecification spec;
		spec.Target = RenderTarget::Create(512, 512);
		spec.Shader = Shader::Create("Color", srcVertex, srcFragment);
		spec.VertexLayout = {
				{ ShaderDataType::Float3, "a_Position" },
				//{ ShaderDataType::Float4, "a_Color" },
				{ ShaderDataType::Float2, "a_TexCoord" }
		};

		m_RenderPass = RenderPass::Create(spec);
	}




	void TWriterProject::CompileShader(const EditorLayer* editor)
	{
		editor->GetWindowTextEditor()->ClearFeedback();

		const std::string srcVertex = R""(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = vec4(a_Position, 1.0);
		}
		)"";

		std::string srcFragment = editor->GetWindowTextEditor()->GetContent();

		OpenGLShaderCompiler::Result res = OpenGLShaderCompiler::Compile(srcVertex, srcFragment);
		if (res.Success)
		{
			m_RenderPass->GetSpecification().Shader.reset();
			m_RenderPass->GetSpecification().Shader = Shader::Create("Color", srcVertex, srcFragment);

			editor->GetWindowPreview()->RenderImage();
		}
		else
		{
			editor->GetWindowTextEditor()->SetFeedback(res);
		}
		//m_RenderPass->GetSpecification().Shader->Compile(shaderSources);

		//Ref<Shader> shader = Shader::Create("Color", srcVertex, srcFragment);
	}
	
}
