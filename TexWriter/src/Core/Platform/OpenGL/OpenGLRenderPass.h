#pragma once

#include "Core/RenderPass.h"

namespace TexWriter {

	class OpenGLRenderPass : public RenderPass
	{
	public:
		OpenGLRenderPass(const RenderPassSpecification& spec);
		virtual ~OpenGLRenderPass();

		virtual RenderPassSpecification& GetSpecification() override { return m_Specification; }
		virtual const RenderPassSpecification& GetSpecification() const override { return m_Specification; }

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;


	private:
		RenderPassSpecification m_Specification;

		uint32_t m_VertexArrayRendererID = 0;
	};

}
