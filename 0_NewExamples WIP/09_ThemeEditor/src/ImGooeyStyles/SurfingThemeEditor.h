// Taken from: https://github.com/pegvin/ImGooeyStyles

/*

	TODO

	define a global color and some main colors.
	link colors between particular settings
	but darker or lighter. add helpers

*/


#pragma once

#include "ofMain.h"

//#include "imgui.h"
//#include "ofxSurfingImGui.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "imgui_styles.h"

//--

class SurfingThemeEditor
{
public:
	ofParameter<bool> bGui;
	ofParameter<bool> bGui_Demo;

	SurfingThemeEditor() {
		bGui.set("Surfing Editor", false);
		bGui_Demo.set("Demo", false);
	};

	~SurfingThemeEditor() {
	};

	void draw()
	{
		if (bGui) drawEditor();
		if (bGui_Demo) drawDemo();
	};

	void drawDemoSurfingWidgets(SurfingGuiManager& ui)
	{
		ui.AddLabelHuge("Theme Tester", true);
		ui.AddSeparated();
		ui.AddSpacing();

		ImVec2 sz1(ImGui::GetContentRegionAvail().x, 2 * ImGui::GetFrameHeight());
		ImVec2 sz2(ImGui::GetContentRegionAvail().x / 2 - ImGui::GetStyle().ItemSpacing.x, 2 * ImGui::GetFrameHeight());

		static ofParameter<float> v1{ "Value", 0.5, 0, 1 };
		static ofParameter<float> v2{ "Value", 0.5, 0, 1 };
		static ofParameter<int> n{ "Number", 0, 0, 10 };
		static bool b1 = false;
		static bool b2 = false;
		static ofParameter<int> i{ "Index",0,0,3 };
		static std::vector<std::string> fileNames{ "ZERO", "ONE","TWO","THREE" };

		ui.AddLabelBig("Surfing API");
		if (ui.AddButton("Button", sz1)) {
		}
		if (ui.AddToggle("Toggle", b1, sz1)) {
		}
		ui.Add(v1, OFX_IM_HSLIDER);
		ui.Add(v2, OFX_IM_KNOB_TICKKNOB);
		ui.Add(i, OFX_IM_STEPPER);
		ui.AddCombo(i, fileNames);

		ui.AddSpacingBigSeparated();

		ui.AddLabelBig("ImGui RAW");
		ui.Add(n);
		if (ImGui::Button("Button")) {
		};
		ImGui::Checkbox("Toggle", &b2);
	};

	void drawEditor()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		static bool b = false;

		ImGui::Begin("Surfing Style Editor");

		ImVec2 sz(ImGui::GetContentRegionAvail().x / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 2 * ImGui::GetFrameHeight());

		if (ImGui::Button("Load Configuration", sz)) {
			ImGui::LoadStyleFrom("imgui_styles.ini");
			printf("Loaded Config From imgui_styles.ini...\n");
		}
		ImGui::SameLine();
		if (ImGui::Button("Save Configuration", sz)) {
			ImGui::SaveStylesTo("imgui_styles.ini");
			printf("Saved Config To imgui_styles.ini...\n");
		}
		ImGui::Separator();

		ImGui::ShowStyleEditor(&style);

		ImGui::End();
	};

	void drawDemo()
	{
		ImGui::ShowDemoWindow(NULL);
		//ImGui::Begin("Preview Window");
		//ImGui::End();
	};
};
