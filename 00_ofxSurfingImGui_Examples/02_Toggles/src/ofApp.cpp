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
			string name = "Knobs";
			ui.BeginWindow(name.c_str());
			{
				ui.AddLabelHuge("LEGACY NON STYLED KNOBS");
				ui.AddSpacing();

				ui.Add(b1, OFX_IM_TOGGLE, 4, true);
				ui.Add(b2, OFX_IM_TOGGLE, 4, true);
				ui.Add(b3, OFX_IM_TOGGLE, 4, true);
				ui.Add(b4, OFX_IM_TOGGLE, 4, false);

				ui.AddSpacingBigSeparated();

				static bool toggle_a = true;
				static bool toggle_b = true;
				static bool toggle_c = true;
				static bool toggle_d = true;
				static bool toggle_e = true;
				static bool toggle_f = true;

				static float frame_rounding = 0.2f;
				static float knob_rounding = 0.2f;

				// a default and default animated toggle
				ImGui::Toggle("Default Toggle", &toggle_a);
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
