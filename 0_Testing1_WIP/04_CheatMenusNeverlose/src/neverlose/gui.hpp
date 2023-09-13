#pragma once

#define  IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"

#include "color_t.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

class c_gui {

public:

	float m_anim = 0.f;
	int m_tab = 0;

	int m_rage_subtab = 0;
	vector < const char* > rage_subtabs = { "General", "Anti aim", "Subtab" };

	color_t accent_color = { 0.3f, 0.49f, 1.f, 1.f };
	//color_t accent_color = { 1.f, 1., 1.f, 1.f };

	color_t text = { 1.f, 1.f, 1.f, 1.f };
	color_t text_disabled = { 0.51f, 0.52f, 0.56f, 1.f };

	color_t border = { 1.f, 1.f, 1.f, 0.03f };

	color_t frame_inactive = { 0.023f, 0.039f, 0.07f, 1.f };
	color_t frame_active = { 0.043f, 0.07f, 0.137f, 1.f };

	color_t button = { 0.031f, 0.035f, 0.058f, 1.f };
	color_t button_hovered = { 0.050f, 0.054f, 0.078f, 1.f };
	color_t button_active = { 0.07f, 0.074f, 0.098f, 1.f };

	color_t group_box_bg = { 0.019f, 0.035f, 0.062f, 1.f };

	void render_circle_for_horizontal_bar(ImVec2 pos, ImColor color, float alpha);

	inline void group_title(const char* name) {

		SetCursorPosX(GetCursorPosX() + 10);
		PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 0.5f));
		Text(name);
		PopStyleColor();
	}

	void group_box(const char* name, ImVec2 size_arg);
	void end_group_box();

	bool tab(const char* icon, const char* label, bool selected);
	bool subtab(const char* label, bool selected, int size, ImDrawFlags flags);



	//IMGUI_API bool Checkbox2(const char* label, bool* v);
};


//inline c_gui gui;
extern c_gui gui;


//--

// Modified ImGui widgets

/*
namespace ImGuiEx {

	static inline bool Checkbox(const char* label, bool* v) {

		ImGuiWindow* window = GetCurrentWindow();
		ImDrawList* draw = window->DrawList;

		ImGuiContext& g = *GImGui;
		ImGuiStyle& style = g.Style;
		ImGuiID id = window->GetID(label);
		ImVec2 label_size = CalcTextSize(label, NULL, true);

		float w = GetWindowWidth();
		ImVec2 size = { 30, 17 };

		ImVec2 pos = window->DC.CursorPos;
		ImRect frame_bb(pos + ImVec2(w - size.x, 0), pos + ImVec2(w, size.y));
		ImRect total_bb(pos, pos + ImVec2(w, label_size.y));
		ItemAdd(total_bb, id);
		ItemSize(total_bb, style.FramePadding.y);

		bool hovered, held;
		bool pressed = ButtonBehavior(frame_bb, id, &hovered, &held);
		if (pressed) {

			*v = !(*v);
			MarkItemEdited(id);
		}

		static std::unordered_map < ImGuiID, float > values;
		auto value = values.find(id);
		if (value == values.end()) {

			values.insert({ id, 0.f });
			value = values.find(id);
		}

		value->second = ImLerp(value->second, (*v ? 1.f : 0.f), 0.08f);

		draw->AddText(ImVec2(total_bb.Min.x, frame_bb.GetCenter().y - label_size.y / 2), *v ? gui.text.to_im_color() : gui.text_disabled.to_im_color(), label);

		draw->AddRectFilled(frame_bb.Min, frame_bb.Max, gui.frame_inactive.to_im_color(), 10);
		draw->AddRectFilled(frame_bb.Min, frame_bb.Max, gui.frame_active.to_im_color(value->second), 10);

		draw->AddRect(frame_bb.Min, frame_bb.Max, gui.border.to_im_color(), 10);

		draw->AddCircleFilled(ImVec2(frame_bb.Min.x + 8 + (14 * value->second), frame_bb.GetCenter().y), 7, *v ? gui.accent_color.to_im_color() : gui.text_disabled.to_im_color(), 30);

		return pressed;
	}
}
*/
