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
	data = new dataCustom();
	data->color = ofColor::fuchsia;
	data->someString = "hello";
	data->someVar = -1;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(data->color);

	//update data
	data->someVar = ofGetFrameNum();

	string title = ofToString(data->someVar);
	ofSetWindowTitle(title);

	string s;

	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddLabelBig("surfingConsole");
			ui.AddSpacingSeparated();

			ui.AddLabelBig("dataCustom");
			ui.AddLabel("someVar:" + ofToString(data->someVar));
			ui.AddLabel("someString:" + ofToString(data->someString));
			ui.AddLabel("color:" + ofToString(data->color));
			ui.AddSpacingSeparated();

			if (ui.AddButton("HELP")) {
				s = "HELP";
				addToLog(s);

				c.help_();
			}
			if (ui.AddButton("CLEAR")) {
				s = "CLEAR";
				addToLog(s);
				
				c.clear_();
			}
			ui.AddSpacingSeparated();

			ui.AddLabelBig("Post Commands");
			ui.AddLabel("setColor");
			if (ui.AddButton("red", OFX_IM_BUTTON, 2, true)) {
				s = "setColor red";
				c.addLineCommnand(s, data);
			}
			if (ui.AddButton("blue", OFX_IM_BUTTON, 2)) {
				s = "setColor blue";
				c.addLineCommnand(s, data);
			}

			if (ui.AddButton("DO")) {
				s = "DO #" + ofToString(ofGetFrameNum());
				addToLog(s);
				c.addLine(s);
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