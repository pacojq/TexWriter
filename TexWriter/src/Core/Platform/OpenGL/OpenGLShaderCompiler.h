#pragma once


#pragma once

#include "Core/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace TexWriter {

	class OpenGLShaderCompiler
	{
	public:
		struct Result
		{
			bool Success;
			std::string InfoLog;
		};

		static Result Compile(const std::string& vertexSrc, const std::string& fragmentSrc);

	private:
		static Result Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	};

}