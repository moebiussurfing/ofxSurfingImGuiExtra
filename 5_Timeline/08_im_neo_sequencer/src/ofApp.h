#pragma once

#include <array>
#include <vector>

#include "ofMain.h"

#include "BangParticle.h"
#include "BangTimelineManager.h"
#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp {
public:
  ofxSurfingGui ui;
  ofParameter<bool> bGuiMain{ "Main", true };
  ofParameter<bool> bGuiTransport{ "Transport", true };
  ofParameter<bool> bGuiTimeline{ "Timeline", true };

  void setup();
  void update();
  void draw();
  void drawGui();
  void exit();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

private:
  BangTimelineManager manager_;
  double lastUpdateTime_ = 0.0;

  ofParameter<int> bangDrawInt_{ "Bang Draw Int", 0, 0, static_cast<int>(BangTimelineManager::kBangCount) - 1 };

  std::array<ofFloatColor, BangTimelineManager::kBangCount> laneColors_{};
  std::vector<BangParticle> particles_;

  void drawMainBangPanel();
  void onBangEvent(std::size_t lane, ImGui::FrameIndexType step, bool fromTimeline);
  ofVec2f getLaneAnchorPosition(std::size_t lane) const;
  void drawLaneAnchors() const;
  void spawnParticleForLane(std::size_t lane);
  void updateParticles(float deltaSeconds);
  void drawParticles() const;
};
