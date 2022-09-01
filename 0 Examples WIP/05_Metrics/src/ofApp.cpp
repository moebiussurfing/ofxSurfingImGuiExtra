#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	metrics.setup();

	ui.setup();
}

//--------------------------------------------------------------
void ofApp::update()
{
	//metrics.update(); 
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		metrics.draw();
	}
	ui.End();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') {
	}

	// Theme
	if (key == '1') {
		ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	}
	if (key == '2') {
		ofxImGuiSurfing::ImGui_Xemu();
	}
	if (key == '3') {
		ofxImGuiSurfing::ImGui_ThemeYave();
	}


}