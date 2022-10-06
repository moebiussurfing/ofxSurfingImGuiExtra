#ifndef IMGUI_WIDGET_H
#define IMGUI_WIDGET_H

#include <functional>
#include <vector>
#include <algorithm>
#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <imgui_json.h>
#include <immat.h>

namespace ImGui {
enum ImGuiKnobType
{
    IMKNOB_TICK = 0,
    IMKNOB_TICK_DOT,
    IMKNOB_TICK_WIPER,
    IMKNOB_WIPER,
    IMKNOB_WIPER_TICK,
    IMKNOB_WIPER_DOT,
    IMKNOB_WIPER_ONLY,
    IMKNOB_STEPPED_TICK,
    IMKNOB_STEPPED_DOT,
    IMKNOB_SPACE,
};

struct ColorSet 
{
    ImVec4 base;
    ImVec4 hovered;
    ImVec4 active;
};

template<typename T, typename SIGNED_T>                     IMGUI_API T     RoundScalarWithFormatKnobT(const char* format, ImGuiDataType data_type, T v);
template<typename T, typename SIGNED_T, typename FLOAT_T>   IMGUI_API bool  SliderBehaviorKnobT(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, T* v, T v_min, T v_max, const char* format, float power, ImGuiSliderFlags flags, ImRect* out_grab_bb);
template<typename T, typename FLOAT_T>                      IMGUI_API float SliderCalcRatioFromValueT(ImGuiDataType data_type, T v, T v_min, T v_max, float power, float linear_zero_pos);

IMGUI_API bool SliderBehavior(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, void* p_v, const void* p_min, const void* p_max, const char* format, float power, ImGuiSliderFlags flags, ImRect* out_grab_bb);

IMGUI_API void UvMeter(char const *label, ImVec2 const &size, int *value, int v_min, int v_max, int steps = 10, int* stack = nullptr, int* count = nullptr);
IMGUI_API void UvMeter(char const *label, ImVec2 const &size, float *value, float v_min, float v_max, int steps = 10, float* stack = nullptr, int* count = nullptr);

IMGUI_API bool Knob(char const *label, float *p_value, float v_min, float v_max, float v_step, float v_default, float size,
                    ColorSet circle_color, ColorSet wiper_color, ColorSet track_color, ColorSet tick_color,
                    ImGuiKnobType type = IMKNOB_WIPER, char const *format = nullptr, int tick_steps = 0);

IMGUI_API bool Fader(const char* label, const ImVec2& size, int* v, const int v_min, const int v_max, const char* format = nullptr, float power = 1.0f);

IMGUI_API void RoundProgressBar(float radius, float *p_value, float v_min, float v_max, ColorSet bar_color, ColorSet progress_color, ColorSet text_color);

// Splitter
IMGUI_API bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size = -1.0f);

// Based on the code from: https://github.com/benoitjacquier/imgui
IMGUI_API bool ColorCombo(const char* label,ImVec4 *pColorOut=NULL,bool supportsAlpha=false,float width=0.f,bool closeWhenMouseLeavesIt=true);
// Based on the code from: https://github.com/benoitjacquier/imgui
IMGUI_API bool ColorChooser(bool* open,ImVec4* pColorOut=NULL, bool supportsAlpha=true);

// ToggleButton
IMGUI_API bool ToggleButton(const char* str_id, bool* v);
IMGUI_API bool ToggleButton(const char *str_id, bool *v, const ImVec2 &size);
IMGUI_API bool BulletToggleButton(const char* label,bool* v, ImVec2 &pos, ImVec2 &size);

// RotateButton
IMGUI_API bool RotateButton(const char* label, const ImVec2& size_arg, int rotate = 0);

// Input with int64
IMGUI_API bool InputInt64(const char* label, int64_t* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);

// CheckButton
IMGUI_API bool CheckButton(const char* label, bool* pvalue, bool useSmallButton = false, float checkedStateAlphaMult = 0.5f);

// ColoredButtonV1: code posted by @ocornut here: https://github.com/ocornut/imgui/issues/4722
// [Button rounding depends on the FrameRounding Style property (but can be overridden with the last argument)]
IMGUI_API bool ColoredButton(const char* label, const ImVec2& size, ImU32 text_color, ImU32 bg_color_1, ImU32 bg_color_2, float frame_rounding_override=-1.f);

// new ProgressBar
// Please note that you can tweak the "format" argument if you want to add a prefix (or a suffix) piece of text to the text that appears at the right of the bar.
// returns the value "fraction" in 0.f-1.f.
// It does not need any ID.
IMGUI_API float ProgressBar(const char* optionalPrefixText,float value,const float minValue=0.f,const float maxValue=1.f,const char* format="%1.0f%%",const ImVec2& sizeOfBarWithoutTextInPixels=ImVec2(-1,-1),
                const ImVec4& colorLeft=ImVec4(0,1,0,0.8),const ImVec4& colorRight=ImVec4(0,0.4,0,0.8),const ImVec4& colorBorder=ImVec4(0.25,0.25,1.0,1));

// ProgressBar with 0 as center
IMGUI_API void ProgressBarPanning(float fraction, const ImVec2& size_arg = ImVec2(-FLT_MIN, 0));

// new PlotEx
IMGUI_API int   PlotEx(ImGuiPlotType plot_type, const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 frame_size, bool b_tooltops = true, bool b_comband = false);
IMGUI_API void  PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float), bool b_tooltips = true, bool b_comband = false);
IMGUI_API void  PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), bool b_tooltips = true, bool b_comband = false);

// new menu item
IMGUI_API bool  MenuItemEx(const char* label, const char* icon, const char* shortcut = NULL, bool selected = false, bool enabled = true, const char* subscript = nullptr);
IMGUI_API bool  MenuItem(const char* label, const char* shortcut, bool selected, bool enabled, const char* subscript);  

// new Drag for timestamp(millisecond)
IMGUI_API bool DragTimeMS(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const int decimals = 3, ImGuiSliderFlags flags = 0);

// Slider 2D and Slider 3D 
IMGUI_API bool InputVec2(char const* pLabel, ImVec2* pValue, ImVec2 const vMinValue, ImVec2 const vMaxValue, float const fScale = 1.0f);
IMGUI_API bool InputVec3(char const* pLabel, ImVec4* pValue, ImVec4 const vMinValue, ImVec4 const vMaxValue, float const fScale = 1.0f);
IMGUI_API bool SliderScalar2D(char const* pLabel, float* fValueX, float* fValueY, const float fMinX, const float fMaxX, const float fMinY, const float fMaxY, float const fZoom = 1.0f);
IMGUI_API bool SliderScalar3D(char const* pLabel, float* pValueX, float* pValueY, float* pValueZ, float const fMinX, float const fMaxX, float const fMinY, float const fMaxY, float const fMinZ, float const fMaxZ, float const fScale = 1.0f);

