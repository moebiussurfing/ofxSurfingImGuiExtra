/*

	TODO

	use imgui_stdlib.h
		ofParams string
	font sizes
	one line text or multi line
	responsive using ofRectangle
	substract window header
		to correlate hide/show header
	add anim show/hide

*/


#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "BigTextInput.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void exit();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;
	void drawImGui();
	ofParameter<bool> bGui{ "ofApp", true };

	BigTextInput bigTextInput;
};
