#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "imgui_neo_sequencer.h"
#include "imgui_neo_internal.h"

class ofApp : public ofBaseApp {

public:
	ofxSurfingGui ui;
	ofParameter<bool> bGui{ "ofApp", true };

	void setup();
	void update();
	void draw();
	void drawGui();

	void drawTimeline();
	int32_t currentFrame = 0;
	int32_t startFrame = -10;
	int32_t endFrame = 64;
	bool transformOpen = false;
	std::vector<ImGui::FrameIndexType> keys = { 0, 10, 24 };
	bool doDelete = false;

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

};
