#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h" 
#include "imgui_color_gradient.h" 

class exampleSurfingGradient
{
public:
	exampleSurfingGradient();
	~exampleSurfingGradient();
	
	ofParameter<bool> bGui{ "Gradient Editor", true };

private:
	void setup();
	//void keyPressed(ofKeyEventArgs &eventArgs);
	//void exit();

	//void update();
	//void draw();
	//void update(ofEventArgs & args);
	//void draw(ofEventArgs & args);

public:
	void drawWidgets();
	void drawImGui();

private:

	//string path = "exampleSurfingGradient_AppSettings.xml";
	//ofParameterGroup params;
	ofParameter<bool> bKeys;

public:
	ofParameter<int> indexPreset;
	float prcGrad = 0.5f;
	ofFloatColor color;

private:
	ImGradient gradient;
	void loadGradient(int index);
	ofEventListener listenerIndex;
};

