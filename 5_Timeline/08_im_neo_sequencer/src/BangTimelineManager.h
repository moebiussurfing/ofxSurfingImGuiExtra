#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "ofMain.h"

#include "BangParticle.h"
#include "imgui_neo_internal.h"
#include "imgui_neo_sequencer.h"
#include "ofxSurfingImGui.h"

class ofApp;

class BangTimelineManager {
public:
  static constexpr std::size_t kBangCount = 8;

  void setup(ofApp* app, ofxSurfingGui* ui)
  {
    app_ = app;
    ui_ = ui;

    setupBangParameters();
    setupBangListeners();
    setupActionListeners();

    timelineKeys_.assign(kBangCount, {});
    lanesOpen_.assign(kBangCount, true);
    laneMute_.assign(kBangCount, false);
    laneSolo_.assign(kBangCount, false);
    effectState_.assign(kBangCount, false);
    lastBangTriggeredTime_.assign(kBangCount, -1000.0f);

    particles_.reserve(256);

    laneColors_ = {
      ofFloatColor::fromHex(0xFF4D6D),
      ofFloatColor::fromHex(0xF59E0B),
      ofFloatColor::fromHex(0xFDE047),
      ofFloatColor::fromHex(0x22C55E),
      ofFloatColor::fromHex(0x06B6D4),
      ofFloatColor::fromHex(0x3B82F6),
      ofFloatColor::fromHex(0x8B5CF6),
      ofFloatColor::fromHex(0xEC4899)
    };

    // Seed a small pattern so the app starts with visible activity.
    timelineKeys_[0] = { 0, 8, 16, 24, 32, 40, 48, 56 };
    timelineKeys_[1] = { 4, 12, 20, 28, 36, 44, 52, 60 };
    timelineKeys_[2] = { 0, 16, 32, 48 };
    timelineKeys_[3] = { 8, 24, 40, 56 };

    updateTimelineBounds();
    sanitizeAllLanes();

    auto& style = ImGui::GetNeoSequencerStyle();
    style.MaxSizePerTick = 8.0f;

    if (ui_) {
      ui_->AddToLog("Neo sequencer ready. Mouse edit + drag enabled.", "INFO");
    }
  }

  void update(double deltaSeconds)
  {
    updateTransport(deltaSeconds);
    updateParticles(static_cast<float>(deltaSeconds));
  }

  void drawParticles() const
  {
    ofPushStyle();
    ofFill();
    for (const auto& particle : particles_) {
      particle.draw();
    }
    ofPopStyle();
  }

  void drawMainUi()
  {
    if (!ui_) return;

    ui_->AddLabelBig("Bang Sequencer");
    ui_->AddLabel("8 tracks of ofParameter<void> bangs. Mouse timeline editor.");
    ui_->AddSpacingSeparated();

    ui_->Add(play_, OFX_IM_TOGGLE_BIG_BORDER_BLINK, 2, true);
    ui_->Add(loop_, OFX_IM_TOGGLE_BIG_BORDER, 2);

    ui_->Add(bpm_, OFX_IM_HSLIDER_BIG);
    ui_->Add(bars_, OFX_IM_STEPPER);

    ui_->Add(ui_->bLog, OFX_IM_TOGGLE_ROUNDED_SMALL);
    ui_->AddLabel("Cursor: " + formatStepMusical(currentFrame_) + " (step " + ofToString(currentFrame_) + ")");

    ui_->AddSpacingSeparated();
    ui_->AddLabelBig("Scene");
    ui_->Add(saveScene_, OFX_IM_BUTTON_BORDER, 2, true);
    ui_->Add(loadScene_, OFX_IM_BUTTON_BORDER, 2);

    ui_->Add(clearAll_, OFX_IM_BUTTON_BORDER_BLINK, 2, true);
    ImGui::BeginDisabled(selectedLane_ < 0);
    ui_->Add(clearSelected_, OFX_IM_BUTTON_BORDER, 2);
    ImGui::EndDisabled();

    if (selectedLane_ >= 0) {
      ui_->AddLabel("Selected lane: " + getLaneLabel(static_cast<std::size_t>(selectedLane_)));
    } else {
      ui_->AddLabel("Selected lane: none");
    }

    ui_->AddLabel("JSON: " + ofToDataPath(scenePath_, true));

    ui_->AddSpacingSeparated();
    ui_->AddLabelBig("Manual Bang Buttons");
    for (std::size_t i = 0; i < kBangCount; ++i) {
      const bool sameLine = (i % 2 == 0);
      ui_->Add(bangs_[i], OFX_IM_BUTTON_BIG_BORDER, 2, sameLine);
    }

    ui_->AddSpacingSeparated();
    for (std::size_t i = 0; i < kBangCount; ++i) {
      if (i % 4 != 0) ImGui::SameLine();
      const bool active = effectState_[i];
      ImGui::TextColored(toImVec4(laneColors_[i], active ? 1.0f : 0.45f), "%s:%s",
        getLaneLabel(i).c_str(), active ? "ON" : "off");
    }
  }

