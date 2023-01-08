#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//ui.setEnablebDrawInFront(false);

	ui.setup();

	auto& gui = ui.getGui();

	//--

	{
		auto normalCharRanges = ImGui::GetIO().Fonts->GetGlyphRangesDefault();

		customFont = gui.addFont("Roboto-Medium.ttf", 16.f, nullptr, normalCharRanges);

		// Add fontawesome fonts by merging new glyphs
		ImFontConfig config;
		config.MergeMode = true;
		config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		gui.addFont("fa-regular-400.ttf", 18.f, &config, icon_ranges);
	}

	//--

	//surfNotify::init();

	//TODO:\
	//WIP
	if (0) 
	{
		ImGuiIO* io = &ImGui::GetIO();

		// We must load a font before loading notify, because we cannot merge font-awesome with default font
		// FontDataOwnedByAtlas = false is required (also in ImGui::MergeIconsWithLatestFont())
		// because otherwise ImGui will call free() while freeing resources which will lead into a crash
		// since tahoma is defined as readonly and wasn't allocated with malloc()
		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;

		io->Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);
		//ImFont* font = io->Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);

		// Initialize notify
		ImGui::MergeIconsWithLatestFont(16.f, false);

		io->Fonts->Build();

		//if (io->Fonts->Fonts.size() > 0) {
			//io->Fonts->Build();
		//	//if (engine.updateFontsTexture()) {
		//	//	if (_setAsDefaultFont) setDefaultFont(font);
		//	//	return font;
		//	//}
		//	//else return nullptr;
		//}
		//else {
		//	//return nullptr;
		//}

		//ui.setDefaultFont();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		//// init
		//static bool b = false;
		//if (!b) {
		//	b = true;
		//	surfNotify::init();
		//}

		//--

		//ui.pushStyleFont(0);

		if (ui.BeginWindow(bGui))
		{
			ui.Add(ui.bAutoResize);

			// Fontawesome
			ImGui::Dummy(ImVec2(0, 10));
			ImGui::CollapsingHeader("Fontawesome icons", ImGuiTreeNodeFlags_Leaf);
			ImGui::PushFont(customFont);
			ImGui::Text("FontAweome is loaded too ! %s", ICON_FA_THUMBS_UP);
			ImGui::Button(ICON_FA_TRASH_ALT " Trash it !");
			ImGui::SameLine();
			ImGui::Button(ICON_FA_ANGRY " Mad button !");
			ImGui::SameLine();
			ImGui::Button(ICON_FA_BELL " Ring it !");
			ImGui::PopFont();
			ImGui::Dummy(ImVec2(0, 10));

			ui.EndWindow();
		}

		//ui.popStyleFont();


		//ui.setNextWindowAfterWindowNamed(bGui);
		//ui.setNextWindowOnViewport(ImGuiCond_Always);
		surfNotify::render();
	}
	ui.End();

	{
		ofPushStyle();
		ofSetColor(ofColor(ofColor::turquoise, 200));
		ofSetCircleResolution(300);
		ofFill();
		glm::vec2 p(ofGetWidth() / 2, ofGetHeight() / 2);
		float r = 0.7 * MIN(ofGetWidth() / 2, ofGetHeight() / 2);
		ofDrawCircle(p, r);
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') {
		bGui = !bGui;
	}
	
	if (key == 'b') {
		ui.setToggleAutoDraw();
	}

	//--

	//// Theme
	//if (key == '1') {
	//	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	//}
	//if (key == '2') {
	//	ofxImGuiSurfing::ImGui_Xemu();
	//}
	//if (key == '3') {
	//	ofxImGuiSurfing::ImGui_ThemeYave();
	//}

	//// Queue a notitification
	//if (key == ' ') 
	//{
	//	stringstream ss;
	//	ss << textAtribute[rand() % 5] << textObject[rand() % 4] << textVerb[rand() % 6] << textSubject[rand() % 5];
	//	string str(ss.str());
	//	notification_manager.QueueNotification(str.c_str());
	//}

	//// Queue an error
	//if (key == OF_KEY_BACKSPACE) 
	//{
	//	stringstream ss2;
	//	ss2 << "We wanted to have " << 2 << " more pints, but it was past " << 11 << " o'clock." << endl;
	//	string str2(ss2.str());
	//	notification_manager.QueueError(str2.c_str());
	//}

	//// Queue a notitification
	//if (key == OF_KEY_RETURN) 
	//{
	//	stringstream ss;
	//	ss << textAtribute[rand() % 5] << textObject[rand() % 4] << textVerb[rand() % 6] << textSubject[rand() % 5];
	//	string str(ss.str());
	//	notifier.addNotification(str);
	//}
}