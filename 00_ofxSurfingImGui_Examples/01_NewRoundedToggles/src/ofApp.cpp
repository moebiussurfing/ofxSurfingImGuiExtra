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

		//-

		ui.DrawWindowAdvanced();

		//--

		//IMGUI_SUGAR__WINDOWS_CONSTRAINTSW;

		if (ui.BeginWindow("TOGGLES", ImGuiWindowFlags_None))
		{
			ui.Add(ui.bAdvanced, OFX_IM_TOGGLE_ROUNDED_MINI);
			ui.AddSpacingBigSeparated();

			//--

			if (ui.BeginTree("LEGACY"))
			{
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


				ui.EndTree();
			}

			//--

			ui.EndWindow();
		}
		
		//--

		drawWindowNewToggles();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawWindowNewToggles()
{
	if (ui.BeginWindow("NEW", ImGuiWindowFlags_None))
	{
		ui.AddLabel("BY @cmdwtf");
		ui.AddLabelLinkURL("GitHub/imgui_toggle", "https://github.com/cmdwtf/imgui_toggle", OFX_IM_FONT_DEFAULT);

		ui.AddSpacingBig();

		static bool toggle_a = true;
		static bool toggle_b = true;
		static bool toggle_c = true;
		static bool toggle_d = true;
		static bool toggle_e = true;
		static bool toggle_f = true;
		static bool toggle_custom = true;

		// use some lovely gray backgrounds for "off" toggles
		// the default will use your theme's frame background colors.
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.45f, 0.45f, 0.45f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.65f, 0.65f, 0.65f, 1.0f));

		// a default and default animated toggle
		ImGui::Toggle("Default Toggle", &toggle_a);
		ImGui::Toggle("Animated Toggle", &toggle_b, ImGuiToggleFlags_Animated);

		// this toggle draws a simple border around it's frame and knob
		ImGui::Toggle("Bordered Knob", &toggle_c, ImGuiToggleFlags_Bordered, 1.0f);

		// this toggle uses stack-pushed style colors to change the way it displays
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.16f, 0.66f, 0.45f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.57f, 1.0f));
		ImGui::Toggle("Green Toggle", &toggle_d);
		ImGui::PopStyleColor(2);

		ImGui::Toggle("Toggle with A11y Labels", &toggle_e, ImGuiToggleFlags_A11yLabels);

		// this toggle shows no label
		ImGui::Toggle("##Toggle With Hidden Label", &toggle_f);

		//////////////////////////////////////////////////////////////////////////
		// Custom Toggle

		ImGui::BeginChild("Custom Toggle Window", ImVec2(), true, ImGuiWindowFlags_MenuBar);
		ImGui::BeginMenuBar();
		ImGui::Text("Custom Toggle");
		ImGui::EndMenuBar();

		static ImGuiToggleConfig config;
		ImGui::Toggle("Customized Toggle", &toggle_custom, config);
		ImGui::NewLine();

		// animation speed controls how quickly the toggle animates. if set to 0, animation is disabled.
		ImGui::SliderFloat("AnimationSpeed", &config.AnimationSpeed, ImGuiToggleConstants::AnimationSpeedMinimum, 2.0f);

		// frame rounding sets how round the frame is when drawn, where 0 is a rectangle, and 1 is a circle.
		ImGui::SliderFloat("FrameRounding", &config.FrameRounding, ImGuiToggleConstants::FrameRoundingMinimum, ImGuiToggleConstants::FrameRoundingMaximum);

		// knob rounding sets how round the knob is when drawn, where 0 is a rectangle, and 1 is a circle.
		ImGui::SliderFloat("KnobRounding", &config.KnobRounding, ImGuiToggleConstants::KnobRoundingMinimum, ImGuiToggleConstants::KnobRoundingMaximum);

		// size controls the width and the height of the toggle frame
		ImGui::SliderFloat2("Size", &config.Size.x, 0.0f, 100.0f, "%.0f");

		// width ratio sets how wide the toggle is with relation to the frame height. if Size is non-zero, this is unused.
		ImGui::SliderFloat("WidthRatio", &config.WidthRatio, ImGuiToggleConstants::WidthRatioMinimum, ImGuiToggleConstants::WidthRatioMaximum);

		// knob inset controls how many pixels the knob is set into the frame. negative values will cause it to grow outside the frame.
		ImGui::SliderFloat("KnobInset", &config.KnobInset, ImGuiToggleConstants::KnobInsetMinimum, ImGui::GetFrameHeight() * 0.5f);

		// how thick should the frame border be (if enabled)
		ImGui::SliderFloat("FrameBorderThickness", &config.FrameBorderThickness, 0.0f, 3.0f);

		// how thick should the knob border be (if enabled)
		ImGui::SliderFloat("KnobBorderThickness", &config.KnobBorderThickness, 0.0f, 3.0f);

		// flags for various toggle features
		ImGui::Columns(2);
		ImGui::Text("Meta Flags");
		ImGui::CheckboxFlags("Bordered", &config.Flags, ImGuiToggleFlags_Bordered);
		ImGui::NextColumn();
		ImGui::CheckboxFlags("BorderedFrame", &config.Flags, ImGuiToggleFlags_BorderedFrame);
		ImGui::CheckboxFlags("BorderedKnob", &config.Flags, ImGuiToggleFlags_BorderedKnob);
		ImGui::CheckboxFlags("A11yLabels", &config.Flags, ImGuiToggleFlags_A11yLabels);
		ImGui::CheckboxFlags("HighlightEnabledKnob", &config.Flags, ImGuiToggleFlags_HighlightEnabledKnob);
		ImGui::Columns();

		if (ImGui::Button("Reset Config"))
		{
			config = ImGuiToggleConfig();
		}
		ImGui::SameLine();

		if (ImGui::Button("iOS Style"))
		{
			config = ImGuiToggleConfig();
			config.Flags |= ImGuiToggleFlags_A11yLabels;
		}
		ImGui::SameLine();

		if (ImGui::Button("Material Style"))
		{
			config = ImGuiToggleConfig();
			config.Flags |= ImGuiToggleFlags_HighlightEnabledKnob;
			config.KnobInset = -3.0f;
			config.WidthRatio = 1.714f;
		}

		ImGui::EndChild();

		// End Custom Toggle
		//////////////////////////////////////////////////////////////////////////

		// pop the FrameBg/FrameBgHover color styles
		ImGui::PopStyleColor(2);

		//--

		ui.EndWindow();
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