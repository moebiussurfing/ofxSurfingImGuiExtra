#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::exit()
{
	delete data;
	data = NULL;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	data = new customType();
	data->color = ofColor::fuchsia;
	data->someString = "hello";
	data->someVar = -1;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(data->color);

	data->someVar = ofGetFrameNum();//update data
	string title = ofToString(data->someVar);
	ofSetWindowTitle(title);

	string s;

	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddLabelBig("ConsoleWidget");

			if (ui.AddButton("DO")) {
				s = "DO #" + ofToString(ofGetFrameNum());
				addToLog(s);
				c.addLine(s);
			}

			if (ui.AddButton("HELP")) {
				c.help_();
				s = "HELP";
				addToLog(s);
			}
			if (ui.AddButton("CLEAR")) {
				s = "CLEAR";
				addToLog(s);
				c.clear_();
			}

			ui.AddLabel("setColor");
			if (ui.AddButton("red", OFX_IM_BUTTON, 2, true)) {
				s = "setColor red";
				c.addLineCommnand(s, data);
			}
			if (ui.AddButton("blue", OFX_IM_BUTTON, 2)) {
				s = "setColor blue";
				c.addLineCommnand(s, data);
			}

			ui.EndWindow();
		}

		//--

		c.show(data);

	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//if (key == ' ') bGui = !bGui;
}

//--------------------------------------------------------------
void ofApp::addToLog(string s)
{
	return;

	stringstream ss;
	ss << s;

	std::cout << ss.str() << endl;
	ofLog() << ss.str();
}