#pragma once

#include "Core/Layer.h"

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "Modules/ImGuiConsole.h"

namespace TexWriter {

	/*
		Specific layer for ImGui rendering.
	*/
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		void SetBlockEvents(bool blockEvents) { m_BlockEvents = blockEvents; }

		inline void ShowConsole() { m_ShowConsole = true; }


	private:
		bool m_BlockEvents = false;

		bool m_ShowConsole = true;
	};

}