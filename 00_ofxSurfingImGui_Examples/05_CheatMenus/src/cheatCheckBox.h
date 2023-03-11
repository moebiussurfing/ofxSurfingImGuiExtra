#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "imgui_tricks.hpp"

namespace ImGui
{
	static bool Checkbox44(const char* label, bool* v)
	{
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = CalcTextSize(label, NULL, true);

		const float w = GetWindowWidth() - 30;

		const float square_sz = 20;
		const ImVec2 pos = window->DC.CursorPos;
		const ImRect total_bb(pos, pos + ImVec2(w, square_sz + 10));
		ItemSize(total_bb, style.FramePadding.y);
		if (!ItemAdd(total_bb, id))
		{
			IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
			return false;
		}

		bool hovered, held;
		bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
		if (pressed)
		{
			*v = !(*v);
			MarkItemEdited(id);
		}

		float anim = ImTricks::Animations::FastFloatLerp(std::string(label).append("checkbox.anim"), *v, 0.f, 1.f, 0.04f);

		auto col = ImTricks::Animations::FastColorLerp(GetColorU32(ImGuiCol_FrameBg), GetColorU32(ImVec4{1,0,1,1}), anim);
		//auto col = ImTricks::Animations::FastColorLerp(GetColorU32(ImGuiCol_FrameBg), GetColorU32(ImGuiCol_Scheme), anim);

		window->DrawList->AddRectFilled({ total_bb.Max.x - square_sz, total_bb.Min.y }, { total_bb.Max.x, total_bb.Min.y + square_sz }, col, 2);
		RenderCheckMark(window->DrawList, { total_bb.Max.x - square_sz / 2 - 3.5f, total_bb.Min.y + square_sz / 2 - 3.5f }, GetColorU32(ImGuiCol_CheckMark, anim), 7.f);
		window->DrawList->AddRectFilled({ total_bb.Min.x, total_bb.Max.y - 1 }, total_bb.Max, GetColorU32(ImGuiCol_Border));

		RenderText({ total_bb.Min.x, total_bb.Max.y - label_size.y - 13 }, label);

		IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
		return pressed;
	}
}

namespace ofxSurfingHelpers
{








	/*
	How to add:

	Checkbox | Locate the imgui_widgets.cpp file in your source, control + f and search for checkbox, find "bool ImGui::Checkbox" and replace it with the code provided.

	Menu Source | pretty simple ig, just locate where your menu is in ur source and add it. very UD!

	any issues / questions DM me
	*/

	static bool Checkbox2(const char* label, bool* v)
	{
		ImGuiWindow* window = GetCurrentWindow();

		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;

		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = CalcTextSize(label, NULL, true);
		const ImRect check_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(label_size.y + style.FramePadding.y * 3.f, label_size.y + style.FramePadding.y * 3.f)); // We want a square shape to we use Y twice

		ItemSize(check_bb, style.FramePadding.y);

		ImRect total_bb = check_bb;

		if (label_size.x > 0)
			SameLine(0, style.ItemInnerSpacing.x);

		const ImRect text_bb(window->DC.CursorPos + ImVec2(0, style.FramePadding.y), window->DC.CursorPos + ImVec2(0, style.FramePadding.y) + label_size);

		if (label_size.x > 0) {

			ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
			total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
		}

		if (!ItemAdd(total_bb, id))
			return false;

		bool hovered, held;
		bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
		if (pressed)
			*v = !(*v);

		auto borderColor = ImColor(1, 1, 1, 255);
		auto topColor = ImColor(65, 64, 64, 255);
		auto bottomColor = ImColor(65, 64, 64, 255);
		auto topColorHovered = ImColor(65, 64, 64, 255);
		auto bottomColorHovered = ImColor(65, 64, 64, 255);
		auto checkedTopColor = ImColor(111, 3, 252);
		auto checkedBottomColor = ImColor(111, 3, 252);

