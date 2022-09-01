#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ui.setMouseWheelFlip(false);//flip for natural direction
	ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ui.Begin();
	{
		ui.DrawWindowAdvanced();

		{
			string name = "Knobs";
			ImGuiColorEditFlags _flagw = ui.bAutoResize ?
				ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;

			ui.BeginWindow(name.c_str(), NULL, _flagw);
			{
				if (ui.BeginTree("Settings", false))
				{
					ui.Add(ui.bAutoResize, OFX_IM_TOGGLE_ROUNDED_SMALL);
					ui.Add(ui.bAdvanced, OFX_IM_TOGGLE_ROUNDED_SMALL);
					ui.AddSpacing();

					ui.Add(ui.bMouseWheel, OFX_IM_TOGGLE_ROUNDED_MINI);
					ui.Add(ui.bMouseWheelFlip, OFX_IM_TOGGLE_ROUNDED_MINI);
					ui.EndTree();
				}
				
				ui.AddSpacingBigSeparated();

				//----

				if (0)
				{
					// 1. Legacy Non Styled Knobs ofParams
					{
						ui.AddLabelHuge("LEGACY NON STYLED KNOBS");
						ui.AddSpacing();

						ui.Add(valueKnob1, OFX_IM_KNOB, 4, true);
						ui.Add(valueKnob2, OFX_IM_KNOB, 4, true);
						ui.Add(valueKnob3, OFX_IM_KNOB, 4, true);
						ui.Add(valueKnob4, OFX_IM_KNOB, 4, false);

						ui.AddSpacingHugeSeparated();
					}
				}

				//--

				// 2. NEW Styled Knobs ofParams
				{
					ui.AddLabelHuge("NEW STYLED KNOBS");
					ui.AddLabelBig("from Simon Altschuler");
					ui.AddLinkURL("https://github.com/altschuler/imgui-knobs", "https://github.com/altschuler/imgui-knobs");
					ui.AddSpacingBig();

					ui.AddLabel("Style Selector");
					ui.AddSpacing();

					SurfingGuiTypes style;
					{
						// Style selector
						vector<string> knobStyles;
						knobStyles.push_back("TICKKNOB");
						knobStyles.push_back("DOTKNOB");
						knobStyles.push_back("WIPERKNOB");
						knobStyles.push_back("WIPERONLYKNOB");
						knobStyles.push_back("WIPERDOTKNOB");
						knobStyles.push_back("STEPPEDKNOB");
						knobStyles.push_back("SPACEKNOB");
						const int sz = (int)(knobStyles.size()) - 1;
						static ofParameter<int> index{ "Style", 0, 0, sz };
						ui.AddComboButtonDualLefted(index, knobStyles);
						switch (index)
						{
						case 0: style = OFX_IM_KNOB_TICKKNOB; break;
						case 1: style = OFX_IM_KNOB_DOTKNOB; break;
						case 2: style = OFX_IM_KNOB_WIPERKNOB; break;
						case 3: style = OFX_IM_KNOB_WIPERONLYKNOB; break;
						case 4: style = OFX_IM_KNOB_WIPERDOTKNOB; break;
						case 5: style = OFX_IM_KNOB_STEPPEDKNOB; break;
						case 6: style = OFX_IM_KNOB_SPACEKNOB; break;
						}
					}

					// Draw
					ui.Add(valueKnob1, style, 4, true);
					ui.Add(valueKnob2, style, 4, true);
					ui.Add(valueKnob3, style, 4, true);
					ui.Add(valueKnob4, style, 4, false);
				}
			}
			ui.EndWindow();
		}
	}
	ui.End();
}
