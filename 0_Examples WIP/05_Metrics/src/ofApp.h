#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "surfingMetrics.h"
//https://github.com/GameTechDev/MetricsGui

/*

	TODO:
	make common measurements:
	hardcoded framerate
	add custom values

*/

class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();
	void update();
	void keyPressed(int key);

	ofxSurfingGui ui;

	surfingMetrics metrics;
};
