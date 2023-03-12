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

			ImGui::Checkbox44("Enabled", &enabled);






			static int i1 = 50;
			static bool b = false;

			ImGui::SliderInt_("hola1", &i1, 0, 100);
			ImGui::SliderInt_2("hola2", &i1, 0, 100);
			ImGui::SliderInt_3("hola3", &i1, 0, 100);

			int k = (int)char('k');
			ImGui::Hotkey("hotkey", k, 0, ImVec2{ 100,100 });
			{
			}
			float sat = 1; float value = 0.5; float alpha = 0.5; float speed = 1; float offset = 0; float range = 2;
			ImGui::chromaText("texttechromaTextxttexttchromaTextxttexttexttexttext", sat, value, alpha, speed, offset, range);

			ImGui::Checkbox2("hello1", &b);
			ImGui::Checkbox("hello2", &b);



			ofxSurfingHelpers::Checkbox2("hello3", &b);
			ofxSurfingHelpers::drawWidgets();
			ofxSurfingHelpers::ButtonEx7("label", ImVec2{ 100,50 }, ImGuiButtonFlags_None);

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