#include "exampleSurfingGradient.h"
//--------------------------------------------------------------
exampleSurfingGradient::exampleSurfingGradient() {
	//ofAddListener(ofEvents().update, this, &exampleSurfingGradient::update);
	//ofAddListener(ofEvents().draw, this, &exampleSurfingGradient::draw);
	//ofAddListener(ofEvents().keyPressed, this, &exampleSurfingGradient::keyPressed);

	setup();
}

//--------------------------------------------------------------
exampleSurfingGradient::~exampleSurfingGradient() {
	//ofRemoveListener(ofEvents().update, this, &exampleSurfingGradient::update);
	//ofRemoveListener(ofEvents().draw, this, &exampleSurfingGradient::draw);
	//ofRemoveListener(ofEvents().keyPressed, this, &exampleSurfingGradient::keyPressed);

	//exit();
}

//--------------------------------------------------------------
void exampleSurfingGradient::setup() {
	//params.setName("params");

	indexPreset.set("Preset", 0, 0, 8);

	listenerIndex = indexPreset.newListener([this](int &i) {
		ofLogNotice("exampleSurfingGradient::loadGradient: ") << i;
		loadGradient(indexPreset);
	});

	//--

	// Gradient
	gradient.getMarks().clear();
	gradient.addMark(0.0f, ImColor(ofColor(0)));
	gradient.addMark(1.0f, ImColor(ofColor(255)));
}

////--------------------------------------------------------------
//void exampleSurfingGradient::update(ofEventArgs & args)
//{
//}
//
////--------------------------------------------------------------
//void exampleSurfingGradient::update() {
//}
//
////--------------------------------------------------------------
//void exampleSurfingGradient::draw(ofEventArgs & args)
//{
//}
//
////--------------------------------------------------------------
//void exampleSurfingGradient::draw() {
//}

//--------------------------------------------------------------
void exampleSurfingGradient::drawImGui()
{
	static bool p_open = true;
	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	flags += ImGuiWindowFlags_AlwaysAutoResize;

	if (p_open) {
		ImVec2 size_min = ImVec2(230, -1);
		ImVec2 size_max = ImVec2(230, -1);
		ImGui::SetNextWindowSizeConstraints(size_min, size_max);
	}

	ImGui::Begin("Gradient Editor", &p_open, flags);
	{
		drawWidgets();
	}
	ImGui::End();
}

//--------------------------------------------------------------
void exampleSurfingGradient::drawWidgets()
{
	// A Gradient color tool

		float _h = ofxImGuiSurfing::getWidgetsHeightUnit();
		float _w1= ofxImGuiSurfing::getWidgetsWidth(1); // 1 widget full width
		float _w2 = ofxImGuiSurfing::getWidgetsWidth(2); // 2 widgets half width
		float _w3 = ofxImGuiSurfing::getWidgetsWidth(3); // 3 widgets per row

		//--

		static bool bEditGrad = false;
		if (ImGui::GradientButton(&gradient))
		{
			// Set show editor flag to true/false
			bEditGrad = !bEditGrad;
		}

		// Editor
		if (bEditGrad)
		{
			static ImGradientMark* draggingMark = nullptr;
			static ImGradientMark* selectedMark = nullptr;

			bool updated = ImGui::GradientEditor(&gradient, draggingMark, selectedMark);
		}

		//--

		ImGui::Spacing();

		// Level selector
		ImGui::PushItemWidth(_w1);
		ImGui::Text("Select Percent");
		if (ImGui::SliderFloat("##s", &prcGrad, 0, 1))
		{
			// Get a color
			float _color[3];
			gradient.getColorAt(prcGrad, _color); // position from 0 to 1
			color.set(_color[0], _color[1], _color[2], 1.0f);
		}
		ImGui::PopItemWidth();

		ImGui::Spacing();
}

////--------------------------------------------------------------
//void exampleSurfingGradient::keyPressed(ofKeyEventArgs &eventArgs)
//{
//	const int key = eventArgs.key;
//
//	// modifiers
//	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
//	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
//	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
//	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);
//
//	ofLogNotice("exampleSurfingGradient::keyPressed") << " : " << key;
//
//	//--
//
//	if (0) {}
//
//	else if (key == 'G' && !mod_ALT)
//	{
//	}
//}

////--------------------------------------------------------------
//void exampleSurfingGradient::exit() {
//}

//--------------------------------------------------------------
void exampleSurfingGradient::loadGradient(int index) {

	int i = index;

	if (i == 0) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::blue));
		gradient.addMark(0.3f, ImColor(ofColor::blueViolet));
		gradient.addMark(0.6f, ImColor(ofColor::yellow));
		gradient.addMark(1.0f, ImColor(ofColor::orangeRed));
	}
	else if (i == 1) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(0xA0, 0x79, 0x3D));
		//gradient.addMark(0.2f, ImColor(0xAA, 0x83, 0x47));
		gradient.addMark(0.3f, ImColor(0xB4, 0x8D, 0x51));
		//gradient.addMark(0.4f, ImColor(0xBE, 0x97, 0x5B));
		//gradient.addMark(0.6f, ImColor(0xC8, 0xA1, 0x65));
		gradient.addMark(0.7f, ImColor(0xD2, 0xAB, 0x6F));
		gradient.addMark(0.8f, ImColor(0xDC, 0xB5, 0x79));
		gradient.addMark(1.0f, ImColor(0xE6, 0xBF, 0x83));
	}
	else if (i == 2) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::red));
		gradient.addMark(0.3f, ImColor(ofColor::yellowGreen));
		gradient.addMark(1.0f, ImColor(ofColor::green));
	}
	else if (i == 3) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::blueSteel));
		gradient.addMark(0.3f, ImColor(ofColor::blueViolet));
		gradient.addMark(0.7f, ImColor(ofColor::cornflowerBlue));
		gradient.addMark(1.0f, ImColor(ofColor::cadetBlue));
	}
	else if (i == 4) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::yellow));
		gradient.addMark(0.5f, ImColor(ofColor::lightYellow));
		gradient.addMark(1.0f, ImColor(ofColor::lightGoldenRodYellow));
	}
	else if (i == 5) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::red));
		gradient.addMark(0.5f, ImColor(ofColor::orangeRed));
		gradient.addMark(1.0f, ImColor(ofColor::blueViolet));
	}
	else if (i == 6) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::lightYellow));
		gradient.addMark(0.5f, ImColor(ofColor::floralWhite));
		gradient.addMark(1.0f, ImColor(ofColor::whiteSmoke));
	}

	// repeat some if index is too big. just for testing..
	else {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::paleVioletRed));
		gradient.addMark(0.3f, ImColor(ofColor::red));
		gradient.addMark(0.7f, ImColor(ofColor::darkRed));
		gradient.addMark(1.0f, ImColor(ofColor::black));
	}

	// refresh
	float _color[3];
	gradient.getColorAt(prcGrad, _color); // position from 0 to 1
	color.set(_color[0], _color[1], _color[2], 1.0f);
}