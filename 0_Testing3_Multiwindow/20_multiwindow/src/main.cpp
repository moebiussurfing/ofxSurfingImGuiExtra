#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

#pragma message "Warning, ofxImGui in multiple ofAppBaseWindows is in testing phase. Proceed with caution !"

//========================================================================
int main( ){
    ofSetLogLevel( OF_LOG_VERBOSE );

    ofGLFWWindowSettings settings; // <-- GLES or GL depending on environment

    settings.setGLVersion(3,2);
	settings.setSize(400, 400);
	settings.setPosition(ofVec2f(0, 220));

	settings.title="Master Window";
	auto window1 = ofCreateWindow(settings);

    // Note: using a different width to test coordinates, specially useful in non-viewports mode where they are relative
    settings.setPosition(ofVec2f(400, 20));
    settings.setSize(500, 600);
    settings.title="Slave Window";
    settings.shareContextWith = window1;

	// WARNING :
    // For now, both GL versions must be the same for ImGui to work in a multiwindow context.
	//settings.setGLVersion(2, 1);
    auto window2 = ofCreateWindow(settings);

    auto app1 = std::make_shared<ofApp>();
    auto app2 = std::make_shared<ofApp>();

	std::cout << "Window 1 = (ofAppBaseWindow)" << window1.get() << " // (ofAppBaseWindow)" << (ofAppBaseWindow*) window1.get() << " // " << std::endl;
	std::cout << "Window 2 = (ofAppBaseWindow)" << window2.get() << " // (ofAppBaseWindow)" << (ofAppBaseWindow*) window2.get() << " // " << std::endl;

	ofRunApp(window1, app1);
    ofRunApp(window2, app2);

	return ofRunMainLoop();
}
