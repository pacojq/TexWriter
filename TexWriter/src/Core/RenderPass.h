#pragma once

#include "Core.h"
#include "RenderTarget.h"
#include "Shader.h"
#include "VertexBuffer.h"

namespace TexWriter {

	struct RenderPassSpecification
	{
		Ref<RenderTarget> Target;
		Ref<Shader> Shader;
		VertexBufferLayout VertexLayout;
	};

	class RenderPass
	{
	public:
		virtual ~RenderPass() = default;

		virtual RenderPassSpecification& GetSpecification() = 0;
		virtual const RenderPassSpecification& GetSpecification() const = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;


		static Ref<RenderPass> Create(const RenderPassSpecification& spec);
	};

}