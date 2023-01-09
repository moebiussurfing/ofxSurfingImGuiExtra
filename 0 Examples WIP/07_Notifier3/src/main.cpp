#include "ofMain.h"
#include "ofApp.h"

int main()
{

#if defined(TARGET_OPENGLES)
    ofGLESWindowSettings settings;
    settings.setGLESVersion(2);
#else
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2);
#endif
    settings.setPosition(ofVec2f(0, 25));
    settings.setSize(1920, 1080);
    settings.title="ofxImGui font usage example";
    ofCreateWindow(settings);

    ofRunApp( new ofApp());

}
