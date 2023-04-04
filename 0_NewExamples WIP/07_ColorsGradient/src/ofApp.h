#pragma once
#include "ofMain.h"

/*

	This is an example about how to build a more "complex widget".
	Uses small raw ImGui widgets from other 3rd party/users community.

	TODO: make workflow to create colors marks, remove etc

*/


#include "ofxSurfingImGui.h"
#include "exampleSurfingGradient.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();
	void keyPressed(int key);

	ofParameter<int> indexPreset;
	ofParameter<bool> bGui{ "07_ColorsGradient", true };

	ofxSurfingGui ui;
	void setupImGui();
	void drawImGui();
	void drawImGuiWidgets();

	exampleSurfingGradient surfingGradient;
};
