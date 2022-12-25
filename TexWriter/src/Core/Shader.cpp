#include "twpch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace TexWriter {


	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		return CreateRef<OpenGLShader>(filepath);
	}


	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
	}

}