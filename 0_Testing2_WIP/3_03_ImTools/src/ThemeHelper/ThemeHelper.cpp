//// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
///*
// * Copyright 2020 Stephane Cuillerdier (aka Aiekick)
// *
// * Licensed under the Apache License, Version 2.0 (the "License");
// * you may not use this file except in compliance with the License.
// * You may obtain a copy of the License at
// *
// *      http://www.apache.org/licenses/LICENSE-2.0
// *
// * Unless required by applicable law or agreed to in writing, software
// * distributed under the License is distributed on an "AS IS" BASIS,
// * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// * See the License for the specific language governing permissions and
// * limitations under the License.
// */
//#include "ThemeHelper.h"
//
//#include <Res/CustomFont.h>
//
//#include <Gui/ImWidgets.h>
//#include <Res/CustomFont.h>
//#include <ctools/cTools.h>
//#include <imgui/imgui.h>
//
//#include <imgui/imgui_internal.h>
//
////// STATIC ///////////////////////////////////////////////////////////////////////////////////
//
//#ifdef USE_SHADOW
//float ThemeHelper::puShadowStrength = 0.5f; // low value is darker than higt (0.0f - 2.0f)
//bool ThemeHelper::puUseShadow = false;
//bool ThemeHelper::puUseTextureForShadow = false;
//#endif
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//ThemeHelper::ThemeHelper()
//{
//	ImGui::CustomStyle::Init();
//	ApplyStyleColorsDefault();
//}
//
//ThemeHelper::~ThemeHelper() = default;
//
//void ThemeHelper::Draw(
//#ifdef USE_NODEGRAPH
//	ax::NodeEditor::EditorContext* vNodeEditorContext
//#endif
//)
//{
//	if (puShowImGuiStyleEdtor)
//	{
//#ifdef USE_NODEGRAPH
//		if (vNodeEditorContext)
//			ax::NodeEditor::SetCurrentEditor(vNodeEditorContext);
//#endif
//		ShowCustomImGuiStyleEditor(&puShowImGuiStyleEdtor);
//	}
//
//#ifdef USE_CODEEDITOR
//	if (puShowTextEditorStyleEditor)
//		ShowCustomTextEditorStyleEditor(&puShowTextEditorStyleEditor);
//#endif
//}
//
//void ThemeHelper::DrawMenu()
//{
//	if (ImGui::BeginMenu("General UI"))
//	{
//		if (ImGui::MenuItem("Orange/Blue (Default)")) ApplyStyleColorsOrangeBlue();
//		if (ImGui::MenuItem("Green/Blue")) ApplyStyleColorsGreenBlue();
//		if (ImGui::MenuItem("Classic")) ApplyStyleColorsClassic();
//		if (ImGui::MenuItem("Dark"))	ApplyStyleColorsDark();
//		if (ImGui::MenuItem("Darcula"))	ApplyStyleColorsDarcula();
//		if (ImGui::MenuItem("RedDark"))	ApplyStyleColorsRedDark();
//		if (ImGui::MenuItem("Light"))	ApplyStyleColorsLight();
//
//		ImGui::Separator();
//
//		ImGui::MenuItem("Customize", "", &puShowImGuiStyleEdtor);
//		
//		ImGui::Separator();
//		
//		if (ImGui::BeginMenu("Contrast"))
//		{
//			ImGui::DrawContrastWidgets();
//
//			ImGui::EndMenu();
//		}
//		ImGui::EndMenu();
//	}
//
//#ifdef USE_CODEEDITOR
//	if (ImGui::BeginMenu("Editor"))
//	{
//		if (ImGui::MenuItem("Dark (default)")) ApplyPalette(TextEditor::GetDarkPalette());
//		if (ImGui::MenuItem("Light")) ApplyPalette(TextEditor::GetLightPalette());
//		if (ImGui::MenuItem("Retro Blue")) ApplyPalette(TextEditor::GetRetroBluePalette());
//
//		ImGui::Separator();
//
//		ImGui::MenuItem("Customize", "", &puShowTextEditorStyleEditor);
//
//		ImGui::EndMenu();
//	}
//#endif
//
//	if (ImGui::BeginMenu("File Type Colors"))
//	{
//		bool fileColorUpdate = false;
//
//		for (auto &it : prFileTypeInfos)
//		{
//			fileColorUpdate |= ImGui::ColorEdit4(it.first.c_str(), &prFileTypeInfos[it.first].color.x);
//		}
//
//		if (fileColorUpdate)
//		{
//			ApplyFileTypeColors();
//		}
//
//		ImGui::EndMenu();
//	}
//}
//
///* default theme */
//void ThemeHelper::ApplyStyleColorsDefault()
//{
//	ApplyStyleColorsOrangeBlue();
//
//#ifdef USE_NODEGRAPH
//	ApplyDefaultGraphStyle();
//#endif
//
//#ifdef USE_CODEEDITOR
//	ApplyPalette(TextEditor::GetDarkPalette());
//#endif
//}
//
//#ifdef USE_NODEGRAPH
//void ThemeHelper::ApplyDefaultGraphStyle()
//{
//	prNodeGraphStyle = ax::NodeEditor::Style();
//	
//	// Main
//	prNodeGraphStyle.NodePadding = ImVec4(2.00f, 2.00f, 2.00f, 2.00f);
//	prNodeGraphStyle.NodeRounding = 2.00f;
//	prNodeGraphStyle.NodeBorderWidth = 1.00f;
//	prNodeGraphStyle.HoveredNodeBorderWidth = 2.00f;
//	prNodeGraphStyle.SelectedNodeBorderWidth = 3.00f;
//	prNodeGraphStyle.PinRounding = 2.00f;
//	prNodeGraphStyle.PinBorderWidth = 1.00f;
//	prNodeGraphStyle.LinkStrength = 100.00f;
//	prNodeGraphStyle.SourceDirection = ImVec2(1.00f, 0.00f);
//	prNodeGraphStyle.TargetDirection = ImVec2(-1.00f, 0.00f);
//	prNodeGraphStyle.ScrollDuration = 0.35f;
//	prNodeGraphStyle.FlowMarkerDistance = 30.00f;
//	prNodeGraphStyle.FlowSpeed = 150.00f;
//	prNodeGraphStyle.FlowDuration = 2.00f;
//	prNodeGraphStyle.PivotAlignment = ImVec2(0.50f, 0.50f);
//	prNodeGraphStyle.PivotSize = ImVec2(0.00f, 0.00f);
//	prNodeGraphStyle.PivotScale = ImVec2(1.00f, 1.00f);
//	prNodeGraphStyle.PinCorners = 15.00f;
//	prNodeGraphStyle.PinRadius = 0.00f;
//	prNodeGraphStyle.PinArrowSize = 0.00f;
//	prNodeGraphStyle.PinArrowWidth = 0.00f;
//	prNodeGraphStyle.GroupRounding = 6.00f;
//	prNodeGraphStyle.GroupBorderWidth = 1.00f;
//}
//#endif
//
//void ThemeHelper::ApplyStyleColorsOrangeBlue()
//{
//	const auto colors = prImGuiStyle.Colors;
//	colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
//	colors[ImGuiCol_TextDisabled] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
//	colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.16f, 0.17f, 1.00f);
//	colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.16f, 0.17f, 1.00f);
//	colors[ImGuiCol_PopupBg] = ImVec4(0.15f, 0.16f, 0.17f, 1.00f);
//	colors[ImGuiCol_Border] = ImVec4(0.26f, 0.28f, 0.29f, 1.00f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.32f, 0.34f, 0.36f, 1.00f);
//	colors[ImGuiCol_FrameBg] = ImVec4(0.21f, 0.29f, 0.36f, 1.00f);
//	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.71f);
//	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.93f);
//	colors[ImGuiCol_TitleBg] = ImVec4(0.18f, 0.20f, 0.21f, 1.00f);
//	colors[ImGuiCol_TitleBgActive] = ImVec4(0.23f, 0.25f, 0.26f, 1.00f);
//	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.30f, 0.33f, 0.35f, 1.00f);
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.16f, 0.17f, 1.00f);
//	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.21f, 0.29f, 0.36f, 0.89f);
//	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.13f, 0.52f, 0.94f, 0.45f);
//	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.13f, 0.71f, 1.00f, 0.89f);
//	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.24f, 0.78f, 0.78f, 0.31f);
//	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
//	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
//	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_Button] = ImVec4(1.00f, 0.60f, 0.00f, 0.80f);
//	colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.48f, 0.00f, 0.80f);
//	colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.40f, 0.00f, 0.80f);
//	colors[ImGuiCol_Header] = ImVec4(0.13f, 0.52f, 0.94f, 0.66f);
//	colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.52f, 0.94f, 1.00f);
//	colors[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.52f, 0.94f, 0.59f);
//	colors[ImGuiCol_Separator] = ImVec4(0.18f, 0.35f, 0.58f, 0.59f);
//	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
//	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
//	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
//	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
//	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
//	colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.41f, 0.68f, 0.00f);
//	colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
//	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
//	colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.41f, 0.68f, 0.00f);
//	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
//	colors[ImGuiCol_DockingPreview] = ImVec4(0.13f, 0.52f, 0.94f, 1.00f);
//	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.00f);
//	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
//	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
//	colors[ImGuiCol_PlotHistogram] = ImVec4(0.13f, 0.52f, 0.94f, 0.95f);
//	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
//	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
//	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
//	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
//	colors[ImGuiCol_TableRowBg] = ImVec4(0.15f, 0.16f, 0.17f, 1.00f);
//	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
//	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
//	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
//	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
//	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
//	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
//
//	colors[ImGuiCol_WindowBg].w = 0.70f;
//	colors[ImGuiCol_PopupBg].w = 0.70f;
//	colors[ImGuiCol_ChildBg].w = 0.00f;
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//
//	ImGui::CustomStyle::GoodColor = ImVec4(0.00f, 0.35f, 0.00f, 1.00f);
//	ImGui::CustomStyle::BadColor = ImVec4(0.35f, 0.00f, 0.00f, 1.00f);
//
//	// Main
//	prImGuiStyle.WindowPadding = ImVec2(4.00f, 4.00f);
//	prImGuiStyle.FramePadding = ImVec2(4.00f, 4.00f);
//	prImGuiStyle.ItemSpacing = ImVec2(4.00f, 4.00f);
//	prImGuiStyle.ItemInnerSpacing = ImVec2(4.00f, 4.00f);
//	prImGuiStyle.TouchExtraPadding = ImVec2(0.00f, 0.00f);
//	prImGuiStyle.IndentSpacing = 10;
//	prImGuiStyle.ScrollbarSize = 10.00f;
//	prImGuiStyle.GrabMinSize = 8.00f;
//
//	// Borders
//	prImGuiStyle.WindowBorderSize = 0.00f;
//	prImGuiStyle.ChildBorderSize = 0.00f;
//	prImGuiStyle.PopupBorderSize = 1.00f;
//	prImGuiStyle.FrameBorderSize = 0.00f;
//	prImGuiStyle.TabBorderSize = 0.00f;
//
//	// Rounding
//	prImGuiStyle.WindowRounding = 2.00f;
//	prImGuiStyle.ChildRounding = 2.00f;
//	prImGuiStyle.FrameRounding = 2.00f;
//	prImGuiStyle.PopupRounding = 2.00f;
//	prImGuiStyle.ScrollbarRounding = 2.00f;
//	prImGuiStyle.GrabRounding = 2.00f;
//	prImGuiStyle.TabRounding = 2.00f;
//
//	// Alignment
//	prImGuiStyle.WindowTitleAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.WindowMenuButtonPosition = ImGuiDir_Left;
//	prImGuiStyle.ColorButtonPosition = ImGuiDir_Right;
//	prImGuiStyle.ButtonTextAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.SelectableTextAlign = ImVec2(0.00f, 0.50f);
//
//	// Safe Area Padding
//	prImGuiStyle.DisplaySafeAreaPadding = ImVec2(3.00f, 3.00f);
//
//	prFileTypeInfos[".dbc"] = IGFD::FileStyle(ImVec4(0.1f, 0.9f, 0.5f, 1.0f), ICON_NDP_FILE_TEXT);
//
//	// dark theme so high color
//	ImGui::CustomStyle::GoodColor = ImVec4(0.0f, 0.353f, 0.0f, 1.0f);
//	ImGui::CustomStyle::BadColor = ImVec4(0.353f, 0.0f, 0.0f, 1.0f);
//
//	memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//
//	ApplyFileTypeColors();
//}
//
//void ThemeHelper::ApplyStyleColorsGreenBlue()
//{
//	const auto colors = prImGuiStyle.Colors;
//	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
//	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
//	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
//	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
//	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_FrameBg] = ImVec4(0.44f, 0.44f, 0.44f, 0.60f);
//	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.57f, 0.57f, 0.57f, 0.70f);
//	colors[ImGuiCol_FrameBgActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.80f);
//	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
//	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
//	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
//	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
//	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
//	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
//	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
//	colors[ImGuiCol_CheckMark] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
//	colors[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
//	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
//	colors[ImGuiCol_Button] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
//	colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
//	colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
//	colors[ImGuiCol_Header] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
//	colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
//	colors[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
//	colors[ImGuiCol_Separator] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
//	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
//	colors[ImGuiCol_SeparatorActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
//	colors[ImGuiCol_ResizeGrip] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
//	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
//	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
//	colors[ImGuiCol_Tab] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
//	colors[ImGuiCol_TabHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
//	colors[ImGuiCol_TabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
//	colors[ImGuiCol_TabUnfocused] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
//	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.36f, 0.36f, 0.36f, 0.54f);
//	colors[ImGuiCol_DockingPreview] = ImVec4(0.00f, 0.57f, 0.38f, 1.00f);
//	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
//	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
//	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
//	colors[ImGuiCol_PlotHistogram] = ImVec4(0.11f, 0.90f, 0.00f, 1.00f);
//	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
//	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
//	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
//	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
//	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
//	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
//	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
//	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
//	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
//	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
//
//	colors[ImGuiCol_WindowBg].w = 0.70f;
//	colors[ImGuiCol_PopupBg].w = 0.70f;
//	colors[ImGuiCol_ChildBg].w = 0.00f;
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//
//	prImGuiStyle.WindowPadding = ImVec2(4, 4);
//	prImGuiStyle.FramePadding = ImVec2(4, 4);
//	prImGuiStyle.ItemSpacing = ImVec2(4, 4);
//	prImGuiStyle.ItemInnerSpacing = ImVec2(4, 4);
//	prImGuiStyle.IndentSpacing = 10;
//	prImGuiStyle.ScrollbarSize = 20;
//	prImGuiStyle.GrabMinSize = 4;
//
//	prImGuiStyle.WindowRounding = 0;
//	prImGuiStyle.ChildRounding = 0;
//	prImGuiStyle.FrameRounding = 0;
//	prImGuiStyle.PopupRounding = 0;
//	prImGuiStyle.ScrollbarRounding = 0;
//	prImGuiStyle.GrabRounding = 0;
//	prImGuiStyle.TabRounding = 0;
//
//	prImGuiStyle.WindowBorderSize = 0;
//	prImGuiStyle.ChildBorderSize = 0;
//	prImGuiStyle.PopupBorderSize = 0;
//	prImGuiStyle.FrameBorderSize = 1;
//	prImGuiStyle.TabBorderSize = 0;
//
//	// Alignment
//	prImGuiStyle.WindowTitleAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.WindowMenuButtonPosition = ImGuiDir_Left;
//	prImGuiStyle.ColorButtonPosition = ImGuiDir_Right;
//	prImGuiStyle.ButtonTextAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.SelectableTextAlign = ImVec2(0.00f, 0.50f);
//
//	prFileTypeInfos[".dbc"].color = ImVec4(0.1f, 0.9f, 0.5f, 1.0f); // green high
//
//	// dark theme so high color
//	ImGui::CustomStyle::GoodColor = ImVec4(0.2f, 0.8f, 0.2f, 1.0f);
//	ImGui::CustomStyle::BadColor = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
//
//	memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//
//	ApplyFileTypeColors();
//}
//
//void ThemeHelper::ApplyStyleColorsClassic()
//{
//	const auto colors = prImGuiStyle.Colors;
//	colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
//	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
//	colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.85f);
//	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
//	colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_FrameBg] = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
//	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.47f, 0.47f, 0.69f, 0.40f);
//	colors[ImGuiCol_FrameBgActive] = ImVec4(0.42f, 0.41f, 0.64f, 0.69f);
//	colors[ImGuiCol_TitleBg] = ImVec4(0.27f, 0.27f, 0.54f, 0.83f);
//	colors[ImGuiCol_TitleBgActive] = ImVec4(0.32f, 0.32f, 0.63f, 0.87f);
//	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
//	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
//	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
//	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
//	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
//	colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
//	colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
//	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
//	colors[ImGuiCol_Button] = ImVec4(0.35f, 0.40f, 0.61f, 0.62f);
//	colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.48f, 0.71f, 0.79f);
//	colors[ImGuiCol_ButtonActive] = ImVec4(0.46f, 0.54f, 0.80f, 1.00f);
//	colors[ImGuiCol_Header] = ImVec4(0.40f, 0.40f, 0.90f, 0.45f);
//	colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
//	colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
//	colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
//	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
//	colors[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.70f, 0.90f, 1.00f);
//	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
//	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.78f, 0.82f, 1.00f, 0.60f);
//	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.82f, 1.00f, 0.90f);
//	colors[ImGuiCol_Tab] = ImVec4(0.34f, 0.34f, 0.68f, 0.79f);
//	colors[ImGuiCol_TabHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
//	colors[ImGuiCol_TabActive] = ImVec4(0.40f, 0.40f, 0.73f, 0.84f);
//	colors[ImGuiCol_TabUnfocused] = ImVec4(0.28f, 0.28f, 0.57f, 0.82f);
//	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.35f, 0.65f, 0.84f);
//	colors[ImGuiCol_DockingPreview] = ImVec4(0.29f, 0.00f, 1.00f, 1.00f);
//	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
//	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
//	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
//	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
//	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
//	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.27f, 0.27f, 0.38f, 1.00f);
//	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.45f, 1.00f);
//	colors[ImGuiCol_TableBorderLight] = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);
//	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
//	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
//	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
//	colors[ImGuiCol_NavHighlight] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
//	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
//	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
//	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
//
//	colors[ImGuiCol_WindowBg].w = 0.70f;
//	colors[ImGuiCol_PopupBg].w = 0.70f;
//	colors[ImGuiCol_ChildBg].w = 0.00f;
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//
//	prImGuiStyle.WindowPadding = ImVec2(4, 4);
//	prImGuiStyle.FramePadding = ImVec2(4, 4);
//	prImGuiStyle.ItemSpacing = ImVec2(4, 4);
//	prImGuiStyle.ItemInnerSpacing = ImVec2(4, 4);
//	prImGuiStyle.IndentSpacing = 10;
//	prImGuiStyle.ScrollbarSize = 20;
//	prImGuiStyle.GrabMinSize = 4;
//
//	prImGuiStyle.WindowRounding = 0;
//	prImGuiStyle.ChildRounding = 0;
//	prImGuiStyle.FrameRounding = 0;
//	prImGuiStyle.PopupRounding = 0;
//	prImGuiStyle.ScrollbarRounding = 0;
//	prImGuiStyle.GrabRounding = 0;
//	prImGuiStyle.TabRounding = 0;
//
//	prImGuiStyle.WindowBorderSize = 0;
//	prImGuiStyle.ChildBorderSize = 0;
//	prImGuiStyle.PopupBorderSize = 0;
//	prImGuiStyle.FrameBorderSize = 1;
//	prImGuiStyle.TabBorderSize = 0;
//
//	// Alignment
//	prImGuiStyle.WindowTitleAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.WindowMenuButtonPosition = ImGuiDir_Left;
//	prImGuiStyle.ColorButtonPosition = ImGuiDir_Right;
//	prImGuiStyle.ButtonTextAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.SelectableTextAlign = ImVec2(0.00f, 0.50f);
//
//	prFileTypeInfos[".dbc"].color = ImVec4(0.1f, 0.9f, 0.5f, 1.0f); // green high
//
//	// dark theme so high color
//	ImGui::CustomStyle::GoodColor = ImVec4(0.2f, 0.8f, 0.2f, 1.0f);
//	ImGui::CustomStyle::BadColor = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
//
//	memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//
//	ApplyFileTypeColors();
//}
//
//void ThemeHelper::ApplyStyleColorsDark()
//{
//	const auto colors = prImGuiStyle.Colors;
//	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
//	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
//	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
//	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
//	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
//	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
//	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
//	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
//	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
//	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
//	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
//	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
//	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
//	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
//	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
//	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
//	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
//	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
//	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
//	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
//	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
//	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
//	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
//	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
//	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
//	colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
//	colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
//	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
//	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
//	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
//	colors[ImGuiCol_DockingPreview] = ImVec4(0.02f, 0.00f, 1.00f, 1.00f);
//	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
//	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
//	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
//	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
//	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
//	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
//	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
//	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
//	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
//	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
//	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
//	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
//	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
//	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
//
//	colors[ImGuiCol_WindowBg].w = 0.70f;
//	colors[ImGuiCol_PopupBg].w = 0.70f;
//	colors[ImGuiCol_ChildBg].w = 0.00f;
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//
//	prImGuiStyle.WindowPadding = ImVec2(4, 4);
//	prImGuiStyle.FramePadding = ImVec2(4, 4);
//	prImGuiStyle.ItemSpacing = ImVec2(4, 4);
//	prImGuiStyle.ItemInnerSpacing = ImVec2(4, 4);
//	prImGuiStyle.IndentSpacing = 10;
//	prImGuiStyle.ScrollbarSize = 20;
//	prImGuiStyle.GrabMinSize = 4;
//
//	prImGuiStyle.WindowRounding = 0;
//	prImGuiStyle.ChildRounding = 0;
//	prImGuiStyle.FrameRounding = 0;
//	prImGuiStyle.PopupRounding = 0;
//	prImGuiStyle.ScrollbarRounding = 0;
//	prImGuiStyle.GrabRounding = 0;
//	prImGuiStyle.TabRounding = 0;
//
//	prImGuiStyle.WindowBorderSize = 0;
//	prImGuiStyle.ChildBorderSize = 0;
//	prImGuiStyle.PopupBorderSize = 0;
//	prImGuiStyle.FrameBorderSize = 1;
//	prImGuiStyle.TabBorderSize = 0;
//
//	// Alignment
//	prImGuiStyle.WindowTitleAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.WindowMenuButtonPosition = ImGuiDir_Left;
//	prImGuiStyle.ColorButtonPosition = ImGuiDir_Right;
//	prImGuiStyle.ButtonTextAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.SelectableTextAlign = ImVec2(0.00f, 0.50f);
//
//	prFileTypeInfos[".dbc"].color = ImVec4(0.1f, 0.9f, 0.5f, 1.0f); // green high
//
//	// dark theme so high color
//	ImGui::CustomStyle::GoodColor = ImVec4(0.2f, 0.8f, 0.2f, 1.0f);
//	ImGui::CustomStyle::BadColor = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
//
//	memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//
//	ApplyFileTypeColors();
//}
//
//void ThemeHelper::ApplyStyleColorsLight()
//{
//	const auto colors = prImGuiStyle.Colors;
//	colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
//	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
//	colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
//	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
//	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
//	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
//	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
//	colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
//	colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
//	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
//	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
//	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
//	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
//	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
//	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
//	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
//	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
//	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
//	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
//	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
//	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
//	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
//	colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
//	colors[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.35f, 0.35f, 0.17f);
//	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
//	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
//	colors[ImGuiCol_Tab] = ImVec4(0.76f, 0.80f, 0.84f, 0.93f);
//	colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
//	colors[ImGuiCol_TabActive] = ImVec4(0.60f, 0.73f, 0.88f, 1.00f);
//	colors[ImGuiCol_TabUnfocused] = ImVec4(0.92f, 0.93f, 0.94f, 0.99f);
//	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.74f, 0.82f, 0.91f, 1.00f);
//	colors[ImGuiCol_DockingPreview] = ImVec4(0.00f, 0.01f, 1.00f, 1.00f);
//	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
//	colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
//	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
//	colors[ImGuiCol_PlotHistogram] = ImVec4(0.02f, 0.00f, 1.00f, 1.00f);
//	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
//	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
//	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);
//	colors[ImGuiCol_TableBorderLight] = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);
//	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
//	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
//	colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
//	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
//	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
//	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
//	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
//
//	colors[ImGuiCol_WindowBg].w = 0.70f;
//	colors[ImGuiCol_PopupBg].w = 0.70f;
//	colors[ImGuiCol_ChildBg].w = 0.00f;
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//
//	prImGuiStyle.WindowPadding = ImVec2(4, 4);
//	prImGuiStyle.FramePadding = ImVec2(4, 4);
//	prImGuiStyle.ItemSpacing = ImVec2(4, 4);
//	prImGuiStyle.ItemInnerSpacing = ImVec2(4, 4);
//	prImGuiStyle.IndentSpacing = 10;
//	prImGuiStyle.ScrollbarSize = 20;
//	prImGuiStyle.GrabMinSize = 4;
//
//	prImGuiStyle.WindowRounding = 0;
//	prImGuiStyle.ChildRounding = 0;
//	prImGuiStyle.FrameRounding = 0;
//	prImGuiStyle.PopupRounding = 0;
//	prImGuiStyle.ScrollbarRounding = 0;
//	prImGuiStyle.GrabRounding = 0;
//	prImGuiStyle.TabRounding = 0;
//
//	prImGuiStyle.WindowBorderSize = 0;
//	prImGuiStyle.ChildBorderSize = 0;
//	prImGuiStyle.PopupBorderSize = 0;
//	prImGuiStyle.FrameBorderSize = 1;
//	prImGuiStyle.TabBorderSize = 0;
//
//	// Alignment
//	prImGuiStyle.WindowTitleAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.WindowMenuButtonPosition = ImGuiDir_Left;
//	prImGuiStyle.ColorButtonPosition = ImGuiDir_Right;
//	prImGuiStyle.ButtonTextAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.SelectableTextAlign = ImVec2(0.00f, 0.50f);
//
//	prFileTypeInfos[".dbc"].color = ImVec4(0.1f, 0.5f, 0.1f, 1.0f); // green low
//
//	// light theme so low color
//	ImGui::CustomStyle::GoodColor = ImVec4(0.2f, 0.5f, 0.2f, 1.0f);
//	ImGui::CustomStyle::BadColor = ImVec4(0.5f, 0.2f, 0.2f, 1.0f);
//
//	memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//
//	ApplyFileTypeColors();
//}
//
//void ThemeHelper::ApplyStyleColorsDarcula()
//{
//	// https://github.com/ocornut/imgui/issues/707
//	// by ice1000
//
//	const auto colors = prImGuiStyle.Colors;
//	colors[ImGuiCol_Text] = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
//	colors[ImGuiCol_TextDisabled] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
//	colors[ImGuiCol_WindowBg] = ImVec4(0.24f, 0.25f, 0.25f, 0.94f);
//	colors[ImGuiCol_ChildBg] = ImVec4(0.24f, 0.25f, 0.25f, 0.00f);
//	colors[ImGuiCol_PopupBg] = ImVec4(0.24f, 0.25f, 0.25f, 0.94f);
//	colors[ImGuiCol_Border] = ImVec4(0.33f, 0.33f, 0.33f, 0.50f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.16f, 0.16f, 0.16f, 0.00f);
//	colors[ImGuiCol_FrameBg] = ImVec4(0.17f, 0.17f, 0.17f, 0.54f);
//	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.45f, 0.68f, 1.00f, 0.67f);
//	colors[ImGuiCol_FrameBgActive] = ImVec4(0.47f, 0.47f, 0.47f, 0.67f);
//	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
//	colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
//	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.27f, 0.29f, 0.29f, 0.80f);
//	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.27f, 0.29f, 0.29f, 0.60f);
//	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.22f, 0.31f, 0.42f, 0.51f);
//	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.22f, 0.31f, 0.42f, 1.00f);
//	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.14f, 0.19f, 0.26f, 0.91f);
//	colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
//	colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
//	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
//	colors[ImGuiCol_Button] = ImVec4(0.33f, 0.35f, 0.36f, 0.49f);
//	colors[ImGuiCol_ButtonHovered] = ImVec4(0.22f, 0.31f, 0.42f, 1.00f);
//	colors[ImGuiCol_ButtonActive] = ImVec4(0.14f, 0.19f, 0.26f, 1.00f);
//	colors[ImGuiCol_Header] = ImVec4(0.33f, 0.35f, 0.36f, 0.53f);
//	colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.68f, 1.00f, 0.67f);
//	colors[ImGuiCol_HeaderActive] = ImVec4(0.47f, 0.47f, 0.47f, 0.67f);
//	colors[ImGuiCol_Separator] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
//	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
//	colors[ImGuiCol_SeparatorActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
//	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
//	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
//	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
//	colors[ImGuiCol_Tab] = ImVec4(0.07f, 0.07f, 0.07f, 0.51f);
//	colors[ImGuiCol_TabHovered] = ImVec4(0.45f, 0.68f, 1.00f, 0.67f);
//	colors[ImGuiCol_TabActive] = ImVec4(0.19f, 0.19f, 0.19f, 0.57f);
//	colors[ImGuiCol_TabUnfocused] = ImVec4(0.05f, 0.05f, 0.05f, 0.90f);
//	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.74f);
//	colors[ImGuiCol_DockingPreview] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
//	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
//	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
//	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
//	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
//	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
//	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
//	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
//	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
//	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
//	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
//	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
//	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
//	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
//	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
//
//	colors[ImGuiCol_WindowBg].w = 0.70f;
//	colors[ImGuiCol_PopupBg].w = 0.70f;
//	colors[ImGuiCol_ChildBg].w = 0.00f;
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//
//	prImGuiStyle.WindowPadding = ImVec2(4, 4);
//	prImGuiStyle.FramePadding = ImVec2(4, 4);
//	prImGuiStyle.ItemSpacing = ImVec2(4, 4);
//	prImGuiStyle.ItemInnerSpacing = ImVec2(4, 4);
//	prImGuiStyle.IndentSpacing = 10;
//	prImGuiStyle.ScrollbarSize = 20;
//	prImGuiStyle.GrabMinSize = 4;
//
//	prImGuiStyle.WindowRounding = 0;
//	prImGuiStyle.ChildRounding = 0;
//	prImGuiStyle.FrameRounding = 0;
//	prImGuiStyle.PopupRounding = 0;
//	prImGuiStyle.ScrollbarRounding = 0;
//	prImGuiStyle.GrabRounding = 0;
//	prImGuiStyle.TabRounding = 0;
//
//	prImGuiStyle.WindowBorderSize = 0;
//	prImGuiStyle.ChildBorderSize = 0;
//	prImGuiStyle.PopupBorderSize = 0;
//	prImGuiStyle.FrameBorderSize = 1;
//	prImGuiStyle.TabBorderSize = 0;
//
//	// Alignment
//	prImGuiStyle.WindowTitleAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.WindowMenuButtonPosition = ImGuiDir_Left;
//	prImGuiStyle.ColorButtonPosition = ImGuiDir_Right;
//	prImGuiStyle.ButtonTextAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.SelectableTextAlign = ImVec2(0.00f, 0.50f);
//
//	prFileTypeInfos[".dbc"].color = ImVec4(0.1f, 0.9f, 0.5f, 1.0f); // green high
//
//	// dark theme so high color
//	ImGui::CustomStyle::GoodColor = ImVec4(0.2f, 0.8f, 0.2f, 1.0f);
//	ImGui::CustomStyle::BadColor = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
//
//	memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//
//	ApplyFileTypeColors();
//}
//
//void ThemeHelper::ApplyStyleColorsRedDark()
//{
//	const auto colors = prImGuiStyle.Colors;
//	colors[ImGuiCol_Text] = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
//	colors[ImGuiCol_TextDisabled] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
//	colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
//	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
//	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
//	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.37f, 0.14f, 0.14f, 0.67f);
//	colors[ImGuiCol_FrameBgActive] = ImVec4(0.39f, 0.20f, 0.20f, 0.67f);
//	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
//	colors[ImGuiCol_TitleBgActive] = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
//	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
//	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
//	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
//	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
//	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
//	colors[ImGuiCol_CheckMark] = ImVec4(0.56f, 0.10f, 0.10f, 1.00f);
//	colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.19f, 0.19f, 0.40f);
//	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.89f, 0.00f, 0.19f, 1.00f);
//	colors[ImGuiCol_Button] = ImVec4(1.00f, 0.19f, 0.19f, 0.40f);
//	colors[ImGuiCol_ButtonHovered] = ImVec4(0.80f, 0.17f, 0.00f, 1.00f);
//	colors[ImGuiCol_ButtonActive] = ImVec4(0.89f, 0.00f, 0.19f, 1.00f);
//	colors[ImGuiCol_Header] = ImVec4(0.33f, 0.35f, 0.36f, 0.53f);
//	colors[ImGuiCol_HeaderHovered] = ImVec4(0.76f, 0.28f, 0.44f, 0.67f);
//	colors[ImGuiCol_HeaderActive] = ImVec4(0.47f, 0.47f, 0.47f, 0.67f);
//	colors[ImGuiCol_Separator] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
//	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
//	colors[ImGuiCol_SeparatorActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
//	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
//	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
//	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
//	colors[ImGuiCol_Tab] = ImVec4(0.07f, 0.07f, 0.07f, 0.51f);
//	colors[ImGuiCol_TabHovered] = ImVec4(0.86f, 0.23f, 0.43f, 0.67f);
//	colors[ImGuiCol_TabActive] = ImVec4(0.19f, 0.19f, 0.19f, 0.57f);
//	colors[ImGuiCol_TabUnfocused] = ImVec4(0.05f, 0.05f, 0.05f, 0.90f);
//	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.74f);
//	colors[ImGuiCol_DockingPreview] = ImVec4(1.00f, 0.79f, 0.00f, 1.00f);
//	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
//	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
//	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
//	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.98f, 0.00f, 1.00f);
//	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
//	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
//	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
//	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
//	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
//	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
//	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
//	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
//	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
//	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
//	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
//
//	colors[ImGuiCol_WindowBg].w = 0.70f;
//	colors[ImGuiCol_PopupBg].w = 0.70f;
//	colors[ImGuiCol_ChildBg].w = 0.00f;
//	colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//	colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
//
//	prImGuiStyle.WindowPadding = ImVec2(4, 4);
//	prImGuiStyle.FramePadding = ImVec2(4, 4);
//	prImGuiStyle.ItemSpacing = ImVec2(4, 4);
//	prImGuiStyle.ItemInnerSpacing = ImVec2(4, 4);
//	prImGuiStyle.IndentSpacing = 10;
//	prImGuiStyle.ScrollbarSize = 20;
//	prImGuiStyle.GrabMinSize = 4;
//
//	prImGuiStyle.WindowRounding = 0;
//	prImGuiStyle.ChildRounding = 0;
//	prImGuiStyle.FrameRounding = 0;
//	prImGuiStyle.PopupRounding = 0;
//	prImGuiStyle.ScrollbarRounding = 0;
//	prImGuiStyle.GrabRounding = 0;
//	prImGuiStyle.TabRounding = 0;
//
//	prImGuiStyle.WindowBorderSize = 0;
//	prImGuiStyle.ChildBorderSize = 0;
//	prImGuiStyle.PopupBorderSize = 0;
//	prImGuiStyle.FrameBorderSize = 1;
//	prImGuiStyle.TabBorderSize = 0;
//
//	// Alignment
//	prImGuiStyle.WindowTitleAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.WindowMenuButtonPosition = ImGuiDir_Left;
//	prImGuiStyle.ColorButtonPosition = ImGuiDir_Right;
//	prImGuiStyle.ButtonTextAlign = ImVec2(0.50f, 0.50f);
//	prImGuiStyle.SelectableTextAlign = ImVec2(0.00f, 0.50f);
//
//	prFileTypeInfos[".dbc"] = IGFD::FileStyle(ImVec4(0.1f, 0.5f, 0.1f, 1.0f), ICON_NDP_FILE_TEXT);
//
//	// dark theme so high color
//	ImGui::CustomStyle::GoodColor = ImVec4(0.2f, 0.8f, 0.2f, 1.0f);
//	ImGui::CustomStyle::BadColor = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
//
//	memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//
//	ApplyFileTypeColors();
//}
//
//void ThemeHelper::ApplyFileTypeColors()
//{
//	for (auto &it : prFileTypeInfos)
//	{
//		ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, it.first.c_str(), it.second.color, it.second.icon);
//	}
//}
//
//#ifdef USE_CODEEDITOR
//TextEditor::Palette ThemeHelper::GetPalette()
//{
//	return prTextEditorPalette;
//}
//
//void ThemeHelper::ApplyPalette(TextEditor::Palette vPalette)
//{
//	prTextEditorPalette = vPalette;
//	CodePane::Instance()->GetEditor()->SetPalette(prTextEditorPalette);
//}
//#endif
//
/////////////////////////////////////////////////////////
////// CONFIGURATION ////////////////////////////////////
/////////////////////////////////////////////////////////
//
//std::string ThemeHelper::getXml(const std::string& vOffset, const std::string& vUserDatas)
//{
//	UNUSED(vUserDatas);
//
//	std::string str;
//
//	{
//		prImGuiStyle = prImGuiStyle;
//		auto colors = prImGuiStyle.Colors;
//		
//		str += vOffset + "<ImGui_Styles>\n";
//		for (auto i = 0; i < ImGuiCol_COUNT; i++)
//		{
//			str += vOffset + "\t<" + GetStyleColorName(i) + " value=\"" + ct::fvec4(colors[i]).string() + "\"/>\n";
//		}
//		str += vOffset + "\t<WindowPadding value=\"" + ct::fvec2(prImGuiStyle.WindowPadding).string() + "\"/>\n";
//		str += vOffset + "\t<FramePadding value=\"" + ct::fvec2(prImGuiStyle.FramePadding).string() + "\"/>\n";
//		str += vOffset + "\t<ItemSpacing value=\"" + ct::fvec2(prImGuiStyle.ItemSpacing).string() + "\"/>\n";
//		str += vOffset + "\t<ItemInnerSpacing value=\"" + ct::fvec2(prImGuiStyle.ItemInnerSpacing).string() + "\"/>\n";
//		str += vOffset + "\t<IndentSpacing value=\"" + ct::toStr(prImGuiStyle.IndentSpacing) + "\"/>\n";
//		str += vOffset + "\t<ScrollbarSize value=\"" + ct::toStr(prImGuiStyle.ScrollbarSize) + "\"/>\n";
//		str += vOffset + "\t<GrabMinSize value=\"" + ct::toStr(prImGuiStyle.GrabMinSize) + "\"/>\n";
//		str += vOffset + "\t<WindowRounding value=\"" + ct::toStr(prImGuiStyle.WindowRounding) + "\"/>\n";
//		str += vOffset + "\t<ChildRounding value=\"" + ct::toStr(prImGuiStyle.ChildRounding) + "\"/>\n";
//		str += vOffset + "\t<FrameRounding value=\"" + ct::toStr(prImGuiStyle.FrameRounding) + "\"/>\n";
//		str += vOffset + "\t<PopupRounding value=\"" + ct::toStr(prImGuiStyle.PopupRounding) + "\"/>\n";
//		str += vOffset + "\t<ScrollbarRounding value=\"" + ct::toStr(prImGuiStyle.ScrollbarRounding) + "\"/>\n";
//		str += vOffset + "\t<GrabRounding value=\"" + ct::toStr(prImGuiStyle.GrabRounding) + "\"/>\n";
//		str += vOffset + "\t<TabRounding value=\"" + ct::toStr(prImGuiStyle.TabRounding) + "\"/>\n";
//		str += vOffset + "\t<WindowBorderSize value=\"" + ct::toStr(prImGuiStyle.WindowBorderSize) + "\"/>\n";
//		str += vOffset + "\t<ChildBorderSize value=\"" + ct::toStr(prImGuiStyle.ChildBorderSize) + "\"/>\n";
//		str += vOffset + "\t<PopupBorderSize value=\"" + ct::toStr(prImGuiStyle.PopupBorderSize) + "\"/>\n";
//		str += vOffset + "\t<FrameBorderSize value=\"" + ct::toStr(prImGuiStyle.FrameBorderSize) + "\"/>\n";
//		str += vOffset + "\t<TabBorderSize value=\"" + ct::toStr(prImGuiStyle.TabBorderSize) + "\"/>\n";
//#ifdef USE_SHADOW
//		str += vOffset + "\t<useshadow value=\"" + (puUseShadow ? "true" : "false") + "\"/>\n";
//		str += vOffset + "\t<shadowstrength value=\"" + ct::toStr(puShadowStrength) + "\"/>\n";
//		str += vOffset + "\t<useshadowtexture value=\"" + (puUseTextureForShadow ? "true" : "false") + "\"/>\n";
//#endif
//		str += vOffset + "</ImGui_Styles>\n";
//	}
//
//	{
//#ifdef USE_NODEGRAPH
//		str += vOffset + "<Graph_Styles>\n";
//		str += vOffset + "\t<NodePadding value=\"" + ct::toStrFromImVec4(prNodeGraphStyle.NodePadding) + "\"/>\n";
//		str += vOffset + "\t<NodeRounding value=\"" + ct::toStr(prNodeGraphStyle.NodeRounding) + "\"/>\n";
//		str += vOffset + "\t<NodeBorderWidth value=\"" + ct::toStr(prNodeGraphStyle.NodeBorderWidth) + "\"/>\n";
//		str += vOffset + "\t<HoveredNodeBorderWidth value=\"" + ct::toStr(prNodeGraphStyle.HoveredNodeBorderWidth) + "\"/>\n";
//		str += vOffset + "\t<SelectedNodeBorderWidth value=\"" + ct::toStr(prNodeGraphStyle.SelectedNodeBorderWidth) + "\"/>\n";
//		str += vOffset + "\t<PinRounding value=\"" + ct::toStr(prNodeGraphStyle.PinRounding) + "\"/>\n";
//		str += vOffset + "\t<PinBorderWidth value=\"" + ct::toStr(prNodeGraphStyle.PinBorderWidth) + "\"/>\n";
//		str += vOffset + "\t<LinkStrength value=\"" + ct::toStr(prNodeGraphStyle.LinkStrength) + "\"/>\n";
//		str += vOffset + "\t<SourceDirection value=\"" + ct::toStrFromImVec2(prNodeGraphStyle.SourceDirection) + "\"/>\n";
//		str += vOffset + "\t<TargetDirection value=\"" + ct::toStrFromImVec2(prNodeGraphStyle.TargetDirection) + "\"/>\n";
//		str += vOffset + "\t<ScrollDuration value=\"" + ct::toStr(prNodeGraphStyle.ScrollDuration) + "\"/>\n";
//		str += vOffset + "\t<FlowMarkerDistance value=\"" + ct::toStr(prNodeGraphStyle.FlowMarkerDistance) + "\"/>\n";
//		str += vOffset + "\t<FlowSpeed value=\"" + ct::toStr(prNodeGraphStyle.FlowSpeed) + "\"/>\n";
//		str += vOffset + "\t<FlowDuration value=\"" + ct::toStr(prNodeGraphStyle.FlowDuration) + "\"/>\n";
//		str += vOffset + "\t<PivotAlignment value=\"" + ct::toStrFromImVec2(prNodeGraphStyle.PivotAlignment) + "\"/>\n";
//		str += vOffset + "\t<PivotSize value=\"" + ct::toStrFromImVec2(prNodeGraphStyle.PivotSize) + "\"/>\n";
//		str += vOffset + "\t<PivotScale value=\"" + ct::toStrFromImVec2(prNodeGraphStyle.PivotScale) + "\"/>\n";
//		str += vOffset + "\t<PinCorners value=\"" + ct::toStr(prNodeGraphStyle.PinCorners) + "\"/>\n";
//		str += vOffset + "\t<PinRadius value=\"" + ct::toStr(prNodeGraphStyle.PinRadius) + "\"/>\n";
//		str += vOffset + "\t<PinArrowSize value=\"" + ct::toStr(prNodeGraphStyle.PinArrowSize) + "\"/>\n";
//		str += vOffset + "\t<PinArrowWidth value=\"" + ct::toStr(prNodeGraphStyle.PinArrowWidth) + "\"/>\n";
//		str += vOffset + "\t<GroupRounding value=\"" + ct::toStr(prNodeGraphStyle.GroupRounding) + "\"/>\n";
//		str += vOffset + "\t<GroupBorderWidth value=\"" + ct::toStr(prNodeGraphStyle.GroupBorderWidth) + "\"/>\n";
//		str += vOffset + "</Graph_Styles>\n";
//#endif
//	}
//
//	{
//		str += vOffset + "<FileTypes>\n";
//		for (auto& it : prFileTypeInfos)
//		{
//			str += vOffset + "\t<filetype value=\"" + it.first + "\" color=\"" +
//				ct::fvec4(it.second.color).string() + "\"/>\n";
//		}
//		str += vOffset + "</FileTypes>\n";
//	}
//
//	return str;
//}
//
//bool ThemeHelper::setFromXml(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent, const std::string& vUserDatas)
//{
//	UNUSED(vUserDatas);
//
//	// The value of this child identifies the name of this element
//	std::string strName;
//	std::string strValue;
//	std::string strParentName;
//
//	strName = vElem->Value();
//	if (vElem->GetText())
//		strValue = vElem->GetText();
//	if (vParent != nullptr)
//		strParentName = vParent->Value();
//
//	if (strParentName == "FileTypes")
//	{
//		std::string fileType;
//		std::string color;
//		
//		for (auto attr = vElem->FirstAttribute(); attr != nullptr; attr = attr->Next())
//		{
//			std::string attName = attr->Name();
//			const std::string attValue = attr->Value();
//
//			if (attName == "value") fileType = attValue;
//			if (attName == "color") color = attValue;
//		}
//
//		prFileTypeInfos[fileType] = IGFD::FileStyle(ct::toImVec4(ct::fvariant(color).GetV4()));
//		ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, fileType.c_str(), prFileTypeInfos[fileType]);
//	}
//
//#ifdef USE_NODEGRAPH
//	if (strParentName == "Graph_Styles")
//	{
//		const auto att = vElem->FirstAttribute();
//		if (att && std::string(att->Name()) == "value")
//		{
//			strValue = att->Value();
//			
//			if (strName == "NodePadding")
//				prNodeGraphStyle.NodePadding = ct::toImVec4(ct::fvariant(strValue).GetV4());
//			if (strName == "NodeRounding")
//				prNodeGraphStyle.NodeRounding = ct::fvariant(strValue).GetF();
//			if (strName == "NodeBorderWidth")
//				prNodeGraphStyle.NodeBorderWidth = ct::fvariant(strValue).GetF();
//			if (strName == "HoveredNodeBorderWidth")
//				prNodeGraphStyle.HoveredNodeBorderWidth = ct::fvariant(strValue).GetF();
//			if (strName == "SelectedNodeBorderWidth")
//				prNodeGraphStyle.SelectedNodeBorderWidth = ct::fvariant(strValue).GetF();
//			if (strName == "PinRounding")
//				prNodeGraphStyle.PinRounding = ct::fvariant(strValue).GetF();
//			if (strName == "PinBorderWidth")
//				prNodeGraphStyle.PinBorderWidth = ct::fvariant(strValue).GetF();
//			if (strName == "LinkStrength")
//				prNodeGraphStyle.LinkStrength = ct::fvariant(strValue).GetF();
//			if (strName == "SourceDirection")
//				prNodeGraphStyle.SourceDirection = ct::toImVec2(ct::fvariant(strValue).GetV2());
//			if (strName == "TargetDirection")
//				prNodeGraphStyle.TargetDirection = ct::toImVec2(ct::fvariant(strValue).GetV2());
//			if (strName == "ScrollDuration")
//				prNodeGraphStyle.ScrollDuration = ct::fvariant(strValue).GetF();
//			if (strName == "FlowMarkerDistance")
//				prNodeGraphStyle.FlowMarkerDistance = ct::fvariant(strValue).GetF();
//			if (strName == "FlowSpeed")
//				prNodeGraphStyle.FlowSpeed = ct::fvariant(strValue).GetF();
//			if (strName == "FlowDuration")
//				prNodeGraphStyle.FlowDuration = ct::fvariant(strValue).GetF();
//			if (strName == "PivotAlignment")
//				prNodeGraphStyle.PivotAlignment = ct::toImVec2(ct::fvariant(strValue).GetV2());
//			if (strName == "PivotSize")
//				prNodeGraphStyle.PivotSize = ct::toImVec2(ct::fvariant(strValue).GetV2());
//			if (strName == "PivotScale")
//				prNodeGraphStyle.PivotScale = ct::toImVec2(ct::fvariant(strValue).GetV2());
//			if (strName == "PinCorners")
//				prNodeGraphStyle.PinCorners = ct::fvariant(strValue).GetF();
//			if (strName == "PinRadius")
//				prNodeGraphStyle.PinRadius = ct::fvariant(strValue).GetF();
//			if (strName == "PinArrowSize")
//				prNodeGraphStyle.PinArrowSize = ct::fvariant(strValue).GetF();
//			if (strName == "PinArrowWidth")
//				prNodeGraphStyle.PinArrowWidth = ct::fvariant(strValue).GetF();
//			if (strName == "GroupRounding")
//				prNodeGraphStyle.GroupRounding = ct::fvariant(strValue).GetF();
//			if (strName == "GroupBorderWidth")
//				prNodeGraphStyle.GroupBorderWidth = ct::fvariant(strValue).GetF();
//		}
//	}
//#endif
//
//	if (strParentName == "ImGui_Styles")
//	{
//		const auto att = vElem->FirstAttribute();
//		if (att && std::string(att->Name()) == "value")
//		{
//			strValue = att->Value();
//
//			if (strName.find("ImGuiCol") != std::string::npos)
//			{
//				const auto& id = GetImGuiColFromName(strName);
//				if (id >= 0)
//				{
//					prImGuiStyle.Colors[id] = ct::toImVec4(ct::fvariant(strValue).GetV4());
//					memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//					return false;
//				}
//			}
//
//			if (strName == "WindowPadding") {
//				prImGuiStyle.WindowPadding = ct::toImVec2(ct::fvariant(strValue).GetV2());
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "FramePadding") {
//				prImGuiStyle.FramePadding = ct::toImVec2(ct::fvariant(strValue).GetV2());
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "ItemSpacing") {
//				prImGuiStyle.ItemSpacing = ct::toImVec2(ct::fvariant(strValue).GetV2());
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "ItemInnerSpacing") {
//				prImGuiStyle.ItemInnerSpacing = ct::toImVec2(ct::fvariant(strValue).GetV2());
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "IndentSpacing") {
//				prImGuiStyle.IndentSpacing = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "ScrollbarSize") {
//				prImGuiStyle.ScrollbarSize = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "GrabMinSize") {
//				prImGuiStyle.GrabMinSize = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "WindowRounding") {
//				prImGuiStyle.WindowRounding = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "ChildRounding") {
//				prImGuiStyle.ChildRounding = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "FrameRounding") {
//				prImGuiStyle.FrameRounding = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "PopupRounding") {
//				prImGuiStyle.PopupRounding = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "ScrollbarRounding") {
//				prImGuiStyle.ScrollbarRounding = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "GrabRounding") {
//				prImGuiStyle.GrabRounding = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "TabRounding") {
//				prImGuiStyle.TabRounding = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "WindowBorderSize") {
//				prImGuiStyle.WindowBorderSize = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "ChildBorderSize") {
//				prImGuiStyle.ChildBorderSize = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "PopupBorderSize") {
//				prImGuiStyle.PopupBorderSize = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "FrameBorderSize") {
//				prImGuiStyle.FrameBorderSize = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//			else if (strName == "TabBorderSize") {
//				prImGuiStyle.TabBorderSize = ct::fvariant(strValue).GetF();
//				memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//			}
//#ifdef USE_SHADOW
//			else if (strName == "useshadow") puUseShadow = ct::ivariant(strValue).GetB();
//			else if (strName == "shadowstrength") puShadowStrength = ct::fvariant(strValue).GetF();
//			else if (strName == "useshadowtexture") puUseTextureForShadow = ct::ivariant(strValue).GetB();
//#endif
//		}
//	}
//
//#ifdef USE_CODEEDITOR
//	if (strParentName == "ImGuiColorTextEdit_Styles")
//	{
//		auto att = vElem->FirstAttribute();
//		if (att && std::string(att->Name()) == "value")
//		{
//			strValue = att->Value();
//
//			//ImGuiStyle* imgui_style = &prImGuiStyle;
//			//ImVec4* colors = prImGuiStyle.Colors;
//
//			auto id = Get_ImGuiColorTextEditPalette_ColFromName(strName);
//			if (id < TextEditor::PaletteIndex::Max)
//			{
//				auto pal = GetPalette();
//				pal[(int)id] = (ImU32)ct::ivariant(strValue).GetU();
//				ApplyPalette(pal);
//			}
//		}
//	}
//#endif
//
//	return true;
//}
//
//
/////////////////////////////////////////////////////////
////// PRIVVATE /////////////////////////////////////////
/////////////////////////////////////////////////////////
//
//std::string ThemeHelper::GetStyleColorName(ImGuiCol idx)
//{
//	switch (idx)
//	{
//	case ImGuiCol_Text: return "ImGuiCol_Text";
//	case ImGuiCol_TextDisabled: return "ImGuiCol_TextDisabled";
//	case ImGuiCol_WindowBg: return "ImGuiCol_WindowBg";
//	case ImGuiCol_ChildBg: return "ImGuiCol_ChildBg";
//	case ImGuiCol_PopupBg: return "ImGuiCol_PopupBg";
//	case ImGuiCol_Border: return "ImGuiCol_Border";
//	case ImGuiCol_BorderShadow: return "ImGuiCol_BorderShadow";
//	case ImGuiCol_FrameBg: return "ImGuiCol_FrameBg";
//	case ImGuiCol_FrameBgHovered: return "ImGuiCol_FrameBgHovered";
//	case ImGuiCol_FrameBgActive: return "ImGuiCol_FrameBgActive";
//	case ImGuiCol_TitleBg: return "ImGuiCol_TitleBg";
//	case ImGuiCol_TitleBgActive: return "ImGuiCol_TitleBgActive";
//	case ImGuiCol_TitleBgCollapsed: return "ImGuiCol_TitleBgCollapsed";
//	case ImGuiCol_MenuBarBg: return "ImGuiCol_MenuBarBg";
//	case ImGuiCol_ScrollbarBg: return "ImGuiCol_ScrollbarBg";
//	case ImGuiCol_ScrollbarGrab: return "ImGuiCol_ScrollbarGrab";
//	case ImGuiCol_ScrollbarGrabHovered: return "ImGuiCol_ScrollbarGrabHovered";
//	case ImGuiCol_ScrollbarGrabActive: return "ImGuiCol_ScrollbarGrabActive";
//	case ImGuiCol_CheckMark: return "ImGuiCol_CheckMark";
//	case ImGuiCol_SliderGrab: return "ImGuiCol_SliderGrab";
//	case ImGuiCol_SliderGrabActive: return "ImGuiCol_SliderGrabActive";
//	case ImGuiCol_Button: return "ImGuiCol_Button";
//	case ImGuiCol_ButtonHovered: return "ImGuiCol_ButtonHovered";
//	case ImGuiCol_ButtonActive: return "ImGuiCol_ButtonActive";
//	case ImGuiCol_Header: return "ImGuiCol_Header";
//	case ImGuiCol_HeaderHovered: return "ImGuiCol_HeaderHovered";
//	case ImGuiCol_HeaderActive: return "ImGuiCol_HeaderActive";
//	case ImGuiCol_Separator: return "ImGuiCol_Separator";
//	case ImGuiCol_SeparatorHovered: return "ImGuiCol_SeparatorHovered";
//	case ImGuiCol_SeparatorActive: return "ImGuiCol_SeparatorActive";
//	case ImGuiCol_ResizeGrip: return "ImGuiCol_ResizeGrip";
//	case ImGuiCol_ResizeGripHovered: return "ImGuiCol_ResizeGripHovered";
//	case ImGuiCol_ResizeGripActive: return "ImGuiCol_ResizeGripActive";
//	case ImGuiCol_Tab: return "ImGuiCol_Tab";
//	case ImGuiCol_TabHovered: return "ImGuiCol_TabHovered";
//	case ImGuiCol_TabActive: return "ImGuiCol_TabActive";
//	case ImGuiCol_TabUnfocused: return "ImGuiCol_TabUnfocused";
//	case ImGuiCol_TabUnfocusedActive: return "ImGuiCol_TabUnfocusedActive";
//	case ImGuiCol_DockingPreview: return "ImGuiCol_DockingPreview";
//	case ImGuiCol_DockingEmptyBg: return "ImGuiCol_DockingEmptyBg";
//	case ImGuiCol_PlotLines: return "ImGuiCol_PlotLines";
//	case ImGuiCol_PlotLinesHovered: return "ImGuiCol_PlotLinesHovered";
//	case ImGuiCol_PlotHistogram: return "ImGuiCol_PlotHistogram";
//	case ImGuiCol_PlotHistogramHovered: return "ImGuiCol_PlotHistogramHovered";
//	case ImGuiCol_TableHeaderBg: return "ImGuiCol_TableHeaderBg";
//	case ImGuiCol_TableBorderStrong: return "ImGuiCol_TableBorderStrong";
//	case ImGuiCol_TableBorderLight: return "ImGuiCol_TableBorderLight";
//	case ImGuiCol_TableRowBg: return "ImGuiCol_TableRowBg";
//	case ImGuiCol_TableRowBgAlt: return "ImGuiCol_TableRowBgAlt";
//	case ImGuiCol_TextSelectedBg: return "ImGuiCol_TextSelectedBg";
//	case ImGuiCol_DragDropTarget: return "ImGuiCol_DragDropTarget";
//	case ImGuiCol_NavHighlight: return "ImGuiCol_NavHighlight";
//	case ImGuiCol_NavWindowingHighlight: return "ImGuiCol_NavWindowingHighlight";
//	case ImGuiCol_NavWindowingDimBg: return "ImGuiCol_NavWindowingDimBg";
//	case ImGuiCol_ModalWindowDimBg: return "ImGuiCol_ModalWindowDimBg";
//	default:;
//	}
//	return "ImGuiCol_Unknown";
//}
//
//int ThemeHelper::GetImGuiColFromName(const std::string& vName)
//{
//	if (vName == "ImGuiCol_Text") return ImGuiCol_Text;
//	else if (vName == "ImGuiCol_TextDisabled") return ImGuiCol_TextDisabled;
//	else if (vName == "ImGuiCol_WindowBg") return ImGuiCol_WindowBg;
//	else if (vName == "ImGuiCol_ChildBg") return ImGuiCol_ChildBg;
//	else if (vName == "ImGuiCol_PopupBg") return ImGuiCol_PopupBg;
//	else if (vName == "ImGuiCol_Border") return ImGuiCol_Border;
//	else if (vName == "ImGuiCol_BorderShadow") return ImGuiCol_BorderShadow;
//	else if (vName == "ImGuiCol_FrameBg") return ImGuiCol_FrameBg;
//	else if (vName == "ImGuiCol_FrameBgHovered") return ImGuiCol_FrameBgHovered;
//	else if (vName == "ImGuiCol_FrameBgActive") return ImGuiCol_FrameBgActive;
//	else if (vName == "ImGuiCol_TitleBg") return ImGuiCol_TitleBg;
//	else if (vName == "ImGuiCol_TitleBgActive") return ImGuiCol_TitleBgActive;
//	else if (vName == "ImGuiCol_TitleBgCollapsed") return ImGuiCol_TitleBgCollapsed;
//	else if (vName == "ImGuiCol_MenuBarBg") return ImGuiCol_MenuBarBg;
//	else if (vName == "ImGuiCol_ScrollbarBg") return ImGuiCol_ScrollbarBg;
//	else if (vName == "ImGuiCol_ScrollbarGrab") return ImGuiCol_ScrollbarGrab;
//	else if (vName == "ImGuiCol_ScrollbarGrabHovered") return ImGuiCol_ScrollbarGrabHovered;
//	else if (vName == "ImGuiCol_ScrollbarGrabActive") return ImGuiCol_ScrollbarGrabActive;
//	else if (vName == "ImGuiCol_CheckMark") return ImGuiCol_CheckMark;
//	else if (vName == "ImGuiCol_SliderGrab") return ImGuiCol_SliderGrab;
//	else if (vName == "ImGuiCol_SliderGrabActive") return ImGuiCol_SliderGrabActive;
//	else if (vName == "ImGuiCol_Button") return ImGuiCol_Button;
//	else if (vName == "ImGuiCol_ButtonHovered") return ImGuiCol_ButtonHovered;
//	else if (vName == "ImGuiCol_ButtonActive") return ImGuiCol_ButtonActive;
//	else if (vName == "ImGuiCol_Header") return ImGuiCol_Header;
//	else if (vName == "ImGuiCol_HeaderHovered") return ImGuiCol_HeaderHovered;
//	else if (vName == "ImGuiCol_HeaderActive") return ImGuiCol_HeaderActive;
//	else if (vName == "ImGuiCol_Separator") return ImGuiCol_Separator;
//	else if (vName == "ImGuiCol_SeparatorHovered") return ImGuiCol_SeparatorHovered;
//	else if (vName == "ImGuiCol_SeparatorActive") return ImGuiCol_SeparatorActive;
//	else if (vName == "ImGuiCol_ResizeGrip") return ImGuiCol_ResizeGrip;
//	else if (vName == "ImGuiCol_ResizeGripHovered") return ImGuiCol_ResizeGripHovered;
//	else if (vName == "ImGuiCol_ResizeGripActive") return ImGuiCol_ResizeGripActive;
//	else if (vName == "ImGuiCol_Tab") return ImGuiCol_Tab;
//	else if (vName == "ImGuiCol_TabHovered") return ImGuiCol_TabHovered;
//	else if (vName == "ImGuiCol_TabActive") return ImGuiCol_TabActive;
//	else if (vName == "ImGuiCol_TabUnfocused") return ImGuiCol_TabUnfocused;
//	else if (vName == "ImGuiCol_TabUnfocusedActive") return ImGuiCol_TabUnfocusedActive;
//	else if (vName == "ImGuiCol_DockingPreview") return ImGuiCol_DockingPreview;
//	else if (vName == "ImGuiCol_DockingEmptyBg") return ImGuiCol_DockingEmptyBg;
//	else if (vName == "ImGuiCol_PlotLines") return ImGuiCol_PlotLines;
//	else if (vName == "ImGuiCol_PlotLinesHovered") return ImGuiCol_PlotLinesHovered;
//	else if (vName == "ImGuiCol_PlotHistogram") return ImGuiCol_PlotHistogram;
//	else if (vName == "ImGuiCol_PlotHistogramHovered") return ImGuiCol_PlotHistogramHovered;
//	else if (vName == "ImGuiCol_TableHeaderBg") return ImGuiCol_TableHeaderBg;
//	else if (vName == "ImGuiCol_TableBorderStrong") return ImGuiCol_TableBorderStrong;
//	else if (vName == "ImGuiCol_TableBorderLight") return ImGuiCol_TableBorderLight;
//	else if (vName == "ImGuiCol_TableRowBg") return ImGuiCol_TableRowBg;
//	else if (vName == "ImGuiCol_TableRowBgAlt") return ImGuiCol_TableRowBgAlt;
//	else if (vName == "ImGuiCol_TextSelectedBg") return ImGuiCol_TextSelectedBg;
//	else if (vName == "ImGuiCol_DragDropTarget") return ImGuiCol_DragDropTarget;
//	else if (vName == "ImGuiCol_NavHighlight") return ImGuiCol_NavHighlight;
//	else if (vName == "ImGuiCol_NavWindowingHighlight") return ImGuiCol_NavWindowingHighlight;
//	else if (vName == "ImGuiCol_NavWindowingDimBg") return ImGuiCol_NavWindowingDimBg;
//	else if (vName == "ImGuiCol_ModalWindowDimBg") return ImGuiCol_ModalWindowDimBg;
//	return -1;
//}
//
//#ifdef USE_CODEEDITOR
//const char* ThemeHelper::Get_ImGuiColorTextEditPalette_NameFromCol(TextEditor::PaletteIndex idx)
//{
//	switch (idx)
//	{
//	case TextEditor::PaletteIndex::Default: return "Default";
//	case TextEditor::PaletteIndex::Keyword: return "Keyword";
//	case TextEditor::PaletteIndex::Number: return "Number";
//	case TextEditor::PaletteIndex::String: return "String";
//	case TextEditor::PaletteIndex::CharLiteral: return "CharLiteral";
//	case TextEditor::PaletteIndex::Punctuation: return "Punctuation";
//	case TextEditor::PaletteIndex::Preprocessor: return "Preprocessor";
//	case TextEditor::PaletteIndex::Identifier: return "Identifier";
//	case TextEditor::PaletteIndex::KnownIdentifier: return "KnownIdentifier";
//	case TextEditor::PaletteIndex::PreprocIdentifier: return "PreprocIdentifier";
//	case TextEditor::PaletteIndex::Comment: return "Comment";
//	case TextEditor::PaletteIndex::MultiLineComment: return "MultiLineComment";
//	case TextEditor::PaletteIndex::Background: return "Background";
//	case TextEditor::PaletteIndex::Cursor: return "Cursor";
//	case TextEditor::PaletteIndex::Selection: return "Selection";
//	case TextEditor::PaletteIndex::ErrorMarker: return "ErrorMarker";
//	case TextEditor::PaletteIndex::Breakpoint: return "Breakpoint";
//	case TextEditor::PaletteIndex::LineNumber: return "LineNumber";
//	case TextEditor::PaletteIndex::CurrentLineFill: return "CurrentLineFill";
//	case TextEditor::PaletteIndex::CurrentLineFillInactive: return "CurrentLineFillInactive";
//	case TextEditor::PaletteIndex::CurrentLineEdge: return "CurrentLineEdge";
//	//
//	default:;
//	}
//	return "Unknow";
//}
//
//TextEditor::PaletteIndex ThemeHelper::Get_ImGuiColorTextEditPalette_ColFromName(const std::string& vName)
//{
//	if (vName == "Default") return TextEditor::PaletteIndex::Default;
//	if (vName == "Keyword") return TextEditor::PaletteIndex::Keyword;
//	if (vName == "Number") return TextEditor::PaletteIndex::Number;
//	if (vName == "String") return TextEditor::PaletteIndex::String;
//	if (vName == "CharLiteral") return TextEditor::PaletteIndex::CharLiteral;
//	if (vName == "Punctuation") return TextEditor::PaletteIndex::Punctuation;
//	if (vName == "Preprocessor") return TextEditor::PaletteIndex::Preprocessor;
//	if (vName == "Identifier") return TextEditor::PaletteIndex::Identifier;
//	if (vName == "KnownIdentifier") return TextEditor::PaletteIndex::KnownIdentifier;
//	if (vName == "PreprocIdentifier") return TextEditor::PaletteIndex::PreprocIdentifier;
//	if (vName == "Comment") return TextEditor::PaletteIndex::Comment;
//	if (vName == "MultiLineComment") return TextEditor::PaletteIndex::MultiLineComment;
//	if (vName == "Background") return TextEditor::PaletteIndex::Background;
//	if (vName == "Cursor") return TextEditor::PaletteIndex::Cursor;
//	if (vName == "Selection") return TextEditor::PaletteIndex::Selection;
//	if (vName == "ErrorMarker") return TextEditor::PaletteIndex::ErrorMarker;
//	if (vName == "Breakpoint") return TextEditor::PaletteIndex::Breakpoint;
//	if (vName == "LineNumber") return TextEditor::PaletteIndex::LineNumber;
//	if (vName == "CurrentLineFill") return TextEditor::PaletteIndex::CurrentLineFill;
//	if (vName == "CurrentLineFillInactive") return TextEditor::PaletteIndex::CurrentLineFillInactive;
//	if (vName == "CurrentLineEdge") return TextEditor::PaletteIndex::CurrentLineEdge;
//
//	return TextEditor::PaletteIndex::Max;
//}
//
//enum class PaletteIndex : uint8_t
//{
//	Default,
//	Keyword,
//	Number,
//	String,
//	CharLiteral,
//	Punctuation,
//	Preprocessor,
//	Identifier,
//	KnownIdentifier,
//	PreprocIdentifier,
//	Comment,
//	MultiLineComment,
//	Background,
//	Cursor,
//	Selection,
//	ErrorMarker,
//	Breakpoint,
//	LineNumber,
//	CurrentLineFill,
//	CurrentLineFillInactive,
//	CurrentLineEdge,
//	Max
//};
//#endif
//
//inline void DrawItem(int vIdx, const ImGuiTextFilter& vFilter, const char* vName, ImVec4& vStyleColor, ImVec4& vRefColor, ImGuiColorEditFlags vFlags)
//{
//	if (!vFilter.PassFilter(vName))
//		return;
//
//	ImGuiStyle& imgui_style = ImGui::GetStyle();
//	ImGui::PushID(vIdx);
//	ImGui::ColorEdit4("##color", (float*)&vStyleColor, ImGuiColorEditFlags_AlphaBar | vFlags);
//	if (memcmp(&vStyleColor, &vRefColor, sizeof(ImVec4)) != 0)
//	{
//		// Tips: in a real user application, you may want to merge and use an icon font into the main font, so instead of "Save"/"Revert" you'd use icons.
//		// Read the FAQ and docs/FONTS.txt about using icon fonts. It's really easy and super convenient!
//		ImGui::SameLine(0.0f, imgui_style.ItemInnerSpacing.x); if (ImGui::ContrastedButton("Save")) vRefColor = vStyleColor;
//		ImGui::SameLine(0.0f, imgui_style.ItemInnerSpacing.x); if (ImGui::ContrastedButton("Revert")) vStyleColor = vRefColor;
//	}
//	ImGui::SameLine(0.0f, imgui_style.ItemInnerSpacing.x);
//	ImGui::TextUnformatted(vName);
//	ImGui::PopID();
//}
//
//inline void ExportColors(ImGuiStyle& style_to_export, ImGuiStyle& ref_style, bool export_only_modified)
//{
//	ImGui::LogText("ImVec4* colors = prImGuiStyle.Colors;" IM_NEWLINE);
//
//	for (auto i = 0; i < ImGuiCol_COUNT; i++)
//	{
//		const auto& col = style_to_export.Colors[i];
//		const auto name = ImGui::GetStyleColorName(i);
//		if (!export_only_modified || memcmp(&col, &ref_style.Colors[i], sizeof(ImVec4)) != 0)
//			ImGui::LogText("colors[ImGuiCol_%s]%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE, name, 23 - (int)strlen(name), "", col.x, col.y, col.z, col.w);
//	}
//
//	ImGui::LogText(IM_NEWLINE);
//
//	ImGui::LogText("ImGui::CustomStyle::GoodColor%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE, 32 - (int)strlen("ImGui::CustomStyle::GoodColor"),
//		"", ImGui::CustomStyle::GoodColor.x, ImGui::CustomStyle::GoodColor.y, ImGui::CustomStyle::GoodColor.z, ImGui::CustomStyle::GoodColor.w);
//	ImGui::LogText("ImGui::CustomStyle::BadColor%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE, 32 - (int)strlen("ImGui::CustomStyle::BadColor"),
//		"", ImGui::CustomStyle::BadColor.x, ImGui::CustomStyle::BadColor.y, ImGui::CustomStyle::BadColor.z, ImGui::CustomStyle::BadColor.w);
//}
//
//inline void ExportSize_Float(const char* name, float& size_to_export, float& ref_size, bool export_only_modified)
//{
//	if (!export_only_modified || memcmp(&size_to_export, &ref_size, sizeof(float)) != 0)
//		ImGui::LogText("imgui_style.%s%*s= %.2ff;" IM_NEWLINE, name, 25 - (int)strlen(name), "", size_to_export);
//}
//
//inline void ExportSize_ImVec2(const char* name, ImVec2& size_to_export, ImVec2& ref_size, bool export_only_modified)
//{
//	if (!export_only_modified || memcmp(&size_to_export, &ref_size, sizeof(ImVec2)) != 0)
//		ImGui::LogText("imgui_style.%s%*s= ImVec2(%.2ff, %.2ff);" IM_NEWLINE, name, 25 - (int)strlen(name), "", size_to_export.x, size_to_export.y);
//}
//
//inline void ExportSize_ImVec4(const char* name, ImVec4& size_to_export, ImVec4& ref_size, bool export_only_modified)
//{
//	if (!export_only_modified || memcmp(&size_to_export, &ref_size, sizeof(ImVec4)) != 0)
//		ImGui::LogText("imgui_style.%s%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE, name, 25 - (int)strlen(name), "", 
//			size_to_export.x, size_to_export.y, size_to_export.z, size_to_export.w);
//}
//
//inline void ExportSizes(ImGuiStyle& style_to_export, ImGuiStyle& ref_style, bool export_only_modified)
//{
//	ImGui::LogText("ImGuiStyle& imgui_style = prImGuiStyle;" IM_NEWLINE);
//
//	{
//		ImGui::LogText(IM_NEWLINE "// Main" IM_NEWLINE);
//
//		ExportSize_ImVec2("WindowPadding", style_to_export.WindowPadding, ref_style.WindowPadding, export_only_modified);
//		ExportSize_ImVec2("FramePadding", style_to_export.FramePadding, ref_style.FramePadding, export_only_modified);
//		ExportSize_ImVec2("ItemSpacing", style_to_export.ItemSpacing, ref_style.ItemSpacing, export_only_modified);
//		ExportSize_ImVec2("ItemInnerSpacing", style_to_export.ItemInnerSpacing, ref_style.ItemInnerSpacing, export_only_modified);
//		ExportSize_ImVec2("TouchExtraPadding", style_to_export.TouchExtraPadding, ref_style.TouchExtraPadding, export_only_modified);
//		ExportSize_Float("IndentSpacing", style_to_export.IndentSpacing, ref_style.IndentSpacing, export_only_modified);
//		ExportSize_Float("ScrollbarSize", style_to_export.ScrollbarSize, ref_style.ScrollbarSize, export_only_modified);
//		ExportSize_Float("GrabMinSize", style_to_export.GrabMinSize, ref_style.GrabMinSize, export_only_modified);
//	}
//
//	{
//		ImGui::LogText(IM_NEWLINE "// Borders" IM_NEWLINE);
//
//		ExportSize_Float("WindowBorderSize", style_to_export.WindowBorderSize, ref_style.WindowBorderSize, export_only_modified);
//		ExportSize_Float("ChildBorderSize", style_to_export.ChildBorderSize, ref_style.ChildBorderSize, export_only_modified);
//		ExportSize_Float("PopupBorderSize", style_to_export.PopupBorderSize, ref_style.PopupBorderSize, export_only_modified);
//		ExportSize_Float("FrameBorderSize", style_to_export.FrameBorderSize, ref_style.FrameBorderSize, export_only_modified);
//		ExportSize_Float("TabBorderSize", style_to_export.TabBorderSize, ref_style.TabBorderSize, export_only_modified);
//	}
//	
//	{
//		ImGui::LogText(IM_NEWLINE "// Rounding" IM_NEWLINE);
//
//		ExportSize_Float("WindowRounding", style_to_export.WindowRounding, ref_style.WindowRounding, export_only_modified);
//		ExportSize_Float("ChildRounding", style_to_export.ChildRounding, ref_style.ChildRounding, export_only_modified);
//		ExportSize_Float("FrameRounding", style_to_export.FrameRounding, ref_style.FrameRounding, export_only_modified);
//		ExportSize_Float("PopupRounding", style_to_export.PopupRounding, ref_style.PopupRounding, export_only_modified);
//		ExportSize_Float("ScrollbarRounding", style_to_export.ScrollbarRounding, ref_style.ScrollbarRounding, export_only_modified);
//		ExportSize_Float("GrabRounding", style_to_export.GrabRounding, ref_style.GrabRounding, export_only_modified);
//		ExportSize_Float("TabRounding", style_to_export.TabRounding, ref_style.TabRounding, export_only_modified);
//	}
//
//	{
//		ImGui::LogText(IM_NEWLINE "// Alignment" IM_NEWLINE);
//
//		ExportSize_ImVec2("WindowTitleAlign", style_to_export.WindowTitleAlign, ref_style.WindowTitleAlign, export_only_modified);
//
//		// for this one we could just save ImGuiDir number, but its more redable to have ImGuiDir_ name
//		if (!export_only_modified || memcmp(&style_to_export.WindowMenuButtonPosition, &ref_style.WindowMenuButtonPosition, sizeof(ImGuiDir)) != 0)
//		{
//			const char* dirName = 0;
//			switch (style_to_export.WindowMenuButtonPosition)
//			{
//			case ImGuiDir_None: dirName = "ImGuiDir_None"; break;
//			case ImGuiDir_Left: dirName = "ImGuiDir_Left"; break;
//			case ImGuiDir_Right: dirName = "ImGuiDir_Right"; break;
//			};
//
//			ImGui::LogText("imgui_style.%s%*s= %s;" IM_NEWLINE, "WindowMenuButtonPosition", 25 - (int)strlen("WindowMenuButtonPosition"), "", dirName);
//		}
//
//		// for this one we could just save ImGuiDir number, but its more redable to have ImGuiDir_ name
//		if (!export_only_modified || memcmp(&style_to_export.ColorButtonPosition, &ref_style.ColorButtonPosition, sizeof(ImGuiDir)) != 0)
//		{
//			const char* dirName = 0;
//			switch (style_to_export.ColorButtonPosition)
//			{
//			case ImGuiDir_Left: dirName = "ImGuiDir_Left"; break;
//			case ImGuiDir_Right: dirName = "ImGuiDir_Right"; break;
//			};
//
//			ImGui::LogText("imgui_style.%s%*s= %s;" IM_NEWLINE, "ColorButtonPosition", 25 - (int)strlen("ColorButtonPosition"), "", dirName);
//		}
//
//		ExportSize_ImVec2("ButtonTextAlign", style_to_export.ButtonTextAlign, ref_style.ButtonTextAlign, export_only_modified);
//		ExportSize_ImVec2("SelectableTextAlign", style_to_export.SelectableTextAlign, ref_style.SelectableTextAlign, export_only_modified);
//	}
//	
//	{
//		ImGui::LogText(IM_NEWLINE "// Safe Area Padding" IM_NEWLINE);
//
//		ExportSize_ImVec2("DisplaySafeAreaPadding", style_to_export.DisplaySafeAreaPadding, ref_style.DisplaySafeAreaPadding, export_only_modified);
//	}
//}
//
//#ifdef USE_NODEGRAPH
//inline void ExportGraph(ax::NodeEditor::Style& style_to_export, ax::NodeEditor::Style& ref_style, bool export_only_modified)
//{
//	ImGui::LogText("ax::NodeEditor::Style imgui_style = prNodeGraphStyle;" IM_NEWLINE);
//
//	{
//		ImGui::LogText(IM_NEWLINE "// Main" IM_NEWLINE);
//
//		ExportSize_ImVec4("NodePadding", style_to_export.NodePadding, ref_style.NodePadding, export_only_modified);
//		ExportSize_Float("NodeRounding", style_to_export.NodeRounding, ref_style.NodeRounding, export_only_modified);
//		ExportSize_Float("NodeBorderWidth", style_to_export.NodeBorderWidth, ref_style.NodeBorderWidth, export_only_modified);
//		ExportSize_Float("HoveredNodeBorderWidth", style_to_export.HoveredNodeBorderWidth, ref_style.HoveredNodeBorderWidth, export_only_modified);
//		ExportSize_Float("SelectedNodeBorderWidth", style_to_export.SelectedNodeBorderWidth, ref_style.SelectedNodeBorderWidth, export_only_modified);
//		ExportSize_Float("PinRounding", style_to_export.PinRounding, ref_style.PinRounding, export_only_modified);
//		ExportSize_Float("PinBorderWidth", style_to_export.PinBorderWidth, ref_style.PinBorderWidth, export_only_modified);
//		ExportSize_Float("LinkStrength", style_to_export.LinkStrength, ref_style.LinkStrength, export_only_modified);
//		ExportSize_ImVec2("SourceDirection", style_to_export.SourceDirection, ref_style.SourceDirection, export_only_modified);
//		ExportSize_ImVec2("TargetDirection", style_to_export.TargetDirection, ref_style.TargetDirection, export_only_modified);
//		ExportSize_Float("ScrollDuration", style_to_export.ScrollDuration, ref_style.ScrollDuration, export_only_modified);
//		ExportSize_Float("FlowMarkerDistance", style_to_export.FlowMarkerDistance, ref_style.FlowMarkerDistance, export_only_modified);
//		ExportSize_Float("FlowSpeed", style_to_export.FlowSpeed, ref_style.FlowSpeed, export_only_modified);
//		ExportSize_Float("FlowDuration", style_to_export.FlowDuration, ref_style.FlowDuration, export_only_modified);
//		ExportSize_ImVec2("PivotAlignment", style_to_export.PivotAlignment, ref_style.PivotAlignment, export_only_modified);
//		ExportSize_ImVec2("PivotSize", style_to_export.PivotSize, ref_style.PivotSize, export_only_modified);
//		ExportSize_ImVec2("PivotScale", style_to_export.PivotScale, ref_style.PivotScale, export_only_modified);
//		ExportSize_Float("PinCorners", style_to_export.PinCorners, ref_style.PinCorners, export_only_modified);
//		ExportSize_Float("PinRadius", style_to_export.PinRadius, ref_style.PinRadius, export_only_modified);
//		ExportSize_Float("PinArrowSize", style_to_export.PinArrowSize, ref_style.PinArrowSize, export_only_modified);
//		ExportSize_Float("PinArrowWidth", style_to_export.PinArrowWidth, ref_style.PinArrowWidth, export_only_modified);
//		ExportSize_Float("GroupRounding", style_to_export.GroupRounding, ref_style.GroupRounding, export_only_modified);
//		ExportSize_Float("GroupBorderWidth", style_to_export.GroupBorderWidth, ref_style.GroupBorderWidth, export_only_modified);
//	}
//}
//#endif
//
//void ThemeHelper::ShowCustomImGuiStyleEditor(bool* vOpen, ImGuiStyle* ref_imgui
//#ifdef USE_NODEGRAPH
//	, ax::NodeEditor::Style* ref_graph
//#endif
//)
//{
//	if (ImGui::Begin("Styles Editor", vOpen))
//	{
//		// You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to an internally stored reference)
//		auto& imgui_style = prImGuiStyle;
//		static ImGuiStyle ref_imgui_saved_style;
//		static ImVec4 ref_imgui_Good_Color;
//		static ImVec4 ref_imgui_Bad_Color;
//
//#ifdef USE_NODEGRAPH
//		auto& graph_Style = prNodeGraphStyle;
//		static ax::NodeEditor::Style ref_graph_saved_style;
//#endif
//
//		// Default to using internal storage as reference
//		static auto init = true;
//		if (init && ref_imgui == nullptr)
//		{
//			ref_imgui_saved_style = imgui_style;
//#ifdef USE_NODEGRAPH
//			ref_graph_saved_style = graph_Style;
//#endif
//		}
//		init = false;
//		if (ref_imgui == nullptr)
//		{
//			ref_imgui = &ref_imgui_saved_style;
//		}
//#ifdef USE_NODEGRAPH
//		if (ref_graph == nullptr)
//		{
//			ref_graph = &ref_graph_saved_style;
//		}
//#endif
//		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);
//
//		if (ImGui::ShowStyleSelector("Colors##Selector"))
//			ref_imgui_saved_style = imgui_style;
//		ImGui::ShowFontSelector("Fonts##Selector");
//
//		// Simplified Settings
//		if (ImGui::SliderFloat("FrameRounding", &imgui_style.FrameRounding, 0.0f, 12.0f, "%.0f"))
//			imgui_style.GrabRounding = imgui_style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
//		
//		auto window_border = (imgui_style.WindowBorderSize > 0.0f);
//		if (ImGui::Checkbox("WindowBorder", &window_border))
//			imgui_style.WindowBorderSize = window_border ? 1.0f : 0.0f;
//
//		ImGui::SameLine();
//
//		auto frame_border = (imgui_style.FrameBorderSize > 0.0f);
//		if (ImGui::Checkbox("FrameBorder", &frame_border))
//			imgui_style.FrameBorderSize = frame_border ? 1.0f : 0.0f;
//
//		ImGui::SameLine();
//
//		auto popup_border = (imgui_style.PopupBorderSize > 0.0f);
//		if (ImGui::Checkbox("PopupBorder", &popup_border))
//			imgui_style.PopupBorderSize = popup_border ? 1.0f : 0.0f;
//
//#ifdef USE_SHADOW
//		// Custom Shadow
//		ImGui::Checkbox("Use Shadow", &puUseShadow);
//		if (puUseShadow)
//		{
//			ImGui::SliderFloatDefaultCompact(300.0f, "Inner Shadow", &puShadowStrength, 2.0f, 0.0f, 0.5f);
//			ImGui::Checkbox("Use Texture for Shadow", &puUseTextureForShadow);
//		}
//#endif
//
//		// Save/Revert button
//		if (ImGui::ContrastedButton("Save Ref"))
//		{
//			*ref_imgui = ref_imgui_saved_style = imgui_style;
//			ref_imgui_Good_Color = ImGui::CustomStyle::GoodColor;
//			ref_imgui_Bad_Color = ImGui::CustomStyle::BadColor;
//#ifdef USE_NODEGRAPH
//			*ref_graph = ref_graph_saved_style = graph_Style;
//#endif
//		}
//		ImGui::SameLine();
//		if (ImGui::ContrastedButton("Revert Ref"))
//		{
//			imgui_style = *ref_imgui;
//			ImGui::CustomStyle::GoodColor = ref_imgui_Good_Color;
//			ImGui::CustomStyle::BadColor = ref_imgui_Bad_Color;
//#ifdef USE_NODEGRAPH
//			graph_Style = *ref_graph;
//#endif
//		}
//		ImGui::SameLine();
//		ImGui::HelpMarker("Save/Revert in local non-persistent storage. Default Colors definition are not affected. Use \"Export\" below to save them somewhere.");
//
//		ImGui::Separator();
//		
//		static auto output_dest = 0;
//		static auto output_only_modified = true;
//		if (ImGui::ContrastedButton("Export Sizes and Colors"))
//		{
//			if (output_dest == 0)
//				ImGui::LogToClipboard();
//			else
//				ImGui::LogToTTY();
//
//			ExportColors(imgui_style, *ref_imgui, output_only_modified);
//
//			ImGui::LogText(IM_NEWLINE);
//
//			ExportSizes(imgui_style, *ref_imgui, output_only_modified);
//
//#ifdef USE_NODEGRAPH
//			ImGui::LogText(IM_NEWLINE);
//
//			ExportGraph(graph_Style, *ref_graph, output_only_modified);
//#endif
//
//			ImGui::LogFinish();
//		}
//		ImGui::SameLine(); ImGui::SetNextItemWidth(120); ImGui::Combo("##output_type_size_and_colors", &output_dest, "To Clipboard\0To TTY\0");
//		ImGui::SameLine(); ImGui::Checkbox("Only Modified##size_and_colors", &output_only_modified);
//
//		ImGui::Separator();
//
//		if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
//		{
//			if (ImGui::BeginTabItem("Sizes"))
//			{
//				static auto output_dest_sizes = 0;
//				static auto output_only_modified_sizes = true;
//				if (ImGui::ContrastedButton("Export"))
//				{
//					if (output_dest_sizes == 0)
//						ImGui::LogToClipboard();
//					else
//						ImGui::LogToTTY();
//
//					ExportSizes(imgui_style, *ref_imgui, output_only_modified_sizes);
//
//					ImGui::LogFinish();
//				}
//				ImGui::SameLine(); ImGui::SetNextItemWidth(120); ImGui::Combo("##output_type", &output_dest_sizes, "To Clipboard\0To TTY\0");
//				ImGui::SameLine(); ImGui::Checkbox("Only Modified", &output_only_modified_sizes);
//
//				ImGui::Separator();
//
//				ImGui::BeginChild("##sizes", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
//				ImGui::PushItemWidth(-160);
//
//				ImGui::Text("Main");
//				ImGui::SliderFloat2("WindowPadding", (float*)&imgui_style.WindowPadding, 0.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat2("FramePadding", (float*)&imgui_style.FramePadding, 0.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat2("ItemSpacing", (float*)&imgui_style.ItemSpacing, 0.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat2("ItemInnerSpacing", (float*)&imgui_style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat2("TouchExtraPadding", (float*)&imgui_style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
//				ImGui::SliderFloat("IndentSpacing", &imgui_style.IndentSpacing, 0.0f, 30.0f, "%.0f");
//				ImGui::SliderFloat("ScrollbarSize", &imgui_style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("GrabMinSize", &imgui_style.GrabMinSize, 1.0f, 20.0f, "%.0f");
//
//				ImGui::Text("Borders");
//				ImGui::SliderFloat("WindowBorderSize", &imgui_style.WindowBorderSize, 0.0f, 1.0f, "%.0f");
//				ImGui::SliderFloat("ChildBorderSize", &imgui_style.ChildBorderSize, 0.0f, 1.0f, "%.0f");
//				ImGui::SliderFloat("PopupBorderSize", &imgui_style.PopupBorderSize, 0.0f, 1.0f, "%.0f");
//				ImGui::SliderFloat("FrameBorderSize", &imgui_style.FrameBorderSize, 0.0f, 1.0f, "%.0f");
//				ImGui::SliderFloat("TabBorderSize", &imgui_style.TabBorderSize, 0.0f, 1.0f, "%.0f");
//
//				ImGui::Text("Rounding");
//				ImGui::SliderFloat("WindowRounding", &imgui_style.WindowRounding, 0.0f, 12.0f, "%.0f");
//				ImGui::SliderFloat("ChildRounding", &imgui_style.ChildRounding, 0.0f, 12.0f, "%.0f");
//				ImGui::SliderFloat("FrameRounding", &imgui_style.FrameRounding, 0.0f, 12.0f, "%.0f");
//				ImGui::SliderFloat("PopupRounding", &imgui_style.PopupRounding, 0.0f, 12.0f, "%.0f");
//				ImGui::SliderFloat("ScrollbarRounding", &imgui_style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
//				ImGui::SliderFloat("GrabRounding", &imgui_style.GrabRounding, 0.0f, 12.0f, "%.0f");
//				ImGui::SliderFloat("TabRounding", &imgui_style.TabRounding, 0.0f, 12.0f, "%.0f");
//
//				ImGui::Text("Alignment");
//				ImGui::SliderFloat2("WindowTitleAlign", (float*)&imgui_style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
//				auto window_menu_button_position = imgui_style.WindowMenuButtonPosition + 1;
//				if (ImGui::Combo("WindowMenuButtonPosition", (int*)&window_menu_button_position, "None\0Left\0Right\0"))
//					imgui_style.WindowMenuButtonPosition = window_menu_button_position - 1;
//				ImGui::Combo("ColorButtonPosition", (int*)&imgui_style.ColorButtonPosition, "Left\0Right\0");
//				ImGui::SliderFloat2("ButtonTextAlign", (float*)&imgui_style.ButtonTextAlign, 0.0f, 1.0f, "%.2f"); ImGui::SameLine(); ImGui::HelpMarker("Alignment applies when a button is larger than its text content.");
//				ImGui::SliderFloat2("SelectableTextAlign", (float*)&imgui_style.SelectableTextAlign, 0.0f, 1.0f, "%.2f"); ImGui::SameLine(); ImGui::HelpMarker("Alignment applies when a selectable is larger than its text content.");
//				
//				ImGui::Text("Safe Area Padding"); ImGui::SameLine(); ImGui::HelpMarker("Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).");
//				ImGui::SliderFloat2("DisplaySafeAreaPadding", (float*)&imgui_style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f");
//				
//				ImGui::PopItemWidth();
//				ImGui::EndChild();
//
//				ImGui::EndTabItem();
//			}
//
//#ifdef USE_NODEGRAPH
//			if (ImGui::BeginTabItem("Nodes"))
//			{
//				static auto output_dest_sizes = 0;
//				static auto output_only_modified_sizes = true;
//				if (ImGui::ContrastedButton("Export"))
//				{
//					if (output_dest_sizes == 0)
//						ImGui::LogToClipboard();
//					else
//						ImGui::LogToTTY();
//
//					ExportGraph(graph_Style, *ref_graph, output_only_modified_sizes);
//
//					ImGui::LogFinish();
//				}
//				ImGui::SameLine(); ImGui::SetNextItemWidth(120); ImGui::Combo("##output_type", &output_dest_sizes, "To Clipboard\0To TTY\0");
//				ImGui::SameLine(); ImGui::Checkbox("Only Modified", &output_only_modified_sizes);
//
//				ImGui::Separator();
//
//				ImGui::BeginChild("##sizes", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
//				ImGui::PushItemWidth(-160);
//
//				ImGui::Text("Main");
//				ImGui::SliderFloat4("NodePadding", (float*)&prNodeGraphStyle.NodePadding, 0.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("NodeRounding", (float*)&prNodeGraphStyle.NodeRounding, 0.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("NodeBorderWidth", (float*)&prNodeGraphStyle.NodeBorderWidth, 0.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("HoveredNodeBorderWidth", (float*)&prNodeGraphStyle.HoveredNodeBorderWidth, 0.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("SelectedNodeBorderWidth", (float*)&prNodeGraphStyle.SelectedNodeBorderWidth, 0.0f, 10.0f, "%.0f");
//				ImGui::SliderFloat("PinRounding", (float*)&prNodeGraphStyle.PinRounding, 0.0f, 30.0f, "%.0f");
//				ImGui::SliderFloat("PinBorderWidth", (float*)&prNodeGraphStyle.PinBorderWidth, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("LinkStrength", (float*)&prNodeGraphStyle.LinkStrength, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat2("SourceDirection", (float*)&prNodeGraphStyle.SourceDirection, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat2("TargetDirection", (float*)&prNodeGraphStyle.TargetDirection, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("ScrollDuration", (float*)&prNodeGraphStyle.ScrollDuration, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("FlowMarkerDistance", (float*)&prNodeGraphStyle.FlowMarkerDistance, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("FlowSpeed", (float*)&prNodeGraphStyle.FlowSpeed, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("FlowDuration", (float*)&prNodeGraphStyle.FlowDuration, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat2("PivotAlignment", (float*)&prNodeGraphStyle.PivotAlignment, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat2("PivotSize", (float*)&prNodeGraphStyle.PivotSize, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat2("PivotScale", (float*)&prNodeGraphStyle.PivotScale, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("PinCorners", (float*)&prNodeGraphStyle.PinCorners, 0.0f, 15.0f, "%.0f");
//				ImGui::SliderFloat("PinRadius", (float*)&prNodeGraphStyle.PinRadius, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("PinArrowSize", (float*)&prNodeGraphStyle.PinArrowSize, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("PinArrowWidth", (float*)&prNodeGraphStyle.PinArrowWidth, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("GroupRounding", (float*)&prNodeGraphStyle.GroupRounding, 1.0f, 20.0f, "%.0f");
//				ImGui::SliderFloat("GroupBorderWidth", (float*)&prNodeGraphStyle.GroupBorderWidth, 1.0f, 20.0f, "%.0f");
//
//				ImGui::PopItemWidth();
//				ImGui::EndChild();
//
//				ImGui::EndTabItem();
//			}
//#endif
//
//			if (ImGui::BeginTabItem("Colors"))
//			{
//				static auto output_dest_colors = 0;
//				static auto output_only_modified_colors = true;
//				if (ImGui::ContrastedButton("Export"))
//				{
//					if (output_dest_colors == 0)
//						ImGui::LogToClipboard();
//					else
//						ImGui::LogToTTY();
//
//					ExportColors(imgui_style, *ref_imgui, output_only_modified_colors);
//
//					ImGui::LogFinish();
//				}
//				ImGui::SameLine(); ImGui::SetNextItemWidth(120); ImGui::Combo("##output_type", &output_dest_colors, "To Clipboard\0To TTY\0");
//				ImGui::SameLine(); ImGui::Checkbox("Only Modified", &output_only_modified_colors);
//
//				ImGui::Separator();
//
//				static ImGuiTextFilter filter;
//				filter.Draw("Filter colors", ImGui::GetFontSize() * 16);
//
//				static auto alpha_flags = 0;
//				if (ImGui::RadioButton("Opaque", alpha_flags == 0)) { alpha_flags = 0; } ImGui::SameLine();
//				if (ImGui::RadioButton("Alpha", alpha_flags == ImGuiColorEditFlags_AlphaPreview)) { alpha_flags = ImGuiColorEditFlags_AlphaPreview; } ImGui::SameLine();
//				if (ImGui::RadioButton("Both", alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf)) { alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf; } ImGui::SameLine();
//				ImGui::HelpMarker("In the color list:\nLeft-click on colored square to open color picker,\nRight-click to open edit options menu.");
//
//				ImGui::BeginChild("##colors", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
//				ImGui::PushItemWidth(-160);
//
//				DrawItem(14582, filter, "Good Color", ImGui::CustomStyle::GoodColor, ref_imgui_Good_Color, alpha_flags);
//				DrawItem(114583, filter, "Bad Color", ImGui::CustomStyle::BadColor, ref_imgui_Bad_Color, alpha_flags);
//
//				for (auto i = 0; i < ImGuiCol_COUNT; i++)
//				{
//					DrawItem(i, filter, ImGui::GetStyleColorName(i), imgui_style.Colors[i], ref_imgui->Colors[i], alpha_flags);
//				}
//				ImGui::PopItemWidth();
//				ImGui::EndChild();
//
//				ImGui::EndTabItem();
//			}
//
//			ImGui::EndTabBar();
//		}
//
//		ImGui::PopItemWidth();
//	}
//	ImGui::End();
//
//	memcpy(&ImGui::GetStyle(), &prImGuiStyle, sizeof(ImGuiStyle));
//
//#ifdef USE_NODEGRAPH
//	memcpy(&ax::NodeEditor::GetStyle(), &prNodeGraphStyle, sizeof(ax::NodeEditor::Style));
//#endif
//}
//
//#ifdef USE_CODEEDITOR
//void ThemeHelper::ShowCustomTextEditorStyleEditor(bool* vOpen)
//{
//	if (ImGui::Begin("ImGuiColorTextEdit Style Editor", vOpen))
//	{
//		// You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to an internally stored reference)
//		auto imgui_style = GetPalette();
//		static TextEditor::Palette ref_saved_style;
//		TextEditor::Palette* ref = nullptr;
//
//		// Default to using internal storage as reference
//		static bool init = true;
//		if (init)
//		{
//			ref_saved_style = imgui_style;
//		}
//		init = false;
//		ref = &ref_saved_style;
//
//		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);
//
//		static int style_idx = -1;
//		if (ImGui::Combo("Palette", &style_idx, "Light\0Dark\0Retro Blue\0"))
//		{
//			switch (style_idx)
//			{
//			case 0: ApplyPalette(TextEditor::GetLightPalette()); break;
//			case 1: ApplyPalette(TextEditor::GetDarkPalette()); break;
//			case 2: ApplyPalette(TextEditor::GetRetroBluePalette()); break;
//			}
//			ref_saved_style = imgui_style;
//		}
//
//		// Save/Revert button
//		if (ImGui::ContrastedButton("Save Ref"))
//			*ref = ref_saved_style = imgui_style;
//		ImGui::SameLine();
//		if (ImGui::ContrastedButton("Revert Ref"))
//			imgui_style = *ref;
//		ImGui::SameLine();
//		ImGui::HelpMarker("Save/Revert in local non-persistent storage. Default Colors definition are not affected. Use \"Export\" below to save them somewhere.");
//
//		ImGui::Separator();
//
//		ImGui::BeginChild("##palette", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
//		ImGui::PushItemWidth(-160);
//		for (int i = 0; i < (int)TextEditor::PaletteIndex::Max; i++)
//		{
//			const char* name = Get_ImGuiColorTextEditPalette_NameFromCol((TextEditor::PaletteIndex)i);
//			ImGui::PushID(i);
//			ImVec4 col = ImGui::ColorConvertU32ToFloat4(imgui_style[i]);
//			bool res = ImGui::ColorEdit4("##palettecolor", (float*)&col, ImGuiColorEditFlags_AlphaBar);
//			imgui_style[i] = ImGui::ColorConvertFloat4ToU32(col);
//			if (memcmp(&imgui_style[i], &((*ref)[i]), sizeof(ImU32)) != 0)
//			{
//				// Tips: in a real user application, you may want to merge and use an icon font into the main font, so instead of "Save"/"Revert" you'd use icons.
//				// Read the FAQ and docs/FONTS.txt about using icon fonts. It's really easy and super convenient!
//				ImGui::SameLine(0.0f, prImGuiStyle.ItemInnerSpacing.x); if (ImGui::ContrastedButton("Save")) (*ref)[i] = imgui_style[i];
//				ImGui::SameLine(0.0f, prImGuiStyle.ItemInnerSpacing.x);
//				if (ImGui::ContrastedButton("Revert"))
//				{
//					imgui_style[i] = (*ref)[i];
//					res = true;
//				}
//			}
//			if (res)
//			{
//				ApplyPalette(imgui_style);
//			}
//			ImGui::SameLine(0.0f, prImGuiStyle.ItemInnerSpacing.x);
//			ImGui::TextUnformatted(name);
//			ImGui::PopID();
//		}
//		ImGui::PopItemWidth();
//		ImGui::EndChild();
//	}
//	ImGui::End();
//}
//#endif