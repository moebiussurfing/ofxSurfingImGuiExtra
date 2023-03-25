#pragma once

#include "ofMain.h"

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
	
	ofFbo fbo;
	ofPixels pixels;
	ofImage image;
	ofTexture texture;
	GLuint textureID;
	
	ofParameter<int> index{ "Index", 0, 0, 2 };
	ofEventListener event;
	std::string path = "";

	std::string path1 = "imageAlpha.png";
	//std::string path1 = "image1.jpg";
	std::string path2 = "image2.jpg";
	std::string path3 = "image3.jpg";
};