		if (*v) {

			window->DrawList->AddRectFilledMultiColor(check_bb.Min + ImVec2(3, 3), check_bb.Max - ImVec2(3, 3), checkedTopColor, checkedTopColor, checkedBottomColor, checkedBottomColor);
			window->DrawList->AddRect(check_bb.Min + ImVec2(3, 3), check_bb.Max - ImVec2(3, 3), borderColor, 0, false, 1);
		}
		else {

			if (hovered) {

				window->DrawList->AddRectFilledMultiColor(check_bb.Min + ImVec2(3, 3), check_bb.Max - ImVec2(3, 3), topColorHovered, topColorHovered, bottomColorHovered, bottomColorHovered);
				window->DrawList->AddRect(check_bb.Min + ImVec2(3, 3), check_bb.Max - ImVec2(3, 3), borderColor, 0, false, 1);
			}
			else {

				window->DrawList->AddRectFilledMultiColor(check_bb.Min + ImVec2(3, 3), check_bb.Max - ImVec2(3, 3), topColor, topColor, bottomColor, bottomColor);
				window->DrawList->AddRect(check_bb.Min + ImVec2(3, 3), check_bb.Max - ImVec2(3, 3), borderColor, 0, false, 1);
			}
		}

		if (g.LogEnabled)
			LogRenderedText(&text_bb.Min, *v ? "[x]" : "[ ]");

		if (label_size.x > 0.0f) {


			RenderText(text_bb.Min + ImVec2(1.f, 0.f), label);
		}

