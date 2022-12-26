#pragma once

#include "Core/RenderTarget.h"


namespace TexWriter {

	class OpenGLRenderTarget : public RenderTarget
	{
	public:
		OpenGLRenderTarget(uint32_t witdth, uint32_t height);
		~OpenGLRenderTarget() override;

		virtual void Invalidate() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SaveToFile() override;

		inline virtual uint32_t GetColorRendererID() const override { return m_ColorAttachment; }

	private:
		uint32_t m_Width;
		uint32_t m_Height;

		uint32_t m_RendererID;
		uint32_t m_ColorAttachment;
	};

}