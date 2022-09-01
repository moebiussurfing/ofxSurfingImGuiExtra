#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "ofxMyUtilImGui.h"

/*

Testing ofxMyUtil

*/


class ofApp : public ofBaseApp{

public:
		void setup();
		void draw();
		void exit();
			
		ofxSurfingGui ui; 

		void drawWidgets();
		void drawMainWindow();

		bool bOpen0 = true;
		bool bOpen1 = true;
		bool bAutoResize = true;

		//--

		// ofParameters
		
		// groups
		ofParameterGroup params2;
		ofParameterGroup params1;
		ofParameterGroup params3;

		// params
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

		ofxMyUtil::Im::ImGuiLogWindow ImLog;
		ofxMyUtil::Im::ImGuiWindowFlagsSettings ImWinSettings;
		ofxMyUtil::Im::ImGuiWindowSetCondSettings ImCondSettings;
};
