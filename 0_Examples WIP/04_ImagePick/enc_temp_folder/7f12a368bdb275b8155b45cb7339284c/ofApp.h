#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "ofxSurfingHelpers.h"

#include "surfingImageInspect.h"

//--

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);
	void exit();

	void drawImGui();
	void loadImage(string path);

	ofxSurfingGui ui;

	ofParameter<bool> bGui{ "ofApp", true };
	ofParameter<bool> bDrawImg{ "Draw Image", true };
	ofParameter<int> index{ "Index", 0, 0, 2 };
	ofEventListener eventIndex;

	ofParameterGroup g{ "ofApp" };

	string path1 = pathImages + "imageAlpha.png";
	string path2 = pathImages + "image2.jpg";
	string path3 = pathImages + "image3.bmp";

	string pathImages = "images";//file path
	string path = "";//file name

	ofFloatImage imageFloat;
	bool bLoaded = false;

	//--

	SurfImageInspect imageInspect;

	ofParameter<ofColor> colorPtr{ "ColorPicked", ofColor(128, 128) };
};
