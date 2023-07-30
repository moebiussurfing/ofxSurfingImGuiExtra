#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
#ifdef SURF_IM
	ui.setup();
	ui.startup();

	init();
#else
	// The call to setup() is required BEFORE adding fonts.
	bool autoDraw = true;
	ofxImGui::BaseTheme* theme = nullptr;
	ImGuiConfigFlags customFlags = ImGuiConfigFlags_DockingEnable;
	bool restoreGuiState = false;
	bool showImGuiMouseCursor = false;
	ui.setup(theme, autoDraw, customFlags, restoreGuiState, showImGuiMouseCursor);

	init();
#endif

}

//--------------------------------------------------------------
void ofApp::init()
{
	if (ofGetFrameNum() == 0)
	{
		static bool bDoneSetup = 0;
		if (!bDoneSetup)
		{
			bDoneSetup = 1;

#ifdef SURF_IM
			bar.setup(ui.getGui());
#else
			bar.setup(ui);
#endif
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 1));

	ofClear(ofColor::grey);

#ifdef SURF_IM
	ui.Begin();
	{
		bar.draw();
	}
	ui.End();
#else
	ui.begin();
	{
		bar.draw();
	}
	ui.end();
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bGui = !bGui;
}