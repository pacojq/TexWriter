#include "twpch.h"
#include "ImGuiUtil.h"

#include "imgui/imgui.h"
#include "imgui_internal.h"

namespace TexWriter {

	bool ImGuiUtil::MenuItem(const std::string& text, bool enabled)
	{
		if (enabled)
		{
			return ImGui::MenuItem(text.c_str());
		}
		else
		{
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
			ImGui::MenuItem(text.c_str());
			ImGui::PopItemFlag();
			ImGui::PopStyleVar();
			return false;
		}
	}





	
	bool ImGuiUtil::InputText(const std::string& label, std::string& value, bool error)
	{
		ImGui::Columns(2);
		bool modified = false;

		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		char buffer[256];
		strcpy(buffer, value.c_str());

		std::string lbl = "##" + label;
		if (error) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));

		if (ImGui::InputText(lbl.c_str(), buffer, 256))
		{
			value = buffer;
			modified = true;
		}

		if (error) ImGui::PopStyleColor();

		ImGui::PopItemWidth();
		ImGui::NextColumn();
		ImGui::Columns(1);

		return modified;
	}


	bool ImGuiUtil::Checkbox(const std::string& text, bool* value, bool enabled)
	{
		if (enabled)
		{
			return ImGui::Checkbox(text.c_str(), value);
		}
		else
		{
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
			ImGui::Checkbox(text.c_str(), value);
			ImGui::PopItemFlag();
			ImGui::PopStyleVar();
			return false;
		}
	}

	bool ImGuiUtil::ArrowButton(const std::string& id, int dir, std::string tooltip)
	{
		bool clicked = ImGui::ArrowButton(id.c_str(), dir);
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text(tooltip.c_str());
			ImGui::EndTooltip();
		}
		return clicked;
	}



	void ImGuiUtil::HelpMarker(const char* description)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(description);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
	
}
