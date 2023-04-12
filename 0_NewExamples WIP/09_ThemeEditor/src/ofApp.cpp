#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxSurfingHelpers::setMonitorsLayout(1);

	ui.setup();

	//--

	// We can activate one of the bundled Themes:
	// Must be called after setup() to overwrite the default loaded theme.
	//ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingBlue();

	//--

#if(TEST_CUSTOM_FONTS==1) 
	setupFonts();
#endif

	//--


	bEnable.set("Enable", false);
	amount.set("amount", 10, 0, 25);
}

//--------------------------------------------------------------
void ofApp::setupFonts()
{
#if(TEST_CUSTOM_FONTS==1)

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

#endif
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		// Main
		drawWindowMain();

		// Theme editor
		if (bOpenThemeSelector) drawThemeSelector();

#if(TEST_CUSTOM_FONTS==1) 
		// Stylized 
		if (bOpenWindowStylized) drawWindowStylized();
#endif

		// Surfing Theme editor
		e.draw();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawWindowMain()
{
	string s;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	if (ui.BeginWindow("Main Window", &bOpenWindowMain, window_flags))
	{
		ImVec2 sz1(ui.getWidgetsWidth(), ui.getWidgetsHeightUnit() * 1);
		ImVec2 sz2(ui.getWidgetsWidth(), ui.getWidgetsHeightUnit() * 2 - ImGui::GetStyle().ItemSpacing.x);

		ui.AddToggle("Theme Selector", bOpenThemeSelector, OFX_IM_TOGGLE);

		ui.Add(e.bGui, OFX_IM_TOGGLE);
		ui.Add(e.bGui_Demo, OFX_IM_TOGGLE);

		ui.AddSpacingSeparated();

		//--

#if(TEST_CUSTOM_FONTS==1) 
		ui.AddSpacingBigSeparated();

		if (ui.Add(fontIndex))
		{
			//ui.setDefaultFontIndex(fontIndex);
		}

		s = ofToString(fontIndex) + "/" + ofToString(fontIndex.getMax());
		ui.AddLabel(s.c_str());

		s = ofToString(ui.getFontName(fontIndex));
		ui.AddLabel(s.c_str());

		//if (ImGui::Button("Set Font")) {
		//	ui.setDefaultFontIndex(fontIndex);
		//}

		ui.AddSpacingBigSeparated();

		ui.AddToggle("STYLIZED WINDOW", bOpenWindowStylized);

		if (bOpenWindowStylized)
		{
			ui.AddSpacing();
			ui.AddToggle("STYLIZE FONTS", bStyleFonts);
			// -> will crash if styles are not queued!
		}
#endif
		//--

		// Example widgets
		e.drawDemoSurfingWidgets(ui);

		//--

		ui.AddSpacingSeparated();

		// a public bool variable to allow handle auto-resize. Applied here to all the windows.
		ui.Add(ui.bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);

		//--

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawThemeSelector()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	ImGui::Begin("Theme Selector", &bOpenThemeSelector, window_flags);
	{
		ofxImGuiSurfing::drawThemeSelector(NULL);
	}
	ImGui::End();
}

//--------------------------------------------------------------
void ofApp::drawWindowStylized()
{
#if(TEST_CUSTOM_FONTS==1) 

	// A window but using my ofxSurfingGui.h class helper
	// Uses my own simpler helpers: 
	// ofxSurfing_ImGui_Helpers.h
	// Notice that you can add an ofParameterGroup out of a ofxImGui window. 
	// (TODO: but this potentially make troubles yet [WIP] bc getUniqueNames engine!)

	//-

	// Minimal sizes
	float ww = 300;
	float hh = 600;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		if (ui.BeginWindow("STYLIZED WINDOW", &bOpenWindowStylized, window_flags))
		{
			ui.AddToggle("STYLIZE FONTS", bStyleFonts);
			// -> will crash if styles are not queued!

			ui.AddSpacing();

			if (!bStyleFonts) ui.AddLabelHuge("All widgets now using DEFAULT style");
			else ui.AddLabelHuge("Each widget now using CUSTOM styles");

			ui.AddSpacingSeparated();

			if (bStyleFonts) ui.pushStyleFont(0);
			{
				if (bStyleFonts) {
					ui.AddLabel("Font 0");
					ui.AddLabel(ui.getFontName(0));
				}

				ui.Add(bEnable, OFX_IM_TOGGLE);
				ui.Add(amount);
				ui.AddLabel(txt);
			}
			if (bStyleFonts) ui.popStyleFont();

			ui.AddSpacingSeparated();

			//-

			if (bStyleFonts) ui.pushStyleFont(1);
			{
				if (bStyleFonts) {
					ui.AddLabel("Font 1");
					ui.AddLabel(ui.getFontName(1));
				}

				ui.Add(bEnable, OFX_IM_TOGGLE);
				ui.Add(amount);
				ui.AddLabel(txt);
			}
			if (bStyleFonts) ui.popStyleFont();

			ui.AddSpacingSeparated();

			//-

			if (bStyleFonts) ui.pushStyleFont(2);
			{
				if (bStyleFonts) {
					ui.AddLabel("Font 2");
					ui.AddLabel(ui.getFontName(2));
				}

				ui.Add(bEnable, OFX_IM_TOGGLE);
				ui.Add(amount);
				ui.AddLabel(txt);
			}
			if (bStyleFonts) ui.popStyleFont();

			ui.AddSpacingSeparated();

			//-

			// Take care not pushing a non existing index or it will crash!
			if (bStyleFonts) ui.pushStyleFont(3);
			{
				if (bStyleFonts) {
					ui.AddLabel("Font 3");
					ui.AddLabel(ui.getFontName(3));
				}

				ui.Add(bEnable, OFX_IM_TOGGLE);
				ui.Add(amount);
				ui.AddLabel(txt);
			}
			if (bStyleFonts) ui.popStyleFont();

			ui.EndWindow();
		}
	}
	ImGui::PopStyleVar();

#endif
}
