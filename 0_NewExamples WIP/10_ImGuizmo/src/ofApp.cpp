#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ui.setup();

	setupImGuizmo();
}

//--------------------------------------------------------------
void ofApp::setupImGuizmo()
{
	glGenTextures(1, &procTexture);
	glBindTexture(GL_TEXTURE_2D, procTexture);

	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			float dx = x + .5f;
			float dy = y + .5f;
			float dv = sinf(x * 0.02f) + sinf(0.03f * (x + y)) + sinf(sqrtf(0.4f * (dx * dx + dy * dy) + 1.f));

			tempBitmap[index] = 0xFF000000 +
				(int(255 * fabsf(sinf(dv * 3.141592f))) << 16) +
				(int(255 * fabsf(sinf(dv * 3.141592f + 2 * 3.141592f / 3))) << 8) +
				(int(255 * fabs(sin(dv * 3.141592f + 4.f * 3.141592f / 3.f))));

			index++;
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempBitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	delete[] tempBitmap;

	// sequence with default values
	mySequence.mFrameMin = -100;
	mySequence.mFrameMax = 1000;
	mySequence.myItems.push_back(MySequence::MySequenceItem{ 0, 10, 30, false });
	mySequence.myItems.push_back(MySequence::MySequenceItem{ 1, 20, 30, true });
	mySequence.myItems.push_back(MySequence::MySequenceItem{ 3, 12, 60, false });
	mySequence.myItems.push_back(MySequence::MySequenceItem{ 2, 61, 90, false });
	mySequence.myItems.push_back(MySequence::MySequenceItem{ 4, 90, 99, false });
}

