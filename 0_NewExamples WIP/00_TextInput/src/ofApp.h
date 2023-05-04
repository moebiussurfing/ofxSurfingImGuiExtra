#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();
	void keyPressed(int key);

	ofParameter<string> textA{ "TextA","" };
	ofParameter<string> textB{ "TextB","" };
	ofParameter<string> textC{ "TextC","" };

	ofParameter<bool> bGui{ "Show Gui", true };

	ofxSurfingGui ui;

	void draw_ImGui_ManualSlider();
	ofParameter<bool> bGui_ManualSlider{ "Slider", true };
	ofParameter<bool> bGui_ManualSliderHeader{ "header", true };
	ofParameter<float> controlManual{ "CONTROL", 0, 0, 1.f };
	ofColor cRange = ofColor::green;
	ofColor cRangeRaw = ofColor::red;

	void doResetManualSlider();
};
