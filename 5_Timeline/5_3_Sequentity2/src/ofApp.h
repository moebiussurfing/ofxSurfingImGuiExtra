#pragma once

#include "ofMain.h"

// WIP
// NOT WORKING

#include "ofxSurfingImGui.h"	
#include "Sequentity.h"
#include <entt/entity/registry.hpp>

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;
	void drawGui();
	ofParameter<bool> bGui{ "ofApp",true };

	entt::registry registry;

	// Events may carry application data and a type for you to identify it with
	struct MyEventData {
		float value{ 0.0f };
	};

	enum {
		MyEventType = 0
	};

	int time;
};
