#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "widgets.hh"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
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

    ofxSurfing_ImGui_Manager guiManager;


    static void InitializeStyle()
    {
        //g_font_mgr.Rebuild();

        ImGui::StyleColorsDark();
        ImVec4* c = ImGui::GetStyle().Colors;
        c[ImGuiCol_Text] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
        c[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
        c[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        c[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.98f);
        c[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        c[ImGuiCol_Border] = ImVec4(0.11f, 0.11f, 0.11f, 0.60f);
        c[ImGuiCol_BorderShadow] = ImVec4(0.16f, 0.16f, 0.16f, 0.00f);
        c[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        c[ImGuiCol_FrameBgHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
        c[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.71f, 0.25f, 1.00f);
        c[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.51f, 0.18f, 1.00f);
        c[ImGuiCol_TitleBgActive] = ImVec4(0.26f, 0.66f, 0.23f, 1.00f);
        c[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.16f, 0.16f, 0.75f);
        c[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 0.00f);
        c[ImGuiCol_ScrollbarBg] = ImVec4(0.16f, 0.16f, 0.16f, 0.00f);
        c[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
        c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
        c[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
        c[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.66f, 0.23f, 1.00f);
        c[ImGuiCol_SliderGrab] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
        c[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        c[ImGuiCol_Button] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
        c[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
        c[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.66f, 0.23f, 1.00f);
        c[ImGuiCol_Header] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
        c[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
        c[ImGuiCol_HeaderActive] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
        c[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 0.25f);
        c[ImGuiCol_SeparatorHovered] = ImVec4(0.13f, 0.87f, 0.16f, 0.78f);
        c[ImGuiCol_SeparatorActive] = ImVec4(0.25f, 0.75f, 0.10f, 1.00f);
        c[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.83f, 0.49f, 0.04f);
        c[ImGuiCol_ResizeGripHovered] = ImVec4(0.28f, 0.71f, 0.25f, 0.78f);
        c[ImGuiCol_ResizeGripActive] = ImVec4(0.28f, 0.71f, 0.25f, 1.00f);
        c[ImGuiCol_Tab] = ImVec4(0.26f, 0.67f, 0.23f, 0.95f);
        c[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
        c[ImGuiCol_TabActive] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
        c[ImGuiCol_TabUnfocused] = ImVec4(0.21f, 0.54f, 0.19f, 0.99f);
        c[ImGuiCol_TabUnfocusedActive] = ImVec4(0.24f, 0.60f, 0.21f, 1.00f);
        c[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
        c[ImGuiCol_PlotLinesHovered] = ImVec4(0.28f, 0.71f, 0.25f, 1.00f);
        c[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
        c[ImGuiCol_PlotHistogramHovered] = ImVec4(0.28f, 0.71f, 0.25f, 1.00f);
        c[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.66f, 0.23f, 1.00f);
        c[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        c[ImGuiCol_NavHighlight] = ImVec4(0.28f, 0.71f, 0.25f, 1.00f);
        c[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        c[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        c[ImGuiCol_ModalWindowDimBg] = ImVec4(0.16f, 0.16f, 0.16f, 0.73f);

        ImGuiStyle& s = ImGui::GetStyle();
        s.WindowRounding = 6.0;
        s.FrameRounding = 6.0;
        s.PopupRounding = 6.0;
        //g_base_style = s;
    }
};