  void drawTimelineUi()
  {
    if (!ui_) return;

    ui_->AddLabel("Mouse timeline edit:");
    ui_->AddLabel("- Double Left Click on selected lane: add bang at cursor");
    ui_->AddLabel("- Right Click empty selected lane: add bang at cursor");
    ui_->AddLabel("- Right Click keyframe: remove bang");
    ui_->AddLabel("- Left Drag selected keyframes: move bangs");
    ui_->AddSpacingSeparated();

    constexpr float leftPanelWidth = 210.0f;
    ImGui::BeginChild("##tracks_left", ImVec2(leftPanelWidth, 0.0f), true);
    drawTracksLeftPanel();
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("##tracks_timeline", ImVec2(0.0f, 0.0f), false);
    drawTimelineSequencer();
    ImGui::EndChild();
  }

  void keyPressed(int key)
  {
    if (key == ' ') play_ = !play_;
    if (key == 'r' || key == 'R') currentFrame_ = startFrame_;
    if (key >= '1' && key <= '8') {
      const std::size_t index = static_cast<std::size_t>(key - '1');
      if (index < bangs_.size()) {
        bangs_[index].trigger();
      }
    }
  }

  void exit()
  {
    saveSceneToDisk();
  }

private:
  ofApp* app_ = nullptr;
  ofxSurfingGui* ui_ = nullptr;

  std::vector<ofParameter<void>> bangs_;
  std::array<ofEventListener, kBangCount> bangListeners_;
  std::array<ofEventListener, 4> actionListeners_;

  std::vector<std::vector<ImGui::FrameIndexType>> timelineKeys_;
  std::vector<bool> lanesOpen_;
  std::vector<bool> laneMute_;
  std::vector<bool> laneSolo_;
  std::vector<bool> effectState_;
  std::vector<float> lastBangTriggeredTime_;

  std::array<ofFloatColor, kBangCount> laneColors_{};
  std::vector<BangParticle> particles_;

  ofParameter<float> bpm_{ "BPM", 120.0f, 40.0f, 240.0f };
  ofParameter<int> bars_{ "Bars", 4, 1, 32 };
  ofParameter<bool> play_{ "Play", false };
  ofParameter<bool> loop_{ "Loop", true };

  ofParameter<void> clearAll_{ "Clear All Tracks" };
  ofParameter<void> clearSelected_{ "Clear Selected Track" };
  ofParameter<void> saveScene_{ "Save Scene JSON" };
  ofParameter<void> loadScene_{ "Load Scene JSON" };

  ImGui::FrameIndexType currentFrame_ = 0;
  ImGui::FrameIndexType startFrame_ = 0;
  ImGui::FrameIndexType endFrame_ = 63;

  bool channelsGroupOpen_ = true;
  bool timelineTriggerContext_ = false;
  ImGui::FrameIndexType timelineTriggerStep_ = 0;

  int selectedLane_ = -1;
  int pendingSelectedLane_ = -1;

  double transportAccumulator_ = 0.0;
  bool wasPlaying_ = false;

  std::string scenePath_ = "bang_timeline_scene.json";

  static ImVec4 toImVec4(const ofFloatColor& color, float alpha = -1.0f)
  {
    const float finalAlpha = (alpha < 0.0f) ? color.a : alpha;
    return { color.r, color.g, color.b, finalAlpha };
  }

  void setupBangParameters()
  {
    bangs_.clear();
    bangs_.reserve(kBangCount);
    for (std::size_t i = 0; i < kBangCount; ++i) {
      bangs_.emplace_back();
      bangs_.back().set("FX " + ofToString(i + 1));
    }
  }

  void setupBangListeners()
  {
    for (std::size_t i = 0; i < kBangCount; ++i) {
      bangListeners_[i] = bangs_[i].newListener([this, i](const void*) {
        onBangTriggered(i);
      });
    }
  }

