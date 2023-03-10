#include "twpch.h"
#include "Application.h"

#include "Log.h"

#include "ImGui/ImGuiStyles.h"
#include "Editor/EditorLayer.h"

#include <GLFW/glfw3.h>


namespace TexWriter {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	Application::Application()
	{
		TW_ASSERT(!s_Instance, "Application should be null");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		ImGuiStyles::ApplyDefaultStyle();

		PushLayer(new EditorLayer());
	}

	Application::~Application()
	{
	}


	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		dispatcher.Dispatch<WindowFocusEvent>(BIND_EVENT_FN(OnWindowFocus));

		//XA_CORE_TRACE("{0}", e);

		// Dispatch events down to our layer stack
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			if (e.Handled)
				break;
			(*--it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime(); // TODO Platform::GetTime()
			float timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_Window->GetContext()->Clear();

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);		

				m_ImGuiLayer->Begin();
				{
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();

			}

			m_Window->OnUpdate();
		}

		// TODO Shutdown
	}

	void Application::Close()
	{
		m_Running = false;
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		Close();
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		return true;
	}

	bool Application::OnWindowFocus(WindowFocusEvent& e)
	{		
		m_Focused = e.IsFocused();
		return false;
	}


}
