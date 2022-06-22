#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowPosition(-1920, 28);

	guiManager.setup();

	//--

	// We can activate one of the bundled Themes:
	// Must be called after setup() to overwrite the default loaded theme.

	ofxImGuiSurfing::ImGui_ThemeOlekristensen();
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
	guiManager.clearFonts();

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
	guiManager.pushFont(_path + _fontName, _fontSize);

	// Font #1
	_fontName = "OpenSans-Regular.ttf";
	_fontSize = 14;
	guiManager.pushFont(_path + _fontName, _fontSize);

	// Font #2
	_fontName = "overpass-mono-bold.otf";
	_fontSize = 16;
	guiManager.pushFont(_path + _fontName, _fontSize);

	// Font #3
	_fontName = "JetBrainsMonoNL-ExtraBold.ttf";
	_fontSize = 18;
	guiManager.pushFont(_path + _fontName, _fontSize);

	//--

	//TODO:
	//// default
	//guiManager.addFont(_path + _fontName, FONT_DEFAULT_SIZE);

	int amt = guiManager.getNumFonts();
	fontSize.set("Font Size", 10, 6, 30);
	fontIndex.set("Font Index", 0, 0, amt - 1);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
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
			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Dear ImGui Style Editor", &bOpenWindowEditor, window_flags);
			{
				ofxImGuiSurfing::ShowStyleEditor2(NULL);
			}
			ImGui::End();
		}
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::drawMainWindow()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	string s;

	if (guiManager.beginWindow("MAIN WINDOW", &bOpenWindowMain, window_flags))
	{
		ofxImGuiSurfing::ToggleRoundedButton("THEME EDITOR", &bOpenWindowEditor);

		//TODO: that should be done with a flag to run inside begin/end
		//if (ImGui::Button("Add Font"))
		//{
		//	guiManager.openFontFileDialog(fontSize);
		//	fontIndex.setMax(guiManager.getNumFonts() - 1);
		//}

		//if (guiManager.Add(fontSize))
		//{
		//}
		
		guiManager.AddSpacingBigSeparated();

		if (guiManager.Add(fontIndex))
		{
			//guiManager.setDefaultFontIndex(fontIndex);
		}

		s = ofToString(fontIndex) + "/" + ofToString(fontIndex.getMax());
		guiManager.AddLabel(s.c_str(), false, true);

		s = ofToString(guiManager.getFontName(fontIndex));
		guiManager.AddLabel(s.c_str(), false, true);

		//if (ImGui::Button("Set Font")) {
		//	guiManager.setDefaultFontIndex(fontIndex);
		//}

		//-

		guiManager.AddSpacingBigSeparated();

		ofxImGuiSurfing::ToggleRoundedButton("STYLIZED WINDOW", &bOpenWindowStyled);
		if (bOpenWindowStyled) {
			guiManager.AddSpacing();

			ofxImGuiSurfing::ToggleRoundedButton("STYLIZE FONTS", &bStyleFonts);
			// -> will crash if styles are not queued!
		}

		guiManager.AddSpacingBigSeparated();

		//-

		// a public bool variable to allow handle auto-resize. Applied here to all the windows.
		guiManager.Add(guiManager.bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);
		//guiManager.Add(guiManager.bAutoResize); 

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawWindowStylized()
{
	// A window but using my ofxSurfing_ImGui_Manager.h class helper
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
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		if (guiManager.beginWindow("STYLIZED WINDOW", &bOpenWindowStyled, window_flags))
		{
			ofxImGuiSurfing::ToggleRoundedButton("STYLIZE FONTS", &bStyleFonts);
			// -> will crash if styles are not queued!

			guiManager.AddSpacing();

			if (!bStyleFonts) guiManager.AddLabelHuge("All widgets now using DEFAULT style", false, true);
			else guiManager.AddLabelHuge("Each widget now using CUSTOM styles", false, true);

			guiManager.AddSpacingSeparated();

			if (bStyleFonts) guiManager.pushStyleFont(0);
			{
				if (bStyleFonts) {
					guiManager.AddLabel("Font 0", false, true);
					guiManager.AddLabel(guiManager.getFontName(0), false, true);
				}

				guiManager.Add(bEnable, OFX_IM_TOGGLE);
				guiManager.Add(amount2);
				guiManager.AddLabel(txt, false, true);
			}
			if (bStyleFonts) guiManager.popStyleFont();

			guiManager.AddSpacingSeparated();

			//-

			if (bStyleFonts) guiManager.pushStyleFont(1);
			{
				if (bStyleFonts) {
					guiManager.AddLabel("Font 1", false, true);
					guiManager.AddLabel(guiManager.getFontName(1), false, true);
				}

				guiManager.Add(bEnable, OFX_IM_TOGGLE);
				guiManager.Add(amount2); 
				guiManager.AddLabel(txt, false, true);
			}
			if (bStyleFonts) guiManager.popStyleFont();

			guiManager.AddSpacingSeparated();

			//-

			if (bStyleFonts) guiManager.pushStyleFont(2);
			{
				if (bStyleFonts) {
					guiManager.AddLabel("Font 2", false, true);
					guiManager.AddLabel(guiManager.getFontName(2), false, true);
				}

				guiManager.Add(bEnable, OFX_IM_TOGGLE);
				guiManager.Add(amount2); 
				guiManager.AddLabel(txt, false, true);
			}
			if (bStyleFonts) guiManager.popStyleFont();

			guiManager.AddSpacingSeparated();

			//-

			// Take care not pushing a non existing index or it will crash!
			if (bStyleFonts) guiManager.pushStyleFont(3);
			{
				if (bStyleFonts) {
					guiManager.AddLabel("Font 3", false, true);
					guiManager.AddLabel(guiManager.getFontName(3), false, true);
				}

				guiManager.Add(bEnable, OFX_IM_TOGGLE);
				guiManager.Add(amount2);
				guiManager.AddLabel(txt, false, true);
			}
			if (bStyleFonts) guiManager.popStyleFont();

			guiManager.endWindow();
		}
	}
	ImGui::PopStyleVar();
}
