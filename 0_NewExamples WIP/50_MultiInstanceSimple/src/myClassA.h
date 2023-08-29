#pragma once
#include "ofMain.h"


#define SURFING_USE_INSTANCE2
//#define SURFING_USE_REFERENCED
//#define SURFING_USE_REFERENCED2


//#define OFXIMGUI_DEBUG
#include "ofxSurfingImGui.h"

class myClassA
{
public:
	myClassA();
	~myClassA();

	void setup();

	ofParameterGroup parameters;
	ofParameter<int> shapeType2;
	ofParameter<int> amount2;
	ofParameter<int> size2;

	ofParameter<bool> bGui{ "myClassA", true };

	void drawImGui();

#ifdef SURFING_USE_REFERENCED
	void drawImGuiWindow();
	void drawImGuiWidgets();
#endif

	//--

#ifdef SURFING_USE_REFERENCED
	ofxSurfingGui* ui = nullptr;
	void setUiPtr(ofxSurfingGui* _ui);
#endif

//#ifdef SURFING_USE_REFERENCED2
	//std::unique_ptr<ofxSurfingGui> ui;
	//void setUiPtr(std::unique_ptr<ofxSurfingGui> _ui);
//#endif

#ifdef SURFING_USE_INSTANCE2
	ofxSurfingGui ui_;
#endif
};
