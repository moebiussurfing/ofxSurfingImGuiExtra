#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" 

// new toggle by @cmdwtf from https://github.com/cmdwtf/imgui_toggle
#include "imgui_toggle.h" 

class ofApp : public ofBaseApp 
{
public:

	void setup();
	void draw();

	ofxSurfingGui ui;

	ofParameter<bool> b1{ "b1", false};
	ofParameter<bool> b2{ "b2", false};
	ofParameter<bool> b3{ "b3", false};
	ofParameter<bool> b4{ "b4", false};
};
