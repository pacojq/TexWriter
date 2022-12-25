#include "twpch.h"
#include "RenderTarget.h"

#include "Platform/OpenGL/OpenGLRenderTarget.h"

namespace TexWriter {

	Ref<RenderTarget> RenderTarget::Create(uint32_t witdth, uint32_t height)
	{
		return CreateRef<OpenGLRenderTarget>(witdth, height);
	}

}