#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::exit()
{
	delete t;
	t = NULL;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	t = new customType();
	t->color = ofColor::fuchsia;
	t->someString = "hello";
	t->someVar = -1;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(t->color);

	t->someVar = ofGetFrameNum();//update data
	string title = ofToString(t->someVar);
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

			ui.EndWindow();
		}

		//--

		c.show(t);

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