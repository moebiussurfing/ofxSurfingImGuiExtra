#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowPosition(-1920, 28);

	ui.setup();

	//--

	// We can activate one of the bundled Themes:
	// Must be called after setup() to overwrite the default loaded theme.

	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	//ofxImGuiSurfing::ImGui_ThemeOlekristensen();
	//ofxImGuiSurfing::ImGui_ThemeSequentity();

	//--

	setupFonts();

	//--

	bEnable.set("Enable", false);
	amount2.set("amount2", 10, 0, 25);
}

//--------------------------------------------------------------
void ofApp::setupFonts()
{
	ui.clearFonts();

	// NOTE: We can add font manually pushing "Add Font" button.
	// then we can pick a default font setting "Font Index".
	// this is for testing styles.

	// NOTE: Then, we can add by code too to set hardcoded.
	// Push some fonts:

	std::string _fontName;
	float _fontSize;
	std::string _path = "assets/fonts/"; // assets folder

	// Font #0
	_fontName = "AnonymousPro-Regular.ttf";
	_fontSize = 12;
	ui.pushFont(_path + _fontName, _fontSize);

	// Font #1
	_fontName = "OpenSans-Regular.ttf";
	_fontSize = 14;
	ui.pushFont(_path + _fontName, _fontSize);

	// Font #2
	_fontName = "overpass-mono-bold.otf";
	_fontSize = 16;
	ui.pushFont(_path + _fontName, _fontSize);

	// Font #3
	_fontName = "JetBrainsMonoNL-ExtraBold.ttf";
	_fontSize = 18;
	ui.pushFont(_path + _fontName, _fontSize);

	//--

	//TODO:
	//// default
	//ui.addFont(_path + _fontName, FONT_DEFAULT_SIZE);

	int amt = ui.getNumFonts();
	fontSize.set("Font Size", 10, 6, 30);
	fontIndex.set("Font Index", 0, 0, amt - 1);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin(); // global begin
	{
		// Main Window
		drawMainWindow();

		//-----

		// Stylized Window 
		if (bOpenWindowStyled) drawWindowStylized();

		//-----

		// Theme editor
		if (bOpenWindowEditor)
		{
			IMGUI_SUGAR__WINDOWS_CONSTRAINTS_FULL;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Dear ImGui Style Editor", &bOpenWindowEditor, window_flags);
			{
				ofxImGuiSurfing::ShowStyleEditor2(NULL);
			}
			ImGui::End();
		}
	}
	ui.End(); // global end
}

//--------------------------------------------------------------
void ofApp::drawMainWindow()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	string s;

	if (ui.BeginWindow("MAIN WINDOW", &bOpenWindowMain, window_flags))
	{
		ofxImGuiSurfing::ToggleRoundedButton("THEME EDITOR", &bOpenWindowEditor);

		//TODO: that should be done with a flag to run inside begin/end
		//if (ImGui::Button("Add Font"))
		//{
		//	ui.openFontFileDialog(fontSize);
		//	fontIndex.setMax(ui.getNumFonts() - 1);
		//}

		//if (ui.Add(fontSize))
		//{
		//}

		ui.AddSpacingBigSeparated();

		if (ui.Add(fontIndex))
		{
			//ui.setDefaultFontIndex(fontIndex);
		}

		s = ofToString(fontIndex) + "/" + ofToString(fontIndex.getMax());
		ui.AddLabel(s.c_str(), false, true);

		s = ofToString(ui.getFontName(fontIndex));
		ui.AddLabel(s.c_str(), false, true);

		//if (ImGui::Button("Set Font")) {
		//	ui.setDefaultFontIndex(fontIndex);
		//}

		//-

		ui.AddSpacingBigSeparated();

		ofxImGuiSurfing::ToggleRoundedButton("STYLIZED WINDOW", &bOpenWindowStyled);
		if (bOpenWindowStyled) {
			ui.AddSpacing();

			ofxImGuiSurfing::ToggleRoundedButton("STYLIZE FONTS", &bStyleFonts);
			// -> will crash if styles are not queued!
		}

		ui.AddSpacingBigSeparated();

		//-

		// a public bool variable to allow handle auto-resize. Applied here to all the windows.
		ui.Add(ui.bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);
		//ui.Add(ui.bAutoResize); 

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawWindowStylized()
{
	// A window but using my ofxSurfingGui.h class helper
	// Uses my own simpler helpers: 
	// ofxSurfing_ImGui_Helpers.h
	// Notice that you can add an ofParameterGroup out of a ofxImGui window. 
	// (TODO: but this potentially make troubles yet [WIP] bc getUniqueNames engine!)

	//-

	// Minimal sizes
	float ww = PANEL_WIDGETS_WIDTH_MIN;
	float hh = PANEL_WIDGETS_HEIGHT_MIN;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		if (ui.BeginWindow("STYLIZED WINDOW", &bOpenWindowStyled, window_flags))
		{
			ofxImGuiSurfing::ToggleRoundedButton("STYLIZE FONTS", &bStyleFonts);
			// -> will crash if styles are not queued!

			ui.AddSpacing();

			if (!bStyleFonts) ui.AddLabelHuge("All widgets now using DEFAULT style", false, true);
			else ui.AddLabelHuge("Each widget now using CUSTOM styles", false, true);

			ui.AddSpacingSeparated();

			if (bStyleFonts) ui.pushStyleFont(0);
			{
				if (bStyleFonts) {
					ui.AddLabel("Font 0", false, true);
					ui.AddLabel(ui.getFontName(0), false, true);
				}

				ui.Add(bEnable, OFX_IM_TOGGLE);
				ui.Add(amount2);
				ui.AddLabel(txt, false, true);
			}
			if (bStyleFonts) ui.popStyleFont();

			ui.AddSpacingSeparated();

			//-

			if (bStyleFonts) ui.pushStyleFont(1);
			{
				if (bStyleFonts) {
					ui.AddLabel("Font 1", false, true);
					ui.AddLabel(ui.getFontName(1), false, true);
				}

				ui.Add(bEnable, OFX_IM_TOGGLE);
				ui.Add(amount2);
				ui.AddLabel(txt, false, true);
			}
			if (bStyleFonts) ui.popStyleFont();

			ui.AddSpacingSeparated();

			//-

			if (bStyleFonts) ui.pushStyleFont(2);
			{
				if (bStyleFonts) {
					ui.AddLabel("Font 2", false, true);
					ui.AddLabel(ui.getFontName(2), false, true);
				}

				ui.Add(bEnable, OFX_IM_TOGGLE);
				ui.Add(amount2);
				ui.AddLabel(txt, false, true);
			}
			if (bStyleFonts) ui.popStyleFont();

			ui.AddSpacingSeparated();

			//-

			// Take care not pushing a non existing index or it will crash!
			if (bStyleFonts) ui.pushStyleFont(3);
			{
				if (bStyleFonts) {
					ui.AddLabel("Font 3", false, true);
					ui.AddLabel(ui.getFontName(3), false, true);
				}

				ui.Add(bEnable, OFX_IM_TOGGLE);
				ui.Add(amount2);
				ui.AddLabel(txt, false, true);
			}
			if (bStyleFonts) ui.popStyleFont();

			ui.EndWindow();
		}
	}
	ImGui::PopStyleVar();
}