//--------------------------------------------------------------
void ofApp::drawImGuizmo()
{
	ImGuiIO& io = ImGui::GetIO();
	if (isPerspective)
	{
		Perspective(fov, io.DisplaySize.x / io.DisplaySize.y, 0.1f, 100.f, cameraProjection);
	}
	else
	{
		float viewHeight = viewWidth * io.DisplaySize.y / io.DisplaySize.x;
		OrthoGraphic(-viewWidth, viewWidth, -viewHeight, viewHeight, 1000.f, -1000.f, cameraProjection);
	}
	ImGuizmo::SetOrthographic(!isPerspective);
	ImGuizmo::BeginFrame();

	ImGui::SetNextWindowPos(ImVec2(1024, 100), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(256, 256), ImGuiCond_Appearing);

	// create a window and insert the inspector
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(320, 340), ImGuiCond_Appearing);
	ImGui::Begin("Editor");
	if (ImGui::RadioButton("Full view", !useWindow)) useWindow = false;
	ImGui::SameLine();
	if (ImGui::RadioButton("Window", useWindow)) useWindow = true;

	ImGui::Text("Camera");
	bool viewDirty = false;
	if (ImGui::RadioButton("Perspective", isPerspective)) isPerspective = true;
	ImGui::SameLine();
	if (ImGui::RadioButton("Orthographic", !isPerspective)) isPerspective = false;
	if (isPerspective)
	{
		ImGui::SliderFloat("Fov", &fov, 20.f, 110.f);
	}
	else
	{
		ImGui::SliderFloat("Ortho width", &viewWidth, 1, 20);
	}
	viewDirty |= ImGui::SliderFloat("Distance", &camDistance, 1.f, 10.f);
	ImGui::SliderInt("Gizmo count", &gizmoCount, 1, 4);

	if (viewDirty || firstFrame)
	{
		float eye[] = { cosf(camYAngle) * cosf(camXAngle) * camDistance, sinf(camXAngle) * camDistance, sinf(camYAngle) * cosf(camXAngle) * camDistance };
		float at[] = { 0.f, 0.f, 0.f };
		float up[] = { 0.f, 1.f, 0.f };
		LookAt(eye, at, up, cameraView);
		firstFrame = false;
	}

	ImGui::Text("X: %f Y: %f", io.MousePos.x, io.MousePos.y);
	if (ImGuizmo::IsUsing())
	{
		ImGui::Text("Using gizmo");
	}
	else
	{
		ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "");
		ImGui::SameLine();
		ImGui::Text(ImGuizmo::IsOver(ImGuizmo::TRANSLATE) ? "Over translate gizmo" : "");
		ImGui::SameLine();
		ImGui::Text(ImGuizmo::IsOver(ImGuizmo::ROTATE) ? "Over rotate gizmo" : "");
		ImGui::SameLine();
		ImGui::Text(ImGuizmo::IsOver(ImGuizmo::SCALE) ? "Over scale gizmo" : "");
	}
	ImGui::Separator();
	for (int matId = 0; matId < gizmoCount; matId++)
	{
		ImGuizmo::SetID(matId);

		EditTransform(cameraView, cameraProjection, objectMatrix[matId], lastUsing == matId);
		if (ImGuizmo::IsUsing())
		{
			lastUsing = matId;
		}
	}

	ImGui::End();

	//----

	ImGui::SetNextWindowPos(ImVec2(10, 350), ImGuiCond_Appearing);

	ImGui::SetNextWindowSize(ImVec2(940, 480), ImGuiCond_Appearing);
	ImGui::Begin("Other controls");
	if (ImGui::CollapsingHeader("Zoom Slider"))
	{
		static float uMin = 0.4f, uMax = 0.6f;
		static float vMin = 0.4f, vMax = 0.6f;
		ImGui::Image((ImTextureID)(uint64_t)procTexture, ImVec2(900, 300), ImVec2(uMin, vMin), ImVec2(uMax, vMax));
		{
			ImGui::SameLine();
			ImGui::PushID(18);
			ImZoomSlider::ImZoomSlider(0.f, 1.f, vMin, vMax, 0.01f, ImZoomSlider::ImGuiZoomSliderFlags_Vertical);
			ImGui::PopID();
		}

		{
			ImGui::PushID(19);
			ImZoomSlider::ImZoomSlider(0.f, 1.f, uMin, uMax);
			ImGui::PopID();
		}
	}

	//----

	if (ImGui::CollapsingHeader("Sequencer"))
	{
		// let's create the sequencer
		static int selectedEntry = -1;
		static int firstFrame = 0;
		static bool expanded = true;
		static int currentFrame = 100;

		ImGui::PushItemWidth(130);
		ImGui::InputInt("Frame Min", &mySequence.mFrameMin);
		ImGui::SameLine();
		ImGui::InputInt("Frame ", &currentFrame);
		ImGui::SameLine();
		ImGui::InputInt("Frame Max", &mySequence.mFrameMax);
		ImGui::PopItemWidth();
		Sequencer(&mySequence, &currentFrame, &expanded, &selectedEntry, &firstFrame, ImSequencer::SEQUENCER_EDIT_STARTEND | ImSequencer::SEQUENCER_ADD | ImSequencer::SEQUENCER_DEL | ImSequencer::SEQUENCER_COPYPASTE | ImSequencer::SEQUENCER_CHANGE_FRAME);
		// add a UI to edit that particular item
		if (selectedEntry != -1)
		{
			const MySequence::MySequenceItem& item = mySequence.myItems[selectedEntry];
			ImGui::Text("I am a %s, please edit me", SequencerItemTypeNames[item.mType]);
			// switch (type) ....
		}
	}
#ifndef USE_GraphEditor
	ImGui::End();
#endif

#ifdef USE_GraphEditor
	// Graph Editor
	static GraphEditor::Options options;
	static GraphEditorDelegate delegate;
	static GraphEditor::ViewState viewState;
	static GraphEditor::FitOnScreen fit = GraphEditor::Fit_None;
	static bool showGraphEditor = true;

	if (ImGui::CollapsingHeader("Graph Editor"))
	{
		ImGui::Checkbox("Show GraphEditor", &showGraphEditor);
		GraphEditor::EditOptions(options);
	}

	ImGui::End();

	if (showGraphEditor)
	{
		ImGui::Begin("Graph Editor", NULL, 0);
		if (ImGui::Button("Fit all nodes"))
		{
			fit = GraphEditor::Fit_AllNodes;
		}
		ImGui::SameLine();
		if (ImGui::Button("Fit selected nodes"))
		{
			fit = GraphEditor::Fit_SelectedNodes;
		}
		GraphEditor::Show(delegate, options, viewState, true, &fit);

		ImGui::End();
}
#endif

}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return;

	ui.Begin();
	{
		drawImGuizmo();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') {
		bGui = !bGui;
	}
}