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
	//ImGuiConfigFlags customFlags_ = ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable; 
	
	bool restoreGuiState = true;
	bool showImGuiMouseCursor = false;
	ui.setup(theme, autoDraw, customFlags, restoreGuiState, showImGuiMouseCursor);

	// Uncomment below to perform docking with SHIFT key
// Gives a better user experience, matter of opinion.
//ImGui::GetIO().ConfigDockingWithShift=true;

// Uncomment below to "force" all imgui windows to be standalone
//ImGui::GetIO().ConfigViewportsNoAutoMerge=true;

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
			manager.setup(ui.getGui());
#else
			manager.setup(ui);
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
		manager.draw();
	}
	ui.End();
#else
	ui.begin();
	{
		manager.draw();
	}
	ui.end();
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bGui = !bGui;
}