#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "SurfingImGradientHDR.h"

class ofApp : public ofBaseApp{
    
public:

    void setup();
    void draw();
    void keyPressed(int key);

    ofParameter<bool> bGui{"ImGradientHDR", true};

    ofxSurfing_ImGui_Manager guiManager;

    SurfingImGradientHDR gradient;
};
