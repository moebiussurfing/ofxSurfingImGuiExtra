#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "surfNotify.cpp"
#include "IconsFontAwesome5.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();
	void keyPressed(int key);

	ofParameter<bool> bGui{ "ofApp", true };

	ofxSurfingGui ui;

	ImFont* customFont = nullptr;
};