  void setupActionListeners()
  {
    actionListeners_[0] = clearAll_.newListener([this](const void*) {
      clearAllLanes();
    });

    actionListeners_[1] = clearSelected_.newListener([this](const void*) {
      clearSelectedLane();
    });

    actionListeners_[2] = saveScene_.newListener([this](const void*) {
      saveSceneToDisk();
    });

    actionListeners_[3] = loadScene_.newListener([this](const void*) {
      loadSceneFromDisk();
    });
  }

  void drawTracksLeftPanel()
  {
    ImGui::TextUnformatted("Tracks");
    ImGui::Separator();

    for (std::size_t i = 0; i < kBangCount; ++i) {
      ImGui::PushID(static_cast<int>(i));

      const bool selected = (selectedLane_ == static_cast<int>(i));
      if (selected) {
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 220, 120, 255));
      }

      if (ImGui::SmallButton(selected ? "SEL*" : "SEL")) {
        pendingSelectedLane_ = static_cast<int>(i);
        selectedLane_ = static_cast<int>(i);
      }

      if (selected) {
        ImGui::PopStyleColor();
      }

      ImGui::SameLine();
      if (laneSolo_[i]) {
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(60, 160, 60, 255));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(80, 190, 80, 255));
      }
      if (ImGui::SmallButton(laneSolo_[i] ? "SOLO" : "solo")) {
        laneSolo_[i] = !laneSolo_[i];
      }
      if (laneSolo_[i]) {
        ImGui::PopStyleColor(2);
      }

      ImGui::SameLine();
      if (laneMute_[i]) {
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(190, 60, 60, 255));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(220, 80, 80, 255));
      }
      if (ImGui::SmallButton(laneMute_[i] ? "MUTE" : "mute")) {
        laneMute_[i] = !laneMute_[i];
      }
      if (laneMute_[i]) {
        ImGui::PopStyleColor(2);
      }

      ImGui::SameLine();
      ImGui::TextColored(toImVec4(laneColors_[i], 1.0f), "%s", getLaneLabel(i).c_str());

      ImGui::SameLine();
      ImGui::TextDisabled("(%d)", static_cast<int>(timelineKeys_[i].size()));

      ImGui::PopID();
    }

    ImGui::Separator();
    if (ImGui::Button("Clear ALL", ImVec2(-1.0f, 0.0f))) {
      clearAllLanes();
    }

    ImGui::BeginDisabled(selectedLane_ < 0);
    if (ImGui::Button("Clear Selected", ImVec2(-1.0f, 0.0f))) {
      clearSelectedLane();
    }
    ImGui::EndDisabled();
  }

  void drawTimelineSequencer()
  {
    updateTimelineBounds();

    const ImGuiNeoSequencerFlags flags =
      ImGuiNeoSequencerFlags_EnableSelection |
      ImGuiNeoSequencerFlags_Selection_EnableDragging |
      ImGuiNeoSequencerFlags_Selection_EnableDeletion |
      ImGuiNeoSequencerFlags_AlwaysShowHeader;

    const ImVec2 size{ 0.0f, std::max(260.0f, ImGui::GetContentRegionAvail().y) };

    if (!ImGui::BeginNeoSequencer("BangSequencer", &currentFrame_, &startFrame_, &endFrame_, size, flags)) {
      return;
    }

    if (pendingSelectedLane_ >= 0 && pendingSelectedLane_ < static_cast<int>(kBangCount)) {
      ImGui::SetSelectedTimeline(getLaneTimelineId(static_cast<std::size_t>(pendingSelectedLane_)).c_str());
      selectedLane_ = pendingSelectedLane_;
      pendingSelectedLane_ = -1;
    }

    if (ImGui::BeginNeoGroup("Bang Channels", &channelsGroupOpen_)) {
      for (std::size_t i = 0; i < kBangCount; ++i) {
        const ImVec4 keyColor = toImVec4(laneColors_[i], 0.55f);
        const ImVec4 hoverColor = toImVec4(laneColors_[i], 0.95f);
        const ImVec4 selectedColor = toImVec4(laneColors_[i].getLerped(ofFloatColor::white, 0.2f), 1.0f);

        ImGui::PushNeoSequencerStyleColor(ImGuiNeoSequencerCol_Keyframe, keyColor);
        ImGui::PushNeoSequencerStyleColor(ImGuiNeoSequencerCol_KeyframeHovered, hoverColor);
        ImGui::PushNeoSequencerStyleColor(ImGuiNeoSequencerCol_KeyframeSelected, selectedColor);

        bool laneOpen = lanesOpen_[i];
        const std::string laneId = getLaneTimelineId(i);

        if (ImGui::BeginNeoTimelineEx(laneId.c_str(), &laneOpen)) {
          if (ImGui::IsNeoTimelineSelected()) {
            selectedLane_ = static_cast<int>(i);
          }

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

          if (canInsert && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && !hoveredAnyKey) {
            insertKeyframe(i, currentFrame_);
          }

          if (canInsert && ImGui::IsMouseClicked(ImGuiMouseButton_Right) && !hoveredAnyKey &&
            !ImGui::IsNeoKeyframeSelectionRightClicked()) {
            insertKeyframe(i, currentFrame_);
          }

          if (ImGui::NeoCanDeleteSelection()) {
            const bool deleteByKeyboard = ImGui::IsKeyPressed(ImGuiKey_Delete, false) ||
              ImGui::IsKeyPressed(ImGuiKey_Backspace, false);
            const bool deleteByMouse = ImGui::IsNeoKeyframeSelectionRightClicked();
            if (deleteByKeyboard || deleteByMouse) {
              removeSelectedKeyframesFromLane(i);
            }
          }

          ImGui::EndNeoTimeLine();
        }

        lanesOpen_[i] = laneOpen;
        ImGui::PopNeoSequencerStyleColor(3);
      }

      ImGui::EndNeoGroup();
    }

    if (!ImGui::NeoIsSelecting() && !ImGui::NeoIsDraggingSelection()) {
      sanitizeAllLanes();
    }

    ImGui::EndNeoSequencer();
  }

  void onBangTriggered(std::size_t index)
  {
    if (index >= kBangCount) return;

    effectState_[index] = !effectState_[index];
    lastBangTriggeredTime_[index] = ofGetElapsedTimef();

    spawnParticle(index);

    const std::string stateLabel = effectState_[index] ? "ON" : "OFF";
    std::string text = getLaneLabel(index) + " -> " + stateLabel;
    std::string tag = "BANG";
    if (timelineTriggerContext_) {
      text += " @ " + formatStepMusical(timelineTriggerStep_);
      tag = "SEQ";
    }

    if (ui_) {
      ui_->AddToLog(text, tag);
    }

    ofLogNotice("BangTimelineManager") << text;
  }

  void spawnParticle(std::size_t index)
  {
    if (index >= kBangCount) return;

    const float w = static_cast<float>(ofGetWidth());
    const float h = static_cast<float>(ofGetHeight());
    const float marginX = std::min(80.0f, w * 0.35f);
    const float marginY = std::min(80.0f, h * 0.35f);

    const float xMin = marginX;
    const float xMax = std::max(xMin + 1.0f, w - marginX);
    const float yMin = marginY;
    const float yMax = std::max(yMin + 1.0f, h - marginY);

    const float x = ofRandom(xMin, xMax);
    const float y = ofRandom(yMin, yMax);
    const float radius = ofRandom(34.0f, 88.0f);

    particles_.emplace_back(ofVec2f(x, y), laneColors_[index], radius, 1.0f);
  }

  void updateParticles(float deltaSeconds)
  {
    for (auto& particle : particles_) {
      particle.update(deltaSeconds);
    }

    particles_.erase(std::remove_if(
      particles_.begin(), particles_.end(), [](const BangParticle& particle) {
      return !particle.isAlive();
    }), particles_.end());
  }

  void triggerBangFromTimeline(std::size_t index, ImGui::FrameIndexType step)
  {
    if (index >= kBangCount) return;

    timelineTriggerContext_ = true;
    timelineTriggerStep_ = step;
    bangs_[index].trigger();
    timelineTriggerContext_ = false;
  }

  bool isLanePlayable(std::size_t index) const
  {
    if (index >= kBangCount) return false;

    const bool anySolo = std::any_of(laneSolo_.begin(), laneSolo_.end(), [](bool b) {
      return b;
    });

    if (anySolo) {
      return laneSolo_[index] && !laneMute_[index];
    }

    return !laneMute_[index];
  }

  void updateTransport(double deltaSeconds)
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
      processTimelineStep(currentFrame_);
      wasPlaying_ = true;
    }

    transportAccumulator_ += std::max(0.0, deltaSeconds);
    while (transportAccumulator_ >= secondsPer16th) {
      transportAccumulator_ -= secondsPer16th;

      if (currentFrame_ >= endFrame_) {
        if (loop_) {
          currentFrame_ = startFrame_;
        } else {
          currentFrame_ = endFrame_;
          play_ = false;
          break;
        }
      } else {
        currentFrame_++;
      }

      processTimelineStep(currentFrame_);
    }
  }

  void processTimelineStep(ImGui::FrameIndexType step)
  {
    for (std::size_t i = 0; i < kBangCount; ++i) {
      if (!isLanePlayable(i)) continue;

      const auto& lane = timelineKeys_[i];
      if (std::binary_search(lane.begin(), lane.end(), step)) {
        triggerBangFromTimeline(i, step);
      }
    }
  }

  bool insertKeyframe(std::size_t laneIndex, ImGui::FrameIndexType step)
  {
    if (laneIndex >= kBangCount) return false;

    const ImGui::FrameIndexType clamped = std::clamp(step, startFrame_, endFrame_);
    auto& lane = timelineKeys_[laneIndex];
    if (std::find(lane.begin(), lane.end(), clamped) != lane.end()) return false;

    lane.push_back(clamped);
    sanitizeLane(laneIndex);

    if (ui_) {
      ui_->AddToLog("Add " + getLaneLabel(laneIndex) + " @ " + formatStepMusical(clamped), "EDIT");
    }

    return true;
  }

  bool removeKeyframe(std::size_t laneIndex, ImGui::FrameIndexType step)
  {
    if (laneIndex >= kBangCount) return false;

    auto& lane = timelineKeys_[laneIndex];
    const auto it = std::remove(lane.begin(), lane.end(), step);
    if (it == lane.end()) return false;

    lane.erase(it, lane.end());
    sanitizeLane(laneIndex);

    if (ui_) {
      ui_->AddToLog("Remove " + getLaneLabel(laneIndex) + " @ " + formatStepMusical(step), "EDIT");
    }

    return true;
  }

  void removeSelectedKeyframesFromLane(std::size_t laneIndex)
  {
    if (laneIndex >= kBangCount) return;

    const uint32_t count = ImGui::GetNeoKeyframeSelectionSize();
    if (count == 0) return;

    std::vector<ImGui::FrameIndexType> toRemove(count);
    ImGui::GetNeoKeyframeSelection(toRemove.data());

    auto& lane = timelineKeys_[laneIndex];
    for (const auto frame : toRemove) {
      lane.erase(std::remove(lane.begin(), lane.end(), frame), lane.end());
    }

    sanitizeLane(laneIndex);
    ImGui::NeoClearSelection();

    if (ui_) {
      ui_->AddToLog("Delete selection on " + getLaneLabel(laneIndex), "EDIT");
    }
  }

  void clearAllLanes()
  {
    for (auto& lane : timelineKeys_) {
      lane.clear();
    }

    if (ui_) {
      ui_->AddToLog("Clear all lanes", "EDIT");
    }

    ofLogNotice("BangTimelineManager") << "All lanes cleared.";
  }

  void clearSelectedLane()
  {
    if (selectedLane_ < 0 || selectedLane_ >= static_cast<int>(kBangCount)) {
      if (ui_) {
        ui_->AddToLog("Clear selected ignored: no lane selected", "WARN");
      }
      return;
    }

    auto& lane = timelineKeys_[static_cast<std::size_t>(selectedLane_)];
    lane.clear();

    if (ui_) {
      ui_->AddToLog("Clear " + getLaneLabel(static_cast<std::size_t>(selectedLane_)), "EDIT");
    }
  }

  void sanitizeLane(std::size_t laneIndex)
  {
    if (laneIndex >= kBangCount) return;

    auto& lane = timelineKeys_[laneIndex];
    for (auto& frame : lane) {
      frame = std::clamp(frame, startFrame_, endFrame_);
    }

    std::sort(lane.begin(), lane.end());
    lane.erase(std::unique(lane.begin(), lane.end()), lane.end());
  }

  void sanitizeAllLanes()
  {
    for (std::size_t i = 0; i < kBangCount; ++i) {
      sanitizeLane(i);
    }
  }

  void updateTimelineBounds()
  {
    const auto totalSteps = static_cast<ImGui::FrameIndexType>(std::max<std::size_t>(16, getTotalSteps()));
    startFrame_ = 0;
    endFrame_ = std::max<ImGui::FrameIndexType>(1, totalSteps) - 1;
    currentFrame_ = std::clamp(currentFrame_, startFrame_, endFrame_);
  }

  std::size_t getTotalSteps() const
  {
    return static_cast<std::size_t>(bars_.get()) * 16u;
  }

  std::string getLaneLabel(std::size_t laneIndex) const
  {
    if (laneIndex < bangs_.size()) return bangs_[laneIndex].getName();
    return "FX " + ofToString(laneIndex + 1);
  }

  std::string getLaneTimelineId(std::size_t laneIndex) const
  {
    return getLaneLabel(laneIndex) + "##lane_" + ofToString(laneIndex);
  }

  std::string formatStepMusical(ImGui::FrameIndexType step) const
  {
    const ImGui::FrameIndexType clamped = std::max<ImGui::FrameIndexType>(0, step);
    const ImGui::FrameIndexType bar = clamped / 16 + 1;
    const ImGui::FrameIndexType beat = (clamped % 16) / 4 + 1;
    const ImGui::FrameIndexType sixteenth = clamped % 4 + 1;
    return "Bar " + ofToString(bar) + " Beat " + ofToString(beat) + " 1/16 " + ofToString(sixteenth);
  }

  void saveSceneToDisk() const
  {
    ofJson root;
    root["version"] = 1;
    root["bpm"] = bpm_.get();
    root["bars"] = bars_.get();
    root["currentFrame"] = currentFrame_;
    root["loop"] = loop_.get();
    root["play"] = play_.get();

    root["lanes"] = ofJson::array();
    for (std::size_t i = 0; i < kBangCount; ++i) {
      ofJson lane;
      lane["index"] = static_cast<int>(i);
      lane["name"] = getLaneLabel(i);
      lane["mute"] = laneMute_[i];
      lane["solo"] = laneSolo_[i];
      lane["keys"] = ofJson::array();

      for (const auto frame : timelineKeys_[i]) {
        lane["keys"].push_back(frame);
      }

      root["lanes"].push_back(lane);
    }

    const std::string path = ofToDataPath(scenePath_, true);
    const bool ok = ofSavePrettyJson(path, root);
    if (ok) {
      ofLogNotice("BangTimelineManager") << "Scene saved: " << path;
      if (ui_) ui_->AddToLog("Scene saved", "FILE");
    } else {
      ofLogError("BangTimelineManager") << "Unable to save scene: " << path;
      if (ui_) ui_->AddToLog("Scene save failed", "ERROR");
    }
  }

  void loadSceneFromDisk()
  {
    const std::string path = ofToDataPath(scenePath_, true);
    ofFile file(path);
    if (!file.exists()) {
      ofLogWarning("BangTimelineManager") << "Scene file not found: " << path;
      if (ui_) ui_->AddToLog("Scene file not found", "WARN");
      return;
    }

    const ofJson root = ofLoadJson(path);
    if (root.is_discarded()) {
      ofLogError("BangTimelineManager") << "Invalid JSON scene file: " << path;
      if (ui_) ui_->AddToLog("Scene load failed (invalid JSON)", "ERROR");
      return;
    }

    if (root.contains("bpm")) {
      bpm_ = ofClamp(root["bpm"].get<float>(), bpm_.getMin(), bpm_.getMax());
    }
    if (root.contains("bars")) {
      bars_ = ofClamp(root["bars"].get<int>(), bars_.getMin(), bars_.getMax());
    }
    if (root.contains("loop")) {
      loop_ = root["loop"].get<bool>();
    }
    if (root.contains("play")) {
      play_ = root["play"].get<bool>();
    }

    if (root.contains("lanes") && root["lanes"].is_array()) {
      for (auto& lane : timelineKeys_) {
        lane.clear();
      }

      const auto& lanesJson = root["lanes"];
      const std::size_t count = std::min<std::size_t>(kBangCount, lanesJson.size());
      for (std::size_t i = 0; i < count; ++i) {
        const auto& lane = lanesJson[i];

        laneMute_[i] = lane.value("mute", false);
        laneSolo_[i] = lane.value("solo", false);

        if (lane.contains("keys") && lane["keys"].is_array()) {
          timelineKeys_[i].reserve(lane["keys"].size());
          for (const auto& key : lane["keys"]) {
            if (key.is_number_integer()) {
              timelineKeys_[i].push_back(key.get<ImGui::FrameIndexType>());
            }
          }
        }

        sanitizeLane(i);
      }
    }

    updateTimelineBounds();
    if (root.contains("currentFrame") && root["currentFrame"].is_number_integer()) {
      currentFrame_ = std::clamp(root["currentFrame"].get<ImGui::FrameIndexType>(), startFrame_, endFrame_);
    }

    ofLogNotice("BangTimelineManager") << "Scene loaded: " << path;
    if (ui_) ui_->AddToLog("Scene loaded", "FILE");
  }
};
