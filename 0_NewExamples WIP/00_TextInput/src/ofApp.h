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

	ofParameter<bool> bGui_TextInput{ "Text", true };
	void drawImGui_TextInput();
	void doResetTextInput();

	ofParameterGroup params_Bubble{ "Bubble" };
	ofParameter<bool> bLabel{ "Label", true };
	ofParameter<int> szFont{ "Font Size", 0, 0, 3 };
	ofParameter<float> rounded{ "Rounded", 0, 0, 1 };
	ofParameter<ofColor> colorBubble{ "color Bubble", ofColor::red, ofColor(), ofColor() };
	ofParameter<float> padxBubble{ "padxBubble", 0.f, 0, 1 };
	ofParameter<float> padyBubble{ "padyBubble", 0.f, 0, 1 };
	ofParameter<float> padxText{ "padxText", 0.f, 0, 1 };
	ofParameter<float> padxTextR{ "padxTextR", 1.f, 0, 1 };
	ofParameter<float> padyText{ "padyText", 0.f, -1, 1 };
	ofParameter<int> typeInput{ "Type", 0, 0, 2 };
	ofParameter<string> typeInputName{ "TypeName" ,""};
	ofParameter<void> vResetBubble{ "Reset" };
	ofEventListener eResetBubble;
	ofEventListener eTypeInput;
	bool bResetBubble = 0;
	vector<string> typeInputNames{"InputText","InputTextWithHint","InputTextMultiline"};

	bool bColorize = false;//slider
	bool bBlink = 1;//text bubble
	bool bIntegrate = 1;
	bool bButtons = 1;
	bool bDebug = 0;

	ofParameterGroup g{ "ofApp" };
};
