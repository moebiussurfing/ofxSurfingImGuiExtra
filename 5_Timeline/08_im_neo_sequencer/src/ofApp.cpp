#include "ofApp.h"

#include <algorithm>

//--------------------------------------------------------------
void ofApp::setup()
{
  ui.setName("NeoBangSequencer");
  ui.setup();
  ui.bAutoResize = false;
  ui.bLog = true;

  manager_.setup(this, &ui);

  lastUpdateTime_ = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update()
{
  const double now = ofGetElapsedTimef();
  const double deltaSeconds = std::max(0.0, now - lastUpdateTime_);
  lastUpdateTime_ = now;

  manager_.update(deltaSeconds);
}

//--------------------------------------------------------------
void ofApp::draw()
{
  manager_.drawParticles();
  drawGui();
}

//--------------------------------------------------------------
void ofApp::drawGui()
{
  ui.Begin();
  {
    if (ui.BeginWindow(bGuiMain)) {
      manager_.drawMainUi();
      ui.EndWindow();
    }

    if (ui.BeginWindow(bGuiTimeline)) {
      manager_.drawTimelineUi();
      ui.EndWindow();
    }
  }
  ui.End();
}

//--------------------------------------------------------------
void ofApp::exit()
{
  manager_.exit();
  ui.save();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
  manager_.keyPressed(key);

  if (key == 'g' || key == 'G') bGuiMain = !bGuiMain;
  if (key == 't' || key == 'T') bGuiTimeline = !bGuiTimeline;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