IMGUI_API bool RangeSelect2D(char const* pLabel, float* pCurMinX, float* pCurMinY, float* pCurMaxX, float* pCurMaxY, float const fBoundMinX, float const fBoundMinY, float const fBoundMaxX, float const fBoundMaxY, float const fScale /*= 1.0f*/);
IMGUI_API bool RangeSelectVec2(const char* pLabel, ImVec2* pCurMin, ImVec2* pCurMax, ImVec2 const vBoundMin, ImVec2 const vBoundMax, float const fScale /*= 1.0f*/);

// Bezier Widget
IMGUI_API bool  BezierSelect(const char *label, const ImVec2 size, float P[5]);    // P[4] is curve presets(0 - 24)
IMGUI_API float BezierValue(float dt01, float P[4], int step = 0);


// Color Processing
// func: ImU32(*func)(float const x, float const y)
template < typename Type >
inline
Type	ScaleFromNormalized(Type const x, Type const newMin, Type const newMax)
{
	return x * (newMax - newMin) + newMin;
}
template < bool IsBilinear, typename FuncType >
inline
void DrawColorDensityPlotEx(ImDrawList* pDrawList, FuncType func, float minX, float maxX, float minY, float maxY, ImVec2 position, ImVec2 size, int resolutionX, int resolutionY)
{
	ImVec2 const uv = ImGui::GetFontTexUvWhitePixel();

	float const sx = size.x / ((float)resolutionX);
	float const sy = size.y / ((float)resolutionY);

	float const dy = 1.0f / ((float)resolutionY);
	float const dx = 1.0f / ((float)resolutionX);
	float const hdx = 0.5f / ((float)resolutionX);
	float const hdy = 0.5f / ((float)resolutionY);

	for (int i = 0; i < resolutionX; ++i)
	{
		float x0;
		float x1;
		if (IsBilinear)
		{
			x0 = ScaleFromNormalized(((float)i + 0) * dx, minX, maxX);
			x1 = ScaleFromNormalized(((float)i + 1) * dx, minX, maxX);
		}
		else
		{
			x0 = ScaleFromNormalized(((float)i + 0) * dx + hdx, minX, maxX);
		}

		for (int j = 0; j < resolutionY; ++j)
		{
			float y0;
			float y1;
			if (IsBilinear)
			{
				y0 = ScaleFromNormalized(((float)(j + 0) * dy), maxY, minY);
				y1 = ScaleFromNormalized(((float)(j + 1) * dy), maxY, minY);
			}
			else
			{
				y0 = ScaleFromNormalized(((float)(j + 0) * dy + hdy), maxY, minY);
			}

			ImU32 const col00 = func(x0, y0);
			if (IsBilinear)
			{
				ImU32 const col01 = func(x0, y1);
				ImU32 const col10 = func(x1, y0);
				ImU32 const col11 = func(x1, y1);
				pDrawList->AddRectFilledMultiColor(	position + ImVec2(sx * (i + 0), sy * (j + 0)),
													position + ImVec2(sx * (i + 1), sy * (j + 1)),
													col00, col10, col11, col01);
			}
			else
			{
				pDrawList->AddRectFilledMultiColor(	position + ImVec2(sx * (i + 0), sy * (j + 0)),
													position + ImVec2(sx * (i + 1), sy * (j + 1)),
													col00, col00, col00, col00);
			}
		}
	}
}
// func: ImU32(*func)(float const t)
template <bool IsBilinear, typename FuncType>
inline
void	DrawColorBandEx(ImDrawList* pDrawList, ImVec2 const vpos, ImVec2 const size, FuncType func, int division, float gamma)
{
	float const width = size.x;
	float const height = size.y;

	float const fSlice = static_cast<float>(division);

	ImVec2 dA(vpos);
	ImVec2 dB(vpos.x + width / fSlice, vpos.y + height);

	ImVec2 const dD(ImVec2(width / fSlice, 0));

	auto curColor =	[gamma, &func](float const x, float const)
					{
						return func(ImPow(x, gamma));
					};

	DrawColorDensityPlotEx< IsBilinear >(pDrawList, curColor, 0.0f, 1.0f, 0.0f, 0.0f, vpos, size, division, 1);
}
template <bool IsBilinear, typename FuncType>
inline
void	DrawColorRingEx(ImDrawList* pDrawList, ImVec2 const curPos, ImVec2 const size, float thickness_, FuncType func, int division, float colorOffset)
{
	float const radius = ImMin(size.x, size.y) * 0.5f;

	float const dAngle = -2.0f * IM_PI / ((float)division);
	float angle = 0; //2.0f * IM_PI / 3.0f;

	ImVec2 offset = curPos + ImVec2(radius, radius);
	if (size.x < size.y)
	{
		offset.y += 0.5f * (size.y - size.x);
	}
	else if (size.x > size.y)
	{
		offset.x += 0.5f * (size.x - size.y);
	}

	float const thickness = ImSaturate(thickness_) * radius;

	ImVec2 const uv = ImGui::GetFontTexUvWhitePixel();
	pDrawList->PrimReserve(division * 6, division * 4);
	for (int i = 0; i < division; ++i)
	{
		float x0 = radius * ImCos(angle);
		float y0 = radius * ImSin(angle);

		float x1 = radius * ImCos(angle + dAngle);
		float y1 = radius * ImSin(angle + dAngle);

		float x2 = (radius - thickness) * ImCos(angle + dAngle);
		float y2 = (radius - thickness) * ImSin(angle + dAngle);

		float x3 = (radius - thickness) * ImCos(angle);
		float y3 = (radius - thickness) * ImSin(angle);

		pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx));
		pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx + 1));
		pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx + 2));

		pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx));
		pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx + 2));
		pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx + 3));

		float const t0 = fmodf(colorOffset + ((float)i) / ((float)division), 1.0f);
		ImU32 const uCol0 = func(t0);

		if (IsBilinear)
		{
			float const t1 = fmodf(colorOffset + ((float)(i + 1)) / ((float)division), 1.0f);
			ImU32 const uCol1 = func(t1);
			pDrawList->PrimWriteVtx(offset + ImVec2(x0, y0), uv, uCol0);
			pDrawList->PrimWriteVtx(offset + ImVec2(x1, y1), uv, uCol1);
			pDrawList->PrimWriteVtx(offset + ImVec2(x2, y2), uv, uCol1);
			pDrawList->PrimWriteVtx(offset + ImVec2(x3, y3), uv, uCol0);
		}
		else
		{
			pDrawList->PrimWriteVtx(offset + ImVec2(x0, y0), uv, uCol0);
			pDrawList->PrimWriteVtx(offset + ImVec2(x1, y1), uv, uCol0);
			pDrawList->PrimWriteVtx(offset + ImVec2(x2, y2), uv, uCol0);
			pDrawList->PrimWriteVtx(offset + ImVec2(x3, y3), uv, uCol0);
		}
		angle += dAngle;
	}
}

