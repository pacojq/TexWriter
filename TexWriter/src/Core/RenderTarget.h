#pragma once

#include "Core.h"

namespace TexWriter {

	class RenderTarget
	{
	public:
		virtual ~RenderTarget() = default;

		/// <summary>
		/// Recreates the frame buffer.
		/// </summary>
		virtual void Invalidate() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SaveToFile() = 0;

		virtual uint32_t GetColorRendererID() const = 0;


		static Ref<RenderTarget> Create(uint32_t witdth, uint32_t height);
	};

}