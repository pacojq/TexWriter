#include "twpch.h"
#include "OpenGLContext.h"

#include "Core/Core.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace TexWriter {


	static void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			TW_LOG_ERROR("[OpenGL Debug HIGH] {0}", message);
			TW_ASSERT(false, "GL_DEBUG_SEVERITY_HIGH");
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			TW_LOG_WARN("[OpenGL Debug MEDIUM] {0}", message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			TW_LOG_INFO("[OpenGL Debug LOW] {0}", message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			// HZ_CORE_TRACE("[OpenGL Debug NOTIFICATION] {0}", message);
			break;
		}
	}




	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		TW_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		TW_LOG_TRACE("OpenGL Context initializing...");

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TW_ASSERT(status, "Failed to initialize Glad!");

		TW_LOG_INFO("OpenGL Renderer:");
		TW_LOG_INFO("  Vendor:    {0}", glGetString(GL_VENDOR));
		TW_LOG_INFO("  Renderer:  {0}", glGetString(GL_RENDERER));
		TW_LOG_INFO("  Version:   {0}", glGetString(GL_VERSION));

		glDebugMessageCallback(OpenGLLogMessage, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		#ifdef TW_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		TW_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Texture Forge requires at least OpenGL version 4.5!");
		#endif

		TW_LOG_TRACE("OpenGL Context ready!");
	}


	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}