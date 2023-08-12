#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	params.setName("paramsGroup");
	params.add(bPrevious.set("<"));
	params.add(bNext.set(">"));
	params.add(bEnable1.set("Enable1", false));
	params.add(bEnable2.set("Enable2", false));
	params.add(bEnable3.set("Enable3", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));

	//--

	//ui.setName("ofApp"); // Optional naming to separate settings folders and avoid sharing some ui states.
	ui.setup(); // Can be omitted in many scenarios..

	//--

	A.setUiPtr(&ui);

	//--
	
	//// Advanced
	//callback_t myFunctionDraw = std::bind(&ofApp::drawWidgets, this);
	////std::function<void()> myFunctionDraw = std::bind(&ofApp::drawWidgets, this);
	//C.setDrawWidgetsFunction(myFunctionDraw);

	ui.startup();
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return; // this is the global show visible toggle

	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			// ImGui widgets are placed here.
			// ofParamaters widgets helpers be easy populate,
			// But you can populate raw ImGui too.

			//--

			// These are some of the available useful internal toggles.
			// Note the minimize, auto resize, debug, extra, advanced, log window...
			// and other boolean/toggles are handled and store into the ofxSurfingGui object. 
			// Then they will be shared between classes objects if they share the same ui. 
			// (Or independent if do not shares the ui.)
			ui.AddMinimizerToggle();
			ui.AddAutoResizeToggle();
			ui.AddAdvancedToggle();
			ui.AddSpacingBigSeparated();

			//ui.DrawWidgetsGlobalScaleMini();
			//ui.AddSpacingBigSeparated();

			//--

			ui.AddLabelBig("MULTIPLE CLASSES");
			ui.AddLabel("WITH DIFFERENT ofxSurfingImGui INSTANTIATION APPROACHES");
			ui.AddSpacing();

			// Show / hide each class window
			SurfingGuiTypes style = OFX_IM_TOGGLE_ROUNDED_MEDIUM; // a style shared between widgets
			ui.Add(A.bGui, style);

			// This is a separator line with more spacing
			ui.AddSpacingBigSeparated();

			//--

			ui.AddLabel("These are exposed \nor public ofParams \nfrom the classes objects \nbut populated here");

			if (ui.isMaximized()) 
			{
				ui.AddSpacingBigSeparated();

				//--

				// This is an ofParameterGroup.
				// Contained ofParams are populated 
				// as their default widgets styles
				// (but we could queue custom styles for each param too 
				// that will be applied when populating the group widgets)
				// Note that these ofParams are local in ofApp.
				ui.AddGroup(params);

				//--

				// This is a ofParam widget but customized instead of using the default styled
				//ImGui::PushItemWidth(50);
				//mGui::SetNextItemWidth(50);
				ui.Add(amount, OFX_IM_VSLIDER, 3);
				ui.SameLine();
				ui.Add(separation, OFX_IM_VSLIDER, 3);
				//ui.Add(separation, OFX_IM_VSLIDER, 3);
				//ImGui::PopItemWidth();

				// This is a ofParam widget but customized instead of using the default styled
				//ui.Add(bPrevious, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			}

			//--

			ui.EndWindow();
		}

		A.drawImGuiWindow();
	}
	ui.End();

	//A.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}
