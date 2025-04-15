#define IMGUI_DEFINE_MATH_OPERATORS // access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"
using namespace ImGui;

/*
 * ImGUIUtilities::RangeSliderFloat
 *
 *	A slider with two handles to define a min max float range inside the slider.
 */
inline bool RangeSliderFloat(
	char const* label,
	float* vmin,
	float* vmax,
	float rangeMin,
	float rangeMax,
	bool fSlideBlock,
	const char* formatMin,
	const char* formatMax,
	ImGuiSliderFlags flags)
{
	ImGui::PushID(label);
	bool result = RangeSliderScalar(label, ImGuiDataType_Float, vmin, vmax, &rangeMin, &rangeMax, fSlideBlock, formatMin, formatMax, flags);
	ImGui::PopID();
	return result;
}


/*
 * ImGUIUtilities::RangeSliderScalar
 *
 *	A slider with two handles to define a min max range inside the slider.
 */
inline bool RangeSliderScalar(
	char const* label,
	ImGuiDataType data_type,
	void* p_dataMin,
	void* p_dataMax,
	const void* p_rangeMin,
	const void* p_rangeMax,
	bool fSlideBlock,		//if set, the min handle is not allowed to slide past the max and vice versa. Otherwise, the max handle gets pushed along by the min.
	const char* formatMin,
	const char* formatMax,
	ImGuiSliderFlags flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const float w = ImGui::CalcItemWidth();

	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f));
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

	ImGui::ItemSize(total_bb, style.FramePadding.y);

	// Default format string when passing NULL
	if (formatMin == nullptr)
		formatMin = ImGui::DataTypeGetInfo(data_type)->PrintFmt;
	if (formatMax == nullptr)
		formatMax = ImGui::DataTypeGetInfo(data_type)->PrintFmt;

	const ImGuiID idMin = window->GetID("Min");
	const ImRect frame_bb_Min(frame_bb.Min + ImVec2(0.0f, frame_bb.GetHeight() / 2.0f), frame_bb.Min + ImVec2(frame_bb.GetWidth(), frame_bb.GetHeight()));

	if (!ImGui::ItemAdd(frame_bb_Min, idMin, &frame_bb_Min))
		return false;

	const ImGuiID idMax = window->GetID("Max");
	const ImRect frame_bb_Max(frame_bb.Min, frame_bb.Min + ImVec2(frame_bb.GetWidth(), frame_bb.GetHeight() / 2.0f));

	if (!ImGui::ItemAdd(frame_bb_Max, idMax, &frame_bb_Max))
		return false;

	// Tabbing or CTRL-clicking on either Slider turns it into an input box
	const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
	bool temp_input_is_active_min = temp_input_allowed && ImGui::TempInputIsActive(idMin);
	bool temp_input_is_active_max = temp_input_allowed && ImGui::TempInputIsActive(idMax);

	const bool hoveredMin = !temp_input_is_active_max && ImGui::ItemHoverable(frame_bb_Min, idMin);
	if (!temp_input_is_active_min)
	{
		//bool focus_requested = temp_input_allowed && ImGui::FocusableItemRegister(window, idMin);
		//const bool clickedMin = (hoveredMin && g.IO.MouseClicked[0]);
		//if (focus_requested || clickedMin || g.NavActivateId == idMin || g.NavInputId == idMin)
		//{
		//	ImGui::SetActiveID(idMin, window);
		//	ImGui::SetFocusID(idMin, window);
		//	ImGui::FocusWindow(window);
		//	g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
		//	if (temp_input_allowed && (focus_requested || (clickedMin && g.IO.KeyCtrl) || g.NavInputId == idMin))
		//	{
		//		temp_input_is_active_min = true;
		//		ImGui::FocusableItemUnregister(window);
		//	}
		//}
		const bool clickedMin = (hoveredMin && g.IO.MouseClicked[0]);
		if (clickedMin || g.NavActivateId == idMin) {
			ImGui::SetActiveID(idMin, window);
			ImGui::SetFocusID(idMin, window);
			ImGui::FocusWindow(window);
			g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
			if (temp_input_allowed && ((clickedMin && g.IO.KeyCtrl))) {
				temp_input_is_active_min = true;
			}
		}
	}

	if (temp_input_is_active_min)
	{
		//NOTE: We always block going past the other value when typing. Otherwise in the process of typing, the other value would likely get moved, even if the final entered value is within range.
		// Ideally, we would only apply the changed value when the TempInputScalar loses focus or the user hits enter but there's no easy way to do this.
		bool fBlock = true;
		// Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
		bool clamp_to_min = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
		bool clamp_to_max = ((flags & ImGuiSliderFlags_AlwaysClamp) != 0) || fBlock;
		const void* p_clampMax = fBlock ? p_dataMax : p_rangeMax;
		return ImGui::TempInputScalar(frame_bb, idMin, "Min", data_type, p_dataMin, formatMin, clamp_to_min ? p_rangeMin : nullptr, clamp_to_max ? p_clampMax : nullptr);
	}

	const bool hoveredMax = !temp_input_is_active_min && ImGui::ItemHoverable(frame_bb_Max, idMax);
	if (!temp_input_is_active_max)
	{
		//bool focus_requested = temp_input_allowed && ImGui::FocusableItemRegister(window, idMax);
		//const bool clickedMax = (hoveredMax && g.IO.MouseClicked[0]);
		//if (focus_requested || clickedMax || g.NavActivateId == idMax || g.NavInputId == idMax)
		//{
		//	ImGui::SetActiveID(idMax, window);
		//	ImGui::SetFocusID(idMax, window);
		//	ImGui::FocusWindow(window);
		//	g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
		//	if (temp_input_allowed && (focus_requested || (clickedMax && g.IO.KeyCtrl) || g.NavInputId == idMax))
		//	{
		//		temp_input_is_active_max = true;
		//		ImGui::FocusableItemUnregister(window);
		//	}
		//}
		const bool clickedMax = (hoveredMax && g.IO.MouseClicked[0]);
		if (clickedMax || g.NavActivateId == idMax) {
			ImGui::SetActiveID(idMax, window);
			ImGui::SetFocusID(idMax, window);
			ImGui::FocusWindow(window);
			g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
			if (temp_input_allowed && ((clickedMax && g.IO.KeyCtrl))) {
				temp_input_is_active_max = true;
			}
		}
	}

	if (temp_input_is_active_max)
	{
		//NOTE: We always block going past the other value when typing. Otherwise in the process of typing, the other value would likely get moved, even if the final entered value is within range.
		// Ideally, we would only apply the changed value when the TempInputScalar loses focus or the user hits enter but there's no easy way to do this.
		bool fBlock = true;
		// Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
		bool clamp_to_min = ((flags & ImGuiSliderFlags_AlwaysClamp) != 0) || fBlock;
		bool clamp_to_max = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
		const void* p_clampMin = fBlock ? p_dataMin : p_rangeMin;
		return ImGui::TempInputScalar(frame_bb, idMax, "Max", data_type, p_dataMax, formatMax, clamp_to_min ? p_clampMin : nullptr, clamp_to_max ? p_rangeMax : nullptr);
	}


	// Slider behavior
	ImRect grab_bb_Min;
	bool minChanged = ImGui::SliderBehavior(frame_bb, idMin, data_type, p_dataMin, p_rangeMin, p_rangeMax, formatMin, flags, &grab_bb_Min);
	ImRect grab_bb_Max;
	bool maxChanged = ImGui::SliderBehavior(frame_bb, idMax, data_type, p_dataMax, p_rangeMin, p_rangeMax, formatMax, flags, &grab_bb_Max);

	//make sure the min never goes over the max
	if (minChanged)
	{
		if (ImGui::DataTypeCompare(data_type, p_dataMin, p_dataMax) == 1)
		{
			if (fSlideBlock)
			{
				ImGui::DataTypeClamp(data_type, p_dataMin, p_rangeMin, p_dataMax);
				grab_bb_Min = grab_bb_Max;
			}
			else
			{
				ImGui::DataTypeClamp(data_type, p_dataMax, p_dataMin, p_rangeMax);
				grab_bb_Max = grab_bb_Min;
			}
		}
		ImGui::MarkItemEdited(idMin);
	}
	if (maxChanged)
	{
		if (ImGui::DataTypeCompare(data_type, p_dataMin, p_dataMax) == 1)
		{
			if (fSlideBlock)
			{
				ImGui::DataTypeClamp(data_type, p_dataMax, p_dataMin, p_rangeMax);
				grab_bb_Max = grab_bb_Min;
			}
			else
			{
				ImGui::DataTypeClamp(data_type, p_dataMin, p_rangeMin, p_dataMax);
				grab_bb_Min = grab_bb_Max;
			}
		}
		ImGui::MarkItemEdited(idMax);
	}

	//Draw each half of the frame as needed
	const ImU32 frame_col_Min = ImGui::GetColorU32(g.ActiveId == idMin ? ImGuiCol_FrameBgActive : g.HoveredId == idMin ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	ImGui::PushClipRect(frame_bb_Min.Min, frame_bb_Min.Max, true);
	ImGui::RenderNavHighlight(frame_bb, idMin);
	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, frame_col_Min, true, g.Style.FrameRounding);

	//draw the other half of the Max handle while we have the clip set up, we draw it first so the min handle can cover it if they overlap
	window->DrawList->AddRectFilled(grab_bb_Max.Min, grab_bb_Max.Max, ImGui::GetColorU32(ImGuiCol_SliderGrab, 0.5f), style.GrabRounding);

	// Render grab
	if (grab_bb_Min.Max.x > grab_bb_Min.Min.x)
	{
		window->DrawList->AddRectFilled(grab_bb_Min.Min, grab_bb_Min.Max, frame_col_Min, style.GrabRounding); //The handle color is alpha so we need to clear the space first in case the other half of the max handle is below us.
		window->DrawList->AddRectFilled(grab_bb_Min.Min, grab_bb_Min.Max, ImGui::GetColorU32(g.ActiveId == idMin ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);
	}
	ImGui::PopClipRect();

	const ImU32 frame_col_Max = ImGui::GetColorU32(g.ActiveId == idMax ? ImGuiCol_FrameBgActive : g.HoveredId == idMax ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	ImGui::PushClipRect(frame_bb_Max.Min, frame_bb_Max.Max, true);
	ImGui::RenderNavHighlight(frame_bb, idMax);
	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, frame_col_Max, true, g.Style.FrameRounding);

	//draw the other half of the Min handle while we have the clip set up, we draw it first so the max handle can cover it if they overlap
	window->DrawList->AddRectFilled(grab_bb_Min.Min, grab_bb_Min.Max, ImGui::GetColorU32(ImGuiCol_SliderGrab, 0.5f), style.GrabRounding);

	// Render grab
	if (grab_bb_Max.Max.x > grab_bb_Max.Min.x)
	{
		window->DrawList->AddRectFilled(grab_bb_Max.Min, grab_bb_Max.Max, frame_col_Max, style.GrabRounding); //The handle color is alpha so we need to clear the space first in case the other half of the min handle is below us.
		window->DrawList->AddRectFilled(grab_bb_Max.Min, grab_bb_Max.Max, ImGui::GetColorU32(g.ActiveId == idMax ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);
	}
	ImGui::PopClipRect();

	//Draw a line covering the range
	float lineAlpha = 0.25f;
	float centerHeight = grab_bb_Min.GetCenter().y;
	float thickness = grab_bb_Min.GetHeight() * 0.5f;
	float xStart = grab_bb_Min.Max.x - 1.0f;
	float xEnd = grab_bb_Max.Min.x;
	if (xEnd > xStart)
		window->DrawList->AddLine(ImVec2(xStart, centerHeight), ImVec2(xEnd, centerHeight), ImGui::GetColorU32(ImGuiCol_SliderGrab, lineAlpha), thickness);

	//finally draw the overall border on top.
//	ImGui::RenderFrameBorder(frame_bb.Min, frame_bb.Max, g.Style.FrameRounding);

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	char value_buf[64];
	const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_dataMin, formatMin);
	if (g.LogEnabled)
		ImGui::LogSetNextTextDecoration("{", "}");
	ImGui::RenderTextClipped(frame_bb.Min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.1f, 0.5f));

	value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_dataMax, formatMax);
	if (g.LogEnabled)
		ImGui::LogSetNextTextDecoration("{", "}");
	ImGui::RenderTextClipped(frame_bb.Min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.9f, 0.5f));

	if (label_size.x > 0.0f)
		ImGui::RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
	return minChanged || maxChanged;
}
