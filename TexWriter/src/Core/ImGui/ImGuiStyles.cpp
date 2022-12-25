#include "twpch.h"
#include "ImGuiStyles.h"

#include "imgui.h"
#include "Core/Window.h"

namespace TexWriter {
	
	struct ImGuiStyleData
	{
		ImFont* DefaultFont;
		ImFont* ItalicFont;
	};
	static ImGuiStyleData s_StyleData;



	struct ImGuiLanguageFonts
	{
		ImFont* FontArabic;
		ImFont* FontJapanese;
		ImFont* FontKorean;
		ImFont* FontCyrillic;
		ImFont* FontPolish;
		ImFont* FontChineseSimplified;
	};
	static ImGuiLanguageFonts s_LanguageFonts;


	ImFont* ImGuiStyles::GetJapaneseFont()
	{
		return s_LanguageFonts.FontJapanese;
	};
	ImFont* ImGuiStyles::GetKoreanFont()
	{
		return s_LanguageFonts.FontKorean;
	};
	ImFont* ImGuiStyles::GetCyrillicFont()
	{
		return s_LanguageFonts.FontCyrillic;
	};
	ImFont* ImGuiStyles::GetPolishFont()
	{
		return s_LanguageFonts.FontPolish;
	};
	ImFont* ImGuiStyles::GetChineseSimplifiedFont()
	{
		return s_LanguageFonts.FontChineseSimplified;
	};







	float ImGuiStyles::GetFontSize()
	{
		return Window::s_HighDPIScaleFactor * 16.0f;
	}

	ImFont* ImGuiStyles::GetItalicFont()
	{ 
		return s_StyleData.ItalicFont;
	};




	/*
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x20AC, 0x20AC, // €
		0x2122, 0x2122, // TM
		0x2196, 0x2196, // arrows
		0x21D6, 0x21D6, // arrows
		0x2B01, 0x2B01, // arrows
		0x2B09, 0x2B09, // arrows
		0x2921, 0x2922, // arrows
		0x263A, 0x263A, // smiley
		0x266A, 0x266A, // music
		0,
	};
	*/
	static const ImWchar* GetGlyphRangesPolski()
	{
		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x0100, 0x017F, // Polish characters
			0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
			0x2DE0, 0x2DFF, // Cyrillic Extended-A
			0xA640, 0xA69F, // Cyrillic Extended-B
			0,
		};
		return &ranges[0];
	}

	static ImFont* LoadFont(ImFontConfig& cfg, float fontSize, std::string path, const ImWchar* ranges)
	{
		ImGuiIO& io = ImGui::GetIO();
		return io.Fonts->AddFontFromFileTTF(path.c_str(), fontSize, &cfg, ranges);
	}


	void ImGuiStyles::ApplyDefaultStyle()
	{
		ImGuiIO& io = ImGui::GetIO();
		
		
		ImFontConfig cfg;

		float fontSize = GetFontSize();
		const std::string defaultPath = "assets/fonts/General/Roboto/";
		const std::string defFont = defaultPath + "RobotoMono-VariableFont_wght.ttf";


		s_StyleData.DefaultFont = LoadFont(cfg, fontSize, defFont, io.Fonts->GetGlyphRangesDefault());

		s_LanguageFonts.FontCyrillic = LoadFont(cfg, fontSize, defFont, io.Fonts->GetGlyphRangesCyrillic());

		s_LanguageFonts.FontPolish = LoadFont(cfg, fontSize, defFont, GetGlyphRangesPolski());

		const std::string defFontItalic = defaultPath + "RobotoMono-Italic-VariableFont_wght.ttf";
		s_StyleData.ItalicFont = LoadFont(cfg, fontSize, defFontItalic, io.Fonts->GetGlyphRangesDefault());

		const std::string fontJapanese = "assets/fonts/Japanese/Kosugi/Kosugi-Regular.ttf";
		s_LanguageFonts.FontJapanese = LoadFont(cfg, fontSize * .8f, fontJapanese, io.Fonts->GetGlyphRangesJapanese());

		const std::string fontKorean = "assets/fonts/Korean/NanumGothic/NanumGothic-Regular.ttf";
		s_LanguageFonts.FontKorean = LoadFont(cfg, fontSize, fontKorean, io.Fonts->GetGlyphRangesKorean());

		const std::string fontChinese = "assets/fonts/Chinese_Simplified/DengXian/Deng.ttf";
		s_LanguageFonts.FontChineseSimplified = LoadFont(cfg, fontSize, fontChinese, io.Fonts->GetGlyphRangesChineseFull());
		//s_LanguageFonts.FontChineseSimplified = LoadFont(cfg, fontSize, fontChinese, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());


		io.Fonts->Build();



		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		const ImVec4 white_a_1 = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		const ImVec4 white_a_156 = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		const ImVec4 white_a_0 = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);

		const ImVec4 lightBlue = ImVec4(0.549f, 0.976f, 1.000f, 1.000f);

		const ImVec4 blue = ImVec4(0.317f, 0.882f, 0.910f, 1.000f); //ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		const ImVec4 blue_a = ImVec4(0.317f, 0.882f, 0.910f, 0.781f);

		const ImVec4 gray_469 = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		const ImVec4 gray_391 = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		const ImVec4 gray_195 = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		const ImVec4 gray_180 = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
		const ImVec4 gray_098 = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);


		colors[ImGuiCol_Text] = white_a_1;
		colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(lightBlue.x, lightBlue.y, lightBlue.z, 0.156f); //white_a_156;

		colors[ImGuiCol_WindowBg] = gray_180;
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

		colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);

		colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);

		colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);

		colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);

		colors[ImGuiCol_MenuBarBg] = gray_195;

		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabActive] = blue;

		colors[ImGuiCol_CheckMark] = white_a_1;

		colors[ImGuiCol_SliderGrab] = gray_391;
		colors[ImGuiCol_SliderGrabActive] = blue;

		colors[ImGuiCol_Button] = white_a_0;
		colors[ImGuiCol_ButtonHovered] = ImVec4(lightBlue.x, lightBlue.y, lightBlue.z, 0.156f);
		colors[ImGuiCol_ButtonActive] = ImVec4(lightBlue.x, lightBlue.y, lightBlue.z, 0.391f);

		colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_HeaderHovered] = gray_469;
		colors[ImGuiCol_HeaderActive] = gray_469;

		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = gray_391;
		colors[ImGuiCol_SeparatorActive] = blue;

		colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
		colors[ImGuiCol_ResizeGripActive] = blue;

		colors[ImGuiCol_Tab] = gray_098;
		colors[ImGuiCol_TabHovered] = ImVec4(lightBlue.x, lightBlue.y, lightBlue.z, 0.391f);// ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
		colors[ImGuiCol_TabActive] = gray_195;
		colors[ImGuiCol_TabUnfocused] = gray_098;
		colors[ImGuiCol_TabUnfocusedActive] = gray_195;

		colors[ImGuiCol_DockingPreview] = blue_a;
		colors[ImGuiCol_DockingEmptyBg] = gray_180;

		colors[ImGuiCol_PlotLines] = blue; //gray_469;
		colors[ImGuiCol_PlotLinesHovered] = lightBlue;
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
		colors[ImGuiCol_PlotHistogramHovered] = blue;

		colors[ImGuiCol_DragDropTarget] = blue;

		colors[ImGuiCol_NavHighlight] = blue;
		colors[ImGuiCol_NavWindowingHighlight] = blue;
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);



		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 13.0f;
		style->TabBorderSize = 1.0f;
		style->TabRounding = 0.0f;
		style->WindowRounding = 4.0f;
	}
}
