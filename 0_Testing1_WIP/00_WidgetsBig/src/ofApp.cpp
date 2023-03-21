#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		/* Put windows here */

		if (ui.BeginWindow(bGui))
		{
			ui.AddAutoResizeToggle();

			/* Put widgets here */

			ui.Add(bEnable, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			ui.Add(speed, OFX_IM_VSLIDER);
			ui.Add(speed, OFX_IM_PROGRESS_BAR_NO_TEXT);

			float w = ImGui::GetFrameHeight();

			ImVec2 sz{ 2 * w, 150 };

			static float value;
			value = ofMap(glm::cos(ofGetElapsedTimef()), -1, 1, 0, 1, true);
			if (bEnable)speed = value;

			ofxImGuiSurfing::AddProgressBarVertical(speed, sz);

			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bGui = !bGui;
}