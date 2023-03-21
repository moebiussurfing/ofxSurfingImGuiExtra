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

			//{
			//	ui.AddSpacingHuge();
			//	IMGUI_SUGAR__DEBUG_POINT(ofColor::blue);
			//	ImVec2 pc = ImGui::GetCursorPos();
			//	ImVec2 p = ImGui::GetCursorScreenPos();
			//	IMGUI_SUGAR__DEBUG_POINT(ofColor::blue);
			//	IMGUI_SUGAR__DEBUG_POINT(ofColor::blue);
			//}

			ui.AddSpacingHuge();

			// imgui_tweaker
			{
				//{
				//	if (myFunction)
				//		myFunction();
				//}

				std::function<void()> myFunction2 = std::bind(&ofApp::myWidgets, this);
				//ImSugar::Group(myFunction2);

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