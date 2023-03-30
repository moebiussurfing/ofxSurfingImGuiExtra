#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "ofxSurfingHelpers.h"

//--

#include "imgInspect.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);
	void exit();

	void drawImGui();
	void loadTexture();

	ofxSurfingGui ui;

	ofParameter<bool> bGui{ "Show", true };
	ofParameter<bool> bDrawImg{ "bDrawImg", true };
	ofParameter<bool> bDrawImg2{ "bDrawImg2", true };
	ofParameter<int> index{ "Index", 0, 0, 2 };
	ofParameterGroup g{ "ofApp" };

	ofFbo fbo;
	ofPixels pixels;
	ofImage image;
	ofTexture texture;
	GLuint textureID;

	ofFloatImage imageFloat;
	ofEventListener event;

	string path1 = pathImages + "imageAlpha.png";
	string path2 = pathImages + "image2.jpg";
	string path3 = pathImages + "image3.bmp";

	string pathImages = "images";//file path
	string path = "";//file name
	bool bLoaded = false;

	ofColor c = 0;
	ofColor cBg = 0;

	ofParameter<bool> bDebugAdvanced{ "DebugAdvanced", false};
	ofParameter<bool> bEnableInspector{ "Inspector",true };
	ofParameter<bool> bEnablePicker{ "Picker",false };
	ofParameter<int> zoomSize{ "ZoomOut", 3, 1,50 };
	ofParameter<int> zoomRectangleWidth{ "BoxSize", 200, 50,1000 };
	ofParameterGroup params_ImageInspector{ "Image Inspector" };
};
