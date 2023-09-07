#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofLogNotice(__FUNCTION__);

	//--

	ui.setup(ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING_RAW);
	ui.startup();

	//--

	manager.setup(ui.getGui());
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 1) + " FPS");

	ofClear(ofColor::grey);

	//--

	if (!bGui) return;

	ui.begin();
	{
		manager.draw();
	}
	ui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	ofLogNotice(__FUNCTION__) << char(key);

	if (key == 'g' || key == 'G') bGui = !bGui;
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ofLogNotice(__FUNCTION__);

	manager.exit();
}