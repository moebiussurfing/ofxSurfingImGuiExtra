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
	ui.Begin(); // global begin
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("Panels", &bOpen0, window_flags);
		{
			ofxImGuiSurfing::ToggleRoundedButton("Show 1", &bOpen1);
			//ofxImGuiSurfing::ToggleRoundedButton("Show 2", &bOpen2);
			//ImGui::Dummy(ImVec2(0, 10)); // spacing
		}
		ImGui::End();

		//-

		drawWidgets();
	}
	ui.End(); // global end
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	if (!initialized) {
		initialized = true;
	}

	ImGui::Begin("simple node editor");
	{

	}
	ImGui::End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = ' ') {
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//--------------------------------------------------------------
void ofApp::exit() {
}