IMGUI_API void DrawHueBand(ImVec2 const vpos, ImVec2 const size, int division, float alpha, float gamma, float offset = 0.0f);
IMGUI_API void DrawHueBand(ImVec2 const vpos, ImVec2 const size, int division, float colorStartRGB[3], float alpha, float gamma);
IMGUI_API void DrawLumianceBand(ImVec2 const vpos, ImVec2 const size, int division, ImVec4 const& color, float gamma);
IMGUI_API void DrawSaturationBand(ImVec2 const vpos, ImVec2 const size, int division, ImVec4 const& color, float gamma);
IMGUI_API void DrawContrastBand(ImVec2 const vpos, ImVec2 const size, ImVec4 const& color);
IMGUI_API bool ColorRing(const char* label, float thickness, int split);

// Color Selector
IMGUI_API void HueSelector(char const* label, ImVec2 const size, float* hueCenter, float* hueWidth, float* featherLeft, float* featherRight, float defaultVal, float ui_zoom = 1.0f, int division = 32, float alpha = 1.0f, float hideHueAlpha = 0.75f, float offset = 0.0f);
IMGUI_API void LumianceSelector(char const* label, ImVec2 const size, float* lumCenter, float defaultVal, float vmin, float vmax, float ui_zoom = 1.0f, int division = 32, float gamma = 1.f, bool rgb_color = false, ImVec4 const color = ImVec4(1, 1, 1, 1));
IMGUI_API void GammaSelector(char const* label, ImVec2 const size, float* gammaCenter, float defaultVal, float vmin, float vmax, float ui_zoom = 1.0f, int division = 32);
IMGUI_API void SaturationSelector(char const* label, ImVec2 const size, float* satCenter, float defaultVal, float vmin, float vmax, float ui_zoom = 1.0f, int division = 32, float gamma = 1.f, bool rgb_color = false, ImVec4 const color = ImVec4(1, 1, 1, 1));
IMGUI_API void ContrastSelector(char const* label, ImVec2 const size, float* conCenter, float defaultVal, float ui_zoom = 1.0f, bool rgb_color = false, ImVec4 const color = ImVec4(1, 1, 1, 1));
IMGUI_API void TemperatureSelector(char const* label, ImVec2 const size, float* tempCenter, float defaultVal, float vmin, float vmax, float ui_zoom = 1.0f, int division = 32);
IMGUI_API bool BalanceSelector(char const* label, ImVec2 const size, ImVec4 * rgba, ImVec4 defaultVal, ImVec2* offset = nullptr, float ui_zoom = 1.0f, float speed = 1.0f, int division = 128, float thickness = 1.0f, float colorOffset = 0);

// https://github.com/CedricGuillemet/imgInspect
/*
//example
Image pickerImage;
ImGui::ImageButton(pickerImage.textureID, ImVec2(pickerImage.mWidth, pickerImage.mHeight));
ImRect rc = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
ImVec2 mouseUVCoord = (io.MousePos - rc.Min) / rc.GetSize();
mouseUVCoord.y = 1.f - mouseUVCoord.y;
if (io.KeyShift && io.MouseDown[0] && mouseUVCoord.x >= 0.f && mouseUVCoord.y >= 0.f)
{
        int width = pickerImage.mWidth;
        int height = pickerImage.mHeight;

        ImGuiHelper::ImageInspect(width, height, pickerImage.GetBits(), mouseUVCoord, displayedTextureSize);
}
*/
IMGUI_API void ImageInspect(const int width,
                            const int height,
                            const unsigned char* const bits,
                            ImVec2 mouseUVCoord,
                            ImVec2 displayedTextureSize,
                            bool histogram_full = false,
                            int zoom_size = 8);

// Demo Window
#if IMGUI_BUILD_EXAMPLE
IMGUI_API void ShowExtraWidgetDemoWindow();
IMGUI_API void ShowImKalmanDemoWindow();
IMGUI_API void ShowImFFTDemoWindow();
IMGUI_API void ShowImSTFTDemoWindow();
#endif
} // namespace ImGui

namespace ImGui
{
// Extensions to ImDrawList
IMGUI_API void ImDrawListAddConvexPolyFilledWithVerticalGradient(ImDrawList* dl, const ImVec2* points, const int points_count, ImU32 colTop, ImU32 colBot, float miny=-1.f, float maxy=-1.f);
IMGUI_API void ImDrawListPathFillWithVerticalGradientAndStroke(ImDrawList* dl, const ImU32& fillColorTop, const ImU32& fillColorBottom, const ImU32& strokeColor, bool strokeClosed=false, float strokeThickness = 1.0f, float miny=-1.f, float maxy=-1.f);
IMGUI_API void ImDrawListPathFillAndStroke(ImDrawList* dl,const ImU32& fillColor,const ImU32& strokeColor,bool strokeClosed=false, float strokeThickness = 1.0f);
IMGUI_API void ImDrawListAddRect(ImDrawList* dl,const ImVec2& a, const ImVec2& b,const ImU32& fillColor,const ImU32& strokeColor,float rounding = 0.0f, int rounding_corners = 0,float strokeThickness = 1.0f);
IMGUI_API void ImDrawListAddRectWithVerticalGradient(ImDrawList* dl,const ImVec2& a, const ImVec2& b,const ImU32& fillColorTop,const ImU32& fillColorBottom,const ImU32& strokeColor,float rounding = 0.0f, int rounding_corners = 0,float strokeThickness = 1.0f);
IMGUI_API void ImDrawListAddRectWithVerticalGradient(ImDrawList* dl,const ImVec2& a, const ImVec2& b,const ImU32& fillColor,float fillColorGradientDeltaIn0_05,const ImU32& strokeColor,float rounding = 0.0f, int rounding_corners = 0,float strokeThickness = 1.0f);
IMGUI_API void ImDrawListPathArcTo(ImDrawList* dl,const ImVec2& centre,const ImVec2& radii, float amin, float amax, int num_segments = 10);
IMGUI_API void ImDrawListAddEllipse(ImDrawList* dl,const ImVec2& centre, const ImVec2& radii,const ImU32& fillColor,const ImU32& strokeColor,int num_segments = 12,float strokeThickness = 1.f);
IMGUI_API void ImDrawListAddEllipseWithVerticalGradient(ImDrawList* dl, const ImVec2& centre, const ImVec2& radii, const ImU32& fillColorTop, const ImU32& fillColorBottom, const ImU32& strokeColor, int num_segments = 12, float strokeThickness = 1.f);
IMGUI_API void ImDrawListAddCircle(ImDrawList* dl,const ImVec2& centre, float radius,const ImU32& fillColor,const ImU32& strokeColor,int num_segments = 12,float strokeThickness = 1.f);
IMGUI_API void ImDrawListAddCircleWithVerticalGradient(ImDrawList* dl, const ImVec2& centre, float radius, const ImU32& fillColorTop, const ImU32& fillColorBottom, const ImU32& strokeColor, int num_segments = 12, float strokeThickness = 1.f);
// Overload of ImDrawList::addPolyLine(...) that takes offset and scale:
IMGUI_API void ImDrawListAddPolyLine(ImDrawList *dl,const ImVec2* polyPoints,int numPolyPoints,ImU32 strokeColor=IM_COL32_WHITE,float strokeThickness=1.f,bool strokeClosed=false, const ImVec2 &offset=ImVec2(0,0), const ImVec2& scale=ImVec2(1,1));
IMGUI_API void ImDrawListAddConvexPolyFilledWithHorizontalGradient(ImDrawList *dl, const ImVec2 *points, const int points_count, ImU32 colLeft, ImU32 colRight, float minx=-1.f, float maxx=-1.f);
IMGUI_API void ImDrawListPathFillWithHorizontalGradientAndStroke(ImDrawList *dl, const ImU32 &fillColorLeft, const ImU32 &fillColorRight, const ImU32 &strokeColor, bool strokeClosed=false, float strokeThickness = 1.0f, float minx=-1.f,float maxx=-1.f);
IMGUI_API void ImDrawListAddRectWithHorizontalGradient(ImDrawList *dl, const ImVec2 &a, const ImVec2 &b, const ImU32 &fillColorLeft, const ImU32 &fillColoRight, const ImU32 &strokeColor, float rounding = 0.0f, int rounding_corners = 0, float strokeThickness = 1.0f);
IMGUI_API void ImDrawListAddEllipseWithHorizontalGradient(ImDrawList *dl, const ImVec2 &centre, const ImVec2 &radii, const ImU32 &fillColorLeft, const ImU32 &fillColorRight, const ImU32 &strokeColor, int num_segments = 12, float strokeThickness = 1.0f);
IMGUI_API void ImDrawListAddCircleWithHorizontalGradient(ImDrawList *dl, const ImVec2 &centre, float radius, const ImU32 &fillColorLeft, const ImU32 &fillColorRight, const ImU32 &strokeColor, int num_segments = 12, float strokeThickness = 1.0f);
IMGUI_API void ImDrawListAddRectWithHorizontalGradient(ImDrawList *dl, const ImVec2 &a, const ImVec2 &b, const ImU32 &fillColor, float fillColorGradientDeltaIn0_05, const ImU32 &strokeColor, float rounding = 0.0f, int rounding_corners = 0, float strokeThickness = 1.0f);
// Add Dashed line or circle
IMGUI_API void ImDrawListAddLineDashed(ImDrawList *dl, const ImVec2& a, const ImVec2& b, ImU32 col, float thickness = 1.0f, unsigned int segments = 10, unsigned int on_segments = 1, unsigned int off_segments = 1);
IMGUI_API void ImDrawListAddCircleDashed(ImDrawList *dl, const ImVec2& centre, float radius, ImU32 col, int num_segments = 12, float thickness = 1.0f, int on_segments = 1, int off_segments = 1);
IMGUI_API void ImDrawListPathArcToDashedAndStroke(ImDrawList *dl, const ImVec2& centre, float radius, float a_min, float a_max, ImU32 col, float thickness = 1.0f, int num_segments = 10, int on_segments = 1, int off_segments = 1);
// Add Rotate Image
IMGUI_API void ImDrawListAddImageRotate(ImDrawList *dl, ImTextureID tex_id, ImVec2 pos, ImVec2 size, float angle, ImU32 board_col = IM_COL32(0, 0, 0, 255));
} // namespace ImGui

