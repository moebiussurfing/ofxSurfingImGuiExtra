#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
    
public:

    void setup();
    void draw();
    void keyPressed(int key);
    
	void setup_ImGui();

	ofxSurfingGui gui;
};
