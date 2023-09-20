#pragma once
#include "ofMain.h"

/*

	This is an OF 0.11 WIP example porting ImGuizmo from @CedricGuillemet
	https://forum.openframeworks.cc/t/ofximgui-how-to-add-imguizmo/24982/24
	https://github.com/CedricGuillemet/ImGuizmo // -> Raw ImGui repo.
	https://github.com/nariakiiwatani/ofxImGuizmo // -> Repo with OF helpers (cam/transforms).
	https://github.com/nariakiiwatani/ImGuizmo // -> Small fixes.

*/


#include "ofxSurfingImGui.h"
#include "ImGuizmoMain.cpp"


#include "glm/gtx/matrix_decompose.hpp"

#include "ofxImGuizmo.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();
	void drawScene();
	void keyPressed(int key);

	ofParameter<bool> bGui{ "Show Gui", true };

	ofxSurfingGui ui;

	//--

	void setupImGuizmo();
	void drawImGuizmo();

	bool firstFrame = true;


	int lastUsing = 0;//last used gizmo

	// raw cpp camera
	float cameraView[16] =
	{ 1.f, 0.f, 0.f, 0.f,
	  0.f, 1.f, 0.f, 0.f,
	  0.f, 0.f, 1.f, 0.f,
	  0.f, 0.f, 0.f, 1.f };
	float cameraProjection[16];


#ifndef USE_ONLY_GIZMOS
	// build a procedural texture. 
	// Copy/pasted and adapted from 
	// https://rosettacode.org/wiki/Plasma_effect#Graphics_version
	unsigned int procTexture;

	uint32_t* tempBitmap = new uint32_t[256 * 256];
	int index = 0;

	MySequence mySequence;
#endif

	// Camera projection
	bool isPerspective = true;
	float fov = 27.f;
	float viewWidth = 10.f; // for orthographic
	float camYAngle = 165.f / 180.f * 3.14159f;
	float camXAngle = 32.f / 180.f * 3.14159f;



	//TODO
	ofNode myNode;
	void setOfNodeTransformMatrix(ofNode* node, const glm::mat4& m44) {
		glm::vec3 scale;
		glm::quat orientation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;

		glm::decompose(m44, scale, orientation, translation, skew, perspective);

		node->setGlobalPosition(translation);
		node->setGlobalOrientation(glm::inverse(orientation));
		node->setScale(scale);
	}



	//TODO: ofxImGuizmo
	ofCamera cam;
	//ofEasyCam cam;
	ImGuizmo::OPERATION op_;
	ImGuizmo::MODE mode_;
	ofNode node_;

	float w = 320;
	ofRectangle rect{ 0, 0, w, w / (16 / 9.f) };
};
