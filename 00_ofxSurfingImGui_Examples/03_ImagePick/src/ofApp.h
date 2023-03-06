#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

//--

#include "imgInspect.h"

//https://github.com/nothings/stb/blob/master/stb_image.h
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

class ofApp : public ofBaseApp
{
public:

	void setup();
	void initTexture();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;
	ofParameter<bool> bGui{ "Show", true };

	ofParameter<bool> bEnable{ "Enable", true };
	ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
	ofParameterGroup params{ "Params", bEnable, speed };

	// Magnifying glass 
	unsigned char* data = nullptr;
	int width, height, channels;

	ofTexture tex;
	ofFbo fbo;
	ofImage image;
	std::string path1 = "image1.jpg";
	std::string path2 = "image2.jpg";
	std::string path3 = "image3.jpg";

	ofImage   imageButtonSource;
	GLuint    imageButtonID;

	ofPixels  pixelsButtonSource;
	GLuint    pixelsButtonID;

	ofTexture textureSource;
	GLuint    textureSourceID;
};
