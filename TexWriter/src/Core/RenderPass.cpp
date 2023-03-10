#include "twpch.h"
#include "RenderPass.h"

#include "Platform/OpenGL/OpenGLRenderPass.h"

namespace TexWriter {

	Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
	{
		return CreateRef<OpenGLRenderPass>(spec);
	}

}