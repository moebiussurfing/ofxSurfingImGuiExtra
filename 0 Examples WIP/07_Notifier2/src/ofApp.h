#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();
	void keyPressed(int key);

	ofParameter<bool> bGui{ "Show Gui", true };

	ofxSurfingGui ui;
};
