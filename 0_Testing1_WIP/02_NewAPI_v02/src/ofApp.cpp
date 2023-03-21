#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowPosition(-1920, 25);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		// Initialize
		{
			static bool bFirstFrame = true;
			if (bFirstFrame) {
				bFirstFrame = false;
				//theme.setup();
				ImGui::StyleColorsDark();
			}
		}

		drawNewAPI();

		ui.DrawWindowAdvanced();

		if (ui.BeginWindow("TOGGLES"))
		{
			ui.Add(ui.bAdvanced, OFX_IM_TOGGLE_ROUNDED_MINI);
			ui.AddSpacingBigSeparated();

			//--

			// Label
			static int f = 2;
			if (ui.AddButton("CHANGE FONT SIZE", OFX_IM_BUTTON_BIG))
			{
				f = (++f) % (int)OFX_IM_FONT_AMOUNT;
				ofLogNotice("ofxImGuiSurfing") << "Font#" << f;
			}
			ui.AddLabel("LEGACY ROUNDED TOGGLES", SurfingFontTypes(f));

			ui.AddSpacing();

			ui.Add(b1, OFX_IM_TOGGLE_ROUNDED_BIG);
			ui.Add(b2, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
			ui.Add(b3, OFX_IM_TOGGLE_ROUNDED_SMALL);
			ui.Add(b4, OFX_IM_TOGGLE_ROUNDED_MINI);

			ui.AddSpacingBigSeparated();

			//--

			/*
			ui.AddSpacingBigSeparated();
			float w = ImGui::GetContentRegionAvail().x;
			float h = ImGui::GetFrameHeight(); // single unit height
			float hh = 2 * h; // double height
			float spx = ImGui::GetStyle().ItemSpacing.x; // spacing between two widgets
			float _spx;
			// Calculate spacing for each line:
			// _spx = (spx * (amount - 1)) / amount;  // amount widgets per line
			_spx = (spx * (2 - 1)) / 2;
			ImGui::Button("B1", ImVec2(w * 0.25 - _spx, hh));
			ImGui::SameLine();
			ImGui::Button("B2", ImVec2(w * 0.75 - _spx, hh));
			_spx = (spx * (3 - 1)) / 3;
			ImGui::Button("B3", ImVec2(w * 1 / 3.f - _spx, h));
			ImGui::SameLine();
			ImGui::Button("B4", ImVec2(w * 1 / 3.f - _spx, h));
			ImGui::SameLine();
			ImGui::Button("B5", ImVec2(w * 1 / 3.f - _spx, h));
			*/

			//--

			/*
			//TODO:
			// Gradient Colored buttons
			ui.AddSpacingHuge();
			ofxImGuiSurfing::ColoredButtonV1("Hello", ImVec2(-FLT_MIN, 0.0f), IM_COL32(255, 255, 255, 255), IM_COL32(200, 60, 60, 255), IM_COL32(180, 40, 90, 255));

			ofxImGuiSurfing::ColoredButtonV1("You", ImVec2(-FLT_MIN, 50), IM_COL32(255, 255, 255, 255), IM_COL32(50, 220, 60, 255), IM_COL32(69, 150, 255, 255));
			*/

			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawNewAPI()
{
	if (ui.BeginWindow("NEW API"))
	{
		ui.AddLabel("TESTING NEW API v0.2", OFX_IM_FONT_HUGE);

		ui.AddSpacingBigSeparated();

		static ofParameter<bool> _b1{ "B1",true };
		static ofParameter<bool> _b2{ "B2",false };
		static ofParameter<bool> _b3{ "B3",false };
		static ofParameter<bool> _b4{ "B4",false };
		SurfingGuiTypes sb = OFX_IM_TOGGLE_BIG;
		ui.Add(_b1, sb, 4, 0.5f, true);
		ui.Add(_b2, sb, 4, 0.5f / 3, true);
		ui.Add(_b3, sb, 4, 0.5f / 3, true);
		ui.Add(_b4, sb, 4, 0.5f / 3);

		//ImVec2 sz(100, 100);
		//ui.Add(_b4, OFX_IM_TOGGLE, sz);

		ui.AddSpacingBigSeparated();

		static ofParameter<float> v1{ "Gain",0.5, 0,1 };
		static ofParameter<float> v2{ "Release",0, -1,1 };
		static ofParameter<float> v3{ "Smooth",0, 0,1 };
		SurfingGuiTypes sf = _b1 ? OFX_IM_VSLIDER : OFX_IM_KNOB_STEPPEDKNOB;
		float wf = 0.5f + 0.5f / 3;

		//-

		// a.
		ui.Add(v1, sf, 2, wf, true);
		ui.SameLine();
		ui.Add(v2, sf, 2, 1 - wf, false);

		//-

		//// b.
		//float spcx = ImGui::GetStyle().ItemSpacing.x;
		//float w100 = ImGui::GetContentRegionAvail().x;
		//float w = ofxImGuiSurfing::getWidgetsWidth(1) - spcx;
		//float w1 = w * 0.3f;
		//float w2 = w * 0.7f;

		//ImVec2 sz;
		//float h = 50;
		////float h2 = 150;

		//ImGui::Columns(2, "##tb1", 1);

		////ImGui::SetCursorPosX(w100 * 0.3f);
		////ImGui::SetColumnWidth(0, w100 * 0.4f);
		////ImGui::SetColumnWidth(1, w100 * 0.6f);

		////sz = ImVec2(ImGui::GetContentRegionAvail().x, h);
		//ui.Add(v1, sf, 2, 0.4f);

		//ImGui::NextColumn();

		////sz = ImVec2(ImGui::GetContentRegionAvail().x, h);
		//ui.Add(v2, sf, 2, 0.6f);

		//ImGui::Columns(1);

		////-

		//ui.Add(v3, OFX_IM_VSLIDER);

		//--

		//{
		//	ui.AddSpacingBigSeparated();

		//	ui.AddLabelBig("IMPROVE LAYOUT ENGINE WITH TABLES / COLUMNS AND AUTORESIZE WIDGETS WITH COLUMN DIVIDERS DRAGGING");
		//	
		//	ui.AddSpacingBig();

		//	float spcx = ImGui::GetStyle().ItemSpacing.x;
		//	float w100 = ImGui::GetContentRegionAvail().x;
		//	float w = ofxImGuiSurfing::getWidgetsWidth(1) - spcx;
		//	float w1 = w * 0.3f;
		//	float w2 = w * 0.7f;

		//	ImVec2 sz;
		//	float h = 50;
		//	float h2 = 150;

		//	ImGui::Columns(2, "##table1");

		//	//ImGui::SetCursorPosX(w100 * 0.3f);
		//	//ImGui::SetColumnWidth(0, w100 * 0.3f);
		//	//ImGui::SetColumnWidth(1, w100 * 0.7f);

		//	sz = ImVec2(ImGui::GetContentRegionAvail().x, h);
		//	ImGui::Button("but1", sz);

		//	ImGui::NextColumn();

		//	sz = ImVec2(ImGui::GetContentRegionAvail().x, h);
		//	ImGui::Button("but2", sz);

		//	ImGui::Columns(1);
		//	
		//	ui.AddSpacingBig();

		//	//--

		//	ImGui::Columns(2, "##table2");

		//	static float wc = (ImGui::GetWindowWidth() - spcx);
		//	//ImGui::SetColumnWidth(0, wc * 0.4f);
		//	//wc = ImGui::GetColumnWidth();//allow edit
		//	//ImGui::SetColumnWidth(1, 100.0f);

		//	static float tmpRef1 = 1;
		//	static float tmpRef2 = 1;

		//	sz = ImVec2(ImGui::GetContentRegionAvail().x, h2);
		//	ImGui::VSliderFloat("v1", sz, &tmpRef1, 0, 1);

		//	ImGui::NextColumn();

		//	sz = ImVec2(ImGui::GetContentRegionAvail().x, h2);
		//	ImGui::VSliderFloat("v2", sz, &tmpRef2, 0, 1);

		//	ImGui::Columns(1);

		//	ui.AddSpacingBigSeparated();
		//}

		//--

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == OF_KEY_TAB) {
		iTheme = ++iTheme % 11;
		if (iTheme == 0) theme.setup();//default
		else if (iTheme == 1) ImGui::StyleColorsLight();
		else if (iTheme == 2) ImGui::StyleColorsClassic();
		else if (iTheme == 3) ImGui::StyleColorsDark();
		else if (iTheme == 4) ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
		else if (iTheme == 5) ofxImGuiSurfing::ImGui_ThemeOlekristensen();
		else if (iTheme == 6) ofxImGuiSurfing::ImGui_ThemeSequentity();
		else if (iTheme == 7) ofxImGuiSurfing::ImGui_ThemeT3();
		else if (iTheme == 8) ofxImGuiSurfing::ImGui_ThemeYave();
		else if (iTheme == 9) ofxImGuiSurfing::ImGui_ThemeModernDark();
		else if (iTheme == 10) ofxImGuiSurfing::ImGui_ThemeFlatDryWineGreen();
	}

	if (key == '0') theme.setup();//default
	if (key == '1') ImGui::StyleColorsLight();
	if (key == '2') ImGui::StyleColorsClassic();
	if (key == '3') ImGui::StyleColorsDark();
	if (key == '4') ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	if (key == '5') ofxImGuiSurfing::ImGui_ThemeOlekristensen();
	if (key == '6') ofxImGuiSurfing::ImGui_ThemeSequentity();
	if (key == '7') ofxImGuiSurfing::ImGui_ThemeT3();
	if (key == '8') ofxImGuiSurfing::ImGui_ThemeYave();
	if (key == '9') ofxImGuiSurfing::ImGui_ThemeModernDark();
	if (key == '-') ofxImGuiSurfing::ImGui_ThemeFlatDryWineGreen();
}