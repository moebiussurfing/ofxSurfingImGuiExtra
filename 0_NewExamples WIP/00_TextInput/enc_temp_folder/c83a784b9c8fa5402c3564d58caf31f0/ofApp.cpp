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
	g.add(bGui_TextInput);

	params_Bubble.add(rounded);
	params_Bubble.add(colorBubble);
	params_Bubble.add(szFont);
	params_Bubble.add(bLabel);
	params_Bubble.add(padxBubble, padyBubble);
	params_Bubble.add(padxText, padyText);
	//params_Bubble.add(scalex);
	params_Bubble.add(typeInput);
	params_Bubble.add(vResetBubble);
	g.add(params_Bubble);

	eventResetBubble = vResetBubble.newListener([this]() {
		//rounded = 1;
		padxBubble = padyBubble = 0;
		padxText = 0;
		//padxText = 0.1;
		padyText = 0;
		//scalex = 0;

		bResetBubble = 1;
		});

	ofxImGuiSurfing::loadGroup(g);
}

//--------------------------------------------------------------
void ofApp::drawImGui_TextInput()
{
	if (!bGui_TextInput) return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(50, 50));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
		if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
		if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

		static float x, y, w, h;

		ImVec2 size_min = ImVec2(230, 150);
		ImVec2 size_max = ImVec2(FLT_MAX, FLT_MAX);
		ImGui::SetNextWindowSizeConstraints(size_min, size_max);

		//--

		if (bResetBubble) {
			bResetBubble = 0;
			doResetTextInput();
		}

		if (ui.BeginWindow(bGui_TextInput, window_flags))
		{
			////TODO: remove pad
			//RemoveHeaderHeight();
			//ofxImGuiSurfing::AddSpacingY(ImGui::GetStyle().WindowPadding.y);

			if (!bGui_Headers) AddHeaderHeight();

			static string text = "";
			const char* label = "Prompt";
			const char* hint = "Prompt";
			ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;

			//--

			ImGuiInputTextCallback callback = NULL;

			//TODO:
			//std::function<int(ImGuiInputTextCallbackData*)> callback =
			//	[this](ImGuiInputTextCallbackData* data) -> int {
			//	ui.AddToLog(text, OF_LOG_WARNING);
			//	text = "";
			//	return 0;
			//};

			//TODO:
			//ImGuiInputTextCallback callback = [this](ImGuiInputTextCallbackData* data) -> int {
			//	if (data->EventFlag == ImGuiInputTextFlags_EnterReturnsTrue) {
			//		ui.AddToLog(text, OF_LOG_WARNING);
			//		text = "";
			//	}
			//	return 0;
			//};

			//--

			void* user_data = NULL;
			static bool isChanged = false;

			float xx, yy;

			w = ImGui::GetContentRegionAvail().x;
			h = ImGui::GetContentRegionAvail().y;

			ui.PushFont(SurfingFontTypes(szFont.get()));
			{
				ImDrawList* draw_list = ImGui::GetWindowDrawList();

				ImVec2 p = ImGui::GetCursorScreenPos();
				ImDrawFlags flags = ImDrawFlags_None;

				float pxBubble = padxBubble * (w / 4);
				float pyBubble = padyBubble * (h / 4);

				x = p.x + pxBubble;
				y = p.y + pyBubble;

				w -= 2 * pxBubble;
				h -= 2 * pyBubble;

				w -= 2 * padxBubble;
				h -= 2 * padyBubble;

				ImRect r(x, y, w, h);

				float round = rounded * (h / 2);

				ImU32 col = ImGui::GetColorU32(colorBubble.get());
				//ImU32 col = IM_COL32(colorBubble.get().r, colorBubble.get().g, colorBubble.get().b, colorBubble.get().a);
				//ImU32 col = ImGui::GetColorU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
				//ImU32 col = IM_COL32(255, 0, 0, 255);

				draw_list->AddRectFilled(r.Min, r.Min + r.Max, col, round);

				float _hh = ui.getWidgetsHeightUnit();

				// _offsetx to center in the bubble
				xx = ImGui::GetCursorPosX();
				yy = ImGui::GetCursorPosY();

				xx += padxText * (w / 4);
				//xx += _offsetx;
				xx += pxBubble;

				yy += h / 2;
				yy += padyText * (h / 4);
				yy += pyBubble;

				float hl = ui.getWidgetsHeightUnit();
				yy -= hl / 2;

				////TODO:
				//if (bDebug) {
				//	ImRect r2(10, 10, 50, 50);
				//	//ImRect r2(xx, yy, _ww, _hh);
				//	draw_list->AddRect(r2.Min, r2.Min + r2.Max, IM_COL32(255, 0, 0, 255), 0);
				//}

				//float _offsetx = scalex * (w / 2);
				//float _ww = w - 2 * _offsetx;

				//TODO:
				float _ww = w;
				_ww -= padxText * (w / 4);
				//_ww -= pxBubble/2;
				//float _ww = w - pxBubble;
				//float _ww = w - 2 * pxBubble;

				//--

				ImGui::SetCursorPosX(xx);
				ImGui::SetCursorPosY(yy);

				//--

				if (!bLabel) label = "##label";
				bool _bBlink = bBlink && (text == "");

				PushItemWidth(_ww);
				{
					if (_bBlink) ui.BeginBlinkTextDisabled();
					if (bIntegrate)
					{
						ImVec4 c = ImVec4(0, 0, 0, 0);//transparent
						ImGui::PushStyleColor(ImGuiCol_Border, c);
						ImGui::PushStyleColor(ImGuiCol_FrameBg, c);
					}

					if (typeInput == 0)
					{
						// A
						isChanged = ImGui::InputText(label, &text, flags, callback, user_data);
					}
					else if (typeInput == 1)
					{
						// B
						isChanged = ImGui::InputTextWithHint(label, hint, &text, flags, callback, user_data);
					}
					else if (typeInput == 2)
					{
						// C
						_hh = 2 * ui.getWidgetsHeightUnit();//two lines
						//ui.AddSpacingY(-_hh / 2);
						ImVec2 _sz = ImVec2(_ww, _hh);
						ImGuiInputTextFlags _flags = ImGuiInputTextFlags_None;
						//_flags |= ImGuiInputTextFlags_CallbackResize;
						isChanged = ImGui::InputTextMultiline(label, &text, _sz, _flags, callback, user_data);
					}

					if (bIntegrate) ImGui::PopStyleColor(2);
					if (_bBlink) ui.EndBlinkTextDisabled();
				}
				PopItemWidth();
			}

			ui.popStyleFont();

			//--

			//TODO:
			if (bButtons)
			{
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

			// Get enter
			bool b = ImGui::GetIO().WantTextInput;
			if (b && ImGui::IsKeyPressed(ImGuiKey_Enter))
			{
				ui.AddToLog(text, OF_LOG_WARNING);
				text = "";
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
void ofApp::doResetTextInput()
{
	float xx, yy, ww, hh, pad;

	pad = 50;

	ww = ofGetWidth() - 2 * pad;
	hh = 300;
	xx = pad;
	yy = ofGetHeight() / 2 - hh / 2;

	ImGuiCond flagsCond = ImGuiCond_None;
	flagsCond |= ImGuiCond_FirstUseEver;
	flagsCond = ImGuiCond_None;

	ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
	ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);
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

			if (ui.isMaximized()) {
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
			}

			ui.AddLabelBig("Text");
			ui.Add(bGui_TextInput);
			if (bGui_TextInput) {
				ui.AddGroup(params_Bubble);
				ImGui::Checkbox("Buttons", &bButtons);
				ImGui::Checkbox("Integrate", &bIntegrate);
				ImGui::Checkbox("Blink", &bBlink);
				ImGui::Checkbox("Debug", &bDebug);
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

		drawImGui_TextInput();
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
			if (!bGui_Headers) AddHeaderHeight();

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
	if (key == 'b') bGui_Bg = !bGui_Bg;
	if (key == 'r') bGui_ResizePin = !bGui_ResizePin;
	if (key == 'l') bGui_LockMove = !bGui_LockMove;
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ofxImGuiSurfing::saveGroup(g);
}
