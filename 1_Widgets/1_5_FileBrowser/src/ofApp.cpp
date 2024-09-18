#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);

	gui.setup();
}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.Begin();
	{
		if (ofxImGuiSurfing::drawGui_FileDialog()) {
			ofLogWarning() << "filePath     : " << ofxImGuiSurfing::filePath;
			ofLogWarning() << "filePathName : " << ofxImGuiSurfing::filePathName;
			strPath = filePath;
			strPathName = filePathName;
		}
	}
	gui.End();

	// display last picked file
	if (strPath != "" || strPathName != "") {
		ofDrawBitmapStringHighlight(strPath, 20, 40);
		ofDrawBitmapStringHighlight(strPathName, 20, 420);
	}
}