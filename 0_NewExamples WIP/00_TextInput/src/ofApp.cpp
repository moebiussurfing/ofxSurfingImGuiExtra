#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		static bool bReset = 0;

		if (ui.BeginWindow(bGui))
		{
			ui.AddMinimizerToggle();
			ui.AddAutoResizeToggle();
			ui.AddSpacingBigSeparated();

			ui.AddLabelBig("Floating Slider");
			ui.Add(bGui_ManualSlider);
			ui.Add(bGui_ManualSliderHeader);
			ui.Add(controlManual);
			if (ui.AddButton("Reset")) {
				bReset = 1;
			};
			ui.AddSpacingBigSeparated();

			ui.Add(textA, OFX_IM_TEXT_INPUT);
			ui.AddSpacingBigSeparated();

			ui.Add(textB, OFX_IM_TEXT_INPUT_NAMED);
			ui.AddSpacingBigSeparated();

			ui.Add(textC, OFX_IM_TEXT_INPUT_NO_NAME);
			ui.AddSpacingBigSeparated();

			ui.EndWindow();
		}
	
		if (bReset) {
			bReset = 0;
		doResetManualSlider();
		}
		draw_ImGui_ManualSlider();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}

//--------------------------------------------------------------
void ofApp::draw_ImGui_ManualSlider()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(40, 200));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		window_flags |= ImGuiWindowFlags_NoBackground;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!bGui_ManualSliderHeader) window_flags |= ImGuiWindowFlags_NoTitleBar;

		if (ui.BeginWindow(bGui_ManualSlider, window_flags))
		{
			// markers zones
			float x1, x2, gap, yy, ww, hh;
			ww = ofxImGuiSurfing::getPanelWidth();
			hh = ofxImGuiSurfing::getPanelHeight();
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			ImVec2 p = ImGui::GetCursorScreenPos();
			float linew = 2.f;
			float linea = 0.15f;
			ImVec4 cm = ImVec4(0.0f, 0.0f, 0.0f, linea);

			gap = 10;
			ww -= 2 * gap;
			x1 = p.x + gap;
			x2 = x1 + ww;

			yy = p.y + 0.33 * hh;
			draw_list->AddLine(ImVec2(x1, yy), ImVec2(x2, yy), ImGui::GetColorU32(cm), linew);

			yy = p.y + 0.66 * hh;
			draw_list->AddLine(ImVec2(x1, yy), ImVec2(x2, yy), ImGui::GetColorU32(cm), linew);

			//-

			// v slider

			auto c = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
			ImVec4 _cBg = ImVec4(c.x, c.y, c.z, c.w * 0.2);
			ImGui::PushStyleColor(ImGuiCol_SliderGrab, cRange);
			ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, cRangeRaw);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, _cBg);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, _cBg);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, _cBg);
			{
				ImVec2 sz = ImVec2(-1.f, -1.f);
				bool bNoName = true;
				bool bNoNumber = true;
				ofxImGuiSurfing::AddVSlider(controlManual, sz, bNoName, bNoNumber);
			}
			ImGui::PopStyleColor(5);

			ui.EndWindow();
		}
	}
	ImGui::PopStyleVar();
}


//--------------------------------------------------------------
void ofApp::doResetManualSlider()
{
	float gx, gy, gw, gh, ww, hh, pad;
	pad = 10;
	gw = ofGetWidth() - 2 * pad;
	gx = pad;
	gy = pad;
	ww = gw;
	hh = 50;
	ofRectangle rectPreview(ofRectangle(gx, gy, gw, hh)); // initialize


	// panels sizes
	float xx;
	float yy;
	int padx = 10;
	int pady = 10;
	int pady2 = 50;

	ImGuiCond flagsCond = ImGuiCond_None;
	flagsCond |= ImGuiCond_FirstUseEver;

	ww = 150;
	xx = ofGetWidth() - ww - padx;
	yy = rectPreview.getBottomRight().y + pady;
	hh = ofGetHeight() - yy - pady;

	flagsCond = ImGuiCond_None;

	ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
	ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);
}