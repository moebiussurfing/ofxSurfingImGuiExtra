#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() 
{
	ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw() 
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			gradient.draw();

			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) 
{
	if (key == 'g') {
		bGui = !bGui;
	}
}