#include "ofApp.h"

#define MAX_CAMERA_DISTANCE 500.0f

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	//--

	// Parameters

	bEnable1.set("bEnable1", false);
	bEnable2.set("bEnable2", false);
	bEnable3.set("bEnable3", false);
	bEnable4.set("bEnable4", false);

	bPrevious.set("<", false);
	bNext.set(">", false);

	value.set("value", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
	valueMin.set("valueMin", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
	valueMax.set("valueMax", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);

	pos_1.set("pos_1", glm::vec3(0.f), glm::vec3(-MAX_CAMERA_DISTANCE), glm::vec3(MAX_CAMERA_DISTANCE));
	rot_1.set("rot_1", glm::vec3(0.f), glm::vec3(-2.f*MAX_CAMERA_DISTANCE), glm::vec3(2.f*MAX_CAMERA_DISTANCE));

	lineWidth2.set("lineWidth2", 0.5, 0, 1);
	separation2.set("separation2", 50, 1, 100);
	shapeType2.set("shapeType2", 0, -50, 50);
	amount2.set("amount2", 10, 0, 25);
	speed3.set("speed3", 0.5, 0, 1);
	knob1.set("Knob1", 0.5f, 0.f, 1.0f);
	knob2.set("Knob2", 5.f, -10.f, 10.0f);
	shapeType3.set("shapeType3", 0, -50, 50);
	size3.set("size3", 100, 0, 100);
	shapeType4.set("shapeType4", 0, -50, 50);
	size4.set("size4", 100, 0, 100);
	lineWidth4.set("lineWidth4", 0.5, 0, 1);
	separation4.set("separation4", 50, 1, 100);
	speed4.set("speed4", 0.5, 0, 1);
	color1.set("color1", ofColor(0, 0, 255, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));
	color2.set("color2", ofFloatColor(0, 1, 0, 1), ofColor(0, 0, 0, 0), ofColor(1, 1, 1, 1));

	//--

	// Groups

	params1.setName("params1");
	params2.setName("params2");
	params3.setName("params3");
	params4.setName("params4");

	params1.add(bEnable1);
	params1.add(bEnable2);
	params1.add(bEnable3);
	params1.add(bEnable4);

	params1.add(pos_1);
	params1.add(rot_1);

	params2.add(lineWidth2);
	params2.add(separation2);

	params3.add(speed3);
	params3.add(shapeType3);
	params3.add(knob1);
	params3.add(knob2);
	params3.add(size3);

	params4.add(size4);
	params4.add(speed4);
	params4.add(shapeType4);
	params4.add(lineWidth4);
	params4.add(separation4);
	params4.add(color1);
	params4.add(color2);

	// -> Nesting Groups
	params2.add(params3);
	params1.add(params2);
	params1.add(params4);

	//----


	// ImGui

	// Instantiate

	// -> Optional to customize filename for the settings file for multiple instances on the same ofApp.
	//ui.setSettingsFilename("1_Widgets"); 

	ui.setup(); // IM_GUI_MODE_INSTANTIATED

	//----

	// Customize Styles

	// ->  Styles can be modified on runtime to reflect different modes of your app.
	refreshImGuiStyles();

	//-

	// Callbacks to update Custom Styles on runtime

	//--------------------------------------------------------------
	listener_bEnable1 = bEnable1.newListener([this](bool &b) {
		ofLogNotice("bEnable1: ") << (b ? "TRUE" : "FALSE");

		if (bEnable1) {
			ui.UpdateStyle(rot_1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
			ui.UpdateStyle(pos_1, OFX_IM_DEFAULT);
		}
		else {
			ui.UpdateStyle(rot_1, OFX_IM_DEFAULT);
			ui.UpdateStyle(pos_1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
		}

		// Notice that:
		// For this bool toggle, we do not will call refreshImGuiStyles()
		// We can update these two above params on runtime
		// (without having to clear) previously added ofParams yet.
	});

	//--------------------------------------------------------------
	listener_bEnable2 = bEnable2.newListener([this](bool &b) {
		ofLogNotice("bEnable2: ") << (b ? "TRUE" : "FALSE");

		refreshImGuiStyles(); // -> refresh styles on runtime!
	});

	//--------------------------------------------------------------
	listener_bEnable3 = bEnable3.newListener([this](bool &b) {
		ofLogNotice("bEnable3: ") << (b ? "TRUE" : "FALSE");

		refreshImGuiStyles(); // -> refresh styles on runtime!
	});

	//--------------------------------------------------------------
	listener_bEnable4 = bEnable4.newListener([this](bool &b) {
		ofLogNotice("bEnable4: ") << (b ? "TRUE" : "FALSE");

		refreshImGuiStyles(); // -> refresh styles on runtime!
	});

	//----

	// Sections toggles
	// To hide or show sections

	for (int i = 0; i < NUM_SECTIONS; i++) {
		ofParameter<bool> b{ "Section " + ofToString(i), false };
		bEnablers.emplace_back(b);

		params_Enablers.add(b);

		listeners_Enablers.push(b.newListener(this, &ofApp::Changed_Enablers));
	}

	//--

	// Startup
	// Load last session state settings

	//ofxSurfingHelpers::loadGroup(params_Enablers);//not works
	bEnablers[4] = true;

	ofxSurfingHelpers::loadGroup(params1);
}

//--------------------------------------------------------------
void ofApp::Changed_Enablers(const void * sender, bool & value) {
	if (bAttendingCallback) {
		return;
	}

	bAttendingCallback = true;
	auto param = (ofParameter<bool>*)sender;

	ofLogNotice() << __FUNCTION__ << " : "
		<< (param->getName()) << " "
		<< (param->get() ? "TRUE" : "FALSE");

	if (value == false)
	{
		// Don't let this parameter be deactivated so there's always
		// one active
		param->set(true);
	}
	else
	{
		for (int i = 0; i < NUM_SECTIONS; i++)
		{
			if (param->isReferenceTo(bEnablers[i])) {
				for (int j = 0; j < NUM_SECTIONS; j++)
				{
					if (i == j) continue;
					bEnablers[j].set(false);
				}
			}
		}
	}
	bAttendingCallback = false;
}

//--------------------------------------------------------------
void ofApp::exit() {

	// Save session state settings
	//ofxSurfingHelpers::saveGroup(params_Enablers);
	ofxSurfingHelpers::saveGroup(params1);
}

//--------------------------------------------------------------
void ofApp::refreshImGuiStyles() {

	// Customize Styles

	ui.clearStyles();

	// Notice that:
	// We can update on runtime (without having to clear) previously added ofParams yet.

	// Look on the bEnable1 / bEnable2 / bEnable3 / bEnable4 behaviour: 
	// We recall refreshImGuiStyles() when above bool changes to update the styles.

	//-

	// 1. For params

	// Will be applied when rendering a group when drawing his widgets.

	// 1 widget per row. not sameline for the next. 20 pix y spacing at end.

	ui.AddStyle(bEnable1, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
	ui.AddStyle(bEnable2, OFX_IM_TOGGLE_BIG_BORDER);
	ui.AddStyle(bEnable3, OFX_IM_TOGGLE_BIG);
	ui.AddStyle(bEnable4, OFX_IM_TOGGLE_BIG);

	//-

	if (bEnable1) {
		ui.AddStyle(knob1, OFX_IM_KNOB, 3, true);
		ui.AddStyle(knob2, OFX_IM_KNOB, 3, true);
		ui.AddStyle(size3, OFX_IM_KNOB, 3, false);
		// 3 widgets per row. sameline for the next
		// 3 widgets per row. sameline for the next
		// 3 widgets per row. not sameline for the next
	}
	else {
		ui.AddStyle(knob1, OFX_IM_VSLIDER_NO_LABELS, 3, true);
		ui.AddStyle(knob2, OFX_IM_VSLIDER_NO_LABELS, 3, true);
		ui.AddStyle(size3, OFX_IM_VSLIDER_NO_LABELS, 3, false);
		// 3 widgets per row. sameline for the next
		// 3 widgets per row. sameline for the next
		// 3 widgets per row. not sameline for the next
	}

	if (bEnable2) {
		ui.AddStyle(lineWidth2, OFX_IM_STEPPER);
		ui.AddStyle(separation2, OFX_IM_STEPPER);

		//ui.AddStyle(lineWidth2, OFX_IM_VSLIDER, 2, true);
		//ui.AddStyle(separation2, OFX_IM_VSLIDER, 2, false);
		// 2 widgets per row. sameline for the next
		// 2 widgets per row. not sameline for the next
	}
	else {
		ui.AddStyle(lineWidth2, OFX_IM_DEFAULT);
		ui.AddStyle(separation2, OFX_IM_DEFAULT);

		//ui.AddStyle(lineWidth2, OFX_IM_HSLIDER, 2, true);
		//ui.AddStyle(separation2, OFX_IM_HSLIDER, 2, false);
		// 2 widgets per row. sameline for the next
		// 2 widgets per row. not sameline for the next
	}

	if (bEnable3) {
		ui.AddStyleGroup(params3, OFX_IM_GROUP_COLLAPSED, ImGuiTreeNodeFlags_DefaultOpen);
	}
	else {
		ui.AddStyleGroup(params3, OFX_IM_GROUP_HIDDEN, ImGuiTreeNodeFlags_DefaultOpen);
	}

	if (bEnable4) {
		ui.AddStyleGroup(params4, OFX_IM_GROUP_COLLAPSED, ImGuiTreeNodeFlags_DefaultOpen);

		ui.AddStyle(lineWidth4, OFX_IM_HSLIDER_NO_NAME, 2, true);
		ui.AddStyle(separation4, OFX_IM_HSLIDER_NO_NAME, 2, false);
		// 2 widgets per row. sameline for the next
		// 2 widgets per row. not sameline for the next

		ui.AddStyle(shapeType4, OFX_IM_VSLIDER, 1, false, 20);
		// 1 widget per row. not sameline for the next and 20 y pixels spacing at end
	}
	else {
		ui.AddStyleGroup(params4, OFX_IM_GROUP_TREE, ImGuiTreeNodeFlags_DefaultOpen);

		ui.AddStyle(lineWidth4, OFX_IM_KNOB, 2, true);
		ui.AddStyle(separation4, OFX_IM_KNOB, 2, false);
		// 2 widgets per row. sameline for the next
		// 2 widgets per row. not sameline for the next

		ui.AddStyle(shapeType4, OFX_IM_HSLIDER, 1, false, 20);
		// 1 widget per row. not sameline for the next and 20 y pixels spaning at end

		ui.AddStyle(speed3, OFX_IM_HSLIDER_NO_NAME);
		ui.AddStyle(shapeType3, OFX_IM_HSLIDER_NO_NAME);
	}

	//-

	// 2. For Groups / headers / trees

	// WARNING:

	// Notice that:
	// Some flags may be not be supported/combined for some tree types.
	// ie: OFX_IM_GROUP_TREE maybe can not be with ImGuiTreeNodeFlags_DefaultOpen. 
	// and the tree will be closed by default. 
	// That's bc ImGui::TreeNode has no flags, but (when passing ImGuiTreeNodeFlags_DefaultOpen)
	// we are using an internal workaround doing:
	// bool bOpen = true;
	// ImGui::SetNextTreeNodeOpen(bOpen, ImGuiCond_Appearing);

	// Notice that:
	// Nested groups can heritate flags/types from parent ones.
	// Then, in most cases, it's recommended to define all the flags for each group style!

	//ui.AddStyleGroup(params1, OFX_IM_GROUP_TREE_EX, ImGuiTreeNodeFlags_DefaultOpen);
	//ui.AddStyleGroup(params1, OFX_IM_GROUP_COLLAPSED, ImGuiTreeNodeFlags_DefaultOpen);
	//ui.AddStyleGroup(params1, OFX_IM_GROUP_HIDDEN_HEADER, ImGuiTreeNodeFlags_None);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		// 1. Toggle Section Enablers Window
		{
			// Notice that if you use ImGui Raw begin/end methods to create window panels,
			// some widget helpers can be used, but not all. 
			// In this case will made crash the app if you use ui.Add(..
			// But it will work if you use ofxImGuiSurfing::AddToggleRoundedButton(..
			// --> *
			//ImGui::Begin("Enablers"); 

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			ui.BeginWindow(ofToString("Sections Enablers"), NULL, window_flags);
			{
				for (int i = 0; i < NUM_SECTIONS; i++)
				{
					ui.Add(bEnablers[i], OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);

					// -> *
					//ofxImGuiSurfing::AddToggleRoundedButton(bEnablers[i]);
				}

				ImGui::Spacing();

				//--------------------------------------------------------------

				// An extra advanced / sub-panel 

				// with some common toggles that we must customize/assign destinations.
				{
					ui.DrawAdvancedBundle(true);
				}
			}
			ui.EndWindow();

			// -> *
			//ImGui::End();
		}

		//--------

		// 2. ofApp Window
		{
			//TODO:
			// not working..
			if (ui.bReset_Window) {
				ui.bReset_Window = false;
				ui.resetWindowImGui(true, true);
			}

			//-

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
			if (ui.bLockMove) window_flags |= ImGuiWindowFlags_NoMove;
			if (ui.bNoScroll) window_flags |= ImGuiWindowFlags_NoScrollbar;

			ui.BeginWindow("ofApp", NULL, window_flags);
			{
				
				// Ranges for multidim glm::vec

				if (bEnablers[1])
				{
					ui.refreshLayout();

					static ofParameter<int> coord{ "coord", 0, 0, 2 };
					ofxImGuiSurfing::AddParameter(coord);

					ofxImGuiSurfing::AddParameter(value);
					ofxImGuiSurfing::AddParameter(valueMin);
					ofxImGuiSurfing::AddParameter(valueMax);

					float _h = ofxImGuiSurfing::getWidgetsHeightUnit();
					float _w100 = ofxImGuiSurfing::getWidgetsWidth(1);
					float _w50 = ofxImGuiSurfing::getWidgetsWidth(2);

					ofxImGuiSurfing::AddRangeOneVec3Param("RangePos", pos_1, valueMin, valueMax, value, coord.get());
					//ImGui::SameLine();
					//ImGui::Text("asdf");

					//ofxImGuiSurfing::AddSpacingSeparated();
				}

				//--------------------------------------------------------------

				// A Multidim (xyz) vec2/vec3/vec4 parameter 

				if (bEnablers[2])
				{
					ImGui::Spacing();

					// Two api patterns can be used:
					ui.Add(pos_1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
					//ofxImGuiSurfing::AddParameter(pos_1, true);

					//ofxImGuiSurfing::AddSpacingSeparated();
				}

				//--------------------------------------------------------------

				// Basic folder

				if (bEnablers[3])
				{
					if (ImGui::TreeNode("Tree"))
					{
						ui.Add(bEnable1);
						ui.Add(bEnable2);
						ui.Add(bEnable3);

						ImGui::TreePop();
					}

					//ofxImGuiSurfing::AddSpacingSeparated();
				}

				//--------------------------------------------------------------

				// An ofParameterGroup with monested Groups with params

				//if (0)
				if (bEnablers[4])
				{
					ui.AddGroup(params1);
				}

				//--------------------------------------------------------------

				// Three Rounded Toggles

				if (bEnablers[5])
				{
					ofxImGuiSurfing::AddToggleRoundedButton(bPrevious);
					ImGui::SameLine();
					ofxImGuiSurfing::AddToggleRoundedButton(bNext);
					ImGui::SameLine();
					ofxImGuiSurfing::AddToggleRoundedButton(bEnable1);
				}

				//--------------------------------------------------------------

				// Vertica/Horizontal Big Sliders

				if (bEnablers[6])
				{
					if (ImGui::TreeNodeEx("Vert/Horiz Sliders", ImGuiTreeNodeFlags_DefaultOpen))
					{
						ui.refreshLayout();

						ImGui::TextWrapped("Float and Int ofParameters \ncan be directly rendered as ImGui Widgets \n");
						ImGui::TextWrapped("Try to resize the window panel \nto see the responsive layouting.. \n");

						ofxImGuiSurfing::AddSpacingSeparated();

						ImGui::Spacing();

						if (ImGui::TreeNodeEx("Raw Mode without Styles Engine"))
						{
							ImGui::TextWrapped("> No Responsive! No Mouse Wheel!\n");

							float w = 40;
							float h = 80;
							ofxImGuiSurfing::AddVSlider(speed3, ImVec2(w, h), true);
							ImGui::SameLine();
							ofxImGuiSurfing::AddVSlider(speed4, ImVec2(w, h), true);
							ImGui::SameLine();
							ofxImGuiSurfing::AddVSlider(size3, ImVec2(w, h), true);
							ImGui::SameLine();
							ofxImGuiSurfing::AddVSlider(size4, ImVec2(w, h), true);

							ImGui::TreePop();
						}
						ofxImGuiSurfing::AddSpacingSeparated();

						//TODO:
						// Must improve the widgets.
						// this is a workaround
						// Using columns to mantain alignment
						ImGui::TextWrapped("> Four Vertical Sliders \n");
						ImGui::Spacing();
						ImGui::Columns(4, "_bigSliders", false);
						ui.Add(speed3, OFX_IM_VSLIDER, 4, true);
						ImGui::NextColumn();
						ui.Add(speed4, OFX_IM_VSLIDER, 4, true);
						ImGui::NextColumn();
						ui.Add(size3, OFX_IM_VSLIDER, 4, true);
						ImGui::NextColumn();
						ui.Add(size4, OFX_IM_VSLIDER, 4, false);
						ImGui::Columns(1);

						ofxImGuiSurfing::AddSpacingSeparated();

						ImGui::TextWrapped("> Four Vertical Sliders \nNo Name \n");
						ImGui::Spacing();
						ui.Add(speed3, OFX_IM_VSLIDER_NO_NAME, 4, true);
						ui.Add(speed4, OFX_IM_VSLIDER_NO_NAME, 4, true);
						ui.Add(size3, OFX_IM_VSLIDER_NO_NAME, 4, true);
						ui.Add(size4, OFX_IM_VSLIDER_NO_NAME, 4, false);

						ofxImGuiSurfing::AddSpacingSeparated();

						ImGui::TextWrapped("> Four Horizontal Sliders \n");
						ui.Add(speed3, OFX_IM_HSLIDER_NO_NAME);
						ui.Add(speed4, OFX_IM_HSLIDER_NO_LABELS);
						ui.Add(size3, OFX_IM_HSLIDER_SMALL_NO_NUMBER);
						ui.Add(size4, OFX_IM_HSLIDER_SMALL);

						ofxImGuiSurfing::AddSpacingSeparated();

						ImGui::TextWrapped("> Two Horizontal Sliders \nWithout Labels in One Row \n");
						ui.Add(speed3, OFX_IM_HSLIDER_SMALL_NO_LABELS, 2, true);
						ui.Add(speed4, OFX_IM_HSLIDER_SMALL_NO_LABELS, 2, false);

						ofxImGuiSurfing::AddSpacingSeparated();

						ImGui::TextWrapped("> Four Knobs \n");
						ImGui::Spacing();
						ui.Add(speed3, OFX_IM_KNOB, 4, true);
						ui.Add(speed4, OFX_IM_KNOB, 4, true);
						ui.Add(size3, OFX_IM_KNOB, 4, true);
						ui.Add(size4, OFX_IM_KNOB, 4, false);

						ImGui::TreePop();
					}
				}

				//--------------------------------------------------------------
			}
			ui.EndWindow();
		}

		Example();
	}
	ui.End();
}
