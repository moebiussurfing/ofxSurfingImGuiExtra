#include "ofApp.h"
#include "IconsForkAwesome.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);

	// Init
	{
		bool _autoDraw = true;
		ImGuiConfigFlags _customFlags = ImGuiConfigFlags_None;
		bool _restoreGuiState = true;
		bool _showImGuiMouseCursor = false;
		gui.setup(nullptr, _autoDraw, _customFlags, _restoreGuiState, _showImGuiMouseCursor);
	}

	//--

	ImGuiIO* io = &ImGui::GetIO();
	auto normalCharRanges = ImGui::GetIO().Fonts->GetGlyphRangesDefault();

	//--

	// This wiill not required on ofxSurinfImGuim bc "substrate" fonts are already loaded!
	ImFont* f1 = nullptr;
	{
		//string p = "tahoma.ttf";
		string p = "JetBrainsMono-Bold.ttf";
		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;
		f1 = gui.addFont(p, 16.f, &font_cfg, normalCharRanges);

		//font_cfg.MergeMode = true;
		//font_cfg.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
		//static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		//f1 = gui.addFont(p, 16.f, &font_cfg, icon_ranges);
	}

	//--

	//// Add font-awesome fonts by merging new glyphs
	//ImFontConfig font_cfg2;
	//font_cfg2.MergeMode = true;
	//font_cfg2.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
	//static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	//gui.addFont("fa-regular-400.ttf", 18.f, &font_cfg2, icon_ranges);

	//--

	// This seams to fix working for notify...
	// as unlocks some font-awesome feature.
	// That's bc we can't call without getting crash:
	 //ImGui::MergeIconsWithLatestFont(16.f, false);

	ImFont* f2 = nullptr;
	{
		// this size wil affect to font-awesome icons but notifier icons too!
		//float sz = 30.f;
		float sz = 14.f;

		ImFontConfig font_cfg;
		font_cfg.MergeMode = true;
		font_cfg.GlyphMinAdvanceX = sz; // Use if you want to make the icon monospaced
		static const ImWchar icon_ranges2[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		f2 = gui.addFont("forkawesome-webfont.ttf", sz, &font_cfg, icon_ranges2);
	}

	//--

	notify.setup(gui);

	//--

	//// That's the same that internally does MergeIconsWithLatestFont(
	////ImGui::MergeIconsWithLatestFont(16.f, false);
	//{
	//	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	//	float font_size = 50.f;
	//	ImFontConfig icons_config;
	//	icons_config.MergeMode = true;
	//	icons_config.PixelSnapH = true;
	//	icons_config.FontDataOwnedByAtlas = false;
	//	f3 = gui.addFont((void*)fa_solid_900, sizeof(fa_solid_900), font_size, &icons_config, icons_ranges);
	//}

	//--

	gui.setDefaultFont(f1);
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {

	gui.begin();

	ImGui::Begin("Notifier");
	ImGui::Spacing();

	ImGui::Text("Hello FontAwesome");
	ImGui::Spacing();

	// Fontawesome
	//ImGui::CollapsingHeader("Fontawesome icons", ImGuiTreeNodeFlags_Leaf);
	//ImGui::PushFont(customFont);
	//ImGui::Text("FontAweome is loaded too ! %s", ICON_FA_THUMBS_UP);
	//ImGui::Button(ICON_FA_TRASH_ALT " Trash it !");
	//ImGui::SameLine();
	//ImGui::Button(ICON_FA_ANGRY " Mad button !");
	//ImGui::SameLine();
	//ImGui::Button(ICON_FA_BELL " Ring it !");
	//ImGui::SameLine();
	
	ImVec2 sz = ImVec2(40, 40);

	//ImGui::PushFont(customFont);
	ImGui::Spacing();
	ImGui::Button(ICON_FK_ARROW_LEFT, sz);
	ImGui::SameLine();
	ImGui::Button(ICON_FK_ARROW_RIGHT, sz);
	ImGui::SameLine();
	if(ImGui::Button(ICON_FK_SEARCH_PLUS, sz)){
			string t = "Reload settings.";
			string s = "TAKE CARE!";
			notify.print(s, t, ImGuiToastType_Warning);
		};
	ImGui::Spacing();
	//ImGui::PopFont();

	//--

	{
		ImGui::Dummy(ImVec2(0, 10));
		static bool b = false;
		ImGui::Checkbox("Editor", &b);
		if (b) ImGui::ShowStyleEditor();
		else ImGui::ShowFontSelector("Default font");
	}

	//--

	{
		ImGui::Dummy(ImVec2(0, 10));
		static bool b = false;
		ImGui::Checkbox("Tester", &b);
		if (b) notify.drawTester();
	}

	ImGui::PushFont(f3);
	notify.drawRender();
	ImGui::PopFont();

	//--

	ImGui::End(); // close window

	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == '1') {
		string t = "SUCCESS!";
		string s = "Hello World! This is an info!";
		notify.print(s, t, ImGuiToastType_Success);
	}

	if (key == '2') {
		string t = "Repeat process";
		string s = "Wrong file!";
		notify.print(s, t, ImGuiToastType_Error);
	}

	if (key == '3') {
		string t = "";
		string s = "Running...";
		s += "\nCurrent frame number \nis " + ofToString(ofGetFrameNum(), 0);
		notify.print(s, t, ImGuiToastType_None);
	}

	if (key == '4') {
		string t = "";
		string s = "Hello info";
		notify.print(s, t, ImGuiToastType_Info);
	}

	if (key == '5') {
		string t = "Reload settings.";
		string s = "TAKE CARE!";
		notify.print(s, t, ImGuiToastType_Warning);
	}
}