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
	params2.add(params3);
	params.add(params2);

	ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			static bool enabled = true;
			static int slider = 0, combo = 0;
			static char text[64];
			static float col[4];
			static float sliderf = 0.5;;

			float w = ui.getWidgetsWidth(1);
			float h = ui.getWidgetsHeightUnit();

			// imgui_tricks
			{


			if (ImGui::Button("Create Notify", { w, 2 * h }))
			{
				NotifyState s;
				auto r = ofRandom(1);
				if (r < 0.25) s = ImTrickNotify_Default;
				else if (r < 0.5) s = ImTrickNotify_Success;
				else if (r < 0.75) s = ImTrickNotify_Warning;
				else s = ImTrickNotify_Danger;
				//std::string t = ofToString("The notification was displayed ") + ofToString(r);//?
				//ImTricks::NotifyManager::AddNotify(t.c_str(), s);
				ImTricks::NotifyManager::AddNotify("The notification was displayed ", s);
			}

			ImTricks::NotifyManager::HandleNotifies(ImGui::GetForegroundDrawList());

			ui.AddSpacingHuge();

				static bool enable_animation = true;
				ImGui::Checkbox("Enable Animation", &enable_animation);

				IMGUI_SUGAR__DEBUG_POINT(ofColor::blue);
				//ofxImGuiSurfing::IMGUI_SUGAR__DEBUG_POINT;

				ImVec2 pc = ImGui::GetCursorPos();
				ImVec2 p = ImGui::GetCursorScreenPos();

				float trickFloat = ImTricks::Animations::FastLerpFloat("trickFloat", enable_animation, 0.f, 1.f, 0.05f);
				cout << "trickFloat:" << trickFloat << endl;

				ImColor colorLerped = ImTricks::Animations::FastColorLerp(ImColor(255, 0, 0), ImColor(0, 255, 0), trickFloat);
				
				ImGui::GetWindowDrawList()->AddRectFilled(p, p + ImVec2(w, 2 * h), colorLerped);

				IMGUI_SUGAR__DEBUG_POINT(ofColor::blue);

				ImGui::SetCursorPos(pc + ImVec2(0, 2 * h));
				//ImGui::SetCursorPos(p + ImVec2(0, 2 * h));

				ImGui::Dummy(ImVec2(0, 5));

				IMGUI_SUGAR__DEBUG_POINT(ofColor::blue);

				//ui.AddSpacingHuge();

				float _sliderf = ImTricks::Animations::FastLerpFloat("sliderf", enable_animation, 0.f, 1.f, 0.05f);


				ImGui::SliderFloat("move", &sliderf, 0, 1);
				ImGui::SliderFloat("_sliderf", &_sliderf, 0, 1);

				ui.AddSpacingHuge();
				static ImColor col = ImColor(23, 23, 23);
				ImTricks::Widgets::ColorEdit4("test", col, NULL);
			}



			ui.AddSpacingHuge();



			// imgui_tweaker
			{
				std::function<void()> myFunction = std::bind(&ofApp::myCallbackFunction, this);
				if (ImGui::Button("label1", ImVec2{ w,h }))
				{
					if (myFunction)
						myFunction();
				}



				std::function<void()> myFunction2 = std::bind(&ofApp::myWidgets, this);
				ImSugar::Group(myFunction2);

				//std::function<void()> f;
				ImSugar::Button("B2", ImVec2{ w,h }, myFunction);


				//myWidgets();
				//std::function<void()> myFunction2 = std::bind(&ofApp::myWidgets, this);
				//if (myFunction2) myFunction2();
			}

			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') {
		bGui = !bGui;
	}
}