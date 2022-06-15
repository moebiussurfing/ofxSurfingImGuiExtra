#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "imgui_profiler.h"
//https://github.com/Raikiri/LegitProfiler

class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();
	void update();
	void keyPressed(int key);

	ofxSurfing_ImGui_Manager guiManager;
	
	const int NUM_PASSES = 5;
	ImGuiEx::ProfilersWindow profiler;
	bool profilerActive;
};
