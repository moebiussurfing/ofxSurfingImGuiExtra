#include "imgui.h"
#include <stdio.h>

#include <ImGradientHDR.h>

// Taken from https://github.com/effekseer/ImGradientHDR
/*
Feature

Supported parameters

	Color
	Alpha
	Intensity

*/


class SurfingImGradientHDR
{
public:

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	int32_t stateID = 10;

	ImGradientHDRState state;
	ImGradientHDRTemporaryState tempState;

	SurfingImGradientHDR() { 
		setup(); 
	};

	~SurfingImGradientHDR() {};

	void setup() 
	{
		state.AddColorMarker(0.0f, { 1.0f, 1.0f, 1.0f }, 1.0f);
		state.AddColorMarker(1.0f, { 1.0f, 1.0f, 1.0f }, 1.0f);
		state.AddAlphaMarker(0.0f, 1.0f);
		state.AddAlphaMarker(1.0f, 1.0f);
	}

	void draw() 
	{
		//ImGui::Begin("ImGradientHDR");

		ImGradientHDR(stateID, state, tempState);

		if (tempState.selectedMarkerType == ImGradientHDRMarkerType::Color)
		{
			auto selectedColorMarker = state.GetColorMarker(tempState.selectedIndex);
			if (selectedColorMarker != nullptr)
			{
				ImGui::ColorEdit3("Color", selectedColorMarker->Color.data(), ImGuiColorEditFlags_Float);
				ImGui::DragFloat("Intensity", &selectedColorMarker->Intensity, 0.1f, 0.0f, 100.0f, "%f", 1.0f);
			}
		}

		if (tempState.selectedMarkerType == ImGradientHDRMarkerType::Alpha)
		{
			auto selectedAlphaMarker = state.GetAlphaMarker(tempState.selectedIndex);
			if (selectedAlphaMarker != nullptr)
			{
				ImGui::DragFloat("Alpha", &selectedAlphaMarker->Alpha, 0.1f, 0.0f, 1.0f, "%f", 1.0f);
			}
		}

		if (tempState.selectedMarkerType != ImGradientHDRMarkerType::Unknown)
		{
			if (ImGui::Button("Delete"))
			{
				if (tempState.selectedMarkerType == ImGradientHDRMarkerType::Color)
				{
					state.RemoveColorMarker(tempState.selectedIndex);
					tempState = ImGradientHDRTemporaryState{};
				}
				else if (tempState.selectedMarkerType == ImGradientHDRMarkerType::Alpha)
				{
					state.RemoveAlphaMarker(tempState.selectedIndex);
					tempState = ImGradientHDRTemporaryState{};
				}
			}
		}

		//ImGui::End();
	}

};
