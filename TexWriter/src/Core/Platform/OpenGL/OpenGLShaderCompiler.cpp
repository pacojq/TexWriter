#include "twpch.h"
#include "OpenGLShaderCompiler.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace TexWriter {



	OpenGLShaderCompiler::Result OpenGLShaderCompiler::Compile(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		return Compile(shaderSources);
	}



	static std::string ProcessInfoLog(std::vector<GLchar> infoLog)
	{
		std::basic_stringstream<char> str;

		for (GLchar c : infoLog)
		{
			str << c;
		}

		return str.str();
	}



	// Compile the shader.
	// Code copied from https://www.khronos.org/opengl/wiki/Shader_Compilation#Example

	OpenGLShaderCompiler::Result OpenGLShaderCompiler::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		TW_ASSERT(shaderSources.size() <= 2, "A maximum of two shaders is supported.");

		OpenGLShaderCompiler::Result result;


		int glShaderIDIndex = 0;
		std::array<GLenum, 2> glShaderIDs;

		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				result.Success = false;
				result.InfoLog = ProcessInfoLog(infoLog);

				TW_LOG_ERROR("{0}", infoLog.data());
				//TW_ASSERT(false, "Shader compilation failure!");
				TW_LOG_ERROR("Shader compilation failure!");
				break;
			}

			glDeleteShader(shader);
		}

		return result;
	}


}