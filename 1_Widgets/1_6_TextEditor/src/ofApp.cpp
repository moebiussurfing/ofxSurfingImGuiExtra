#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetFrameRate(60);

	gui.setup();

	// style
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	ofxImGuiSurfing::setDefaultFont(gui, "assets/fonts/telegrama_render.otf", 16);

	textEditor.setup();
	textEditor.loadText(ofToDataPath("text1.txt", true));
}

//--------------------------------------------------------------
void ofApp::draw() {

	bMouseOverGui = ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);

	gui.Begin();
	{
		textEditor.draw();
	}
	gui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (bMouseOverGui) return; // skip when editing

	ofLogVerbose(__FUNCTION__) << key;
	switch (key)
	{
	case '1': {
		string path = ofToDataPath("text1.txt", true);
		textEditor.loadText(path);
		break;
	}
	case '2': {
		string path = ofToDataPath("text2.txt", true);
		textEditor.loadText(path);
		break;
	}
	case '3': {
		string str = "Garc�a Castell�n pone la X de Kitchen a Fern�ndez D�az\n y tapona la investigaci�n a Rajoy, \nla c�pula del PP y \nel CNI El juez \ndetermina que la decisi�n \nde espiar a B�rcenas con \nfondos reservados para evitar problemas judiciales \nal presidente y a Cospedal no \ntrascendi� del Ministerio del Interior.\nEl cierre de la instrucci�n llega \ncuando Anticorrupci�n apunta al CNI en \nel episodio del 'falso cura\n' e investiga una segunda Kitchen \nen la c�rcel";
		textEditor.setText(str);
		break;
	}
	}
}