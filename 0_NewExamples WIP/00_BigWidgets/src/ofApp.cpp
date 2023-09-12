#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxImGuiSurfing::setMonitorsLayout(-1, true, true);

	ui.setup();

	g.add(bGui_Headers);
	g.add(bGui_Bg);
	g.add(bGui_ResizePin);
	g.add(bGui_LockMove);
	g.add(bGui_Toggle);
	g.add(bGui_Button);
	g.add(bGui_Slider);

	bigTextInput.setHint("Type search");

	//--

	ofxImGuiSurfing::loadGroup(g);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawImGui();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddMinimizerToggle();
			if (ui.isMaximized()) {
				ui.AddLogToggle();
				ui.AddDebugToggle();
				ui.AddAutoResizeToggle();
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("Windows");
				ui.Add(bGui_Headers, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_Bg, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_ResizePin, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_LockMove, OFX_IM_TOGGLE_ROUNDED);
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("Toggle");
				ui.Add(bGui_Toggle);
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("Buttons");
				ui.Add(bGui_Button);
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("Slider");
				ui.Add(bGui_Slider);
				if (bGui_Slider)
				{
					ui.Add(value);
					ImGui::Checkbox("Colorize", &bColorize);
					if (ui.AddButton("Reset"))
					{
						bResetSlider = 1;
					};
				}
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("InputText");
				ui.Add(bigTextInput.bGui);
				ui.Add(bigTextInput.bGui_Config);
			}

			ui.EndWindow();
		}

		drawImGui_Slider();
		drawImGui_Toggle();
		drawImGui_Button();

		bigTextInput.draw(ui);
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawImGui_Slider()
{
	if (bResetSlider)
	{
		bResetSlider = 0;
		doResetSlider();
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(40, 200));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
		if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
		if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

		if (ui.BeginWindow(bGui_Slider, window_flags))
		{
			if (!bGui_Headers) AddHeaderHeight();

#if 0
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
#endif
			//--

			// v slider
			if (bColorize) {
				auto c = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
				ImVec4 _cBg = ImVec4(c.x, c.y, c.z, c.w * 0.2);
				ImGui::PushStyleColor(ImGuiCol_SliderGrab, cRange);
				ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, cRangeRaw);
				ImGui::PushStyleColor(ImGuiCol_FrameBg, _cBg);
				ImGui::PushStyleColor(ImGuiCol_FrameBgActive, _cBg);
				ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, _cBg);
			}
			{
				ImVec2 sz = ImVec2(-1.f, -1.f);
				bool bNoName = true;
				bool bNoNumber = true;
				ofxImGuiSurfing::AddVSlider(value, sz, bNoName, bNoNumber);
				ofxImGuiSurfing::AddMouse(value);
			}
			if (bColorize) ImGui::PopStyleColor(5);

			ui.EndWindow();
		}
	}
	ImGui::PopStyleVar();
}

//--------------------------------------------------------------
void ofApp::doResetSlider()
{
	float xx, yy, ww, hh, pad;

	pad = 20;
	ww = 200 - 2 * ImGui::GetStyle().WindowPadding.x;
	hh = ofGetHeight() - 2 * pad;
	xx = ofGetWidth() - ww - pad;
	yy = pad;

	ImGuiCond flagsCond = ImGuiCond_None;
	flagsCond |= ImGuiCond_FirstUseEver;
	flagsCond = ImGuiCond_None;

	ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
	ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);
}

//--

//--------------------------------------------------------------
void ofApp::drawImGui_Toggle()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(40, 200));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
		if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
		if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

		if (ui.BeginWindow(bGui_Toggle, window_flags))
		{
			if (!bGui_Headers) AddHeaderHeight();

			float w = ofxImGuiSurfing::getPanelWidth();
			float h = ofxImGuiSurfing::getPanelHeight();
			ImVec2 sz = ImVec2(w, h);

			int iFont = ofMap(h, 0, ofGetHeight() * RATIO_WIDGETS_FONTS, 0, 3, true);
			ui.PushFontStyle(SurfingFontTypes(iFont));

			auto c = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
			ImVec4 _cBg = ImVec4(c.x, c.y, c.z, c.w * 0.2);
			ImGui::PushStyleColor(ImGuiCol_SliderGrab, cRange);
			ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, cRangeRaw);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, _cBg);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, _cBg);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, _cBg);
			{
				bool _bBorder = true;
				bool _bBlink = true;
				ofxImGuiSurfing::AddBigToggle(bToggle, sz, _bBorder, _bBlink);
			}
			ImGui::PopStyleColor(5);

			ui.PopFontStyle();

			//--

			ui.EndWindow();
		}
	}
	ImGui::PopStyleVar();
}

//--------------------------------------------------------------
void ofApp::drawImGui_Button()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(40, 200));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
		if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
		if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

		if (ui.BeginWindow(bGui_Button, window_flags))
		{
			if (!bGui_Headers) AddHeaderHeight();

			float w = ofxImGuiSurfing::getPanelWidth();
			float h = ofxImGuiSurfing::getPanelHeight();
			ImVec2 sz = ImVec2(w, h);

			int iFont = ofMap(h, 0, ofGetHeight() * RATIO_WIDGETS_FONTS, 0, 3, true);
			ui.PushFontStyle(SurfingFontTypes(iFont));

			auto c = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
			ImVec4 _cBg = ImVec4(c.x, c.y, c.z, c.w * 0.2);
			ImGui::PushStyleColor(ImGuiCol_SliderGrab, cRange);
			ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, cRangeRaw);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, _cBg);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, _cBg);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, _cBg);
			if (ofxImGuiSurfing::AddBigButton(vButton, sz))
			{
			}
			ImGui::PopStyleColor(5);

			ui.PopFontStyle();

			ui.EndWindow();
		}
	}
	ImGui::PopStyleVar();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (ui.isMouseOverInputText()) return;
	//if (ui.isOverGui()) return;

	if (key == 'g') bGui = !bGui;
	if (key == 'h') bGui_Headers = !bGui_Headers;
	if (key == 'b') bGui_Bg = !bGui_Bg;
	if (key == 'r') bGui_ResizePin = !bGui_ResizePin;
	if (key == 'l') bGui_LockMove = !bGui_LockMove;
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ofxImGuiSurfing::saveGroup(g);
}
