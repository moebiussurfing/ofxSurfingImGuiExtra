/*

	TODO

	use imgui_stdlib.h
	add anim show/hide
	font sizes
	one line text or multi line
	responsive using ofRectangle

*/

#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "imgui_stdlib.h"

#define RATIO_WIDGETS_FONTS 0.25f

class ofApp : public ofBaseApp {
public:
	void setup();
	void exit();
	void draw();
	void keyPressed(int key);

	void drawImGui();
	
	ofParameter<string> textA{ "TextA","" };
	ofParameter<string> textB{ "TextB","" };
	ofParameter<string> textC{ "TextC","" };

	ofParameter<bool> bGui{ "Window 1", true };

	ofxSurfingGui ui;

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

	ofParameter<bool> bGui_Toggle{ "Toggle", true };
	ofParameter<bool> bToggle{ "Toggle", false };
	void drawImGui_Toggle();

	ofParameter<bool> bGui_Button{ "Button", true };
	ofParameter<void> vButton{ "Button" };
	void drawImGui_Button();
	
	ofParameter<bool> bGui_Text{ "Text", true };
	ofParameter<bool> bGui_Label{ "Label", true };
	void drawImGui_Text();
	ofParameter<int> szFont{ "Font Size", 0, 0, 3 };

	ofParameterGroup g{"ofApp"};
};
