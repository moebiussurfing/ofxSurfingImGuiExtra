#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//if (key == '0') theme.setup();//default
	if (key == '1') ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	if (key == '2') ofxImGuiSurfing::ImGui_ThemeOlekristensen();
	if (key == '3') ofxImGuiSurfing::ImGui_ThemeSequentity();
	if (key == '4') ofxImGuiSurfing::ImGui_ThemeT3();
	if (key == '5') ofxImGuiSurfing::ImGui_ThemeYave();
	if (key == '6') ofxImGuiSurfing::ImGui_ThemeModernDark();
	if (key == '7') ofxImGuiSurfing::ImGui_ThemeFlatDryWineGreen();
	if (key == '8') ImGui::StyleColorsDark();
	if (key == '9') ImGui::StyleColorsLight();
	if (key == '0') ImGui::StyleColorsClassic();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ui.Begin();
	{
		static bool bFirstFrame = true;
		if (bFirstFrame) {
			bFirstFrame = false;
			theme.setup();
		}

		ui.DrawWindowAdvanced();

		{
			string name = "TOGGLES";
			ui.BeginWindow(name.c_str());
			{
				// label
				static int f = 0;
				if (ui.AddButton("Change Size"))
				{
					f = (++f) % (int)OFX_IM_FONT_AMOUNT;
					ofLogNotice("ofxImGuiSurfing") << "Font#" << f;
				}
				ui.AddLabel("LEGACY ROUNDED TOGGLES", SurfingFontTypes(f));

				ui.AddSpacing();

				ui.Add(b1, OFX_IM_TOGGLE_ROUNDED_BIG);
				ui.Add(b2, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
				ui.Add(b3, OFX_IM_TOGGLE_ROUNDED_SMALL);
				ui.Add(b4, OFX_IM_TOGGLE_ROUNDED_MINI);

				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("NEW TOGGLE BY @cmdwtf");

				ui.AddLinkUrlLabel("github.com/cmdwtf/imgui_toggle", "https://github.com/cmdwtf/imgui_toggle", OFX_IM_FONT_DEFAULT);
				//ui.AddLinkUrlButton("imgui_toggle", "https://github.com/cmdwtf/imgui_toggle", true);

				//--

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

					ImGui::Toggle("Default Toggle Border", &toggle_a, ImGuiToggleFlags_Bordered);
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
				ImGui::Toggle("Animated Square Toggle", &toggle_d, ImGuiToggleFlags_Animated | ImGuiToggleFlags_Bordered, frame_rounding, knob_rounding);
				//ImGui::Toggle("Animated Square Toggle", &toggle_d, ImGuiToggleFlags_Animated, frame_rounding, knob_rounding);

				// this toggle uses stack-pushed style colors to change the way it displays
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.16f, 0.66f, 0.45f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 1.f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.57f, 1.0f));
				ImGui::Toggle("Custom Toggle", &toggle_e);
				ImGui::PopStyleColor(3);

				// this toggle shows no label
				ImGui::Toggle("##Toggle With Hidden Label", &toggle_f);

				ui.AddSpacingBigSeparated();

				//ImGui::PushStyleVar(ImGuiStyleVar_widr)

				//ui.AddSpacingHuge();
				//ImGui::Button("x2", ImVec2(w, 2 * h));

				//ImGui::Button("x1", ImVec2(-FLT_MIN, 0.0f));

				//static float v1 = .5f;
				//ImGui::SliderFloat("v1", &v1, 0, 1);

				//static float v2 = .5f;
				//ImGui::PushItemWidth(w);
				//ImGui::Button("Button");
				////ImGui::Toggle("Default Toggle", &toggle_a);
				////ImGui::SliderFloat("##1", &v2, 0, 1);
				//ImGui::PopItemWidth();

				//ui.AddSpacingHuge();

				//static ofParameter<float> v{ "v", .5f,0,1 };
				//ui.Add(v, OFX_IM_SLIDER);

				//static int v3 = 5;

				ui.AddSpacingHuge();

				float w = ImGui::GetContentRegionAvail().x;
				float h = ImGui::GetFrameHeight(); // single unit height
				float hh = 2 * h; // double height
				float spx = ImGui::GetStyle().ItemSpacing.x; // spacing between two widgets
				float sp; // sp = spx / numWidgets; // numWidgets is amount per line
				//sp = spx / 2;
				ImGui::Button("B1", ImVec2(w * 0.25 - spx, hh));
				ImGui::SameLine();
				ImGui::Button("B2", ImVec2(w * 0.75 - spx, hh));
				//sp = spx / 3;
				ImGui::Button("B3", ImVec2(w * 1 / 3.f - spx, h));
				ImGui::SameLine();
				ImGui::Button("B4", ImVec2(w * 1 / 3.f - spx, h));
				ImGui::SameLine();
				ImGui::Button("B5", ImVec2(w * 1 / 3.f - spx, h));

				ui.AddSpacingHuge();

				//ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(__ww - __sp, 2 * h));
				//ImGui::SetNextItemWidth(w); 
				//ImGui::PushItemWidth(w); 
				//ImGui::SliderInt("v3", &v3, 0, 10);


				//ImGui::Button("Button");
				////ImGui::Button("x1", ImVec2(-FLT_MIN, 0.0f));
				////ImGui::PopItemWidth();
				//ImGui::PopStyleVar();

				//--

				//TODO:
				// Colored buttons
				ofxImGuiSurfing::ColoredButtonV1("Hello", ImVec2(-FLT_MIN, 0.0f), IM_COL32(255, 255, 255, 255), IM_COL32(200, 60, 60, 255), IM_COL32(180, 40, 90, 255));

				//ofxImGuiSurfing::ColoredButtonV1("You", ImVec2(-FLT_MIN, 0.0f), IM_COL32(255, 255, 255, 255), IM_COL32(50, 220, 60, 255), IM_COL32(69, 150, 70, 255));

				ofxImGuiSurfing::ColoredButtonV1("You", ImVec2(-FLT_MIN, 50), IM_COL32(255, 255, 255, 255), IM_COL32(50, 220, 60, 255), IM_COL32(69, 150, 255, 255));
			}
			ui.EndWindow();
		}
	}
	ui.End();
}
