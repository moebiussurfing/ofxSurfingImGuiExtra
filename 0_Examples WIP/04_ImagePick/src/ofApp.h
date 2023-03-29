#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

//--

#include "imgInspect.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void loadTexture();
	void draw();
	void drawImGui();
	void keyPressed(int key);

	ofxSurfingGui ui;
	ofParameter<bool> bGui{ "Show", true };
	ofParameter<bool> bImg2{ "Img2", 1 };

	ofFbo fbo;
	ofPixels pixels;
	ofImage image;
	ofTexture texture;
	GLuint textureID;

	ofFloatImage imageFloat;

	ofParameter<int> index{ "Index", 0, 0, 2 };
	ofEventListener event;
	string path = "";

	string pathImages = "images/";

	string path1 = pathImages + "imageAlpha.png";
	//string path1 = pathImages+"image1.jpg";

	string path2 = pathImages + "image2.jpg";

	//string path3 = pathImages+"image3.jpg";
	string path3 = pathImages + "image3.bmp";

	ofColor c = 0;
	ofColor cBg = 0;
};
