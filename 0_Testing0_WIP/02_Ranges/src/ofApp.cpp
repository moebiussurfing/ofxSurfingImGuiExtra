#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowPosition(-2100, -250);

	// parameters
	params.setName("paramsGroup"); // main container
	//params2.setName("paramsGroup2");// nested
	//params3.setName("paramsGroup3");// nested
	//params.add(bPrevious.set("<", false));
	//params.add(bNext.set(">", false));
	//params.add(bEnable1.set("Enable1", false));
	//params.add(bEnable2.set("Enable2", false));
	//params.add(bEnable3.set("Enable3", false));
	//params.add(speed.set("speed", 0.5, 0, 1));
	//params.add(shapeType.set("shapeType", 0, -50, 50));
	//params.add(size.set("size", 100, 0, 100));
	//params.add(amount.set("amount", 10, 0, 25));
	//params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	//params2.add(size2.set("size2", 100, 0, 100));
	//params2.add(amount2.set("amount2", 10, 0, 25));
	//params3.add(speed3.set("speed3", 0.5, 0, 1));
	//params2.add(params3);
	//params.add(params2);

	params.add(lineMin.set("lineMin", 0.25, 0, 1));
	params.add(lineMax.set("lineMax", 0.75, 0, 1));
	params.add(separationMin.set("separationMin", 0.1, 0, 1));
	params.add(separationMax.set("separationMax", 0.9, 0, 1));

	//ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw() {
	auto p = glm::vec2(ofGetWindowPositionX(), ofGetWindowPositionY());
	ofSetWindowTitle(ofToString(p.x) + ","+ ofToString(p.y));

	ui.Begin();
	{
		if (ui.BeginWindow(bGui)) {
			ui.AddAutoResizeToggle();

			static float vmin1 = 0.2f;
			static float vmax1 = 0.8f;
			RangeSliderFloat("Range 1", &vmin1, &vmax1, 0.0f, 1.0f, true, "%.3f", "%.3f", ImGuiSliderFlags_AlwaysClamp);

			static float vmin2= 0.1f;
			static float vmax2 = 0.9f;
			RangeSliderFloat("Range 2", &vmin2, &vmax2, 0.0f, 1.0f, true, "%.1f", "%.1f", ImGuiSliderFlags_AlwaysClamp);

			ui.AddSeparated();

			//TODO: DEBUG
			static bool bShow = 0;
			AddToggle("show", bShow);
			if (bShow) {
				//ui.AddGroup(params);

				////TODO:
				////Range
				//string n = "MONOCHR";
				//float power = 1;
				//float _sp = ui.getWidgetsSpacingX();
				//float _w = ui.getWidgetsWidth(1) /*- _sp*/;
				//float _h = ui.getWidgetsHeightUnit();
				//ImGui::PushItemWidth(_w);
				//std::string ss = "%.3f    %.3f";
				//ImVec2 shape = ImVec2(_w, _h);
				////ImVec2 shape = ImVec2(-1, -1);
				//bool bfullsize = true;
				//bool bNoLabel = true;
				////AddRange("one", lineMin, lineMax, ss.c_str(), power, shape, bfullsize, bNoLabel);
				//ImGui::PopItemWidth();

				AddRange("one", lineMin, lineMax, 0.01);

				ui.AddSeparated();

				if (1) {
					string n1 = "one";
					string n2 = "two";

					ofxImGuiSurfing::AddRangeParam(n1, lineMin, lineMax);
					ofxImGuiSurfing::AddRangeParam(n2, separationMin, separationMax);
				}

			}
			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'g') {
		bGui = !bGui;
	}
}
