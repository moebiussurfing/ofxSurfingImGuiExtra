#pragma once
#include "ofxSurfingImGui.h"

#include "gui.hpp"

using namespace ImGui;

#define SurfImGui ofxSurfingfImGui::ImGui

namespace ofxSurfingfImGui
{
	namespace ImGui {

		IMGUI_API bool          Button(const char* label, const ImVec2& size = ImVec2(0, 0));   // button
		IMGUI_API bool          Checkbox(const char* label, bool* v);
		IMGUI_API bool          BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
		IMGUI_API void          EndCombo(); // only call EndCombo() if BeginCombo() returns true!
		IMGUI_API bool          Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
		IMGUI_API bool          Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);      // Separate items with \0 within a string, end item-list with \0\0. e.g. "One\0Two\0Three\0"
		IMGUI_API bool          Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);

		//internal
		IMGUI_API bool          BeginComboPopup(ImGuiID popup_id, const ImRect& bb, ImGuiComboFlags flags);

		//?
		IMGUI_API void          EndPopup(); // only call EndCombo() if BeginCombo() returns true!

		IMGUI_API bool          SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
		IMGUI_API bool          SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);
		IMGUI_API bool          InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
		IMGUI_API bool          ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
		//IMGUI_API bool          ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
		IMGUI_API bool          ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);
		IMGUI_API bool          ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // display a color square/button, hover for details, return true when pressed.




		static void MarkItemEdited(ImGuiID id)
		{
			// This marking is solely to be able to provide info for IsItemDeactivatedAfterEdit().
			// ActiveId might have been released by the time we call this (as in the typical press/release button behavior) but still need to fill the data.
			ImGuiContext& g = *GImGui;
			if (g.ActiveId == id || g.ActiveId == 0)
			{
				g.ActiveIdHasBeenEditedThisFrame = true;
				g.ActiveIdHasBeenEditedBefore = true;
			}

			// We accept a MarkItemEdited() on drag and drop targets (see https://github.com/ocornut/imgui/issues/1875#issuecomment-978243343)
			// We accept 'ActiveIdPreviousFrame == id' for InputText() returning an edit after it has been taken ActiveId away (#4714)
			IM_ASSERT(g.DragDropActive || g.ActiveId == id || g.ActiveId == 0 || g.ActiveIdPreviousFrame == id);

			//IM_ASSERT(g.CurrentWindow->DC.LastItemId == id);
			g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_Edited;
		}


		//from imgui_widgets

		static bool ButtonEx(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags) {

			ImGuiWindow* window = GetCurrentWindow();

			ImGuiContext& g = *GImGui;
			ImGuiStyle& style = g.Style;
			ImGuiID id = window->GetID(label);
			ImVec2 label_size = CalcTextSize(label, 0, 1);

			ImVec2 pos = window->DC.CursorPos;
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

			// Render
			const ImU32 col = ((held && hovered) ? gui.button_active.to_im_color() : hovered ? gui.button_hovered.to_im_color() : gui.button.to_im_color());
			RenderNavHighlight(bb, id);
			RenderFrame(bb.Min, bb.Max, col, 0, 4);
			window->DrawList->AddRect(bb.Min, bb.Max, gui.border.to_im_color(), 4);

			window->DrawList->AddText(bb.GetCenter() - label_size / 2, hovered ? gui.text.to_im_color() : gui.text_disabled.to_im_color(), label);

			return pressed;
		}

		//IMGUI_API bool          InputTextEx(const char* label, const char* hint, char* buf, int buf_size, const ImVec2& size_arg, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);

		//IMGUI_API void          InputTextDeactivateHook(ImGuiID id);



			// Widgets: Selectables
	// - A selectable highlights when hovered, and can display another color when selected.
	// - Neighbors selectable extend their highlight bounds in order to leave no gap between them. This is so a series of selected Selectable appear contiguous.
		IMGUI_API bool          Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // "bool selected" carry the selection state (read-only). Selectable() is clicked is returns true so you can modify your selection state. size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height
		IMGUI_API bool          Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));      // "bool* p_selected" point to the selection state (read-write), as a convenient helper.



		IMGUI_API void          ColorEditOptionsPopup(const float* col, ImGuiColorEditFlags flags);
		IMGUI_API bool          SliderBehavior(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, void* p_v, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags, ImRect* out_grab_bb);
		template<typename T, typename SIGNED_T, typename FLOAT_T>   IMGUI_API bool  SliderBehaviorT(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, T* v, T v_min, T v_max, const char* format, ImGuiSliderFlags flags, ImRect* out_grab_bb);


		static const ImS32          IM_S32_MIN = INT_MIN;    // (-2147483647 - 1), (0x80000000);
		static const ImS32          IM_S32_MAX = INT_MAX;    // (2147483647), (0x7FFFFFFF)
		static const ImU32          IM_U32_MIN = 0;
		static const ImU32          IM_U32_MAX = UINT_MAX;   // (0xFFFFFFFF)
