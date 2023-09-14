#pragma once
#include "ofMain.h"

#include "mainNeverlose.cpp"

/*

    WIP Example
    
    migration from 
    neverlose-last cheat menu from 
    @evrope
    https://www.youtube.com/watch?v=wQjYGid-Uqo

    This code requires too much ImGui core modifications.
    So, maybe will be only useful to learn:
    - insert icon fonts.
    - split layout panels with left and top tabs/panels.
    - use some widgets:
        the color picker, slider or toggles.
    - insert images

    - Color picker requires AddRectFilledMultiColorRounded 
        defined into imgui.h:
        //TODO
        IMGUI_API void  AddRectFilledMultiColorRounded(const ImVec2& p_min, const ImVec2& p_max, ImU32 bg_color, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left, float rounding, ImDrawFlags rounding_corners = ImDrawFlags_RoundCornersAll);
        as is declared into \neverlose\imgui_widgets_Neverlose.cpp

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