namespace ImGui
{
// Vertical Text Helper
IMGUI_API ImVec2    ImCalcVerticalTextSize(const char* text, const char* text_end = NULL, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
IMGUI_API void      ImRenderTextVertical(const ImFont* font,ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin,  const char* text_end = NULL, float wrap_width = 0.0f, bool cpu_fine_clip = false, bool rotateCCW = false);
IMGUI_API void      ImAddTextVertical(ImDrawList* drawList,const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL,bool rotateCCW = false);
IMGUI_API void      ImAddTextVertical(ImDrawList* drawList,const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL,bool rotateCCW = false);
IMGUI_API void      ImRenderTextVerticalClipped(const ImVec2& pos_min, const ImVec2& pos_max, const char* text, const char* text_end, const ImVec2* text_size_if_known, const ImVec2& align = ImVec2(0.0f,0.0f), const ImVec2* clip_min = NULL, const ImVec2* clip_max = NULL,bool rotateCCW = false);
} //namespace ImGui

namespace ImGui
{
// Posted by @alexsr here: https://github.com/ocornut/imgui/issues/1901
// Sligthly modified to provide default behaviour with default args
IMGUI_API void      LoadingIndicatorCircle(const char* label, float indicatorRadiusFactor=1.f,
                                        const ImVec4* pOptionalMainColor=NULL, const ImVec4* pOptionalBackdropColor=NULL,
                                        int circle_count=8, const float speed=1.f);
// Posted by @zfedoran here: https://github.com/ocornut/imgui/issues/1901
// Sligthly modified to provide default behaviour with default args
IMGUI_API void      LoadingIndicatorCircle2(const char* label, float indicatorRadiusFactor=1.f, float indicatorRadiusThicknessFactor=1.f, const ImVec4* pOptionalColor=NULL);
} // namespace ImGui

namespace ImGui
{
class IMGUI_API Piano {
public:
    int key_states[256] = {0};
    void up(int key);
    void draw_keyboard(ImVec2 size, bool input = false);
    void down(int key, int velocity);
    void reset();
};
} // namespace ImGui

namespace ImGui
{

IMGUI_API void  ImSpectrogram(const ImMat& in_mat, ImMat& out_mat, int window = 512, bool stft = false, int hope = 128);

} // namespace ImGui

// custom draw leader
namespace ImGui
{
IMGUI_API void Circle(bool filled, bool arrow = false);
IMGUI_API void Square(bool filled, bool arrow = false);
IMGUI_API void BracketSquare(bool filled, bool arrow = false);
IMGUI_API void RoundSquare(bool filled, bool arrow = false);
IMGUI_API void GridSquare(bool filled, bool arrow = false);
IMGUI_API void Diamond(bool filled, bool arrow = false);
} // namespace ImGui

// custom badge draw button
namespace ImGui
{
IMGUI_API bool CircleButton(const char* id_str, bool filled, bool arrow = false);
IMGUI_API bool SquareButton(const char* id_str, bool filled, bool arrow = false);
IMGUI_API bool BracketSquareButton(const char* id_str, bool filled, bool arrow = false);
IMGUI_API bool RoundSquareButton(const char* id_str, bool filled, bool arrow = false);
IMGUI_API bool GridSquareButton(const char* id_str, bool filled, bool arrow = false);
IMGUI_API bool DiamondButton(const char* id_str, bool filled, bool arrow = false);
} // namespace ImGui

namespace ImGui
{
// Set of nice spinners for imgui
// https://github.com/dalerank/imspinner
#define DECLPROP(name,type,def) struct name { type value = def; operator type() { return value; } };
    enum SpinnerTypeT {
        e_st_rainbow = 0,
        e_st_angle,
        e_st_dots,
        e_st_ang,

        e_st_count
    };

    using float_ptr = float *;

