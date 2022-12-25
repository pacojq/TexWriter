#pragma once

#include "Core.h"

#include "Window.h"

#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"


namespace TexWriter {


	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Close();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);


		inline Window& GetWindow() { return *m_Window; }
		
		inline ImGuiLayer* GetImGuiLayer() const { return m_ImGuiLayer; }


		/// <returns>The Application singleton.</returns>
		inline static Application& Get() { return *s_Instance; }


	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowFocus(WindowFocusEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		bool m_Minimized = false;

		bool m_Focused = true;

		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;


	private:
		/// <summary>
		/// Application singleton.
		/// </summary>
		static Application* s_Instance;
	};

}