		return pressed;
	}


	inline void drawWidgets()
	{

		// menu made by aware :)

	/*
		if (0) {
			ImGui::GetOverlayDrawList()->AddRectFilled(ImGui::GetIO().MousePos, ImVec2(ImGui::GetIO().MousePos.x + 5.f,
				ImGui::GetIO().MousePos.y + 5.f), ImColor(255, 255, 255));

			ImGuiStyle* style = &ImGui::GetStyle();

			ImVec4* colors = style->Colors;

			style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
			style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.0f, 0.0263f, 0.0357f, 1.00f);
			style->Colors[ImGuiCol_WindowBg] = ImColor(25, 25, 25);
			style->Colors[ImGuiCol_ChildBg] = ImColor(20, 20, 20);
			style->Colors[ImGuiCol_PopupBg] = ImVec4(0.080f, 0.080f, 0.080f, 0.940f);
			style->Colors[ImGuiCol_Border] = ImColor(57, 57, 57);
			style->Colors[ImGuiCol_BorderShadow] = ImColor(1, 1, 1);
			style->Colors[ImGuiCol_FrameBg] = ImColor(40, 40, 40);
			style->Colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40);
			style->Colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40);
			style->Colors[ImGuiCol_TitleBg] = ImVec4(0.102f, 0.090f, 0.122f, 1.000f);
			style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.102f, 0.090f, 0.122f, 1.000f);
			style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.102f, 0.090f, 0.122f, 1.000f);
			style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.263f, 0.357f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_CheckMark] = ImColor(MenuColor);
			style->Colors[ImGuiCol_SliderGrab] = ImColor(111, 0, 255);
			style->Colors[ImGuiCol_SliderGrabActive] = ImColor(111, 0, 255);
			style->Colors[ImGuiCol_Button] = ImColor(20, 20, 20);
			style->Colors[ImGuiCol_ButtonHovered] = ImColor(20, 20, 20);
			style->Colors[ImGuiCol_ButtonActive] = ImColor(20, 20, 20);
			style->Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_Column] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style->Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
			style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
			style->Colors[ImGuiCol_Separator] = ImColor(105, 0, 255);

			style->WindowRounding = 0;
		}
	*/

		static int tabb = 0;

		ImGui::SetNextWindowSize(ImVec2(450.000f, 550.000f), ImGuiCond_Once);


		ImGui::Begin(("cheat"), 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar);


		ImGui::BeginChild(("##backround"), ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar);
		{
			if (ImGui::Button("TAB 1", ImVec2(77, 20)))
			{
				tabb = 1;
			}


			ImGui::SameLine();


			if (ImGui::Button("TAB 2", ImVec2(77, 20)))
			{
				tabb = 2;
			}

			ImGui::SameLine();

			if (ImGui::Button("TAB 3", ImVec2(77, 20)))
			{
				tabb = 3;
			}

			ImGui::SameLine();

			if (ImGui::Button("TAB 4", ImVec2(77, 20)))
			{
				tabb = 4;
			}

			ImGui::SameLine();

			if (ImGui::Button("TAB 5", ImVec2(77, 20)))
			{
				tabb = 5;
			}



			// BOTTOM BAR BELOW TAB BUTTONS
			if (tabb == 1)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(111, 0, 255, 255)));


				ImGui::Button(" ", ImVec2(77, 3));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			else
			{

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 255)));


				ImGui::Button(" ", ImVec2(77, 3));

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}

			// BOTTOM BAR BELOW TAB BUTTONS

			if (tabb == 2)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(111, 0, 255, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			else
			{

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
			// BOTTOM BAR BELOW TAB BUTTONS

			if (tabb == 3)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(111, 0, 255, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			else
			{

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}

			// BOTTOM BAR BELOW TAB BUTTONS

			if (tabb == 4)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(111, 0, 255, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			else
			{

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
			// BOTTOM BAR BELOW TAB BUTTONS

			if (tabb == 5)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(111, 0, 255, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(111, 0, 255, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));


				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			else
			{

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::SameLine();

				ImGui::Button(" ", ImVec2(77, 3));

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}


			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(15, 15, 15, 255)));




			ImGui::BeginChild(("##backro3und"), ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar);
			{
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::SameLine();



				if (tabb == 1) 			// TAB 1 FEATURES
				{
					ImGui::BeginChild(("##tab1left"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{
						static bool yourbool = false;
						ImGui::Checkbox("Box ESP", &yourbool);
						ImGui::Checkbox("Box ESP", &yourbool);
						ImGui::Checkbox("Box ESP", &yourbool);
						ImGui::Checkbox("Box ESP", &yourbool);

						ImGui::EndChild();
					}

					ImGui::SameLine();

					ImGui::BeginChild(("##tab1right"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{
						ImGui::Text("13452345cghdfghqwreqwerqwerewqr");
						ImGui::Text("13452345cghdfghqwreqwerqwerewqr");
						ImGui::Text("13452345cghdfghqwreqwerqwerewqr");
						ImGui::Text("13452345cghdfghqwreqwerqwerewqr");
						ImGui::Text("13452345cghdfghqwreqwerqwerewqr");



						ImGui::EndChild();
					}
				}

				if (tabb == 2)			// TAB 2 FEATURES
				{
					ImGui::BeginChild(("##tab2left"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						//ImGui::Checkbox("Aimbot", &yourbool);

						ImGui::EndChild();
					}

					ImGui::SameLine();

					ImGui::BeginChild(("##tab2right"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{
						ImGui::Text("13452345cghdfghqwreqwerqwerewqr");
						ImGui::Text("13452345cghdfghqwreqwerqwerewqr");
						ImGui::Text("13452345cghdfghqwreqwerqwerewqr");
						ImGui::Text("13452345cghdfghqwreqwerqwerewqr");
						ImGui::Text("13452345cghdfghqwreqwerqwerewqr");


						static bool yourbool = false;
						ImGui::Checkbox("Box ESP", &yourbool);

						ImGui::EndChild();
					}
				}

				if (tabb == 3)			// TAB 3 FEATURES
				{
					ImGui::BeginChild(("##tab3left"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{
						ImGui::Text("adsafdasdfasdfqwreqwerqwerewqr");

						//ImGui::Checkbox("Exploit", &yourbool);

						ImGui::EndChild();
					}

					ImGui::SameLine();

					ImGui::BeginChild(("##tab3right"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						ImGui::Text("qwreqwerqwerewqr");
						static bool yourbool = false;
						ImGui::Checkbox("Box ESP", &yourbool);

						ImGui::EndChild();
					}
				}

				if (tabb == 4)			// TAB 4 FEATURES
				{
					ImGui::BeginChild(("##tab4left"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						//ImGui::Checkbox("Color", &yourbool);

						ImGui::EndChild();
					}

					ImGui::SameLine();

					ImGui::BeginChild(("##tab4right"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{



						ImGui::EndChild();
					}
				}

				if (tabb == 5)			// TAB 5 FEATURES
				{
					ImGui::BeginChild(("##tab5left"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{

						//ImGui::Checkbox("Checkbox", &yourbool);

						ImGui::EndChild();
					}

					ImGui::SameLine();

					ImGui::BeginChild(("##tab5right"), ImVec2(189, 455), true, ImGuiWindowFlags_NoScrollbar);
					{



						ImGui::EndChild();
					}
				}

				ImGui::EndChild();

			}

			ImGui::PopStyleColor();

			ImGui::EndChild();
		}




		ImGui::End();
	}

	//--

	/*
	IMGUI_API void  AddRectMultiColor(const ImVec2& p_min, const ImVec2& p_max, int alpha, ImU32 leftcolor, ImU32 rightcolor, float rounding, float thickness, float smooth = 350);
	IMGUI_API void  AddRectFilledMultiColorRounded(const ImVec2& p_min, const ImVec2& p_max, ImU32 bg_color, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left, float rounding, ImDrawFlags rounding_corners);
	IMGUI_API void  AddRectFilledMultiColorWithLean(const ImVec2& p_min, const ImVec2& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left, ImGuiDir direction, int leanamount);
	IMGUI_API void  AddRectFilledMultiColor(const ImVec2& p_min, const ImVec2& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
	*/


	struct button7Anims {
		float moveYaxis;
		float multicoloralpha;
	};
	static bool ButtonEx7(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags)
	{
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = CalcTextSize(label, NULL, true);
		ImDrawList* draw = GetWindowDrawList();

		static std::map<ImGuiID, button7Anims> anim; // #include <map> on top of this file, where is "imgui.h" located.
		auto it_anim = anim.find(id);
		if (it_anim == anim.end())
		{
			anim.insert({ id, {0.f, 0.f} });
			it_anim = anim.find(id);
		}

		ImVec2 pos = window->DC.CursorPos - ImVec2(0, it_anim->second.moveYaxis);
		if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
			pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
		ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect bb(pos, pos + size);
		ItemSize(size, style.FramePadding.y);
		if (!ItemAdd(bb, id))
			return false;

		if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
			flags |= ImGuiButtonFlags_Repeat;

		bool hovered, held;
		bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

		it_anim->second.moveYaxis = ImLerp(it_anim->second.moveYaxis, (hovered || held ? 5.f : 0), g.IO.DeltaTime * 15.f);

		if (hovered || held) {
			if (it_anim->second.multicoloralpha < 255.f)
				it_anim->second.multicoloralpha += 5.f / GetIO().Framerate * 160.f;
		}
		else {
			if (it_anim->second.multicoloralpha > 0.f)
				it_anim->second.multicoloralpha -= 5.f / GetIO().Framerate * 160.f;
		}


		// Render
		const ImU32 inside_solid_col = ImColor(5, 6, 43, 255);
		const ImU32 outside_col[2] = { ImColor(6, 210, 235, 255)/*topright*/, ImColor(167, 64, 254, 255)/*botleft*/ };
		const ImU32 inside_gradient_col[4] = { ImColor(168, 64, 255, (int)it_anim->second.multicoloralpha)/*topleft*/, ImColor(54, 131, 240, (int)it_anim->second.multicoloralpha)/*topright*/, ImColor(8, 208, 236, (int)it_anim->second.multicoloralpha)/*botright*/, ImColor(124, 66, 248, (int)it_anim->second.multicoloralpha)/*botleft*/ };
		draw->AddRectFilled(bb.Min, bb.Max, inside_solid_col, 6);
		//draw->AddRectMultiColor(bb.Min, bb.Max, 255, outside_col[0], outside_col[1], 6, 1.75f, 50.f);
		//draw->AddRectFilledMultiColorRounded(bb.Min, bb.Max, GetColorU32(ImGuiCol_WindowBg), inside_gradient_col[0], inside_gradient_col[1], inside_gradient_col[2], inside_gradient_col[3], 6, ImDrawCornerFlags_All);

		if (g.LogEnabled)
			LogSetNextTextDecoration("[", "]");
		RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

		IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
		return pressed;
	}
};
