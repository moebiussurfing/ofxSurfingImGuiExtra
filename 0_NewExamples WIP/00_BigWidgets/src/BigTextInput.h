#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "imgui_stdlib.h"

#define RATIO_WIDGETS_FONTS 0.25f

class BigTextInput
{
public:
	ofParameter<bool> bGui_Global{ "BigTextInput", true };//TODO:
	ofParameter<bool> bGui_Config{ "Config", true };
	ofParameter<bool> bGui{ "TextInput", true };
	ofParameterGroup params{ "TextInputBubble" };

private:
	ofParameterGroup g{ "BigTextInput" };
	ofParameter<bool> bGui_Headers{ "Headers", true };
	ofParameter<bool> bGui_Bg{ "Bg", true };
	ofParameter<bool> bGui_ResizePin{ "Resizer", true };
	ofParameter<bool> bGui_LockMove{ "Lock", false };

	ofParameter<bool> bLabel{ "Label", false };//TODO:
	ofParameter<int> szFont{ "Font Size", 0, 0, 3 };
	ofParameter<float> rounded{ "Rounded", 0, 0, 1 };
	ofParameter<ofColor> colorBubble{ "color Bubble", ofColor::red, ofColor(), ofColor() };
	ofParameter<float> padxBubble{ "padxBubble", 0.f, 0, 1 };
	ofParameter<float> padyBubble{ "padyBubble", 0.f, 0, 1 };
	ofParameter<float> padxText{ "padxText", 0.f, 0, 1 };
	ofParameter<float> padxTextR{ "padxTextR", 1.f, 0, 1 };
	ofParameter<float> padyText{ "padyText", 0.f, -1, 1 };
	ofParameter<int> typeInput{ "Type", 0, 0, 2 };
	ofParameter<string> typeInputName{ "TypeName" ,"" };
	ofParameter<void> vResetBubble{ "Reset" };
	ofEventListener eResetBubble;
	ofEventListener eTypeInput;
	bool bResetBubble = 0;
	vector<string> typeInputNames{ "InputText","InputTextWithHint","InputTextMultiline" };

	bool bBlink = 1;//text bubble
	bool bIntegrate = 1;
	bool bButtons = 0;
	//bool bDebug = 0;
	ofParameter<bool> bDebug{ "Debug", false };
	ofEventListener eDebug;

	//ofParameter<string> textA{ "TextA","" };
	//ofParameter<string> textB{ "TextB","" };
	//ofParameter<string> textC{ "TextC","" };
	string strHint = "Prompt";
public:
	void setHint(string s) { strHint = s; };

public:
	BigTextInput() {
		setup();
	};

	~BigTextInput() {
		exit();
	};

private:
	void setup() {
		typeInputName.setSerializable(false);

		g.add(bGui);
		g.add(bGui_Config);
		g.add(bGui_Headers);
		g.add(bGui_Bg);
		g.add(bGui_ResizePin);
		g.add(bGui_LockMove);

		params.add(rounded);
		params.add(colorBubble);
		params.add(szFont);
		params.add(bLabel);
		params.add(padxBubble, padyBubble);
		params.add(padxText);
		params.add(padxTextR);
		params.add(padyText);
		params.add(typeInput);
		params.add(typeInputName);
		params.add(vResetBubble);
		g.add(params);

		eResetBubble = vResetBubble.newListener([this]() {
			bResetBubble = 1;
			});

		eTypeInput = typeInput.newListener([this](int& value) {
			switch (typeInput.get())
			{
			case 0: typeInputName = typeInputNames[0]; break;
			case 1: typeInputName = typeInputNames[1]; break;
			case 2: typeInputName = typeInputNames[2]; break;
			default: typeInputName = "unknown"; break;
			}
			});

		eDebug = bDebug.newListener([this](bool& b) {
			bGui_Headers = bDebug;
			bGui_ResizePin = bDebug;
			bGui_Bg = bDebug;
			bIntegrate = !bDebug;
			});

		//--

		ofxImGuiSurfing::loadGroup(g);
	};

