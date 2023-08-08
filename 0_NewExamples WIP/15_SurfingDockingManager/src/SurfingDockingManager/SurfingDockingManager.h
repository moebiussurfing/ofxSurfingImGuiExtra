// This class is a port from https://github.com/aiekick/ImTools/tree/main/LayoutManager
// coded by @aiekick. Thanks! 

#pragma once

#include "ofxSurfingImGui.h"
#include "MainFrame.h"

// Required for the advanced feature
#include <functional>
using callback_t = std::function<void()>;

class SurfingDockingManager
{
public:
	SurfingDockingManager();
	~SurfingDockingManager();

	void setup(ofxImGui::Gui& ui);
	void init();
	void draw();
	void exit();

	ImVec2 size;

	MainFrame mainFrame;

	bool bDoneSetup = 0;
	bool bDoneInit = 0;

	//--

	// Pointer to store a function
	callback_t functionDraw = nullptr;
	//std::function<void()> functionDraw = nullptr;

	// Set external widgets to be inserted!
	void setDrawWidgetsFunction(callback_t f = nullptr) {
		functionDraw = f;
	};
};