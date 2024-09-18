#pragma once

// based on: https://github.com/aiekick/ImGuiFileDialog
// https://github.com/AirGuanZ/imgui-filebrowser -> another alternative

/*
	TODO:
	+ add folder picker
	+ a better callback
	+ add other browser classes
*/

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "ofxSurfing_ImGui_WidgetsFileBrowser.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();

	ofxSurfingGui gui;

	string strPath = "";
	string strPathName = "";
};
