#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class myClassA
{
public:

	myClassA();
	~myClassA();

	void setup();
	void drawImGui();
	void drawImGuiWindow();
	void drawImGuiWidgets();

	ofParameterGroup params2;
	ofParameter<int> shapeType2;
	ofParameter<int> amount2;
	ofParameter<int> size2;

	ofParameter<bool> bGui{ "myClassA", true };

	//--

	//ofxSurfingGui ui;
	
	//std::unique_ptr<ofxSurfingGui> ui;
	//void setUiPtr(std::unique_ptr<ofxSurfingGui> _ui);

	ofxSurfingGui* ui = nullptr;
	void setUiPtr(ofxSurfingGui* _ui);
};
