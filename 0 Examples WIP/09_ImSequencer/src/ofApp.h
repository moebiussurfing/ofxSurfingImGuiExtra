#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"	
#include "Surfing_ImSequencer.h"	

// drag ImGuizmo from ofxSurfingImGuiExtra/_libs/ folder to the solution project. e.g. into example/src/

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

		ofxSurfingGui ui;
		void drawWidgets();
		void drawTimeline();

		Surfing_ImSequencer sequencer;

		bool bOpen0 = true;
		bool bOpen1 = true;
		bool bOpen2 = false;

		bool bPlay = false;
};
