
#pragma once

// Taken from: https://github.com/d3cod3/ofxVisualProgramming
// https://github.com/d3cod3/ofxVisualProgramming/blob/master/src/objects/data/FileToData.h
// https://github.com/d3cod3/ofxVisualProgramming/blob/master/src/objects/data/FileToData.cpp

/*
	TODO:
	WIP
	not working..
*/


#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "ImGuiFileBrowser.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui gui;

	ofxImGuiSurfing::ImGuiFileBrowser fileBrowser;

	string strPath = "";
	string strFileName = "";
	
	ofxImGuiSurfing::ImGuiFileBrowser::DialogMode mode;

	bool show = false;
};
