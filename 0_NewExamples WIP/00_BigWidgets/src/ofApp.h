/*

	TODO

	add big knobs

	make classes for these big widgets

	use imgui_stdlib.h ofParams string
	font sizes
	responsive using ofRectangle
	substract window header to correlate hide/show header
	add anim show/hide

*/


#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "imgui_stdlib.h"
#include "BigTextInput.h"

#define RATIO_WIDGETS_FONTS 0.25f

class ofApp : public ofBaseApp {
public:
	void setup();
	void setupImGui();
	void exit();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;
	void drawImGui();
	ofParameter<bool> bGui{ "ofApp", true };

	ofParameter<bool> bGui_Headers{ "Headers", true };
	ofParameter<bool> bGui_Bg{ "Bg", true };
	ofParameter<bool> bGui_ResizePin{ "Resizer", true };
	ofParameter<bool> bGui_LockMove{ "Lock", false };

	void drawImGui_Slider();
	void doResetSlider();
	ofParameter<bool> bGui_Slider{ "Slider", true };
	ofParameter<float> value{ "Value", 0, 0, 1.f };
	ofColor cRange = ofColor::green;
	ofColor cRangeRaw = ofColor::red;
	bool bResetSlider = 0;
	bool bColorize = false;//slider

	ofParameter<bool> bGui_Toggle{ "Toggle", true };
	ofParameter<bool> bToggle{ "Toggle", false };
	void drawImGui_Toggle();

	ofParameter<bool> bGui_Button{ "Button", true };
	ofParameter<void> vButton{ "Button" };
	void drawImGui_Button();

	BigTextInput bigTextInput;

	ofParameterGroup g{ "ofApp" };
};
