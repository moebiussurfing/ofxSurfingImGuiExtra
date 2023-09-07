#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() 
{
	ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw() 
{
	ui.Begin();
	{
		if (bGui) {
			//IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_LOCKED_RESIZE;
			ImVec2 size_min = ImVec2(240, -1);
			ImVec2 size_max = ImVec2(240, -1);
			ImGui::SetNextWindowSizeConstraints(size_min, size_max);
		}

		if (ui.BeginWindow(bGui))
		{
			gradient.draw();

			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) 
{
	if (key == 'g') {
		bGui = !bGui;
	}
}