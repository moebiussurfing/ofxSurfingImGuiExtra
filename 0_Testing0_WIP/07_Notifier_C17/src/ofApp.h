#pragma once

// For more advanced font loading examples, please refer to
// https://github.com/ocornut/imgui/blob/master/docs/FONTS.md

// Requires c++17. supported on oF nightly builds !!

#include "ofMain.h"

#include "ofxImGui.h"

#include "surfNotify.h"

class ofApp : public ofBaseApp 
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	ofxImGui::Gui gui;

	surfNotify notify;

	ImFont* f3 = nullptr;
};
