#include "ofApp.h"

#include <algorithm>

//--------------------------------------------------------------
void ofApp::setup()
{
  ui.setName("NeoBangSequencer");
  ui.setup();
  ui.bAutoResize = false;
  ui.bLog = true;

  setupBangParameters();
  setupBangListeners();

  timelineKeys_.assign(kBangCount, {});
  lanesOpen_.assign(kBangCount, true);
  effectState_.assign(kBangCount, false);
  lastBangTriggeredTime_.assign(kBangCount, -1000.0f);

  // Seed a simple pattern so the example is immediately testable.
  timelineKeys_[0] = { 0, 8, 16, 24, 32, 40, 48, 56 };
  timelineKeys_[1] = { 4, 12, 20, 28, 36, 44, 52, 60 };
  timelineKeys_[2] = { 0, 16, 32, 48 };
  timelineKeys_[3] = { 8, 24, 40, 56 };

  updateTimelineBounds();
  sanitizeAllLanes();
  lastUpdateTime_ = ofGetElapsedTimef();

  ui.AddToLog("Neo sequencer ready. Mouse edit enabled.", "INFO");
}

//--------------------------------------------------------------
void ofApp::update()
{
  const double now = ofGetElapsedTimef();
  const double deltaSeconds = std::max(0.0, now - lastUpdateTime_);
  lastUpdateTime_ = now;

  updateTransport(deltaSeconds);
}

//--------------------------------------------------------------
void ofApp::draw()
{
  drawGui();
}

//--------------------------------------------------------------
void ofApp::drawTimeline()
{
  updateTimelineBounds();

  const ImGuiNeoSequencerFlags flags =
    ImGuiNeoSequencerFlags_EnableSelection |
    ImGuiNeoSequencerFlags_Selection_EnableDragging |
    ImGuiNeoSequencerFlags_Selection_EnableDeletion |
    ImGuiNeoSequencerFlags_AlwaysShowHeader;

  const float minHeight = 260.0f;
  const ImVec2 size{ 0.0f, std::max(minHeight, ImGui::GetContentRegionAvail().y - ImGui::GetFrameHeight() * 2.0f) };

  if (ImGui::BeginNeoSequencer("BangSequencer", &currentFrame, &startFrame, &endFrame, size, flags)) {
    if (ImGui::BeginNeoGroup("Bang Channels", &channelsGroupOpen_)) {
      for (std::size_t i = 0; i < kBangCount; ++i) {
        bool laneOpen = lanesOpen_[i];
        const std::string laneId = getLaneLabel(i) + "##lane_" + ofToString(i);

        if (ImGui::BeginNeoTimelineEx(laneId.c_str(), &laneOpen)) {
          auto& lane = timelineKeys_[i];
          bool hoveredAnyKey = false;
          bool removeOne = false;
          ImGui::FrameIndexType removeFrame = 0;

          for (auto& frame : lane) {
            ImGui::NeoKeyframe(&frame);
            hoveredAnyKey = hoveredAnyKey || ImGui::IsNeoKeyframeHovered();
            if (ImGui::IsNeoKeyframeRightClicked()) {
              removeOne = true;
              removeFrame = frame;
            }
          }

          if (removeOne) {
            removeKeyframe(i, removeFrame);
          }

          const bool canInsert =
            ImGui::IsNeoTimelineSelected() &&
            !ImGui::NeoIsSelecting() &&
            !ImGui::NeoIsDraggingSelection();

          // Mouse-only insertion: double-left-click on selected lane inserts at current time cursor.
          if (canInsert && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && !hoveredAnyKey) {
            insertKeyframe(i, currentFrame);
          }
          // Alternate mouse insertion: right-click empty area on selected lane.
          if (canInsert && ImGui::IsMouseClicked(ImGuiMouseButton_Right) && !hoveredAnyKey &&
            !ImGui::IsNeoKeyframeSelectionRightClicked()) {
            insertKeyframe(i, currentFrame);
          }

          if (ImGui::NeoCanDeleteSelection()) {
            const bool deleteByKeyboard = ImGui::IsKeyPressed(ImGuiKey_Delete, false) || ImGui::IsKeyPressed(ImGuiKey_Backspace, false);
            const bool deleteByMouse = ImGui::IsNeoKeyframeSelectionRightClicked();
            if (deleteByKeyboard || deleteByMouse) {
              removeSelectedKeyframesFromLane(i);
            }
          }

          ImGui::EndNeoTimeLine();
        }

        lanesOpen_[i] = laneOpen;
      }

      ImGui::EndNeoGroup();
    }

    if (!ImGui::NeoIsSelecting() && !ImGui::NeoIsDraggingSelection()) {
      sanitizeAllLanes();
    }

    ImGui::EndNeoSequencer();
  }
}

