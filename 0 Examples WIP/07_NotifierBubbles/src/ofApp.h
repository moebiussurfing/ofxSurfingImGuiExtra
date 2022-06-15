#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "notifications.hh"

#include "ofxNotify.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();
	void keyPressed(int key);


	ofParameter<bool> bGui{ "Show Gui", true };

	ofxSurfing_ImGui_Manager guiManager;

	NotificationManager notification_manager;
	ofxNotify notifier;


	string textAtribute[5] = {
		"Brilliant",
		"Curious",
		"Amazing",
		"Sublime",
		"Ironic",
	};

	string textObject[4] = {
		" disco inferno",
		" camp fire entanglement",
		" wedding promise",
		" man"
	};

	string textVerb[6] = {
		" bites",
		" strikes",
		" lost on",
		" snatches",
		" teases",
		" invites"
	};

	string textSubject[5] = {
		" pope",
		" government",
		" irate schoolmaster",
		" late enthusiast",
		" dog"
	};
};
