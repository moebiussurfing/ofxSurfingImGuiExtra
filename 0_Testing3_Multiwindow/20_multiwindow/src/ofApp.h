#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

class ofApp : public ofBaseApp{

	public:
		ofApp() : v(0) {

		}

        void setup() override {
			gui.setup(nullptr, false, ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable, true);
		}
		void draw() override {
			ofDrawBitmapStringHighlight("Hello",10,10);

            // Draw to ImGui (after OF related stuff, to make it overlay)
			gui.begin();

			gui.drawOfxImGuiDebugWindow();

            //ImGui::End();

            ImGui::ShowMetricsWindow();
            
            gui.end();

            gui.draw();
		}

	private:
		ofxImGui::Gui gui;
		float v;
};