//--------------------------------------------------------------
void ofApp::drawGui()
{
  ui.Begin();
  {
    if (ui.BeginWindow(bGuiMain)) {
      ui.AddLabelBig("Bang Sequencer");
      ui.AddLabel("One lane per void bang. Mouse edit + drag enabled.");
      ui.AddSpacingSeparated();

      ui.Add(play_, OFX_IM_TOGGLE_BIG_BORDER_BLINK, 2, true);
      ui.Add(loop_, OFX_IM_TOGGLE_BIG_BORDER, 2);

      ui.Add(bpm_, OFX_IM_HSLIDER_BIG);
      ui.Add(bars_, OFX_IM_STEPPER);

      ui.Add(ui.bLog, OFX_IM_TOGGLE_ROUNDED_SMALL);
      ui.AddLabel("Cursor: " + formatStepMusical(currentFrame) + " (step " + ofToString(currentFrame) + ")");
      ui.AddSpacingSeparated();

      ui.AddLabelBig("Manual Bang Buttons");
      for (std::size_t i = 0; i < kBangCount; ++i) {
        const bool sameLine = (i % 2 == 0);
        ui.Add(bangs_[i], OFX_IM_BUTTON_BIG_BORDER, 2, sameLine);
      }

      ui.AddSpacingSeparated();
      for (std::size_t i = 0; i < kBangCount; ++i) {
        if (i % 4 != 0) ImGui::SameLine();
        ImGui::Text("%s:%s", getLaneLabel(i).c_str(), effectState_[i] ? "ON" : "OFF");
      }

      ui.EndWindow();
    }

    if (ui.BeginWindow(bGuiTimeline)) {
      ui.AddLabel("Mouse timeline edit:");
      ui.AddLabel("- Double Left Click on selected lane: add point at cursor");
      ui.AddLabel("- Right Click empty selected lane: add point at cursor");
      ui.AddLabel("- Right Click on a keyframe: remove point");
      ui.AddLabel("- Left Drag keyframes/selection: move points");
      ui.AddSpacingSeparated();

      drawTimeline();

      ui.EndWindow();
    }
  }
  ui.End();
}

//--------------------------------------------------------------
void ofApp::exit()
{
  ui.save();
}

//--------------------------------------------------------------
void ofApp::setupBangParameters()
{
  bangs_.clear();
  bangs_.reserve(kBangCount);
  for (std::size_t i = 0; i < kBangCount; ++i) {
    bangs_.emplace_back();
    bangs_.back().set("FX " + ofToString(i + 1));
  }
}

//--------------------------------------------------------------
void ofApp::setupBangListeners()
{
  for (std::size_t i = 0; i < kBangCount; ++i) {
    bangListeners_[i] = bangs_[i].newListener([this, i](const void*) {
      onBangTriggered(i);
    });
  }
}

//--------------------------------------------------------------
void ofApp::onBangTriggered(std::size_t index)
{
  if (index >= kBangCount) return;

  effectState_[index] = !effectState_[index];
  lastBangTriggeredTime_[index] = ofGetElapsedTimef();

  const std::string stateLabel = effectState_[index] ? "ON" : "OFF";
  std::string text = getLaneLabel(index) + " -> " + stateLabel;
  std::string tag = "BANG";
  if (timelineTriggerContext_) {
    text += " @ " + formatStepMusical(timelineTriggerStep_);
    tag = "SEQ";
  }

  ui.AddToLog(text, tag);
  ofLogNotice("ofApp") << text;
}

//--------------------------------------------------------------
void ofApp::triggerBangFromTimeline(std::size_t index, ImGui::FrameIndexType step)
{
  if (index >= kBangCount) return;

  timelineTriggerContext_ = true;
  timelineTriggerStep_ = step;
  bangs_[index].trigger();
  timelineTriggerContext_ = false;
}

//--------------------------------------------------------------
void ofApp::updateTransport(double deltaSeconds)
{
  updateTimelineBounds();

  if (!play_) {
    wasPlaying_ = false;
    transportAccumulator_ = 0.0;
    return;
  }

  const float safeBpm = std::max(1.0f, bpm_.get());
  const double secondsPer16th = 60.0 / (static_cast<double>(safeBpm) * 4.0);

  if (!wasPlaying_) {
    processTimelineStep(currentFrame);
    wasPlaying_ = true;
  }

  transportAccumulator_ += deltaSeconds;
  while (transportAccumulator_ >= secondsPer16th) {
    transportAccumulator_ -= secondsPer16th;

    if (currentFrame >= endFrame) {
      if (loop_) currentFrame = startFrame;
      else {
        currentFrame = endFrame;
        play_ = false;
        break;
      }
    } else currentFrame++;

    processTimelineStep(currentFrame);
  }
}

