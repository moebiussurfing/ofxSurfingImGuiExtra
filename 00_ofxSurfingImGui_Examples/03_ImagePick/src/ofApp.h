#pragma once

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "ofxSurfingImGui.h"

//--

#include "imgInspect.h"

class ofApp : public ofBaseApp
{
public:

	void setup();
	void initTexture();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;
	ofParameter<bool> bGui{ "Show", true };
	
	ofParameter<int> index{ "Index", 0, 0, 2 };
	ofEventListener event;

	ofFbo fbo;
	ofPixels pixels;
	ofImage image;
	ofTexture texture;
	GLuint textureID;

	std::string path = "";
	std::string path1 = "image1.jpg";
	std::string path2 = "image2.jpg";
	std::string path3 = "image3.jpg";
};
