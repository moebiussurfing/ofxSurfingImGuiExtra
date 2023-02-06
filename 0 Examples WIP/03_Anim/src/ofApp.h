#pragma once

/*

+ fix groups/trees crashes
+ fix hide headers
+ split vec3 params to 3 sliders
+ simple combo enum list

*/


#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "ofxSurfingHelpers.h"
#include "ImTween.h"//requires c++20?

class ofApp : public ofBaseApp{
public:
	
    void setup();
    void refreshImGuiStyles();
    void draw();
    void exit();

	ofxSurfingGui ui;

	//-

    // Groups
    
	ofParameterGroup params1;
    ofParameterGroup params2;
    ofParameterGroup params3;
    ofParameterGroup params4;

	//-

    // Parameters
	
	ofParameter<glm::vec3> rot_1;
	ofParameter<glm::vec3> pos_1;
    
	ofParameter<float> value;
	ofParameter<float> valueMin;
	ofParameter<float> valueMax;

	ofParameter<bool> bEnable1;
    ofParameter<bool> bEnable2;
    ofParameter<bool> bEnable3;
    ofParameter<bool> bEnable4;

	ofEventListener listener_bEnable1;
	ofEventListener listener_bEnable2;
	ofEventListener listener_bEnable3;
	ofEventListener listener_bEnable4;

    ofParameter<bool> bPrevious;
    ofParameter<bool> bNext;
	ofParameter<float> knob1;
	ofParameter<float> knob2;
	ofParameter<int> amount2;
    ofParameter<float> lineWidth2;
    ofParameter<float> separation2;
	ofParameter<int> shapeType2;
	ofParameter<float> speed3;
	ofParameter<int> shapeType3;
	ofParameter<int> size3;
	ofParameter<int> shapeType4;
	ofParameter<int> size4;
	ofParameter<float> lineWidth4;
	ofParameter<float> separation4;
	ofParameter<float> speed4;
    ofParameter<ofColor> color1;
    ofParameter<ofFloatColor> color2;

	//-

	// To be used to enable Gui sections
	// Could be used too to enable each window and 
	// allow close them using the top right [x]. 
#define NUM_SECTIONS 7
	vector <ofParameter<bool>> bEnablers;
	ofParameterGroup params_Enablers{ "params_Enablers" };
	// Exclusive toggles
	ofEventListeners listeners_Enablers;
	void Changed_Enablers(const void * sender, bool & value);
	bool bAttendingCallback; // Callback blocker


	//TODO:
	// Helper function to apply blur effect on an ImGui window
	inline void ApplyBlur(ImGuiWindow *window)
	{
		auto g = ImGui::GetCurrentContext();
		//ImGuiContext& g = ImGui::GetCurrentContext();
		//ImGuiContext& g = GImGui;

		//auto window = ImGui::GetCurrentWindow();
		ImVec2 pad_pos = window->DC.CursorPos;
		ImVec2 pad_size = window->Size;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::BeginChild("##blur", pad_size, true, 0);
		ImGui::PopStyleVar();
		ImGui::GetWindowDrawList()->AddRectFilled(pad_pos, ImVec2(pad_pos.x + pad_size.x, pad_pos.y + pad_size.y), ImColor(0, 0, 0, 128));

		//ImGui::Text("This window has a blur effect applied to it.");

		ImGui::EndChild();
	}

	// Usage example
	inline void Example() {
		ImGui::Begin("Blurred window");

		ImGui::Text("This window has a blur effect applied to it.");

		auto window = ImGui::GetCurrentWindow();
		ApplyBlur(window);

		ImGui::End();
	}
};
