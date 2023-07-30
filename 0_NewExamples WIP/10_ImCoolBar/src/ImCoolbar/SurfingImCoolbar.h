#pragma once
#include "ofMain.h"

// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui.h"
#include "imgui_internal.h"
#include "implot.h"

#include <ImCoolbar/ImCoolbar.h>
#include "CustomFont.cpp"
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <clocale>
#include <string>
#include <vector>
#include <array>


class SurfingImCoolbar
{
public:
	SurfingImCoolbar();
	~SurfingImCoolbar();

	int display_w, display_h;

	static void glfw_error_callback(int error, const char* description) { fprintf(stderr, "Glfw Error %d: %s\n", error, description); }

	GLuint loadTexture(const std::string& vFilePathName);

	void drawBackground(const GLuint& vTexId);

	typedef std::vector<std::pair<std::string, GLuint>> TexturesContainer;

	struct AppDatas {
		bool show_app_metrics = false;
		bool show_app_demo = false;
		bool show_graph_demo = false;
		TexturesContainer textures;
	};

	void drawCoolBar(AppDatas& vAppDatas, const size_t& vMaxIcons, const char* vLabel, const ImCoolBarFlags& vFlags = ImCoolBarFlags_Vertical, const ImGui::ImCoolBarConfig& vConfig = {});
	void setup();
	void draw();

	AppDatas _appDatas;
	GLuint background_id;

};