#include "ofApp.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

//--------------------------------------------------------------
void ofApp::setup()
{
  ui.setName("NeoBangSequencer");
  ui.setup();
  ui.bAutoResize = false;
  ui.bLog = true;

  manager_.setup(this, &ui);
  laneColors_ = manager_.getLaneColors();
  particles_.reserve(256);

  manager_.setBangCallback([this](std::size_t lane, ImGui::FrameIndexType step, bool fromTimeline) {
    onBangEvent(lane, step, fromTimeline);
  });

  lastUpdateTime_ = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update()
{
  const double now = ofGetElapsedTimef();
  const double deltaSeconds = std::max(0.0, now - lastUpdateTime_);
  lastUpdateTime_ = now;

  manager_.update(deltaSeconds);
  updateParticles(static_cast<float>(deltaSeconds));
}

//--------------------------------------------------------------
void ofApp::draw()
{
  drawParticles();
  drawGui();
}

//--------------------------------------------------------------
void ofApp::drawGui()
{
  ui.Begin();
  {
    if (ui.BeginWindow(bGuiMain)) {
      drawMainBangPanel();
      ui.EndWindow();
    }

    if (ui.BeginWindow(bGuiTransport)) {
      manager_.drawTransportUi();
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
void ofApp::drawMainBangPanel()
{
  ui.AddLabelBig("Bang Actions");
  ui.AddLabel("Manual bangs + preview int (driven by timeline bangs).");

  ui.Add(bangDrawInt_, OFX_IM_HSLIDER_BIG);
  ui.AddSpacingSeparated();

  ui.AddLabelBig("Manual Bang Buttons");

  auto& bangs = manager_.getBangParameters();
  for (std::size_t i = 0; i < bangs.size(); ++i) {
    const bool sameLine = (i % 2 == 0);
    ui.Add(bangs[i], OFX_IM_BUTTON_BIG_BORDER, 2, sameLine);
  }
}

//--------------------------------------------------------------
void ofApp::onBangEvent(std::size_t lane, ImGui::FrameIndexType step, bool fromTimeline)
{
  if (lane >= BangTimelineManager::kBangCount) return;

  bangDrawInt_ = static_cast<int>(lane);
  spawnParticleForLane(lane);

  const int r = ofClamp(static_cast<int>(laneColors_[lane].r * 255.0f), 0, 255);
  const int g = ofClamp(static_cast<int>(laneColors_[lane].g * 255.0f), 0, 255);
  const int b = ofClamp(static_cast<int>(laneColors_[lane].b * 255.0f), 0, 255);
  std::ostringstream colorHex;
  colorHex << '#' << std::uppercase << std::hex << std::setfill('0')
           << std::setw(2) << r << std::setw(2) << g << std::setw(2) << b;

  const std::string source = fromTimeline ? "[SEQ] " : "[MAN] ";
  const std::string message = source + "bang " + ofToString(lane) + " @ step " + ofToString(step);
  ui.AddToLog(message, "INFO");
}

//--------------------------------------------------------------
void ofApp::spawnParticleForLane(std::size_t lane)
{
  if (lane >= BangTimelineManager::kBangCount) return;

  const float laneCount = static_cast<float>(BangTimelineManager::kBangCount);
  const float w = static_cast<float>(ofGetWidth());
  const float h = static_cast<float>(ofGetHeight());
  const float laneWidth = std::max(1.0f, w / laneCount);

  const float x = laneWidth * static_cast<float>(lane) + laneWidth * 0.5f;
  const float y = std::max(16.0f, h - 56.0f);

  particles_.emplace_back(ofVec2f(x, y), laneColors_[lane], 56.0f, 1.0f);
}

//--------------------------------------------------------------
void ofApp::updateParticles(float deltaSeconds)
{
  for (auto& particle : particles_) {
    particle.update(deltaSeconds);
  }

  particles_.erase(std::remove_if(
    particles_.begin(), particles_.end(), [](const BangParticle& particle) {
    return !particle.isAlive();
  }), particles_.end());
}

//--------------------------------------------------------------
void ofApp::drawParticles() const
{
  ofPushStyle();
  ofFill();
  for (const auto& particle : particles_) {
    particle.draw();
  }
  ofPopStyle();
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
  if (key == 'u' || key == 'U') bGuiTransport = !bGuiTransport;
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
