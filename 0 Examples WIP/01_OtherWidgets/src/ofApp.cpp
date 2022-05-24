#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	// parameters
	params.setName("paramsGroup");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested

	params.add(bPrevious.set("<", false));
	params.add(bNext.set(">", false));
	params.add(bEnable1.set("Enable1", false));
	params.add(bEnable2.set("Enable2", false));
	params.add(bEnable3.set("Enable3", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));

	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));

	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));

	//--

	guiManager.setup(IM_GUI_MODE_INSTANTIATED);

	ofxImGuiSurfing::ImGui_ThemeYave();
	//ofxImGuiSurfing::ImGui_Xemu();

}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		if (guiManager.beginWindow(bGui))
		{
			guiManager.Add(guiManager.bAutoResize);

			static bool btoggle = false;
			static float mfloat = 1.f;

			//ofxSurfingImGui::Toggle("MyToggle", &btoggle, "MyToggle description");
			//ofxSurfingImGui::Slider("MySlider ", &mfloat, "MySlider description");

			//guiManager.AddGroup(params2);

			//ofxSurfingImGui::Separator();//breaks

			//guiManager.AddGroup(params3);


			notification_manager.Draw();


			guiManager.endWindow();
		}
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') {
		bGui = !bGui;
	}

	if (key == ' ') {

		string textAtribute[5] = {
	"Brilliant",
	"Curious",
	"Amazing",
	"Sublime",
	"Ironic",
		};

		string textObject[4] = {
			" disco inferno",
			" camp fire entanglement",
			" wedding promise",
			" man"
		};

		string textVerb[6] = {
			" bites",
			" strikes",
			" lost on",
			" snatches",
			" teases",
			" invites"
		};

		string textSubject[5] = {
			" pope",
			" government",
			" irate schoolmaster",
			" late enthusiast",
			" dog"
		};

		stringstream ss;
		ss << textAtribute[rand() % 5] << textObject[rand() % 4] << textVerb[rand() % 6] << textSubject[rand() % 5];
		string str(ss.str());
		notification_manager.QueueNotification(str.c_str());
	}

	if (key == OF_KEY_BACKSPACE) {
		bool b = ofRandom(1) < 0.5f;

		stringstream ss2;
		ss2 << "We wanted to have " << 2 << " more pints, but it was past " << 11 << " o'clock." << endl;
		//ss2 << textAtribute[rand() % 5] << ", you just pressed key: " << key;
		string str2(ss2.str());
		notification_manager.QueueError(str2.c_str());
	}
}