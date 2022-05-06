#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() 
{
	ofSetFrameRate(60);

	// Parameters
	params_0.setName("paramsGroup0");
	params_1.setName("paramsGroup1");
	params_2.setName("paramsGroup2");
	params_3.setName("paramsGroup3");

	params_0.add(bEnable0.set("Enable0", false));
	params_0.add(speed0.set("speed0", 0.5, 0, 1));
	params_0.add(bPrevious0.set("<", false));
	params_0.add(bNext0.set(">", false));

	params_1.add(bEnable1.set("Enable1", false));
	params_1.add(shapeType1.set("shapeType1", 0, -50, 50));
	params_1.add(size1.set("size1", 100, 0, 100));
	params_1.add(lineWidth1.set("lineWidth1", 0.5, 0, 1));
	params_1.add(separation1.set("separation1", 50, 1, 100));

	params_2.add(bEnable2.set("Enable2", false));
	params_2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params_2.add(size2.set("size2", 100, 0, 100));
	params_2.add(amount2.set("amount2", 10, 0, 25));

	params_3.add(bEnable3.set("Enable3", false));
	params_3.add(speed3.set("speed3", 0.5, 0, 1));
	params_3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params_3.add(separation3.set("separation3", 50, 1, 100));

	//-

	setup_ImGui();
}

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	// Enable "Windows Special Organizer"
	guiManager.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

	guiManager.setup(IM_GUI_MODE_INSTANTIATED);

	// Add and queue "Special Windows" to the Organizer
	guiManager.addWindowSpecial("myWindow 0"); // -> Custom enablers names
	guiManager.addWindowSpecial("myWindow 1");
	guiManager.addWindowSpecial("myWindow 2");
	guiManager.addWindowSpecial("myWindow 3");

	//// Customize names to help integrate into your gui's.
	//guiManager.setNameWindowsSpecialsPanel("My Add-on");//rename "Organizer" to custom name.

	// Startup
	guiManager.startup(); // -> Call after windows has been added.
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(32);

	guiManager.begin();
	{
		// A Simple ImGui Window handled by the manager:
		guiManager.beginWindow("ofApp");
		{
			guiManager.Add(guiManager.getWindowsSpecialGuiToggle(), OFX_IM_TOGGLE_BIG); // Organizer toggle
		}
		guiManager.endWindow();

		//-
		
		/*
			Another window called "Organizer" (by default) will be auto drawn!
			It's a panel who controls all the special windows.
			Features:
			- creates toggles to show/ hide each window.
			- hide/show all/none.
			- align windows as vertical or horizontal cascade. 
			- custom spacing between windows, hide headers...
			- Lock sizes between windows
			- Debug positions.
		*/

		draw_SurfingWidgets_0();
		draw_SurfingWidgets_1();
		draw_SurfingWidgets_2();
		draw_SurfingWidgets_3();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_0() {

	// -> We begin the window like that passing wich special window index is.
	if (guiManager.beginWindowSpecial(0)) 
	{
		// your widgets goes here...
		guiManager.AddGroup(params_0);
	}
	guiManager.endWindowSpecial();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_1() {

	if (guiManager.beginWindowSpecial(1))
	{
		guiManager.AddGroup(params_1);
	}
	guiManager.endWindowSpecial();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_2() {

	if (guiManager.beginWindowSpecial(2))
	{
		guiManager.AddGroup(params_2);
	}
	guiManager.endWindowSpecial();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_3() {

	if (guiManager.beginWindowSpecial(3))
	{
		guiManager.AddGroup(params_3);
	}
	guiManager.endWindowSpecial();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (false) {}

	else if (key == 'h') {
		guiManager.setSpecialWindowsOrganizerOrientationHorizontal();
	}
	else if (key == 'v') {
		guiManager.setSpecialWindowsOrganizerOrientationVertical();
	}
	else if (key == 'o') {
		guiManager.setToggleSpecialWindowsOrganizerOrientation();
	}

	else if (key == '0') {
		guiManager.setWindowSpecialToggleVisible(0);
	}
	else if (key == '1') {
		guiManager.setWindowSpecialToggleVisible(1);
	}
	else if (key == '2') {
		guiManager.setWindowSpecialToggleVisible(2);
	}
	else if (key == '3') {
		guiManager.setWindowSpecialToggleVisible(3);
	}
}