//--------------------------------------------------------------
void ofApp::processTimelineStep(ImGui::FrameIndexType step)
{
  for (std::size_t i = 0; i < kBangCount; ++i) {
    const auto& lane = timelineKeys_[i];
    if (std::binary_search(lane.begin(), lane.end(), step)) {
      triggerBangFromTimeline(i, step);
    }
  }
}

//--------------------------------------------------------------
bool ofApp::insertKeyframe(std::size_t laneIndex, ImGui::FrameIndexType step)
{
  if (laneIndex >= kBangCount) return false;

  const ImGui::FrameIndexType clamped = std::clamp(step, static_cast<ImGui::FrameIndexType>(startFrame), static_cast<ImGui::FrameIndexType>(endFrame));
  auto& lane = timelineKeys_[laneIndex];
  if (std::find(lane.begin(), lane.end(), clamped) != lane.end()) return false;

  lane.push_back(clamped);
  sanitizeLane(laneIndex);
  ui.AddToLog("Add " + getLaneLabel(laneIndex) + " @ " + formatStepMusical(clamped), "EDIT");
  return true;
}

//--------------------------------------------------------------
bool ofApp::removeKeyframe(std::size_t laneIndex, ImGui::FrameIndexType step)
{
  if (laneIndex >= kBangCount) return false;

  auto& lane = timelineKeys_[laneIndex];
  const auto it = std::remove(lane.begin(), lane.end(), step);
  if (it == lane.end()) return false;

  lane.erase(it, lane.end());
  sanitizeLane(laneIndex);
  ui.AddToLog("Remove " + getLaneLabel(laneIndex) + " @ " + formatStepMusical(step), "EDIT");
  return true;
}

//--------------------------------------------------------------
void ofApp::removeSelectedKeyframesFromLane(std::size_t laneIndex)
{
  if (laneIndex >= kBangCount) return;

  const uint32_t count = ImGui::GetNeoKeyframeSelectionSize();
  if (count == 0) return;

  std::vector<ImGui::FrameIndexType> toRemove(count);
  ImGui::GetNeoKeyframeSelection(toRemove.data());

  auto& lane = timelineKeys_[laneIndex];
  for (auto frame : toRemove) {
    lane.erase(std::remove(lane.begin(), lane.end(), frame), lane.end());
  }

  sanitizeLane(laneIndex);
  ImGui::NeoClearSelection();
  ui.AddToLog("Delete selection on " + getLaneLabel(laneIndex), "EDIT");
}

//--------------------------------------------------------------
void ofApp::sanitizeLane(std::size_t laneIndex)
{
  if (laneIndex >= kBangCount) return;

  auto& lane = timelineKeys_[laneIndex];
  for (auto& frame : lane) {
    frame = std::clamp(frame, static_cast<ImGui::FrameIndexType>(startFrame), static_cast<ImGui::FrameIndexType>(endFrame));
  }
  std::sort(lane.begin(), lane.end());
  lane.erase(std::unique(lane.begin(), lane.end()), lane.end());
}

//--------------------------------------------------------------
void ofApp::sanitizeAllLanes()
{
  for (std::size_t i = 0; i < kBangCount; ++i) {
    sanitizeLane(i);
  }
}

//--------------------------------------------------------------
void ofApp::updateTimelineBounds()
{
  const auto totalSteps = static_cast<int32_t>(std::max<std::size_t>(16, getTotalSteps()));
  startFrame = 0;
  endFrame = std::max(1, totalSteps) - 1;
  currentFrame = std::clamp(currentFrame, startFrame, endFrame);
}

//--------------------------------------------------------------
std::size_t ofApp::getTotalSteps() const
{
  return static_cast<std::size_t>(bars_.get()) * 16u;
}

//--------------------------------------------------------------
std::string ofApp::getLaneLabel(std::size_t laneIndex) const
{
  if (laneIndex < bangs_.size()) return bangs_[laneIndex].getName();
  return "FX " + ofToString(laneIndex + 1);
}

//--------------------------------------------------------------
std::string ofApp::formatStepMusical(ImGui::FrameIndexType step) const
{
  const int32_t clamped = std::max(0, step);
  const int32_t bar = clamped / 16 + 1;
  const int32_t beat = (clamped % 16) / 4 + 1;
  const int32_t sixteenth = clamped % 4 + 1;
  return "Bar " + ofToString(bar) + " Beat " + ofToString(beat) + " 1/16 " + ofToString(sixteenth);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == ' ') play_ = !play_;
  if (key == 'g' || key == 'G') bGuiMain = !bGuiMain;
  if (key == 't' || key == 'T') bGuiTimeline = !bGuiTimeline;
  if (key == 'r' || key == 'R') currentFrame = startFrame;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