	void exit() {
		ofxImGuiSurfing::saveGroup(g);
	};

public:
	void draw(ofxSurfingGui& ui) {
		static bool b = 0;
		if (!b) {
			b = 1;
			ui.AddStyle(typeInputName, OFX_IM_TEXT_DISPLAY);
			ui.AddStyle(vResetBubble, OFX_IM_BUTTON_BIG);
		}

		drawImGui_Config(ui);
		drawImGui_TextInput(ui);
	};

private:
	void drawImGui_Config(ofxSurfingGui& ui)
	{
		if (!bGui_Config) return;

		if (ui.BeginWindow(bGui_Config)) {

			if (ui.isMaximized()) {
				ui.AddLabelBig("Window");
				ui.Add(bGui_Headers, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_Bg, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_ResizePin, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_LockMove, OFX_IM_TOGGLE_ROUNDED);
				ui.AddSpacingBigSeparated();
			}

			ui.AddLabelBig("TextInput");
			ui.Add(bGui);
			ui.AddGroup(params);
			ui.AddSpacingSeparated();

			ui.Add(bDebug, OFX_IM_TOGGLE_BORDER_BLINK);
			if (ui.isMaximized()) {
				ImGui::Checkbox("Integrate", &bIntegrate);
				ImGui::Checkbox("Buttons", &bButtons);
				ImGui::Checkbox("Blink", &bBlink);
				//ImGui::Checkbox("Debug", &bDebug);
			}
			//ui.AddSpacingBigSeparated();

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
	};

	void drawImGui_TextInput(ofxSurfingGui& ui)
	{
		if (!bGui) return;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(50, 50));
		{
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			window_flags |= ImGuiWindowFlags_NoScrollbar;
			if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
			if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
			if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
			if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

			static float x, y, w, h;

			ImVec2 size_min = ImVec2(700, 100);
			ImVec2 size_max = ImVec2(FLT_MAX, FLT_MAX);
			ImGui::SetNextWindowSizeConstraints(size_min, size_max);

			//--

			if (bResetBubble) {
				bResetBubble = 0;
				doResetTextInput();
			}

			if (ui.BeginWindow(bGui, window_flags))
			{
				//TODO: remove pad
				//RemoveHeaderHeight();
				//if (!bGui_Headers) ofxImGuiSurfing::AddSpacingY(ImGui::GetStyle().WindowPadding.y);

				if (!bGui_Headers) AddHeaderHeight();

				static string text = "";
				const char* label = "Prompt";
				const char* hint = strHint.c_str();
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
				float _wBb;
				float _padr;

				w = ImGui::GetContentRegionAvail().x;
				h = ImGui::GetContentRegionAvail().y;

				ui.PushFontStyle(SurfingFontTypes(szFont.get()));
				{
					{
						ImDrawList* draw_list = ImGui::GetWindowDrawList();

						ImVec2 p = ImGui::GetCursorScreenPos();
						ImDrawFlags flags = ImDrawFlags_None;

						float pxBubble = padxBubble * (w * 0.25f);
						float pyBubble = padyBubble * (h * 0.25f);

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

						xx += padxText * (w * 0.25f);
						//xx += _offsetx;
						xx += pxBubble;

						yy += h / 2;
						yy += padyText * (h * 0.25f);
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
						_wBb = w;
						_wBb -= padxText * (w * 0.25f);

						_padr = ofMap(padxTextR, 1, 0, 0, w * 0.25);
						_wBb -= _padr;
						//_wBb -= pxBubble/2;

						//--

						ImGui::SetCursorPosX(xx);
						ImGui::SetCursorPosY(yy);

						//--

						if (!bLabel) label = "##label";
						bool _bBlink = bBlink && (text == "");

						PushItemWidth(_wBb);
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
								ui.AddSpacingY(-_hh * 0.25);
								ImVec2 _sz = ImVec2(_wBb, _hh);
								ImGuiInputTextFlags _flags = ImGuiInputTextFlags_None;
								//_flags |= ImGuiInputTextFlags_CallbackResize;
								isChanged = ImGui::InputTextMultiline(label, &text, _sz, _flags, callback, user_data);
							}

							if (bIntegrate) ImGui::PopStyleColor(2);
							if (_bBlink) ui.EndBlinkTextDisabled();
						}
						PopItemWidth();
					}
					//ui.popStyleFont();

					//--

					// Button
					if (!bButtons)
					{
						string s = "Send";
						ImVec2 szButton(30 + ImGui::CalcTextSize(s.c_str()).x, ui.getWidgetsHeightUnit());
						ImGui::SetCursorPosX(xx + _wBb + 0.2 * szButton.x);
						ImGui::SetCursorPosY(yy);
						ImVec4 c = ImGui::GetStyle().Colors[ImGuiCol_Text];
						//ImVec4 _c = ImGui::GetStyle().Colors[ImGuiCol_TextDisabled];
						ImVec4 _c = ImVec4(c.x, c.y, c.z, c.w * 0.6);
						ImGui::PushStyleColor(ImGuiCol_Text, _c);
						if (ImGui::Button(s.c_str(), szButton))
						{
							ui.AddToLog(text, OF_LOG_WARNING);
							//isChanged = true;
							text = "";
						};
						ImGui::PopStyleColor();
					}
				}
				ui.PopFontStyle();

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
	};

	void doResetTextInput()
	{
		rounded = 1;
		padxBubble = padyBubble = 0;
		padxText = 0.3;
		padxTextR = 0.2;
		typeInput = 1;
		szFont = 2;
		colorBubble = ofColor(0, 100);

		//--

		float xx, yy, ww, hh, pad;

		pad = 120;//to borders
		hh = 175;//height

		ww = ofGetWidth() - 2 * pad;//width
		xx = pad;
		yy = ofGetHeight() / 2 - hh / 2;//v centered

		ImGuiCond flagsCond = ImGuiCond_None;
		flagsCond |= ImGuiCond_FirstUseEver;
		flagsCond = ImGuiCond_None;

		ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
		ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);
	};

};
