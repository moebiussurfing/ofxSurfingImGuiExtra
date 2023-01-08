#include "ofApp.h"

#define SEQUENTITY_IMPLEMENTATION

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);

	ui.setup();
	ui.setImGuiAutoResize(false);

	entt::entity entity = registry.create();

	auto& track1 = registry.assign<Sequentity::Track>(entity); {
		track1.label = "Track 1";
		track1.color = ImColor::HSV(0.0f, 0.5f, 0.75f);
	}

	//auto& track2 = registry.assign<Sequentity::Track>(entity); {
	//	track2.label = "Track 2";
	//	track2.color = ImColor::HSV(0.5f, 0.5f, 0.75f);
	//}

	auto& channel1 = Sequentity::PushChannel(track1, MyEventType); {
		channel1.label = "Channel 1";
		channel1.color = ImColor::HSV(0.33f, 0.5f, 0.75f);
	}

	auto& channel2 = Sequentity::PushChannel(track1, MyEventType); {
		channel2.label = "Channel 2";
		channel2.color = ImColor::HSV(0.66f, 0.5f, 0.75f);
	}

	auto& event = Sequentity::PushEvent(channel1); {
		event.time = 3;
		event.length = 7;
		event.color = ImColor::HSV(0.66f, 0.5f, 0.75f);
	}

	////And here's how you query.
	//const int time{ 13 };
	Sequentity::Intersect(track1, time, [](const auto& event) {
		if (event.type == MyEventType) {

			// Do something interesting
			event.time;
			event.length;

			ofLog() << event.time << ":" << event.length;
		}
		});
}

//--------------------------------------------------------------
void ofApp::update()
{
	time = ofGetFrameNum() % 120;

}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawGui();
}

//--------------------------------------------------------------
void ofApp::drawGui()
{
	ui.Begin(); // global begin
	{
		if (ui.BeginWindow(bGui))
		{
			ui.Add(ui.bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);

			string s;
			s += "Time: ";
			s += ofToString(time, 0);
			ui.AddLabelBig(s);

			ui.EndWindow();
		}

		// Draw it!
		Sequentity::EventEditor(registry);
	}
	ui.End(); // global end
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = ' ') {
	}
}