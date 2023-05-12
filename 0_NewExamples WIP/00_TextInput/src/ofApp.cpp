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
	g.add(bGui_Text);

	params_Bubble.add(rounding);
	params_Bubble.add(colorBubble);
	params_Bubble.add(szFont);
	params_Bubble.add(bLabel);
	params_Bubble.add(padx, pady);
	params_Bubble.add(spacingx, spacingy);
	params_Bubble.add(scale);
	g.add(params_Bubble);

	ofxImGuiSurfing::loadGroup(g);
}

//--------------------------------------------------------------
void ofApp::drawImGui_Text()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(50, 50));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
		if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
		if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

		if (ui.BeginWindow(bGui_Text, window_flags))
		{
			if (!bGui_Headers) RemoveHeaderHeight();
			
			const char* label = "Prompt";
			const char* hint = "Prompt";
			static string text = "";
			ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
			ImGuiInputTextCallback callback = NULL;
			void* user_data = NULL;
			static bool isChanged = false;

			float x, y, w, h;
			float xx, yy;

			w = ImGui::GetContentRegionAvail().x;
			h = ImGui::GetContentRegionAvail().y;

			ui.PushFont(SurfingFontTypes(szFont.get()));
			{
				ImDrawList* draw_list = ImGui::GetWindowDrawList();

				ImVec2 p = ImGui::GetCursorScreenPos();
				ImDrawFlags flags = ImDrawFlags_None;

				x = p.x + padx*w;
				y = p.y + pady*h;

				w -= 2 * padx;
				h -= 2 * pady;
				ImRect r(x, y, w, h);

				float round = rounding * (h / 2);

				ImU32 col = IM_COL32(colorBubble.get().r, colorBubble.get().g, colorBubble.get().b, colorBubble.get().a);
				//ImU32 col = ImGui::GetColorU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
				//ImU32 col = IM_COL32(255, 0, 0, 255);

				draw_list->AddRectFilled(r.Min, r.Min + r.Max, col, round);

				// offset to center in the bubble
				xx = ImGui::GetCursorPosX();
				yy = ImGui::GetCursorPosY();
				yy += h / 2;
				xx += spacingx*w;
				yy += spacingy*h;

				float hl = ui.getWidgetsHeightUnit();
				yy -= hl/2;

				float offset = scale * w;
				xx += offset;

				ImGui::SetCursorPosX(xx);
				ImGui::SetCursorPosY(yy);

				//--

				if (!bLabel) label = "##label";

				PushItemWidth(w - 2 * offset);
				//if (!bLabel) PushItemWidth(-1);
				{
					//bBlink = (text == "");
					if (bBlink) ui.BeginBlinkText();

					if (bIntegrate) {
						ImVec4 c = ImVec4(0, 0, 0, 0);//transparent
						ImGui::PushStyleColor(ImGuiCol_Border, c);
						ImGui::PushStyleColor(ImGuiCol_FrameBg, c);
					}


					//// A
					//isChanged = ImGui::InputText(label, &text, flags, callback, user_data);

					// B
					isChanged = ImGui::InputTextWithHint(label, hint, &text, flags, callback, user_data);

					// C
					//float w = ofxImGuiSurfing::getPanelWidth();
					//float h = ofxImGuiSurfing::getPanelHeight();
					//ImVec2 sz = ImVec2(w, h);
					//ImGuiInputTextFlags flags= ImGuiInputTextFlags_None;
					////flags |= ImGuiInputTextFlags_CallbackResize;
					//isChanged = ImGui::InputTextMultiline(label, &text, sz, flags, callback, user_data);

					if (bIntegrate) ImGui::PopStyleColor(2);
					if (bBlink) ui.EndBlinkText();
				}
				//if (!bLabel) PopItemWidth();
				PopItemWidth();
			}
			ui.popStyleFont();

			//--

			if (bButtons) {
				ImGui::SetCursorPosX(xx);
				//ImGui::SetCursorPosY(yy);

				if (ImGui::Button("Enter"))
				{
					ui.AddToLog(text, OF_LOG_WARNING);
					//isChanged = true;
					//text = "";
				};
				ImGui::SameLine();
				if (ImGui::Button("Clear"))
				{
					text = "";
				};
			}

			//--

			ui.EndWindow();

			if (isChanged)
			{
				ui.AddToLog(text, OF_LOG_VERBOSE);
			}
		}
	}
	ImGui::PopStyleVar();
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

			ui.AddLabelBig("Text");
			ui.Add(bGui_Text);
			if (bGui_Text) {
				ui.AddGroup(params_Bubble);
				ImGui::Checkbox("Buttons", &bButtons);
				ImGui::Checkbox("Integrate", &bIntegrate);
				ImGui::Checkbox("Blink", &bBlink);
			}

			//TODO; params
			/*
			ui.AddSpacingBigSeparated();
			ui.Add(textA, OFX_IM_TEXT_INPUT);
			ui.AddSpacingBigSeparated();

			ui.Add(textB, OFX_IM_TEXT_INPUT_NAMED);
			ui.AddSpacingBigSeparated();

			ui.Add(textC, OFX_IM_TEXT_INPUT_NO_NAME);
			ui.AddSpacingBigSeparated();
			*/

			ui.EndWindow();
		}

		drawImGui_Text();
		drawImGui_Slider();
		drawImGui_Toggle();
		drawImGui_Button();
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
			if (!bGui_Headers) RemoveHeaderHeight();

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
			if (!bGui_Headers) RemoveHeaderHeight();

			float w = ofxImGuiSurfing::getPanelWidth();
			float h = ofxImGuiSurfing::getPanelHeight();
			ImVec2 sz = ImVec2(w, h);

			int iFont = ofMap(h, 0, ofGetHeight() * RATIO_WIDGETS_FONTS, 0, 3, true);
			ui.PushFont(SurfingFontTypes(iFont));

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

			ui.popStyleFont();

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
			if (!bGui_Headers) RemoveHeaderHeight();

			float w = ofxImGuiSurfing::getPanelWidth();
			float h = ofxImGuiSurfing::getPanelHeight();
			ImVec2 sz = ImVec2(w, h);

			int iFont = ofMap(h, 0, ofGetHeight() * RATIO_WIDGETS_FONTS, 0, 3, true);
			ui.PushFont(SurfingFontTypes(iFont));

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

			ui.popStyleFont();

			ui.EndWindow();
		}
	}
	ImGui::PopStyleVar();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (ui.isOverGui() || ui.isOverInputText()) return;

	if (key == 'g') bGui = !bGui;
	if (key == 'h') bGui_Headers = !bGui_Headers;
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ofxImGuiSurfing::saveGroup(g);
}
