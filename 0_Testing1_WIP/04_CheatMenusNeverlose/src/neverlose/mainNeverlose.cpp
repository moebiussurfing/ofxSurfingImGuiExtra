#pragma once
#include "ofxSurfingImGui.h"

#include "imgui_widgets_Neverlose.hpp"



#include "gui.hpp"
#include "hashes.hpp"

#include "bytes.hpp"

using namespace SurfImGui;
using namespace ImGui;

#define ALPHA    ( ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )

#define NO_ALPHA ( ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )

// Our state
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

//IDirect3DTexture9* avatar{ };
//IDirect3DTexture9* bg{ };
static ofImage   avatar;
static GLuint    avatarID;
static ofImage   bg;
static GLuint    bgID;


inline void setupNeverlose(ofxImGui::Gui* gui)
{
	// Load images

	avatar.load("image.png");
	avatarID = gui->loadImage(avatar);

	bg.load("bg.png");
	bgID = gui->loadImage(bg);
}

#if 0
inline void initNeverlose(/*ofxImGui::Gui* gui*/)
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

#if 1
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
#endif

	io.Fonts->AddFontFromMemoryTTF(museo500_binary, sizeof museo500_size, 14);
	static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	io.Fonts->AddFontFromMemoryTTF(&font_awesome_binary, font_awesome_size, 13, &icons_config, icon_ranges);
	io.Fonts->AddFontFromMemoryTTF(museo900_binary, museo900_size, 28);
}
#endif

