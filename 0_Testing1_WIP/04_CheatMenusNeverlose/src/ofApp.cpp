#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	// parameters
	params.setName("paramsGroup");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested
	params.add(bPrevious.set("<", false));
	params.add(bNext.set(">", false));
	params.add(bEnable1.set("Enable1", false));
	params.add(bEnable2.set("Enable2", false));
	params.add(bEnable3.set("Enable3", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params2.add(params3);
	params.add(params2);

	ui.setup();
	ui.startup();

	setupFonts();
}

//--------------------------------------------------------------
void ofApp::setupFonts()
{
	ofSetLogLevel(OF_LOG_VERBOSE);

	ImGui::StyleColorsDark();

	// Add fontawesome fonts by merging new glyphs
	ImFontConfig config;
	config.MergeMode = true;
	config.PixelSnapH = true;//?
	//config.GlyphMinAdvanceX = 13.0f;//to make the icon monospaced

	static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

	auto gui = ui.getImGuiPtr();
	
	string s = ofToDataPath("assets/fonts/telegrama_render.otf");
	customFont = gui->addFont(s, 18.f, &config, icon_ranges);
	customFont0 = gui->addFontFromMemory(museo500_binary, museo500_size, 14);
	customFont1 = gui->addFontFromMemory(&font_awesome_binary, font_awesome_size, 13, &config, icon_ranges);
	customFont2 = gui->addFontFromMemory(museo900_binary, museo900_size, 28);
}

//--------------------------------------------------------------
void ofApp::exit()
{
	//TODO: fix exit crash

	//ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->Clear();

	delete customFont;
	delete customFont0;
	delete customFont1;
	delete customFont2;

	customFont = nullptr;
	customFont0 = nullptr;
	customFont1 = nullptr;
	customFont2 = nullptr;
}

//--------------------------------------------------------------
void ofApp::draw()
{
#if 0
	static bool b = 0;
	if (!b) {
		b = 1;
		initNeverlose();
	}
#endif

	ui.Begin();
	{
		ImGui::PushFont(customFont1);
		drawImGuiNeverlose();
		ImGui::PopFont();

		//IMGUI_SUGAR__WINDOWS_CONSTRAINTS;
		//if (ui.BeginWindow(bGui))
		//{
		//	ui.AddLabel("Hi");
		//	ui.EndWindow();
		//}

		ui.DrawDebugImGuiContextsWindows();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') {
		bGui = !bGui;
	}
}