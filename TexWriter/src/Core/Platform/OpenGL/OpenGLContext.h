#pragma once

#include "Core/GraphicsContext.h"

struct GLFWwindow;

namespace TexWriter {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual void Clear() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}