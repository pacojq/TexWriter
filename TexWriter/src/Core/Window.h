#pragma once

#include "twpch.h"

#include "Events/Event.h"

#include "Core.h"
#include "GraphicsContext.h"

namespace TexWriter {
		
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual GraphicsContext* GetContext() const = 0;

		static Window* Create();

	public:
		static float s_HighDPIScaleFactor;
	};


}
