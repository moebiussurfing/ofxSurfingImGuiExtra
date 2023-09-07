
#pragma once
#include "ofMain.h"

#include "SurfingDockingManager.h"

#include "ofxSurfingImGui.h"

// Required for the advanced feature
#include <functional>
using callback_t = std::function<void()>;

//--

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);
	void exit();
	
	ofxSurfingGui ui;
	
	SurfingDockingManager manager;
	
	// Some parameters
	ofParameter<bool> bGui{ "ofApp", true };
	ofParameter<bool> bEnable{ "Enable", true };
	ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
	ofParameter<string> name{ "Name", ""};
	ofParameterGroup params{ "MyParamGroup", bEnable, speed, name };
};
