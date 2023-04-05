#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(t.color);

	t.someVar = ofGetFrameNum();//update data
	string title = ofToString(t.someVar);
	ofSetWindowTitle(title);
	
	string s;

	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddLabelBig("ConsoleWidget");
			ui.EndWindow();
		}

		c.show(t);

		if (ui.AddButton("DO")) {
			s = "DO #" +ofToString(ofGetFrameNum());
			addToLog(s);
		}

		if (ui.AddButton("HELP")) {
			c.clearLines(t);
			s = "HELP";
			addToLog(s);
		}
		if (ui.AddButton("CLEAR")) {
			s = "CLEAR";
			addToLog(s);
			c.clearLines(t);
		}
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
	stringstream ss;
	ss << s;
	
	std::cout << ss << endl;
	ofLog() << ss.str();
}