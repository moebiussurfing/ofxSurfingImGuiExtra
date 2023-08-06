
#pragma once
#include "ofMain.h"
#include "ofxSurfingImGui.h"


//#ifndef IMGUI_DEFINE_MATH_OPERATORS
//#define IMGUI_DEFINE_MATH_OPERATORS
//#endif
//#include "imgui_internal.h"


#include "MainFrame.h"

//#include <stdio.h>
//#include <string>
//#include <sstream>
//#include <fstream>

class ImLayoutManager
{
public:
	ImLayoutManager();
	~ImLayoutManager();

	void setup(ofxImGui::Gui& ui);
	void draw();

	int display_w, display_h;
	ImVec2 size;

	MainFrame mainFrame;

	bool bDoneSetup = 0;
};