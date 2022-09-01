#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetWindowPosition(-1920, 25);

	ui.setImGuiAutodraw(true);
	ui.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		if (bOpen0) {
			ImGui::Begin("Panels", &bOpen0, window_flags);
			{
				ofxImGuiSurfing::ToggleRoundedButton("Show 1", &bOpen1);
				ofxImGuiSurfing::ToggleRoundedButton("Show 2", &bOpen2);
				ImGui::Dummy(ImVec2(0, 10)); // spacing
			}
			ImGui::End();
		}

		//-

		if (bOpen1) drawWidgets();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	if (!initialized) {
		initialized = true;

		// basic-interaction-example
		example.Application_Initialize();
	}

	ImGui::Begin("thedmd/imgui-node-editor");
	{
		// basic-interaction-example
		example.Application_Frame();
	}
	ImGui::End();
}

//--------------------------------------------------------------
void ofApp::exit() {
	// basic-interaction-example
	example.Application_Finalize();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = ' ') {
	}
}