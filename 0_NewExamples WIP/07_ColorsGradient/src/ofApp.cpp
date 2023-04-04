#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);

	setupImGui();

	indexPreset.makeReferenceTo(surfingGradient.indexPreset);
}

//--------------------------------------------------------------
void ofApp::setupImGui()
{
	ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(surfingGradient.color);

	if (bGui) drawImGui();
}

//--------------------------------------------------------------
void ofApp::drawImGui() {

	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			drawImGuiWidgets();
			ui.EndWindow();
		}

		//--

		// Colors Gradient
		surfingGradient.drawImGui();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawImGuiWidgets()
{
	string s;

	// Calculate sizes related to window shape/size widgets.
	// Required when creating a raw ImGui tree manually.
	// Not required when using the API helpers/tools. ( ui.Add(param)); )
	float _w = ofxImGuiSurfing::getWidgetsWidth(2); // 2 widgets half width
	float _h = ofxImGuiSurfing::getWidgetsHeight(); // Double height

	//--

	s = "Gradients Manager";
	ui.AddLabelBig(s);

	ofxImGuiSurfing::Spacing();

	// 1 Two buttons on same line
	if (ImGui::Button("<", ImVec2(_w, _h)))
	{
		indexPreset--;
		indexPreset = ofClamp(indexPreset, indexPreset.getMin(), indexPreset.getMax()); // clamp parameter
	}
	s = "Click to Previous";
	ofxImGuiSurfing::AddTooltip(s, ui.bHelp);
	ImGui::SameLine();
	if (ImGui::Button(">", ImVec2(_w, _h)))
	{
		indexPreset++;
		indexPreset = ofClamp(indexPreset, indexPreset.getMin(), indexPreset.getMax()); // clamp parameter
	}
	s = "Click to Next";
	ofxImGuiSurfing::AddTooltip(s, ui.bHelp);

	// 2 Slider: the master int ofParam!
	//ofxImGuiSurfing::AddParameter(indexPreset);
	ui.Add(indexPreset, OFX_IM_HSLIDER_MINI_NO_LABELS);

	s = "Move the slider index to pick a preset.";
	ofxImGuiSurfing::AddTooltip(s, ui.bHelp);

	// 3 Matrix button clicker
	// Responsive layout with 3 widgets per row
	ofxImGuiSurfing::AddMatrixClicker(indexPreset, true, 3);

	s = "Move the index slider, Click browse buttons or click the Matrix numbers";
	ofxImGuiSurfing::AddTooltipHelp(s);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bGui = !bGui;
}