#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowPosition(-1920, 25);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		// Initialize
		{
			static bool bFirstFrame = true;
			if (bFirstFrame) 
			{
				bFirstFrame = false;
				ImGui::StyleColorsDark();
			}
		}

		ui.DrawWindowAdvanced();

		if (ui.BeginWindow("TOGGLES"))
		{
			ui.Add(ui.bAdvanced, OFX_IM_TOGGLE_ROUNDED_MINI);
			ui.AddSpacingBigSeparated();

			//--

			// Label
			static int f = 2;
			if (ui.AddButton("CHANGE FONT SIZE", OFX_IM_BUTTON_BIG))
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

			//--

			//ui.AddSpacingBig();
			drawNewToggles();

			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawNewToggles()
{
	//ui.AddLabelBig("NEW TOGGLE BY @cmdwtf");
	if (ui.BeginTree("NEW TOGGLE BY @cmdwtf"))
	{
		ui.AddLinkUrlLabel("GitHub/imgui_toggle",
			"https://github.com/cmdwtf/imgui_toggle", OFX_IM_FONT_DEFAULT);

		ui.AddSpacingBig();

		static bool toggle_a = true;
		static bool toggle_b = true;
		static bool toggle_c = true;
		static bool toggle_d = true;
		static bool toggle_e = true;
		static bool toggle_f = true;

		static float frame_rounding = 1.f;
		static float knob_rounding = 1.f;

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

		ui.EndTree();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == OF_KEY_TAB) {
		iTheme = ++iTheme % 11;
		if (iTheme == 0) theme.setup();//default
		else if (iTheme == 1) ImGui::StyleColorsLight();
		else if (iTheme == 2) ImGui::StyleColorsClassic();
		else if (iTheme == 3) ImGui::StyleColorsDark();
		else if (iTheme == 4) ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
		else if (iTheme == 5) ofxImGuiSurfing::ImGui_ThemeOlekristensen();
		else if (iTheme == 6) ofxImGuiSurfing::ImGui_ThemeSequentity();
		else if (iTheme == 7) ofxImGuiSurfing::ImGui_ThemeT3();
		else if (iTheme == 8) ofxImGuiSurfing::ImGui_ThemeYave();
		else if (iTheme == 9) ofxImGuiSurfing::ImGui_ThemeModernDark();
		else if (iTheme == 10) ofxImGuiSurfing::ImGui_ThemeFlatDryWineGreen();
	}

	if (key == '0') theme.setup();//default
	if (key == '1') ImGui::StyleColorsLight();
	if (key == '2') ImGui::StyleColorsClassic();
	if (key == '3') ImGui::StyleColorsDark();
	if (key == '4') ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	if (key == '5') ofxImGuiSurfing::ImGui_ThemeOlekristensen();
	if (key == '6') ofxImGuiSurfing::ImGui_ThemeSequentity();
	if (key == '7') ofxImGuiSurfing::ImGui_ThemeT3();
	if (key == '8') ofxImGuiSurfing::ImGui_ThemeYave();
	if (key == '9') ofxImGuiSurfing::ImGui_ThemeModernDark();
	if (key == '-') ofxImGuiSurfing::ImGui_ThemeFlatDryWineGreen();
}