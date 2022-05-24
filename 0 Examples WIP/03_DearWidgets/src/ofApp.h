#pragma once

#include "ofMain.h"

//-

#include "ofxSurfingImGui.h" // requires  https://github.com/Daandelange/ofxImGui or https://github.com/Daandelange/ofxImGui/tree/ofParameters-Helpers-Test
#include "dear_widgets.h" // -> to use Dearwidgets

//#include "ofxSurfingImGui.h"						// -> This header includes ALL the above classes and some others. 
// You can simplify the workflow just adding only this header if you are planning to use many of the classes of this add-on.

//-

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    
	void setup_ImGui();
    ofxSurfing_ImGui_Manager guiManager;

    void draw_DearWidgets();
    void draw_DearWidgetsColors();
    void draw_MoreWidgets();

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
};
