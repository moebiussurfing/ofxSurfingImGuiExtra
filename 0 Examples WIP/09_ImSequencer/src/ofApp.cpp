#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowPosition(-1920, 25);

	ui.setup();

	sequencer.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (bPlay) {
		sequencer.nextFrame();
		//sequencer.setFrame(int frame);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	float value = ofxSurfingHelpers::getFadeBlink();
	//float value = sequencer;

	ofClear(value * 255.f);


	ui.Begin(); // global begin
	{
		drawWidgets();
		drawTimeline();
	}
	ui.End(); // global end
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("Panels", &bOpen0, window_flags);
		{

			// round toggles widgets
			ofxImGuiSurfing::ToggleRoundedButton("Show Timeline", &bOpen1);
			//ofxImGuiSurfing::ToggleRoundedButton("Show Window 2", &bOpen2);

			ImGui::Dummy(ImVec2(0, 5)); // spacing

			ofxImGuiSurfing::ToggleRoundedButton("PLAY", &bPlay);

			ofxImGuiSurfing::AddToggleRoundedButton(ui.bAutoResize);// a public bool variable to allow handle auto-resize. Applied here to all the windows.
		}
		ImGui::End();
	}
}

//--------------------------------------------------------------
void ofApp::drawTimeline()
{
	if (!bOpen1)return;

	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		//if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("Timeline", &bOpen1, window_flags);
		{
			sequencer.draw();

			//ofxImGuiSurfing::AddToggleRoundedButton(ui.bAutoResize);// a public bool variable to allow handle auto-resize. Applied here to all the windows.
		}
		ImGui::End();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = ' ') { bPlay = !bPlay; }
}