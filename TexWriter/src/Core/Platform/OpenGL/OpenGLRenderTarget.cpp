#include "twpch.h"
#include "OpenGLRenderTarget.h"

#include "Core/Core.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stb_image_write.h>

namespace TexWriter {


	OpenGLRenderTarget::OpenGLRenderTarget(uint32_t witdth, uint32_t height)
		: m_Width(witdth), m_Height(height)
	{
		m_RendererID = 0;
		m_ColorAttachment = 0;

		Invalidate();
	}

	OpenGLRenderTarget::~OpenGLRenderTarget()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
	}


	void OpenGLRenderTarget::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
		}

		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		// COLOR TEXTURE
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		// Linear up-scaling and down-scaling
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		// Check status
		TW_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		// Unbind
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	void OpenGLRenderTarget::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void OpenGLRenderTarget::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	void OpenGLRenderTarget::SaveToFile()
	{
		Bind();

		unsigned char* pixels = (unsigned char*)malloc(m_Width * m_Height * 4);

		glReadBuffer(m_RendererID);
		glReadPixels(0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		const uint16_t nChannels = 4;
		stbi_write_png("result.png", m_Width, m_Height, nChannels, pixels, m_Width * nChannels);

		free(pixels);

		Unbind();
	}

}