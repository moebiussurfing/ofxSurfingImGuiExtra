﻿#include "SurfingImCoolbar.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


SurfingImCoolbar::SurfingImCoolbar()
{
	ofLogNotice(__FUNCTION__);
}

SurfingImCoolbar::~SurfingImCoolbar()
{
	ofLogNotice(__FUNCTION__);
}

GLuint SurfingImCoolbar::loadTexture(const std::string& vFilePathName) {
	ofLogNotice(__FUNCTION__);

	GLuint tex_id = 0U;
	int32_t w, h, chans;
	auto image = stbi_load(vFilePathName.c_str(), &w, &h, &chans, 0);
	if (image) {
		stbi_image_free(image);
		if (chans == 3) {
			image = stbi_load(vFilePathName.c_str(), &w, &h, &chans, STBI_rgb);
		}
		else if (chans == 4) {
			image = stbi_load(vFilePathName.c_str(), &w, &h, &chans, STBI_rgb_alpha);
		}
	}
	if (image) {
		glGenTextures(1, &tex_id);
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (chans == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)w, (GLsizei)h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}
		else if (chans == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)w, (GLsizei)h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}
		glFinish();
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(image);
	}
	return tex_id;
}

void SurfingImCoolbar::drawBackground(const GLuint& vTexId) {
	//ofLogNotice(__FUNCTION__);

	display_w = ofGetWidth();
	display_h = ofGetHeight();


	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
	ImVec2 pos;
	ImVec2 size((float)display_w, (float)display_h);
	ImGui::Begin("##background", nullptr,
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::SetWindowPos(ImVec2());
	ImGui::SetWindowSize(size);
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (!window->SkipItems) { window->DrawList->AddImage((ImTextureID)(size_t)vTexId, pos, pos + size); }
	ImGui::End();
	ImGui::PopStyleVar();
}

void SurfingImCoolbar::drawCoolBar(AppDatas& vAppDatas, const size_t& vMaxIcons, const char* vLabel, const ImCoolBarFlags& vFlags, const ImGui::ImCoolBarConfig& vConfig) {
	//ofLogNotice(__FUNCTION__);

	ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	bool opened = ImGui::BeginCoolBar(vLabel, vFlags, vConfig);
	ImGui::PopStyleVar();
	if (opened) {
		auto window = ImGui::GetCurrentWindow();
		if (window) {
			// correct the rect of the window. maybe a bug on imgui..
			// the workrect can cause issue when clikc a timeline
			// channel close button when close to the toolbar
			// this thing correct the issue
			const auto& rc = window->Rect();
			window->WorkRect = rc;
			window->OuterRectClipped = rc;
			window->InnerRect = rc;
			window->InnerClipRect = rc;
			window->ParentWorkRect = rc;
			window->ClipRect = rc;
			window->ContentRegionRect = rc;
		}
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2());
		size_t idx = 0U;
		for (const auto& arr : vAppDatas.textures) {
			if (idx++ < vMaxIcons) {
				if (ImGui::CoolBarItem()) {
					float w = ImGui::GetCoolBarItemWidth();
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2());
					bool res = ImGui::ImageButton(arr.first.c_str(), (ImTextureID)(size_t)arr.second, ImVec2(w, w));
					ImGui::PopStyleVar();
					ImGui::PopStyleColor(2);

					if (res) {
						if (arr.first == "Settings") {
							vAppDatas.show_app_demo = !vAppDatas.show_app_demo;
						}
						else if (arr.first == "Activa") {
							vAppDatas.show_graph_demo = !vAppDatas.show_graph_demo;
						}
						else if (arr.first == "Magnet") {
							vAppDatas.show_app_metrics = !vAppDatas.show_app_metrics;
						}
					}
				}
			}
		}
		ImGui::PopStyleVar();
		ImGui::EndCoolBar();
	}
}

