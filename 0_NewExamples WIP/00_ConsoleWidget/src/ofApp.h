
/*

	WIP

*/

#pragma once
#include "ofMain.h"
#include "ofxSurfingImGui.h"

#include "surfingConsole.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;
	ofParameter<bool> bGui{ "Show", true };

	customType t;

	myCustomConsole c = { 1 };

	void addToLog(string s);
};
