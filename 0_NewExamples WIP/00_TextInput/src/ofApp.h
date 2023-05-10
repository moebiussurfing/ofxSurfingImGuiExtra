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
#include "imgui_stdlib.h"

#define RATIO_WIDGETS_FONTS 0.25f

class ofApp : public ofBaseApp {
public:
	void setup();
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

	ofParameter<bool> bGui_Toggle{ "Toggle", true };
	ofParameter<bool> bToggle{ "Toggle", false };
	void drawImGui_Toggle();

	ofParameter<bool> bGui_Button{ "Button", true };
	ofParameter<void> vButton{ "Button" };
	void drawImGui_Button();

	ofParameter<string> textA{ "TextA","" };
	ofParameter<string> textB{ "TextB","" };
	ofParameter<string> textC{ "TextC","" };

	ofParameter<bool> bGui_Text{ "Text", true };
	void drawImGui_Text();

	ofParameterGroup params_Bubble{ "Bubble" };
	ofParameter<bool> bLabel{ "Label", true };
	ofParameter<int> szFont{ "Font Size", 0, 0, 3 };
	ofParameter<float>  rounding{ "Round", 0, 0, 1 };
	ofParameter<ofColor> colorBubble{ "color Bubble", ofColor::red, ofColor(), ofColor() };
	ofParameter<float>  padx{ "padx", 50, 0, 100 };
	ofParameter<float>  pady{ "pady", 50, 0, 100 };
	ofParameter<float>  spacingx{ "spacingx", 50, 0, 100 };
	ofParameter<float>  spacingy{ "spacingy", 50, 0, 100 };
	ofParameter<float>  scale{ "scale", 0, 0, 1 };

	ofParameterGroup g{ "ofApp" };
};
