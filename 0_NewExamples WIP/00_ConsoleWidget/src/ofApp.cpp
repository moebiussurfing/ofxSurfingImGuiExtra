#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//myCustomConsole c = new myCustomConsole(true);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddLabelBig("ConsoleWidget");

			ui.EndWindow();
		}

		//customType t;
		//t.someVar = 0;
		//t.someString = string("Hello");

		//TODO:
		//ui.PushFont(SurfingFontTypes(2));
		c.show(t);
		//ui.PopFont();

		if (ui.AddButton("DO")) {
			stringstream ss;
			ss << "DO #" << ofGetFrameNum();
			cout << ss << endl;
			ofLog() << ss.str();
		}
	}
	ui.End();

	//ofLog() << "t:" << t.someVar;
	//ofLog() << "t:" << t.someString << " : " << t.someVar;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//if (key == ' ') bGui = !bGui;
}