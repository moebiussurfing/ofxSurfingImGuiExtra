#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ui.setup();

	static bool bDoneSetup = 1;
	if (!bDoneSetup)
	{
		bDoneSetup = 1;
		bar.setup();
	}
	
	ui.startup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		bar.draw();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bGui = !bGui;
}