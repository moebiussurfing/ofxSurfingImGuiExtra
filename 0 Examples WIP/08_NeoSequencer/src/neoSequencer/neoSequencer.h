#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "imgui_neo_sequencer.h"
// take from https://gitlab.com/GroGy/im-neo-sequencer

class neoSequencer
{
public:

	neoSequencer() {
	};

	~neoSequencer() {
	};

	std::vector<uint32_t> keyframes = {0, 10, 40, 100};
	std::vector<uint32_t> keyframes2 = {30, 60, 90, 120};

	uint32_t m_pFrameIndex;
	uint32_t m_pFrameMin = 0;
	uint32_t m_pFrameMax = 60 * 2;
	bool m_pTransformOpen;

	void draw() {
		m_pFrameIndex = ofGetFrameNum() % m_pFrameMax;

		if (ImGui::BeginNeoSequencer("Custom Sequencer##sequencer", &m_pFrameIndex, &m_pFrameMin, &m_pFrameMax, { 0,0 })) {
			//if (ImGui::BeginNeoGroup("Transform", &m_pTransformOpen)) {
			//	ImU32 c = IM_COL32(0, 120, 120, 255);
			//	ImGui::PushNeoSequencerStyleColor(ImGuiNeoSequencerCol_Keyframe, c);
			//	if (ImGui::BeginNeoTimeline("Position", keyframes2)) {
			//		ImGui::EndNeoTimeLine();
			//	}
			//	ImGui::PopNeoSequencerStyleColor();
			//	ImGui::EndNeoTimeLine();
			//}
			if (ImGui::BeginNeoTimeline("Color", keyframes2)) {
				ImGui::EndNeoTimeLine();
			}
			if (ImGui::BeginNeoTimeline("Skeleton", keyframes)) {
				ImGui::EndNeoTimeLine();
			}

			//if (ImGui::BeginNeoTimeline("Sprite", keyframes)) {
			//	ImGui::EndNeoTimeLine();
			//}

			//if (ImGui::BeginNeoTimeline("Shader", keyframes)) {
			//	ImGui::EndNeoTimeLine();
			//}

			//if (ImGui::BeginNeoTimeline("Facing", keyframes)) {
			//	ImGui::EndNeoTimeLine();
			//}
			ImGui::EndNeoSequencer();
		}
	}

};