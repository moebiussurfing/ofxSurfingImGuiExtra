#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

/*

	ABOUT THIS EXAMPLE:

	WIP
	This is a kind of helper to edit/test your own themes.
	Also loading font files to check styles.

*/

//-

class ofApp : public ofBaseApp
{

public:

		void setup();
		void setupFonts();
		void draw();
			
		//-
		
		ofxSurfingGui ui; 

		//-
		
		void drawMainWindow(); // -> a panel window with widgets
		void drawWindowStylized(); // -> a panel window with widgets

		bool bOpenWindowMain = true;
		bool bOpenWindowStyled = true;
		bool bOpenWindowEditor = true;

		bool bStyleFonts = false; // -> Activate use custom fonts.

		ofParameter<int> fontSize;
		ofParameter<int> fontIndex;

		//-

		ofParameter<bool> bEnable;
		ofParameter<int> amount2;

		string txt = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";

};