void SurfingImCoolbar::setup(ofxImGui::Gui& ui) {
	ofLogNotice(__FUNCTION__);

#ifndef SURF_DISABLE_FONTS
#if 0
	// load icon font file (CustomFont.cpp)
	ImGui::GetIO().Fonts->AddFontDefault();

	static const ImWchar icons_ranges[] = { ICON_MIN_IGFD, ICON_MAX_IGFD, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(FONT_ICON_BUFFER_NAME_IGFD, 50.0f, &icons_config, icons_ranges);
#else
	//if (ui != nullptr)
	{
		ImGui::GetIO().Fonts->AddFontDefault();

		static const ImWchar icons_ranges[] = { ICON_MIN_IGFD, ICON_MAX_IGFD, 0 };
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(FONT_ICON_BUFFER_NAME_IGFD, 50.0f, &icons_config, icons_ranges);

		//// Add fontawesome fonts by merging new glyphs
		//ImFontConfig config;
		//config.MergeMode = true;
		//config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
		//static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

		//TODO: add AddFontFromMemoryCompressedBase85TTF to ofxImGui
		//addFontFromMemory(void* fontData, int fontDataSize, float fontSize, const ImFontConfig* _fontConfig, const ImWchar* _glyphRanges, bool _setAsDefaultFont )
		ui.addFontFromMemory(FONT_ICON_BUFFER_NAME_IGFD, 18.f, &icons_config, icons_ranges);
	}
#endif
#endif

	const std::vector<std::string> icons_name = {
		"Settings",   //
		"Activa",     //
		"Magnet",     //
		"Blender",    //
		"CLion",      //
		"Firefox",    //
		"Gimp",       //
		"Godot",      //
		"VLC",        //
		"Wikipedia",  //
		"GeoGebra"    //
	};

	//background_id = loadTexture("res/desert.jpg");
	//for (const auto& name : icons_name) {
	//	_appDatas.textures.push_back(std::make_pair(name, loadTexture("res/" + name + ".png")));
	//}

	background_id = loadTexture(ofToDataPath("res/desert.jpg"));
	for (const auto& name : icons_name) {
		_appDatas.textures.push_back(std::make_pair(name, loadTexture(ofToDataPath("res/" + name + ".png"))));
	}

	bDoneSetup = 1;
}

void SurfingImCoolbar::draw() {
	//ofLogNotice(__FUNCTION__);

	if (!bDoneSetup) return;

	if (bBg) drawBackground(background_id);

	drawCoolBar(_appDatas, 11, "Top##CoolBarMainWin", ImCoolBarFlags_Horizontal, { ImVec2(0.5f, 0.0f), 50.0f, 100.0f });
	drawCoolBar(_appDatas, 6, "Left##CoolBarMainWin", ImCoolBarFlags_Vertical, { ImVec2(0.0f, 0.5f), 50.0f, 100.0f });
	drawCoolBar(_appDatas, 6, "Right##CoolBarMainWin", ImCoolBarFlags_Vertical, { ImVec2(1.0f, 0.5f), 50.0f, 100.0f });

	const float& ref_font_scale = ImGui::GetIO().Fonts->Fonts[0]->Scale;

	auto coolbar_button = [ref_font_scale](const char* label) {
		float w = ImGui::GetCoolBarItemWidth();
		auto font_ptr = ImGui::GetIO().Fonts->Fonts[0];
		//font_ptr->Scale = ref_font_scale;
		ImGui::PushFont(font_ptr);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2());
		ImGui::PopStyleVar();
		font_ptr->Scale = ImGui::GetCoolBarItemScale();
		bool b = ImGui::Button(label, ImVec2(w, w));
		font_ptr->Scale = ref_font_scale;
		ImGui::PopFont();

		if (b) ofLogNotice(__FUNCTION__) << label;
	};

	static ImGui::ImCoolBarConfig _config;
	_config.normal_size = 25.0f;
	_config.hovered_size = 100.0f;
	_config.anchor = ImVec2(0.5f, 1.0f);

	ImGui::GetIO().Fonts->Fonts[0]->Scale = ref_font_scale;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings;
	if (ImGui::BeginViewportSideBar("BottomBar", ImGui::GetMainViewport(), ImGuiDir_Down, 40.0f, window_flags)) {
		if (ImGui::BeginCoolBar("Bottom##CoolBarMainWin", ImCoolBarFlags_Horizontal, _config)) {
			auto window = ImGui::GetCurrentWindow();
			if (window) {
				// correct the rect of the window. maybe a bug on imgui !?
				// the workrect can cause issue when click around
				// this thing correct the issue
				const auto& rc = window->Rect();
				window->WorkRect = rc;
				window->OuterRectClipped = rc;
				window->InnerRect = rc;
				window->InnerClipRect = rc;
				window->ParentWorkRect = rc;
				window->ClipRect = rc;
				window->ContentRegionRect = rc;
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("A");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("B");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("C");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("D");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("E");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("F");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("G");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("H");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("I");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("J");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("K");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("L");
			}
			if (ImGui::CoolBarItem()) {
				coolbar_button("M");
			}
			ImGui::EndCoolBar();
		}
	}
	ImGui::End();

	if (_appDatas.show_app_metrics) {
		ImGui::ShowMetricsWindow(&_appDatas.show_app_metrics);
	}

	if (_appDatas.show_app_demo) {
		ImGui::ShowDemoWindow(&_appDatas.show_app_demo);
	}

	if (_appDatas.show_graph_demo) {
		ImPlot::ShowDemoWindow(&_appDatas.show_graph_demo);
	}
}
