#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		/* Put windows here */

		if (ui.BeginWindow(bGui))
		{
			/* Put widgets here */

			//ui.AddLabelBig("00_HelloWorld");
			//ui.AddSpacing();
			//ui.Add(bEnable, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			//ui.Add(speed, OFX_IM_HSLIDER);
			//ui.Add(name);
			//ui.AddSpacingSeparated();
			//ui.AddGroup(params, SurfingGuiGroupStyle_Collapsed);

			//ofxImGuiSurfing::AddHSlider(speed, ImVec2(300, 40));
			AddBigSlider(speed, 300,40, "myLabel", string(OFX_IM_FORMAT_SLIDERS).c_str());

			float v = 0.5;
			ImGui::DragFloat("myLabel", &v,0.1, 0, 1);

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