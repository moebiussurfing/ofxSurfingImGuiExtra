#pragma once

/*

	//TODO:
	broken. should be fix.
	these are more alternative to main notifier engine:
	surfingNotifier.h
	they're different/ one is OF native based.
	and with some alpha fading.

*/

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "notifications.hh"

#include "surfingNotify.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();
	void keyPressed(int key);


	ofParameter<bool> bGui{ "Show Gui", true };

	ofxSurfingGui ui;

	NotificationManager notification_manager;
	surfingNotify notifier;


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
