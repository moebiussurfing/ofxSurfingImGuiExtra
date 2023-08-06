#include "ImLayoutManager.h"

ImLayoutManager::ImLayoutManager()
{
	ofLogNotice(__FUNCTION__);
}

ImLayoutManager::~ImLayoutManager()
{
	ofLogNotice(__FUNCTION__);
}

void ImLayoutManager::setup(ofxImGui::Gui& ui)
{
	ofLogNotice(__FUNCTION__);

	mainFrame.Init();

	//ImGuiViewport* viewport = ImGui::GetMainViewport();
	//if (viewport)
	//{
	//	size = viewport->WorkSize;
	//}
	size = ImVec2(ofGetWindowSize());

	bDoneSetup = 1;
}

void ImLayoutManager::draw() 
{
	mainFrame.Unit();
}
