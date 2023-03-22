#pragma once

//https://yougame-biz.translate.goog/threads/255708/?_x_tr_sl=auto&_x_tr_tl=en-US&_x_tr_hl=en-US

#include "ofxSurfingImGui.h"
//#include "ofxImGui.h"

namespace ImGui {



	inline bool DiscordSliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const float w = 331;
		const float f = 30;

		const ImVec2 label_size = CalcTextSize(label, NULL, true);
		const ImRect frame_bb(window->DC.CursorPos + ImVec2(-20, 9.5f) + ImVec2(82, 0), window->DC.CursorPos - ImVec2(42, -4.5f) + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f));
		const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));
		const ImRect frame_bbb(window->DC.CursorPos + ImVec2(-20, -8), window->DC.CursorPos - ImVec2(-42, 9.0f) + ImVec2(w, f + style.FramePadding.y * 2.0f));


		ItemSize(total_bb, style.FramePadding.y);
		if (!ItemAdd(total_bb, id, &frame_bb))
			return false;


		if (format == NULL)
			format = DataTypeGetInfo(data_type)->PrintFmt;
		else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0)
			//format = PatchFormatStringFloatToInt(format);
			format = (format);



		static std::map<ImGuiID, float> animate;
		auto valuealpha = animate.find(id);
		if (valuealpha == animate.end())
		{
			animate.insert({ id, 0.0f });
			valuealpha = animate.find(id);
		}



		const bool hovered = ItemHoverable(frame_bb, id);                               // Размер ховера на слайдере
		const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;        // Если в меню не стоит флаг NoInput, разрешаем ввод через ctrl
		bool temp_input_is_active = temp_input_allowed && TempInputIsActive(id);        // Ввод числа вручную активен

		//if (hovered)
		//    g.MouseCursor = ImGuiMouseCursor_ResizeEW;
		//if (hovered && g.IO.KeyCtrl)                          //  Раскоментите что-бы была смена курсора (как в дискорде)
		//    g.MouseCursor = ImGuiMouseCursor_Hand;

		if (!temp_input_is_active)
		{
			const bool focus_requested = temp_input_allowed && FocusableItemRegister(window, id);
			const bool clicked = (hovered && g.IO.MouseClicked[0]);
			if (focus_requested || clicked || g.NavActivateId == id || g.NavInputSource == id)
				//if (focus_requested || clicked || g.NavActivateId == id || g.NavInputId == id)
			{
				SetActiveID(id, window);
				SetFocusID(id, window);
				FocusWindow(window);
				g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
				if (temp_input_allowed && (focus_requested || (clicked && g.IO.KeyCtrl) || g.NavInputSource == id))
					//if (temp_input_allowed && (focus_requested || (clicked && g.IO.KeyCtrl) || g.NavInputId == id))
				{
					temp_input_is_active = true;
					FocusableItemUnregister(window);
				}
			}
		}

		if (temp_input_is_active)
		{
			PushStyleColor(ImGuiCol_Text, ColorConvertU32ToFloat4(ImColor(255, 255, 255, 255)));
			//const bool is_clamp_input = (flags & ImGuiSliderFlags_ClampOnInput) != 0;
			const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
			return TempInputScalar(frame_bbb, id, label, data_type, p_data, format, is_clamp_input ? p_min : NULL, is_clamp_input ? p_max : NULL);
			PopStyleColor();
		}


		const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
		RenderNavHighlight(frame_bb, id);
		RenderFrame(frame_bb.Min, frame_bb.Max - ImVec2(0, 1.8), ImColor(79, 84, 92, 255), true, 10);       // Фрейм незаполненного слайдера (более серый цвет).


		ImRect grab_bar;
		const bool item_value_changed = SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bar);
		if (item_value_changed)
			MarkItemEdited(id);


		RenderFrame(ImVec2(frame_bb.Min.x, frame_bb.Min.y), ImVec2(grab_bar.Max.x, frame_bb.Max.y - 1.8), ImColor(88, 101, 242, 255), true, 10);    // Фрейм лилового цвета (заполненный)
		window->DrawList->AddCircleFilled(ImVec2(grab_bar.Min.x + 7, frame_bb.Min.y + 2), 6.5, ImColor(255, 255, 255, 255), 512);     // Кружочек :)




		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x - 231, frame_bb.Min.y + style.FramePadding.y - 20), label);     // Название слайдера




		char value_buf[64];
		const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);
		if (hovered || IsItemActive())
		{
			if (valuealpha->second < 255.f)
				valuealpha->second += 25.f;
			RenderFrame(ImVec2(grab_bar.Min.x - 10, frame_bb.Min.y - 37.8) /* + ImVec2(209, -30)*/, ImVec2(grab_bar.Max.x + 12, frame_bb.Max.y - 20.8), ImColor(32, 34, 37, (int)valuealpha->second), true, 5);
			RenderArrow(window->DrawList, ImVec2(grab_bar.Min.x + 1, frame_bb.Min.y - 21), ImColor(32, 34, 37, (int)valuealpha->second), ImGuiDir_Down, 1.5f);
			PushStyleColor(ImGuiCol_Text, ColorConvertFloat4ToU32(ImVec4((int)valuealpha->second, (int)valuealpha->second, (int)valuealpha->second, (int)valuealpha->second)));
			RenderTextClipped(ImVec2(grab_bar.Min.x - 10, frame_bb.Min.y - 37.8), ImVec2(grab_bar.Max.x + 12, frame_bb.Max.y - 20.8), value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));
			PopStyleColor();
		}       // Тут идёт появление фрейма с числом над слайдером
		else
		{
			if (valuealpha->second > 0.f)
				valuealpha->second -= 25.f;
		}


		IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
		return item_value_changed;
	}



	inline bool DiscordSliderF(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
	{
		return DiscordSliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
	}















	inline bool WindowsSliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const float w = 331;
		const float f = 30;

		const ImVec2 label_size = CalcTextSize(label, NULL, true);
		const ImRect frame_bb(window->DC.CursorPos + ImVec2(-20, 9.5f) + ImVec2(82, 0), window->DC.CursorPos - ImVec2(42, -4.5f) + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f));
		const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));
		const ImRect frame_bbb(window->DC.CursorPos + ImVec2(-20, -8), window->DC.CursorPos - ImVec2(-42, 9.0f) + ImVec2(w, f + style.FramePadding.y * 2.0f));


		ItemSize(total_bb, style.FramePadding.y);
		if (!ItemAdd(total_bb, id, &frame_bb))
			return false;


		if (format == NULL)
			format = DataTypeGetInfo(data_type)->PrintFmt;
		else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0)
			format = (format);



		const bool hovered = ItemHoverable(frame_bb, id);                               // Размер ховера на слайдере
		const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;        // Если в меню не стоит флаг NoInput, разрешаем ввод через ctrl
		bool temp_input_is_active = temp_input_allowed && TempInputIsActive(id);        // Ввод числа вручную активен

		//if (hovered)
		//    g.MouseCursor = ImGuiMouseCursor_ResizeEW;
		//if (hovered && g.IO.KeyCtrl)                          //  Раскоментите что-бы была смена курсора при ховере (в слайдере винды её нет)
		//    g.MouseCursor = ImGuiMouseCursor_Hand;

		if (!temp_input_is_active)
		{
			const bool focus_requested = temp_input_allowed && FocusableItemRegister(window, id);
			const bool clicked = (hovered && g.IO.MouseClicked[0]);
			if (focus_requested || clicked || g.NavActivateId == id || g.NavId == id)
			{
				SetActiveID(id, window);
				SetFocusID(id, window);
				FocusWindow(window);
				g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
				if (temp_input_allowed && (focus_requested || (clicked && g.IO.KeyCtrl) || g.NavId == id))
				{
					temp_input_is_active = true;
					FocusableItemUnregister(window);
				}
			}
		}

		if (temp_input_is_active)
		{
			PushStyleColor(ImGuiCol_Text, ColorConvertU32ToFloat4(ImColor(255, 255, 255, 255)));
			const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
			return TempInputScalar(frame_bbb, id, label, data_type, p_data, format, is_clamp_input ? p_min : NULL, is_clamp_input ? p_max : NULL);
			PopStyleColor();
		}


		const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
		RenderNavHighlight(frame_bb, id);
		RenderFrame(frame_bb.Min, frame_bb.Max - ImVec2(0, 3.8), ImColor(102, 102, 102, 255), true, 0);       // Фрейм незаполненного слайдера (более тёмно-серый цвет).


		ImRect grab_bar;
		const bool item_value_changed = SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bar);
		if (item_value_changed)
			MarkItemEdited(id);

		if (!hovered || !IsItemActive())
			RenderFrame(ImVec2(frame_bb.Min.x, frame_bb.Min.y), ImVec2(grab_bar.Max.x + 1, frame_bb.Max.y - 3.8), ImColor(76, 74, 72, 255), true, 0);    // Статик заполненный слайдер




		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x - 231, frame_bb.Min.y + style.FramePadding.y - 20), label);     // Название слайдера




		if (hovered)             // Элементы в этом контейнере работают только при ховер состоянии
		{
			RenderFrame(frame_bb.Min, frame_bb.Max - ImVec2(0, 5), ImColor(153, 153, 153, 255), true, 0);
			RenderFrame(ImVec2(frame_bb.Min.x, frame_bb.Min.y), ImVec2(grab_bar.Max.x, frame_bb.Max.y - 5), ImColor(76, 74, 72, 255), true, 0);
			RenderFrame(ImVec2(grab_bar.Min.x + 4, frame_bb.Min.y - 10), ImVec2(grab_bar.Max.x + 2, frame_bb.Max.y + 4.8), ImColor(242, 242, 242, 255), true, 10);
		}

		if (IsItemActive())      // Элементы в этом контейнере работают только при актив состоянии
		{
			RenderFrame(ImVec2(frame_bb.Min.x, frame_bb.Min.y), ImVec2(grab_bar.Max.x, frame_bb.Max.y - 5), ImColor(76, 74, 72, 255), true, 0);    // Фрейм зелёного цвета (заполненный)
			RenderFrame(ImVec2(grab_bar.Min.x + 4, frame_bb.Min.y - 10), ImVec2(grab_bar.Max.x + 2, frame_bb.Max.y + 4.8), ImColor(118, 118, 118, 255), true, 10);
		}



		char value_buf[64];
		const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);
		PushStyleColor(ImGuiCol_Text, ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 255)));
		RenderTextClipped(ImVec2(frame_bb.Min.x + 200, frame_bb.Min.y - 25.8), ImVec2(frame_bb.Max.x + 12, frame_bb.Max.y - 20.8), value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));
		PopStyleColor();



		IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
		return item_value_changed;
	}




	inline bool WindowsSliderF(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
	{
		return WindowsSliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
	}



};