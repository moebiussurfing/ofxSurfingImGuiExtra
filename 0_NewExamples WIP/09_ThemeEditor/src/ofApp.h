#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "SurfingThemeEditor.h"

#define TEST_CUSTOM_FONTS 0

/*

	WIP

	This is a kind of helper to:
	- Edit/test your own themes.
	- Save themes to allow loading on your apps.
	- Loading font files to check and tweak styles.


	TODO

	add serializer for themes using ImGooeyStyles
		fix ImVec2 params
	make new ImGui_ThemeMoebiusSurfingV3 dark theme with more 3d styled look

*/


//--

class ofApp : public ofBaseApp
{
public:
		void setup();
		void setupFonts();
		void draw();
			
		ofxSurfingGui ui; 

		void drawWindowMain(); 
		void drawThemeSelector();
		void drawWindowStylized(); 

		bool bOpenWindowMain = 1;
		bool bOpenThemeSelector = 0;
		bool bOpenWindowStylized = 0;

		//--

		bool bStyleFonts = false; 

		ofParameter<int> fontSize;
		ofParameter<int> fontIndex;


		ofParameter<bool> bEnable;
		ofParameter<int> amount;

		string txt = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";

		SurfingThemeEditor e;
};
