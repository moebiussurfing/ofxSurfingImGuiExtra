#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() 
{
	guiManager.setup();
}

//--------------------------------------------------------------
void ofApp::draw() 
{
	guiManager.begin();
	{
		if (guiManager.beginWindow(bGui))
		{
			gradient.draw();

			guiManager.endWindow();
		}
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) 
{
	if (key == 'g') {
		bGui = !bGui;
	}
}