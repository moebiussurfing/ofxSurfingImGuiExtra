#pragma once

/*

Broken
Updated new comits.

*/

#include "ofMain.h"

#include "ofxImGui.h"	

#include "ofxSurfingImGui.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

#include <ImTools/LayoutManager/LayoutManager.h>
#include <ImTools/LayoutManager/SamplePane.h>
#include "TopPane.h"
#include "RightPane.h"
//#include "LeftPane.h"
//#include "BottomPane.h"
//#include "CentralPane.h"

#include <ImTools/ctools/ConfigAbstract.h>

#include <string>


//class ofApp : public ofBaseApp, conf::ConfigAbstract
class ofApp : public ofBaseApp 
{

public:
	void setup();
	void draw();
	void exit();

public:
	void Init();
	void Unit();

	void Display(ImVec2 vSize);


	//ImVec2 vSize = ImVec2(700,700);
	bool m_ShowImGui = false;				// show ImGui win
	bool m_ShowMetric = false;				// show metrics
	int _widgetId = 8953;


	// configuration
	std::string getXml(const std::string& vOffset, const std::string& vUserDatas = "");
	bool setFromXml(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent, const std::string& vUserDatas = "");

	//-

	ofxSurfingGui ui;

	//-

	// parameters
	ofParameterGroup params1;
	ofParameter<bool> bEnable;
	ofParameter<bool> bPrevious;
	ofParameter<bool> bMode1;
	ofParameter<bool> bMode2;
	ofParameter<bool> bMode3;
	ofParameter<bool> bMode4;
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

	//-

	bool binitiated = false;

};