inline void drawImGuiNeverlose()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	static bool bools[50]{};
	static int ints[50]{}, combo = 0;
	vector < const char* > items = { "Option", "Option 1", "Option 2", "Option 3", "Option 4", "Option 5", ICON_FA_AXE_BATTLE " Option 6", "Option 7", "Option 8", "Option 9" };
	static char buf[64];

	//static float color[4] = { 1.f, 1.f, 1.f, 1.f };
	static float color[4] = { gui.accent_color.r ,gui.accent_color.g ,gui.accent_color.b ,gui.accent_color.a };

	PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	PushStyleVar(ImGuiStyleVar_WindowRounding, 10);

	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	flags |= ImGuiWindowFlags_NoDecoration;
	//flags |= ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Hello, world!", NULL, flags); {

		auto window = GetCurrentWindow();
		auto draw = window->DrawList;
		auto pos = window->Pos;
		auto size = window->Size;
		auto style = GetStyle();

		gui.m_anim = ImLerp(gui.m_anim, 1.f, 0.045f);

		SetWindowSize(ImVec2(690, 500));

		//GetBackgroundDrawList()->AddImage(bg, ImVec2(0, 0), io.DisplaySize);
		GetBackgroundDrawList()->AddImage((ImTextureID)(uintptr_t)(bgID), ImVec2(0, 0), io.DisplaySize);

		static int ifont = 6;
		//ImGui::SliderInt("f", &ifont, 0, io.Fonts->Fonts.size()-1);

		draw->AddText(io.Fonts->Fonts[ifont], io.Fonts->Fonts[ifont]->FontSize, pos + ImVec2(170 / 2 - io.Fonts->Fonts[ifont]->CalcTextSizeA(io.Fonts->Fonts[ifont]->FontSize, FLT_MAX, 0, "NEVERLOSE").x / 2 + 1, 20), gui.accent_color.to_im_color(), "NEVERLOSE");
		draw->AddText(io.Fonts->Fonts[ifont], io.Fonts->Fonts[ifont]->FontSize, pos + ImVec2(170 / 2 - io.Fonts->Fonts[ifont]->CalcTextSizeA(io.Fonts->Fonts[ifont]->FontSize, FLT_MAX, 0, "NEVERLOSE").x / 2, 20), GetColorU32(ImGuiCol_Text), "NEVERLOSE");

		draw->AddLine(pos + ImVec2(0, size.y - 50), pos + ImVec2(170, size.y - 50), GetColorU32(ImGuiCol_WindowBg, 0.5f));

		draw->AddImageRounded((ImTextureID)(uintptr_t)(avatarID), pos + ImVec2(15, size.y - 40), pos + ImVec2(45, size.y - 10), ImVec2(0, 0), ImVec2(1, 1), ImColor(1.f, 1.f, 1.f, 1.f), 100);

		draw->AddText(pos + ImVec2(50, size.y - 40), gui.text.to_im_color(), "evrope");
		draw->AddText(pos + ImVec2(50, size.y - 25), gui.text_disabled.to_im_color(), "Till:");
		draw->AddText(pos + ImVec2(50 + CalcTextSize("Till: ").x, size.y - 25), gui.accent_color.to_im_color(), "Lifetime");

		SetCursorPos(ImVec2(10, 70));
		BeginChild("##tabs", ImVec2(150, size.y - 120));

		gui.group_title("Aimbot");
		if (gui.tab(ICON_FA_CROSSHAIRS, "Ragebot", gui.m_tab == 0) && gui.m_tab != 0)
			gui.m_tab = 0, gui.m_anim = 0.f;

		if (gui.tab(ICON_FA_GHOST, "Anti-aim", gui.m_tab == 1) && gui.m_tab != 1)
			gui.m_tab = 1, gui.m_anim = 0.f;

		if (gui.tab(ICON_FA_MOUSE, "Legitbot", gui.m_tab == 2) && gui.m_tab != 2)
			gui.m_tab = 2, gui.m_anim = 0.f;

		Spacing(), Spacing(), Spacing();

		gui.group_title("Visuals");
		if (gui.tab(ICON_FA_USER, "Players", gui.m_tab == 3) && gui.m_tab != 3)
			gui.m_tab = 3, gui.m_anim = 0.f;

		if (gui.tab(ICON_FA_PALLET, "World", gui.m_tab == 4) && gui.m_tab != 4)
			gui.m_tab = 4, gui.m_anim = 0.f;

		Spacing(), Spacing(), Spacing();

		gui.group_title("Miscellaneous");
		if (gui.tab(ICON_FA_HAMMER, "Main", gui.m_tab == 5) && gui.m_tab != 5)
			gui.m_tab = 5, gui.m_anim = 0.f;

		if (gui.tab(ICON_FA_CODE, "Scripts", gui.m_tab == 6) && gui.m_tab != 6)
			gui.m_tab = 6, gui.m_anim = 0.f;

		EndChild();

		SetCursorPos(ImVec2(190, 20));
		SurfImGui::Button(ICON_FA_SAVE " Save", ImVec2(100, 25));

		PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

		SetCursorPos(ImVec2(300, 20));
		BeginChild("##subtabs", ImVec2(240, 25));

		GetWindowDrawList()->AddRectFilled(GetWindowPos(), GetWindowPos() + GetWindowSize(), gui.button.to_im_color(), 4);
		GetWindowDrawList()->AddRect(GetWindowPos(), GetWindowPos() + GetWindowSize(), gui.border.to_im_color(), 4);

		for (int i = 0; i < gui.rage_subtabs.size(); ++i) {
			if (gui.subtab(gui.rage_subtabs.at(i), gui.m_rage_subtab == i, gui.rage_subtabs.size(), i == 0 ? ImDrawFlags_RoundCornersLeft : i == gui.rage_subtabs.size() ? ImDrawFlags_RoundCornersRight : 0) && gui.m_rage_subtab != i)
				gui.m_rage_subtab = i, gui.m_anim = 0.f;

			if (i != gui.rage_subtabs.size() - 1)
				SameLine();

		}

		EndChild();

		PopStyleVar();

		PushStyleVar(ImGuiStyleVar_Alpha, gui.m_anim);
		PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 8));

		SetCursorPos(ImVec2(185, 81 - (5 * gui.m_anim)));
		BeginChild("##childs", ImVec2(size.x - 200, size.y - 96));

		switch (gui.m_tab) {

		case 0:

			gui.group_box(ICON_FA_FEATHER " Feather", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, 210)); {

				SurfImGui::Checkbox("Skoro t'ma otstypit " ICON_FA_DAGGER, &bools[0]);
				SurfImGui::SliderInt("Slider", &ints[0], 0, 100, "%d%%");
				///*Surf*/ImGui::Combo("Combo", &combo, items.data(), items.size());
				//SurfImGui::InputText("Input", buf, sizeof buf);
				bool b = SurfImGui::ColorEdit4("Color", color, ALPHA);
				if (b)gui.accent_color = { color[0], color[1], color[2], color[3] };
				SurfImGui::Button("Button", ImVec2(GetWindowWidth(), 25));

			} gui.end_group_box();

			SameLine();

			gui.group_box(ICON_FA_CROWN " Crown", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {

				for (int i = 1; i < 50; ++i) {
					SurfImGui::Checkbox(std::to_string(i).c_str(), &bools[i]);

					if (i != 49)
						Separator();

				}

			} gui.end_group_box();

			break;

		case 1:

			gui.group_box(ICON_FA_BABY " Baby", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight() / 2 - GetStyle().ItemSpacing.y / 2)); {

			} gui.end_group_box();

			gui.group_box(ICON_FA_AD " Ad", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight() / 2 - GetStyle().ItemSpacing.y / 2)); {

			} gui.end_group_box();

			SameLine(), SetCursorPosY(0);

			gui.group_box("Non icon name", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {

			} gui.end_group_box();

			break;

		case 2:

			break;
		}

		EndChild();

		PopStyleVar(2);

	} ImGui::End();

	PopStyleVar();
	PopStyleVar();
}
