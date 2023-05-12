#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxImGuiSurfing::setMonitorsLayout(-1, true, true);

	ui.setup();

	bigTextInput.setHint("Type search");
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawImGui();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddMinimizerToggle();
			if (ui.isMaximized()) {
				ui.AddLogToggle();
				ui.AddDebugToggle();
				ui.AddAutoResizeToggle();
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("InputText");
				ui.Add(bigTextInput.bGui);
				ui.Add(bigTextInput.bGui_Config);
			}

			ui.EndWindow();
		}

		bigTextInput.draw(ui);
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (ui.isOverInputText()) return;
	//if (ui.isOverGui()) return;

	if (key == 'g') bGui = !bGui;
}

//--------------------------------------------------------------
void ofApp::exit()
{
}
