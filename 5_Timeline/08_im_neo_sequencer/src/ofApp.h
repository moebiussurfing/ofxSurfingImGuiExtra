#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <vector>

#include "ofMain.h"

#include "imgui_neo_internal.h"
#include "imgui_neo_sequencer.h"
#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp {

public:
  ofxSurfingGui ui;
  ofParameter<bool> bGuiMain{ "Main", true };
  ofParameter<bool> bGuiTimeline{ "Timeline", true };

  void setup();
  void update();
  void draw();
  void drawGui();
  void drawTimeline();
  void exit();

  int32_t currentFrame = 0;
  int32_t startFrame = 0;
  int32_t endFrame = 63;

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
  static constexpr std::size_t kBangCount = 8;

  std::vector<ofParameter<void>> bangs_;
  std::array<ofEventListener, kBangCount> bangListeners_;
  std::vector<std::vector<ImGui::FrameIndexType>> timelineKeys_;
  std::vector<bool> lanesOpen_;
  std::vector<bool> effectState_;
  std::vector<float> lastBangTriggeredTime_;

  ofParameter<float> bpm_{ "BPM", 120.0f, 40.0f, 240.0f };
  ofParameter<int> bars_{ "Bars", 4, 1, 32 };
  ofParameter<bool> play_{ "Play", false };
  ofParameter<bool> loop_{ "Loop", true };
  bool channelsGroupOpen_ = true;

  bool timelineTriggerContext_ = false;
  ImGui::FrameIndexType timelineTriggerStep_ = 0;

  double lastUpdateTime_ = 0.0;
  double transportAccumulator_ = 0.0;
  bool wasPlaying_ = false;

  void setupBangParameters();
  void setupBangListeners();
  void onBangTriggered(std::size_t index);
  void triggerBangFromTimeline(std::size_t index, ImGui::FrameIndexType step);
  void updateTransport(double deltaSeconds);
  void processTimelineStep(ImGui::FrameIndexType step);

  bool insertKeyframe(std::size_t laneIndex, ImGui::FrameIndexType step);
  bool removeKeyframe(std::size_t laneIndex, ImGui::FrameIndexType step);
  void removeSelectedKeyframesFromLane(std::size_t laneIndex);
  void sanitizeLane(std::size_t laneIndex);
  void sanitizeAllLanes();
  void updateTimelineBounds();

  std::size_t getTotalSteps() const;
  std::string getLaneLabel(std::size_t laneIndex) const;
  std::string formatStepMusical(ImGui::FrameIndexType step) const;

};
