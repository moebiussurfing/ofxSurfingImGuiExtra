#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "ImGuizmoMain.cpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    void keyPressed(int key);

    ofParameter<bool> bGui{"Show Gui", true};

    ofxSurfingGui ui;

    //--

    void setupImGuizmo();
    void drawImGuizmo();


    int lastUsing = 0;

    float cameraView[16] =
    { 1.f, 0.f, 0.f, 0.f,
      0.f, 1.f, 0.f, 0.f,
      0.f, 0.f, 1.f, 0.f,
      0.f, 0.f, 0.f, 1.f };

    float cameraProjection[16];

    // build a procedural texture. 
    // Copy/pasted and adapted from https://rosettacode.org/wiki/Plasma_effect#Graphics_version
    unsigned int procTexture;

    uint32_t* tempBitmap = new uint32_t[256 * 256];
    int index = 0;

    // Camera projection
    bool isPerspective = true;
    float fov = 27.f;
    float viewWidth = 10.f; // for orthographic
    float camYAngle = 165.f / 180.f * 3.14159f;
    float camXAngle = 32.f / 180.f * 3.14159f;
    
    MySequence mySequence;

    bool firstFrame = true;
};
