#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	// Profiler
	profilerActive = true;

	ui.setup();
}

//--------------------------------------------------------------
void ofApp::update()
{
	ImGuiEx::ProfilerTask* pt = new ImGuiEx::ProfilerTask[NUM_PASSES];

	for (size_t i = 0; i < NUM_PASSES; i++)
	{
		pt[i].color = profiler.cpuGraph.colors[static_cast<unsigned int>( 8 + i % 8)];
		pt[i].startTime = ofGetElapsedTimef();
		pt[i].name = "cpuTask" + ofToString(i);

		int t = ofRandom(9);
		ofSleepMillis(t);

		pt[i].endTime = ofGetElapsedTimef();
	}

	profiler.cpuGraph.LoadFrameData(pt, NUM_PASSES);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ImGuiEx::ProfilerTask* pt = new ImGuiEx::ProfilerTask[NUM_PASSES];

	for (size_t i = 0; i < NUM_PASSES; i++)
	{
		pt[i].color = profiler.gpuGraph.colors[static_cast<unsigned int>(i % 16)];
		pt[i].startTime = ofGetElapsedTimef();
		pt[i].name = "gpuTask" + ofToString(i);

		int t = ofRandom(i * 2);
		ofSleepMillis(t);

		pt[i].endTime = ofGetElapsedTimef();
	}

	profiler.gpuGraph.LoadFrameData(pt, NUM_PASSES);

	//--

	ui.Begin();
	{
		// PROFILER
		if (profilerActive) {
			profiler.Render(&profilerActive);
		}
	}
	ui.End();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') {
		profilerActive = !profilerActive;
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


}