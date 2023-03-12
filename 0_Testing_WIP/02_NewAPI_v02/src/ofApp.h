#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" 
#include "DefaultTheme.h"

class ofApp : public ofBaseApp 
{
public:

	void setup();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;

	ofParameter<bool> b1{ "b1", false};
	ofParameter<bool> b2{ "b2", true};
	ofParameter<bool> b3{ "b3", true};
	ofParameter<bool> b4{ "b4", false};

	ofxImGui::DefaultTheme theme;

	void drawNewAPI();

	int iTheme = 0;
};