#ifdef LLONG_MIN
		static const ImS64          IM_S64_MIN = LLONG_MIN;  // (-9223372036854775807ll - 1ll);
		static const ImS64          IM_S64_MAX = LLONG_MAX;  // (9223372036854775807ll);
#else
		static const ImS64          IM_S64_MIN = -9223372036854775807LL - 1;
		static const ImS64          IM_S64_MAX = 9223372036854775807LL;
#endif
		static const ImU64          IM_U64_MIN = 0;
#ifdef ULLONG_MAX
		static const ImU64          IM_U64_MAX = ULLONG_MAX; // (0xFFFFFFFFFFFFFFFFull);
#else
		static const ImU64          IM_U64_MAX = (2ULL * 9223372036854775807LL + 1);
#endif



		//TODO
		static inline void AddRectFilledMultiColorRounded(ImDrawList* draw_list, const ImVec2& p_min, const ImVec2& p_max, ImU32 bg_color, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left, float rounding, ImDrawFlags rounding_corners = ImDrawFlags_RoundCornersAll)
		{
			rounding = ImMin(rounding, ImFabs(p_max.x - p_min.x) * (((rounding_corners & ImDrawCornerFlags_Top) == ImDrawCornerFlags_Top) || ((rounding_corners & ImDrawCornerFlags_Bot) == ImDrawCornerFlags_Bot) ? 0.5f : 1.0f) - 1.0f);
			rounding = ImMin(rounding, ImFabs(p_max.y - p_min.y) * (((rounding_corners & ImDrawCornerFlags_Left) == ImDrawCornerFlags_Left) || ((rounding_corners & ImDrawCornerFlags_Right) == ImDrawCornerFlags_Right) ? 0.5f : 1.0f) - 1.0f);

			if (rounding <= 0.0f || rounding_corners == 0)
				return;
			else
			{
				const float rounding_tl = (rounding_corners & ImDrawCornerFlags_TopLeft) ? rounding : 0.0f;
				const float rounding_tr = (rounding_corners & ImDrawCornerFlags_TopRight) ? rounding : 0.0f;
				const float rounding_br = (rounding_corners & ImDrawCornerFlags_BotRight) ? rounding : 0.0f;
				const float rounding_bl = (rounding_corners & ImDrawCornerFlags_BotLeft) ? rounding : 0.0f;

				const ImVec2 uv = draw_list->_Data->TexUvWhitePixel;
				draw_list->PrimReserve(6, 4);
				draw_list->PrimWriteIdx((ImDrawIdx)(draw_list->_VtxCurrentIdx)); draw_list->PrimWriteIdx((ImDrawIdx)(draw_list->_VtxCurrentIdx + 1)); draw_list->PrimWriteIdx((ImDrawIdx)(draw_list->_VtxCurrentIdx + 2));
				draw_list->PrimWriteIdx((ImDrawIdx)(draw_list->_VtxCurrentIdx)); draw_list->PrimWriteIdx((ImDrawIdx)(draw_list->_VtxCurrentIdx + 2)); draw_list->PrimWriteIdx((ImDrawIdx)(draw_list->_VtxCurrentIdx + 3));
				draw_list->PrimWriteVtx(p_min, uv, col_upr_left);
				draw_list->PrimWriteVtx(ImVec2(p_max.x, p_min.y), uv, col_upr_right);
				draw_list->PrimWriteVtx(p_max, uv, col_bot_right);
				draw_list->PrimWriteVtx(ImVec2(p_min.x, p_max.y), uv, col_bot_left);

				draw_list->PathLineTo(p_min);
				draw_list->PathArcTo(ImVec2(p_min.x + rounding_tl, p_min.y + rounding_tl), rounding_tl, 4.820f, 3.100f);
				draw_list->PathFillConvex(bg_color);

				draw_list->PathLineTo(ImVec2(p_max.x, p_min.y));
				draw_list->PathArcTo(ImVec2(p_max.x - rounding_tr, p_min.y + rounding_tr), rounding_tr, 6.3400f, 4.620f);
				draw_list->PathFillConvex(bg_color);

				draw_list->PathLineTo(ImVec2(p_max.x, p_max.y));
				draw_list->PathArcTo(ImVec2(p_max.x - rounding_br, p_max.y - rounding_br), rounding_br, 7.960f, 6.240f);
				draw_list->PathFillConvex(bg_color);

				draw_list->PathLineTo(ImVec2(p_min.x, p_max.y));
				draw_list->PathArcTo(ImVec2(p_min.x + rounding_bl, p_max.y - rounding_bl), rounding_bl, 9.5f, 7.770f);
				draw_list->PathFillConvex(bg_color);

			}
		}
	}
}