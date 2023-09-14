#pragma once
#include "ofMain.h"

#include "mainNeverlose.cpp"

/*

    WIP Example
    
    migrated from 
    neverlose-last cheat menu from @evrope
    https://www.youtube.com/watch?v=wQjYGid-Uqo

    Will be only useful to learn:
    - insert icon fonts.
    - split layout panels with left and top tabs/panels.
    - use some custom widgets: the color picker, slider or toggles.
    - insert images.

    - fix required: text input, combos
    - fix crash on exit

*/

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void draw();
    void exit();
    void keyPressed(int key);

    // parameters
    ofParameterGroup params;
    ofParameter<bool> bEnable1;
    ofParameter<bool> bEnable2;
    ofParameter<bool> bEnable3;
    ofParameter<bool> bPrevious;
    ofParameter<bool> bNext;
    ofParameter<float> lineWidth;
    ofParameter<float> separation;
    ofParameter<float> speed;
    ofParameter<int> shapeType;
    ofParameter<int> amount;
    ofParameter<int> size;
    ofParameterGroup params2;
    ofParameter<int> shapeType2;
    ofParameter<int> amount2;
    ofParameter<int> size2;
    ofParameterGroup params3;
    ofParameter<float> lineWidth3;
    ofParameter<float> separation3;
    ofParameter<float> speed3;
    ofParameter<int> shapeType3;

    ofParameter<bool> bGui{"Show Gui", true};

    ofxSurfingGui ui;

    void setupFonts();
    ImFont* customFont0 = nullptr;
    ImFont* customFont1 = nullptr;
    ImFont* customFont2 = nullptr;

};