    DECLPROP (SpinnerType, SpinnerTypeT, e_st_rainbow)
    DECLPROP (Radius, float, 16.f)
    DECLPROP (Speed, float, 1.f)
    DECLPROP (Thickness, float, 1.f)
    DECLPROP (Color, ImColor, 0xffffffff)
    DECLPROP (BgColor, ImColor, 0xffffffff)
    DECLPROP (Angle, float, IM_PI)
    DECLPROP (FloatPtr, float_ptr, nullptr)
    DECLPROP (Dots, int, 0)
    DECLPROP (MiddleDots, int, 0)
    DECLPROP (MinThickness, float, 0.f)
#undef DECLPROP

#define IMPLRPOP(basetype,type) basetype m_##type; \
                                void set##type(const basetype& v) { m_##type = v;} \
                                void set(type h) { m_##type = h.value;} \
                                template<typename First, typename... Args> \
                                void set(const type& h, const Args&... args) { set##type(h.value); this->template set<Args...>(args...); }
    struct SpinnerConfig {
        SpinnerConfig() {}

        template<typename none = void> void set() {}

        template<typename... Args>
        SpinnerConfig(const Args&... args) { this->template set<Args...>(args...); }

        IMPLRPOP(SpinnerTypeT, SpinnerType)
        IMPLRPOP(float, Radius)
        IMPLRPOP(float, Speed)
        IMPLRPOP(float, Thickness)
        IMPLRPOP(ImColor, Color)
        IMPLRPOP(ImColor, BgColor)
        IMPLRPOP(float, Angle)
        IMPLRPOP(float_ptr, FloatPtr)
        IMPLRPOP(int, Dots)
        IMPLRPOP(int, MiddleDots)
        IMPLRPOP(float, MinThickness)
    };
#undef IMPLRPOP

IMGUI_API void SpinnerRainbow(const char *label, float radius, float thickness, const ImColor &color, float speed);
IMGUI_API void SpinnerAng(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, const ImColor &bg = 0xffffff80, float speed = 2.8f, float angle = IM_PI);
IMGUI_API void SpinnerClock(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, const ImColor &bg = 0xffffff80, float speed = 2.8f);
IMGUI_API void SpinnerPulsar(const char *label, float radius, float thickness, const ImColor &bg = 0xffffff80, float speed = 2.8f, bool sequence = true);
IMGUI_API void SpinnerDoubleFadePulsar(const char *label, float radius, float thickness, const ImColor &bg = 0xffffff80, float speed = 2.8f);
IMGUI_API void SpinnerTwinPulsar(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, int rings = 2);
IMGUI_API void SpinnerFadePulsar(const char *label, float radius, const ImColor &color = 0xffffffff, float speed = 2.8f, int rings = 2);
IMGUI_API void SpinnerDots(const char *label, float *nextdot, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t dots = 12, size_t mdots = 6, float minth = -1.f);
IMGUI_API void SpinnerVDots(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t dots = 12, size_t mdots = 6);
IMGUI_API void SpinnerBounceDots(const char *label, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t dots = 3);
IMGUI_API void SpinnerFadeDots(const char *label, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t dots = 3);
IMGUI_API void SpinnerScaleDots(const char *label, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t dots = 3);
IMGUI_API void SpinnerMovingDots(const char *label, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t dots = 3);
IMGUI_API void SpinnerRotateDots(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, int dots = 2);
IMGUI_API void SpinnerTwinAng(const char *label, float radius1, float radius2, float thickness, const ImColor &color1 = 0xffffffff, const ImColor &color2 = 0xff0000ff, float speed = 2.8f);
IMGUI_API void SpinnerFilling(const char *label, float radius, float thickness, const ImColor &color1 = 0xffffffff, const ImColor &color2 = 0xff0000ff, float speed = 2.8f);
IMGUI_API void SpinnerTopup(const char *label, float radius1, float radius2, const ImColor &color = 0xff0000ff, const ImColor &fg = 0xffffffff, const ImColor &bg = 0xffffffff, float speed = 2.8f);
IMGUI_API void SpinnerTwinAng180(const char *label, float radius1, float radius2, float thickness, const ImColor &color1 = 0xffffffff, const ImColor &color2 = 0xff0000ff, float speed = 2.8f);
IMGUI_API void SpinnerTwinAng360(const char *label, float radius1, float radius2, float thickness, const ImColor &color1 = 0xffffffff, const ImColor &color2 = 0xff0000ff, float speed1 = 2.8f, float speed2 = 2.5f);
IMGUI_API void SpinnerIncDots(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t dots = 6);
IMGUI_API void SpinnerIncFullDots(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t dots = 4);
IMGUI_API void SpinnerFadeBars(const char *label, float w, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t bars = 3, bool scale = false);
IMGUI_API void SpinnerBarsRotateFade(const char *label, float rmin, float rmax , float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t bars = 6);
IMGUI_API void SpinnerBarsScaleMiddle(const char *label, float w, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t bars = 3);
IMGUI_API void SpinnerAngTwin(const char *label, float radius1, float radius2, float thickness, const ImColor &color = 0xffffffff, const ImColor &bg = 0xffffff80, float speed = 2.8f, float angle = IM_PI, size_t arcs = 1);
IMGUI_API void SpinnerIncScaleDots(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t dots = 6);
IMGUI_API void SpinnerBounceBall(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f);
IMGUI_API void SpinnerArcRotation(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t arcs = 4);
IMGUI_API void SpinnerArcFade(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t arcs = 4);
IMGUI_API void SpinnerFilledArcFade(const char *label, float radius, const ImColor &color = 0xffffffff, float speed = 2.8f, size_t arcs = 4);
IMGUI_API void SpinnerFilledArcColor(const char *label, float radius, const ImColor &color = 0xffff0000, const ImColor &bg = 0xffffffff, float speed = 2.8f, size_t arcs = 4);
IMGUI_API void SpinnerTwinBall(const char *label, float radius1, float radius2, float thickness, float b_thickness, const ImColor &ball = 0xffffffff, const ImColor &bg = 0xffffff80, float speed = 2.8f, size_t balls = 2);
IMGUI_API void SpinnerAngTriple(const char *label, float radius1, float radius2, float radius3, float thickness, const ImColor &c1 = 0xffffffff, const ImColor &c2 = 0xffffff80, const ImColor &c3 = 0xffffffff, float speed = 2.8f, float angle = IM_PI);
IMGUI_API void SpinnerAngEclipse(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, float angle = IM_PI);
IMGUI_API void SpinnerIngYang(const char *label, float radius, float thickness, bool reverse, float yang_detlta_r, const ImColor &colorI = 0xffffffff, const ImColor &colorY = 0xffffffff, float speed = 2.8f, float angle = IM_PI * 0.7f);
IMGUI_API void SpinnerGooeyBalls(const char *label, float radius, const ImColor &color = 0xffffffff, float speed = 2.8f);
IMGUI_API void SpinnerRotateGooeyBalls(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, float speed = 2.8f, int balls = 1);
IMGUI_API void SpinnerMoonLine(const char *label, float radius, float thickness, const ImColor &color = 0xffffffff, const ImColor &bg = 0xff000000, float speed = 2.8f, float angle = IM_PI);
template<SpinnerTypeT Type, typename... Args>
void Spinner(const char *label, const Args&... args)
{
    struct SpinnerDraw { SpinnerTypeT type; void (*func)(const char *, const SpinnerConfig &); }

    spinner_draw_funcs[e_st_count] = {
        { e_st_rainbow, [] (const char *label, const SpinnerConfig &c) { SpinnerRainbow(label, c.m_Radius, c.m_Thickness, c.m_Color, c.m_Speed); } },
        { e_st_angle, [] (const char *label, const SpinnerConfig &c) { SpinnerAng(label, c.m_Radius, c.m_Thickness, c.m_Color, c.m_BgColor, c.m_Speed, c.m_Angle); } },
        { e_st_dots, [] (const char *label, const SpinnerConfig &c) { SpinnerDots(label, c.m_FloatPtr, c.m_Radius, c.m_Thickness, c.m_Color, c.m_Speed, c.m_Dots, c.m_MiddleDots, c.m_MinThickness); } },
        { e_st_ang, [] (const char *label, const SpinnerConfig &c) { SpinnerAng(label, c.m_Radius, c.m_Thickness, c.m_Color, c.m_BgColor, c.m_Speed, c.m_Angle); } }
    };

    SpinnerConfig config(SpinnerType{Type}, args...);
    if (config.m_SpinnerType < sizeof(spinner_draw_funcs))
    {
        spinner_draw_funcs[config.m_SpinnerType].func(label, config);
    }
}
} // namespace ImGui

// CurveEdit from https://github.com/CedricGuillemet/ImGuizmo
namespace ImGui
{
struct IMGUI_API ImCurveEdit
{
#define CURVE_EDIT_FLAG_NONE            (0)
#define CURVE_EDIT_FLAG_VALUE_LIMITED   (1)
#define CURVE_EDIT_FLAG_SCROLL_V        (1<<1)
#define CURVE_EDIT_FLAG_MOVE_CURVE      (1<<2)
#define CURVE_EDIT_FLAG_KEEP_BEGIN_END  (1<<3)
#define CURVE_EDIT_FLAG_DOCK_BEGIN_END  (1<<4)

    enum CurveType
    {
        UnKnown = -1,
        Hold,
        Step,
        Linear,
        Smooth,
        QuadIn,
        QuadOut,
        QuadInOut,
        CubicIn,
        CubicOut,
        CubicInOut,
        SineIn,
        SineOut,
        SineInOut,
        ExpIn,
        ExpOut,
        ExpInOut,
        CircIn,
        CircOut,
        CircInOut,
        ElasticIn,
        ElasticOut,
        ElasticInOut,
        BackIn,
        BackOut,
        BackInOut,
        BounceIn,
        BounceOut,
        BounceInOut
    };

    struct KeyPoint
    {
        ImVec2 point {0, 0};
        ImCurveEdit::CurveType type {UnKnown};
    };

    struct keys
    {
        keys() {};
        keys(std::string _name, ImGui::ImCurveEdit::CurveType _type, ImU32 _color, bool _visible, float _min, float _max, float _default)
            : type(_type), name(_name), color(_color), visible(_visible), m_min(_min), m_max(_max), m_default(_default) {};
        std::vector<ImGui::ImCurveEdit::KeyPoint> points;
        ImGui::ImCurveEdit::CurveType type {Smooth};
        std::string name;
        ImU32 color;
        float m_min {0.f};
        float m_max {0.f};
        float m_default {0.f};
        bool visible {true};
        int64_t m_id {-1};
    };

    struct editPoint
    {
        int curveIndex;
        int pointIndex;
        bool operator <(const editPoint& other) const
        {
            if (curveIndex < other.curveIndex)
                return true;
            if (curveIndex > other.curveIndex)
                return false;
            if (pointIndex < other.pointIndex)
                return true;
            return false;
        }
    };
    struct Delegate
    {
        bool focused = false;
        virtual size_t GetCurveCount() = 0;
        virtual bool IsVisible(size_t /*curveIndex*/) { return true; }
        virtual CurveType GetCurveType(size_t /*curveIndex*/) const { return Linear; }
        virtual CurveType GetCurvePointType(size_t /*curveIndex*/, size_t /*pointIndex*/) const { return Linear; }
        virtual ImVec2& GetMin() = 0;
        virtual ImVec2& GetMax() = 0;
        virtual void SetMin(ImVec2 vmin, bool dock = false) = 0;
        virtual void SetMax(ImVec2 vmax, bool dock = false) = 0;
        virtual void MoveTo(float x) = 0;
        virtual void SetRangeX(float _min, float _max, bool dock = false) = 0;
        virtual size_t GetCurvePointCount(size_t curveIndex) = 0;
        virtual ImU32 GetCurveColor(size_t curveIndex) = 0;
        virtual std::string GetCurveName(size_t curveIndex) = 0;
        virtual KeyPoint* GetPoints(size_t curveIndex) = 0;
        virtual KeyPoint GetPoint(size_t curveIndex, size_t pointIndex) = 0;
        virtual int EditPoint(size_t curveIndex, size_t pointIndex, ImVec2 value, CurveType type) = 0;
        virtual void AddPoint(size_t curveIndex, ImVec2 value, CurveType type) = 0;
        virtual float GetValue(size_t curveIndex, float t) = 0;
        virtual void DeletePoint(size_t curveIndex, size_t pointIndex) = 0;
        virtual int AddCurve(std::string name, CurveType type, ImU32 color, bool visible, float _min, float _max, float _default) = 0;
        virtual void DeleteCurve(size_t curveIndex) = 0;
        virtual void DeleteCurve(std::string name) = 0;
        virtual int GetCurveIndex(std::string name) = 0;
        virtual void SetCurveColor(size_t curveIndex, ImU32 color) = 0;
        virtual void SetCurveName(size_t curveIndex, std::string name) = 0;
        virtual void SetCurveVisible(size_t curveIndex, bool visible) = 0;
        virtual float GetCurveMin(size_t curveIndex) = 0;
        virtual float GetCurveMax(size_t curveIndex) = 0;
        virtual float GetCurveDefault(size_t curveIndex) = 0;
        virtual void SetCurveMin(size_t curveIndex, float _min) = 0;
        virtual void SetCurveMax(size_t curveIndex, float _max) = 0;
        virtual void SetCurveDefault(size_t curveIndex, float _default) = 0;
        virtual void SetCurvePointDefault(size_t curveIndex, size_t pointIndex) = 0;

        virtual ImU32 GetBackgroundColor() { return 0xFF101010; }
        virtual ImU32 GetGraticuleColor() { return 0xFF202020; }
        virtual void SetBackgroundColor(ImU32 color) = 0;
        virtual void SetGraticuleColor(ImU32 color) = 0;
        // TODO::Dicky handle undo/redo thru this functions
        virtual void BeginEdit(int /*index*/) {}
        virtual void EndEdit() {}
    };
private:
    static int DrawPoint(ImDrawList* draw_list, ImVec2 pos, const ImVec2 size, const ImVec2 offset, bool edited);
public:
    static int GetCurveTypeName(char**& list);
    static float smoothstep(float edge0, float edge1, float t, CurveType type);
    static float distance(float x1, float y1, float x2, float y2);
    static float distance(float x, float y, float x1, float y1, float x2, float y2);
    static bool Edit(Delegate& delegate, const ImVec2& size, unsigned int id, unsigned int flags = CURVE_EDIT_FLAG_NONE, const ImRect* clippingRect = NULL, bool * changed = nullptr, ImVector<editPoint>* selectedPoints = NULL, float cursor_pos = -1.f);
};

struct IMGUI_API KeyPointEditor : public ImCurveEdit::Delegate
{
    KeyPointEditor() {}
    KeyPointEditor(ImU32 bg_color, ImU32 gr_color) 
        : BackgroundColor(bg_color), GraticuleColor(gr_color)
    {}
    ~KeyPointEditor() { mKeys.clear(); }

    KeyPointEditor& operator=(const KeyPointEditor& keypoint);

    ImU32 GetBackgroundColor() { return BackgroundColor; }
    ImU32 GetGraticuleColor() { return GraticuleColor; }
    void SetBackgroundColor(ImU32 color) { BackgroundColor = color; }
    void SetGraticuleColor(ImU32 color) { GraticuleColor = color; }
    size_t GetCurveCount() { return mKeys.size(); }
    std::string GetCurveName(size_t curveIndex) { if (curveIndex < mKeys.size()) return mKeys[curveIndex].name; return ""; }
    size_t GetCurvePointCount(size_t curveIndex) { if (curveIndex < mKeys.size()) return mKeys[curveIndex].points.size(); return 0; }
    ImU32 GetCurveColor(size_t curveIndex) { if (curveIndex < mKeys.size()) return mKeys[curveIndex].color; return 0; }
    ImCurveEdit::CurveType GetCurveType(size_t curveIndex) const { if (curveIndex < mKeys.size()) return mKeys[curveIndex].type; return ImCurveEdit::Linear; }
    void SetCurveColor(size_t curveIndex, ImU32 color) { if (curveIndex < mKeys.size()) mKeys[curveIndex].color = color; }
    void SetCurveName(size_t curveIndex, std::string name) { if (curveIndex < mKeys.size()) mKeys[curveIndex].name = name; }
    void SetCurveVisible(size_t curveIndex, bool visible) { if (curveIndex < mKeys.size()) mKeys[curveIndex].visible = visible; }
    ImCurveEdit::CurveType GetCurvePointType(size_t curveIndex, size_t point) const 
    {
        if (curveIndex < mKeys.size())
        {
            if (point < mKeys[curveIndex].points.size())
            {
                return mKeys[curveIndex].points[point].type;
            }
        }
        return ImCurveEdit::CurveType::Hold;
    }
    ImCurveEdit::KeyPoint* GetPoints(size_t curveIndex) { if (curveIndex < mKeys.size()) return mKeys[curveIndex].points.data(); return nullptr; }
    ImCurveEdit::KeyPoint GetPoint(size_t curveIndex, size_t pointIndex)
    {
        if (curveIndex < mKeys.size())
        {
            if (pointIndex < mKeys[curveIndex].points.size())
            {
                auto value_range = fabs(GetCurveMax(curveIndex) - GetCurveMin(curveIndex)); 
                ImCurveEdit::KeyPoint point = mKeys[curveIndex].points[pointIndex];
                point.point.y = point.point.y * value_range + GetCurveMin(curveIndex);
                return point;
            }
        }
        return {};
    }
    
    int EditPoint(size_t curveIndex, size_t pointIndex, ImVec2 value, ImCurveEdit::CurveType type)
    {
        if (curveIndex < mKeys.size())
        {
            if (pointIndex < mKeys[curveIndex].points.size())
            {
                auto value_range = fabs(GetCurveMax(curveIndex) - GetCurveMin(curveIndex)); 
                auto point_value = (value.y - GetCurveMin(curveIndex)) / (value_range + FLT_EPSILON);
                mKeys[curveIndex].points[pointIndex] = {ImVec2(value.x, point_value), type};
                SortValues(curveIndex);
                for (size_t i = 0; i < GetCurvePointCount(curveIndex); i++)
                {
                    if (mKeys[curveIndex].points[i].point.x == value.x)
                        return (int)i;
                }
            }
        }
        return -1;
    }

    void AddPoint(size_t curveIndex, ImVec2 value, ImCurveEdit::CurveType type)
    {
        if (curveIndex < mKeys.size())
        {
            mKeys[curveIndex].points.push_back({ImVec2(value.x, value.y), type});
            SortValues(curveIndex);
        }
    }
    void DeletePoint(size_t curveIndex, size_t pointIndex)
    {
        if (curveIndex < mKeys.size())
        {
            if (pointIndex < mKeys[curveIndex].points.size())
            {
                auto iter = mKeys[curveIndex].points.begin() + pointIndex;
                mKeys[curveIndex].points.erase(iter);
            }
        }
    }
    int AddCurve(std::string name, ImCurveEdit::CurveType type, ImU32 color, bool visible, float _min, float _max, float _default)
    {
        auto new_key = ImCurveEdit::keys(name, type, color, visible, _min, _max, _default);
        mKeys.push_back(new_key);
        return mKeys.size() - 1;
    }

    void DeleteCurve(size_t curveIndex)
    {
        if (curveIndex < mKeys.size())
        {
            auto iter = mKeys.begin() + curveIndex;
            mKeys.erase(iter);
        }
    }

    void DeleteCurve(std::string name)
    {
        int index = GetCurveIndex(name);
        if (index != -1)
        {
            DeleteCurve(index);
        }
    }

    int GetCurveIndex(std::string name)
    {
        int index = -1;
        auto iter = std::find_if(mKeys.begin(), mKeys.end(), [name](const ImCurveEdit::keys& key)
        {
            return key.name == name;
        });
        if (iter != mKeys.end())
        {
            index = iter - mKeys.begin();
        }
        return index;
    }
    float GetPointValue(size_t curveIndex, float t)
    {
        auto value_range = GetCurveMax(curveIndex) - GetCurveMin(curveIndex); 
        auto value = GetValue(curveIndex, t);
        value = (value - GetCurveMin(curveIndex)) / (value_range + FLT_EPSILON);
        return value;
    }
    float GetValue(size_t curveIndex, float t)
    {
        if (curveIndex <  mKeys.size())
        {
            auto range = GetMax() - GetMin() + ImVec2(1.f, 0.f); 
            auto value_range = fabs(GetCurveMax(curveIndex) - GetCurveMin(curveIndex)); 
            auto pointToRange = [&](ImVec2 pt) { return (pt - GetMin()) / range; };
            const size_t ptCount = GetCurvePointCount(curveIndex);
            if (ptCount <= 0)
                return 0;
            const ImCurveEdit::KeyPoint* pts = GetPoints(curveIndex);
            if (ptCount <= 1)
                return pointToRange(pts[0].point).x;
            int found_index = -1;
            for (int i = 0; i < ptCount - 1; i++)
            {
                if (t >= pts[i].point.x && t <= pts[i + 1].point.x)
                {
                    found_index = i;
                    break;
                }
            }
            if (found_index != -1)
            {
                const ImVec2 p1 = pointToRange(pts[found_index].point);
                const ImVec2 p2 = pointToRange(pts[found_index + 1].point);
                float x = (t - pts[found_index].point.x) / (pts[found_index + 1].point.x - pts[found_index].point.x);
                const ImVec2 sp = ImLerp(p1, p2, x);
                ImCurveEdit::CurveType type = (t - pts[found_index].point.x) < (pts[found_index + 1].point.x - t) ? pts[found_index].type : pts[found_index + 1].type;
                const float rt = ImCurveEdit::smoothstep(p1.x, p2.x, sp.x, type);
                const float v = ImLerp(p1.y, p2.y, rt);
                return v * value_range + GetCurveMin(curveIndex);
            }
        }
        return 0;
    }

    ImVec2& GetMax() { return mMax; }
    ImVec2& GetMin() { return mMin; }
    float GetCurveMin(size_t curveIndex) { if (curveIndex < mKeys.size()) return mKeys[curveIndex].m_min; return 0.f; }
    float GetCurveMax(size_t curveIndex) { if (curveIndex < mKeys.size()) return mKeys[curveIndex].m_max; return 0.f; }
    void SetCurveMin(size_t curveIndex, float _min) { if (curveIndex < mKeys.size()) mKeys[curveIndex].m_min = _min;  }
    void SetCurveMax(size_t curveIndex, float _max) { if (curveIndex < mKeys.size()) mKeys[curveIndex].m_max = _max;  }
    float GetCurveDefault(size_t curveIndex) { if (curveIndex < mKeys.size()) return mKeys[curveIndex].m_default; return 0.f; }
    void SetCurveDefault(size_t curveIndex, float _default) { if (curveIndex < mKeys.size()) mKeys[curveIndex].m_default = _default; }
    void SetCurvePointDefault(size_t curveIndex, size_t pointIndex)
    {
        if (curveIndex < mKeys.size())
        {
            if (pointIndex < mKeys[curveIndex].points.size())
            {
                auto value_range = fabs(GetCurveMax(curveIndex) - GetCurveMin(curveIndex)); 
                auto value_default = GetCurveDefault(curveIndex);
                value_default = (value_default - GetCurveMin(curveIndex)) / (value_range + FLT_EPSILON);
                mKeys[curveIndex].points[pointIndex].point.y = value_default;
                mKeys[curveIndex].points[pointIndex].type = GetCurveType(curveIndex);
            }
        }
    }
    void MoveTo(float x)
    {
        float offset = x - mMin.x;
        float length = fabs(mMax.x - mMin.x);
        mMin.x = x;
        mMax.x = mMin.x + length;
        for (size_t i = 0; i < mKeys.size(); i++)
        {
            for (auto iter = mKeys[i].points.begin(); iter != mKeys[i].points.end(); iter++)
            {
                iter->point.x += offset;
            }
        }
    }
    void SetRangeX(float _min, float _max, bool dock)
    {
        SetMin(ImVec2(_min, 0.f), dock);
        SetMax(ImVec2(_max, 1.f), dock);
    }
    void SetMin(ImVec2 vmin, bool dock = false)
    {
        if (dock)
        {
            for (size_t i = 0; i < mKeys.size(); i++)
            {
                // first get current begin value
                auto value = GetPointValue(i, mMin.x);
                if (vmin.x > mMin.x) value = GetPointValue(i, vmin.x);
                // second delete out of range points, keep begin end
                if (mKeys[i].points.size() > 2)
                {
                    for (auto iter = mKeys[i].points.begin() + 1; iter != mKeys[i].points.end() - 1;)
                    {
                        if (iter->point.x < vmin.x || iter->point.y < vmin.y)
                        {
                            iter = mKeys[i].points.erase(iter);
                        }
                        else
                            ++iter;
                    }
                }
                // finanl reset begin point
                if (mKeys[i].points.size() > 0)
                {
                    auto start_iter = mKeys[i].points.begin();
                    if (start_iter != mKeys[i].points.end()) 
                    {
                        start_iter->point.x = vmin.x;
                        start_iter->point.y = value;
                    }
                }
            }
        }
        mMin = vmin;
    }
    void SetMax(ImVec2 vmax, bool dock = false)
    {
        if (dock)
        {
            for (size_t i = 0; i < mKeys.size(); i++)
            {
                // first get current begin value
                auto value = GetPointValue(i, mMax.x);
                if (vmax.x < mMax.x) value = GetPointValue(i, vmax.x);
                // second delete out of range points, keep begin end
                if (mKeys[i].points.size() > 2)
                {
                    for (auto iter = mKeys[i].points.begin() + 1; iter != mKeys[i].points.end() - 1;)
                    {
                        if (iter->point.x > vmax.x)
                        {
                            iter = mKeys[i].points.erase(iter);
                        }
                        else
                            ++iter;
                    }
                }
                // finanl reset begin end point
                if (mKeys[i].points.size() > 0)
                {
                    auto end_iter = mKeys[i].points.begin() + mKeys[i].points.size() - 1;
                    if (end_iter != mKeys[i].points.end()) 
                    {
                        end_iter->point.x = vmax.x;
                        end_iter->point.y = value;
                    }
                }
            }
        }
        mMax = vmax;
    }
    bool IsVisible(size_t curveIndex) { if (curveIndex < mKeys.size()) return mKeys[curveIndex].visible; return false; }

    void Load(const imgui_json::value& value);
    void Save(imgui_json::value& value);

private:
    std::vector<ImCurveEdit::keys> mKeys;
    ImVec2 mMin {-1.f, -1.f};
    ImVec2 mMax {-1.f, -1.f};
    ImU32 BackgroundColor {IM_COL32(24, 24, 24, 255)};
    ImU32 GraticuleColor {IM_COL32(48, 48, 48, 128)};

private:
    void SortValues(size_t curveIndex)
    {
        if (curveIndex < mKeys.size())
        {
            auto b = std::begin(mKeys[curveIndex].points);
            auto e = std::begin(mKeys[curveIndex].points) + GetCurvePointCount(curveIndex);
            std::sort(b, e, [](ImCurveEdit::KeyPoint a, ImCurveEdit::KeyPoint b) { return a.point.x < b.point.x; });
        }
    }
};

IMGUI_API bool ImCurveEditKey(std::string button_lable, ImGui::ImCurveEdit::keys * key, std::string name, float _min, float _max, float _default, float space = 0);
IMGUI_API bool ImCurveCheckEditKey(std::string button_lable, ImGui::ImCurveEdit::keys * key, bool &check, std::string name, float _min, float _max, float _default, float space = 0);

} // namespace ImGui
#endif // IMGUI_WIDGET_H
