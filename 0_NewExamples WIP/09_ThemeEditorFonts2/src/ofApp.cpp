#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxSurfingHelpers::setMonitorsLayout(1, true, true);

	g.add(sizeFont);
	g.add(windowScale);
	g.add(scaleGlobal);
	g.add(vReload);
	g.add(vBuild);
	ofAddListener(g.parameterChangedE(), this, &ofApp::Changed);

	ui.setup();

	//ui.clearFonts();

#ifdef CUSTOM_FONTS
	// Load all the fonts of a folder
	string p = "/assets/fonts2/";
	float size = 12;
	ui.pushFontsFromFolder(p, size);

	// Load another single font
	p = "/assets/fonts2/Inter-Black.ttf";
	size = 17;
	string label = "Inter-Black_" + ofToString(size);
	ui.pushFont(p, size, label);
#endif

	//--

	e.setPathGlobal(ui.getPath());
	e.setUiPtr(&ui);
	e.setup();
	e.windowScale.makeReferenceTo(windowScale);

	ofxSurfingHelpers::load(g);
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ofxSurfingHelpers::save(g);
	ofRemoveListener(g.parameterChangedE(), this, &ofApp::Changed);
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (bBuildFonts) {
		bBuildFonts = 0;

		ui.BuildFonts("/assets/fonts2/", "Inter-Black.ttf", sizeFont);
	}

	if (bReload) { // Load another single font
		bReload = 0;

		string p = "/assets/fonts2/Inter-Black.ttf";
		float size = sizeFont;
		string label = "Inter-Black_" + ofToString(size);
		ui.pushFont(p, size, label);
	}
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	// The Editor Windows

#ifdef CUSTOM_FONTS
	// Apply font styles
	ui.PushFontByIndex();



	e.draw();

	ui.PopFontByIndex();
#else 
	e.draw();

#endif
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		ImGui::SetWindowFontScale(1.f);

		IMGUI_SUGAR__WINDOWS_CONSTRAINTS_MEDIUM;

		if (ui.BeginWindow("ofApp"))
		{
			if (ImGui::Button("Reset")) {
				scaleGlobal = 1;
				windowScale = 1;
			}

			// Set the global font scale to 1.5x
			ImGui::GetIO().FontGlobalScale = scaleGlobal; 

			string s;

			ui.Add(e.bGui, OFX_IM_TOGGLE_ROUNDED_BIG);
			//s = "Note that these widgets are not affected by the selected index font! ";
			//s += "\nui.AddLabel() methods will use the default fonts too.";
			//ui.AddLabel(s);
			ui.AddSpacingBigSeparated();

			ui.Add(g);
			ui.AddSpacingBigSeparated();
			s = "Font: " + ofToString(ui.getFontIndex()) + "/" + ofToString(ui.getAmountFonts() - 1);
			ui.AddLabel(s);
			ui.AddSpacing();
			ui.AddLabel(ui.getFontIndexName());

			ui.DrawWidgetsFonts();
			ui.AddSpacingBig();

			ui.PushFontByIndex();
			{
				// Select day/night theme

				// A. A simple toggle
				//ui.DrawWidgetsTheme();

				// B. A custom combo
				ui.AddLabel("THEME ALT");
				ui.AddThemeToggle();
				ui.AddSpacingBig();

			}
			ui.PopFontByIndex();

			ui.EndWindow();
		}

		//--

		drawImGui();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	ofLogNotice("ofApp") << "keyPressed: " << (char)key;

	if (0) {}

	else if (key == OF_KEY_LEFT)
	{
		int i = ui.getFontIndex();
		if (i > 0) i--;
		ui.setFontIndex(i);
	}

	else if (key == OF_KEY_RIGHT)
	{
		int i = ui.getFontIndex();
		if (i < ui.getAmountFonts() - 1) i++;
		ui.setFontIndex(i);
	}
}

//--------------------------------------------------------------
void ofApp::Changed(ofAbstractParameter& e)
{
	std::string n = e.getName();

	ofLogNotice("ofApp") << "Changed: " << n << ": " << e;

	//--

	if (0) {}

	//--

	else if (n == sizeFont.getName())
	{
		return;
	}
	else if (n == windowScale.getName())
	{
		return;
	}
	else if (n == scaleGlobal.getName())
	{
		return;
	}
	else if (n == vBuild.getName())
	{
		bBuildFonts = 1;
		return;
	}
	else if (n == vReload.getName())
	{
		bReload = 1;
		return;
	}
}