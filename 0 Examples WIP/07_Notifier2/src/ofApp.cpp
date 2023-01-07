#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//notifier.setup("assets/fonts/telegrama_render.otf", 13);
	//notifier.setup("assets/fonts/overpass-mono-bold.otf", 10, 30);

	notifier.setMessagesLifeTime(4000);

	ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.Add(ui.bAutoResize);

			notification_manager.Draw();

			ui.EndWindow();
		}
	}
	ui.End();

	notifier.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') {
		bGui = !bGui;
	}
	
	// Theme
	if (key == '1') {
		ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	}
	if (key == '2') {
		ofxImGuiSurfing::ImGui_Xemu();
	}
	if (key == '3') {
		ofxImGuiSurfing::ImGui_ThemeYave();
	}

	// Queue a notitification
	if (key == ' ') 
	{
		stringstream ss;
		ss << textAtribute[rand() % 5] << textObject[rand() % 4] << textVerb[rand() % 6] << textSubject[rand() % 5];
		string str(ss.str());
		notification_manager.QueueNotification(str.c_str());
	}

	// Queue an error
	if (key == OF_KEY_BACKSPACE) 
	{
		stringstream ss2;
		ss2 << "We wanted to have " << 2 << " more pints, but it was past " << 11 << " o'clock." << endl;
		string str2(ss2.str());
		notification_manager.QueueError(str2.c_str());
	}

	// Queue a notitification
	if (key == OF_KEY_RETURN) 
	{
		stringstream ss;
		ss << textAtribute[rand() % 5] << textObject[rand() % 4] << textVerb[rand() % 6] << textSubject[rand() % 5];
		string str(ss.str());
		notifier.addNotification(str);
	}

	
}