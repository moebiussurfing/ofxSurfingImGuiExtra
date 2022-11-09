#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
}

//--------------------------------------------------------------
void ofApp::draw() {

	ui.Begin();
	{
		ui.DrawWindowAdvanced();

		{
			string name = "TOGGLES";
			ui.BeginWindow(name.c_str());
			{
				ui.AddLabelBig("LEGACY ROUNDED TOGGLES");
				ui.AddSpacing();

				ui.Add(b1, OFX_IM_TOGGLE_ROUNDED_BIG);
				ui.Add(b2, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
				ui.Add(b3, OFX_IM_TOGGLE_ROUNDED_SMALL);
				ui.Add(b4, OFX_IM_TOGGLE_ROUNDED_MINI);

				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("NEW TOGGLE BY @cmdwtf FROM");
				ui.AddLinkURL("imgui_toggle", "https://github.com/cmdwtf/imgui_toggle", true);
				ui.AddSpacing();

				static bool toggle_a = true;
				static bool toggle_b = true;
				static bool toggle_c = true;
				static bool toggle_d = true;
				static bool toggle_e = true;
				static bool toggle_f = true;

				static float frame_rounding = 0.2f;
				static float knob_rounding = 0.2f;

				// a default and default animated toggle
				{
					bool is_active = ImGui::IsItemActive();
					bool is_hovered = ImGui::IsItemHovered();

					ImU32 col_frame;
					ImU32 col_fill;

					// State true
					if (toggle_a)
					{
						col_frame = ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBg : ImGuiCol_FrameBgHovered);
						col_fill = col_frame;
					}
					// State false
					else
					{
						col_frame = ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
						col_fill = col_frame;
					}

					ImGui::PushStyleColor(ImGuiCol_Button, col_frame);
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, col_fill);
					//col_frame = ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBg : ImGuiCol_FrameBgHovered);

					ImGui::Toggle("Default Toggle", &toggle_a);
					ImGui::PopStyleColor(2);
				}

				//--

				ImGui::Toggle("Animated Toggle", &toggle_b, ImGuiToggleFlags_Animated);

				// sliders for adjusting the rounding for the next two toggles.
				ImGui::SliderFloat("frame_rounding", &frame_rounding, 0.0f, 1.0f);
				ImGui::SliderFloat("knob_rounding", &knob_rounding, 0.0f, 1.0f);

				// a default and animated toggle that can have their frames and knobs rounded
				// a rounding of 0 is completely square, a rounding of 1 is fully rounded.
				ImGui::Toggle("Square Toggle", &toggle_c, ImGuiToggleFlags_Default, frame_rounding, knob_rounding);
				ImGui::Toggle("Animated Square Toggle", &toggle_d, ImGuiToggleFlags_Animated, frame_rounding, knob_rounding);

				// this toggle uses stack-pushed style colors to change the way it displays
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.16f, 0.66f, 0.45f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.57f, 1.0f));
				ImGui::Toggle("Green Toggle", &toggle_e);
				ImGui::PopStyleColor(2);

				// this toggle shows no label
				ImGui::Toggle("##Toggle With Hidden Label", &toggle_f);
			}
			ui.EndWindow();
		}
	}
	ui.End();
}
