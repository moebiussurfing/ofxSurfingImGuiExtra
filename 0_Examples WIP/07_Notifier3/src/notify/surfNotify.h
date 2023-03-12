// WIP
// 
// TODO: 
// WIN32 only ?
//
// Error
// inline variables require at least '/std:c++17'
// 07_Notifier2	C : \Users\moebi\OneDrive\Documents\openFrameworks\addons\ofxSurfingImGuiExtra\0 Examples WIP\07_Notifier2\src\notify\imgui_notify.h	215
//
// Should be tested on newer c++17 / OF version! (nightly builds)

//----

//#include "ofxSurfingImGui.h"

#include "ofxImGui.h"
#include "imgui_internal.h"
#define IMGUI_DEFINE_MATH_OPERATORS

//----

#include "imgui_notify.h"
#include "tahoma.h"

//namespace surfNotify
//{

class surfNotify
{
private:

	ofxImGui::Gui* gui = nullptr;
	ImFont* customFont = nullptr;

	void setGuiPtr(ofxImGui::Gui& g) { gui = &g; };

	int duration = 5000; // 5 seconds

public:

	surfNotify::surfNotify() {
	};

	surfNotify::~surfNotify() {
		//delete gui;
		//delete customFont;
	};

	void setup(ofxImGui::Gui& g)
	{
		setGuiPtr(g);
	};

private:

	void setup()
	{
		if (gui == nullptr)
		{
			ofLogError("surfNotify") << "ofxImGui::Gui* gui is nullptr. You must pass it as a ptr reference!";
			return;
		}

		if (1)
		{
			float sz = 20.f;

			ImGuiIO* io = &ImGui::GetIO();
			auto normalCharRanges = ImGui::GetIO().Fonts->GetGlyphRangesDefault();
			ImFontConfig font_cfg;
			font_cfg.FontDataOwnedByAtlas = false;
			
			//font_cfg.MergeMode = true;
			//font_cfg.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced

			customFont = gui->addFont((void*)tahoma, sizeof(tahoma), sz, &font_cfg, normalCharRanges);
			
			//ImGui::MergeIconsWithLatestFont(16.f, false);
		}
	};

public:

	void drawRender()
	{
		//ImGui::PushFont(customFont);

		if (gui == nullptr)
		{
			ofLogError("surfNotify") << "ofxImGui::Gui* gui is nullptr. You must pass it as a ptr reference!";
			return;
		}

		// Render toasts on top of everything, at the end of your code!
		// You should push style vars here
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
		ImGui::RenderNotifications();
		ImGui::PopStyleVar(1); // Don't forget to Pop()
		ImGui::PopStyleColor(1);

		//ImGui::PopFont();
	};

	void drawTester()
	{
		if (gui == nullptr)
		{
			ofLogError("surfNotify") << "ofxImGui::Gui* gui is nullptr. You must pass it as a ptr reference!";
			return;
		}

		//ImGui::SetNextWindowPos({ 50, 50 }, ImGuiCond_Once);
		//ImGui::SetNextWindowSize({ 550, 550 }, ImGuiCond_Once);
		ImGui::Begin("Hello World!", NULL, NULL);

		if (ImGui::CollapsingHeader("Examples without title", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::Button("Success"))
			{
				ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Hello World! This is a success! %s", "We can also format here:)" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Warning"))
			{
				ImGui::InsertNotification({ ImGuiToastType_Warning, 3000, "Hello World! This is a warning!" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Error"))
			{
				//ImGui::InsertNotification({ ImGuiToastType_None, 3000, "Hello World! This is an error!" });
				ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Hello World! This is an error!" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Info"))
			{
				ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "Hello World! This is an info!" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Info long"))
			{
				ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation" });
			}
		}

		if (ImGui::CollapsingHeader("Do it yourself", ImGuiTreeNodeFlags_DefaultOpen))
		{
			static char title[4096] = "A wonderful quote!";
			ImGui::InputTextMultiline("Title", title, sizeof(title));

			static char content[4096] = "Ours is a friendship forged once in this life, and again in the next. Goodbye, my brother. \n- Dembe Zuma";
			ImGui::InputTextMultiline("Content", content, sizeof(content));

			static int duration = 5000; // 5 seconds
			ImGui::InputInt("Duration (ms)", &duration, 100);
			if (duration < 0) duration = 0; // Shouldn't be negative

			static char* type_str[] = { "None", "Success", "Warning", "Error", "Info" };
			static ImGuiToastType type = ImGuiToastType_Success;
			IM_ASSERT(type < ImGuiToastType_COUNT);

			if (ImGui::BeginCombo("Type", type_str[type]))
			{
				for (auto n = 0; n < IM_ARRAYSIZE(type_str); n++)
				{
					const bool is_selected = (type == n);

					if (ImGui::Selectable(type_str[n], is_selected))
						type = n;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			static bool enable_title = true, enable_content = true;
			ImGui::Checkbox("Enable title", &enable_title);
			ImGui::SameLine();
			ImGui::Checkbox("Enable content", &enable_content);

			if (ImGui::Button("Show"))
			{
				ImGuiToast toast(type, duration);

				if (enable_title)
					toast.set_title(title);

				if (enable_content)
					toast.set_content(content);

				ImGui::InsertNotification(toast);
			}
		}

		ImGui::End();
	};

	void print(std::string content, std::string title = "", ImGuiToastType type = ImGuiToastType_Success)
	{
		bool enable_title = (title == "" ? false : true);
		bool enable_content = (content == "" ? false : true);
		ImGuiToast toast(type, duration);
		if (enable_title) toast.set_title(title.c_str());
		if (enable_content) toast.set_content(content.c_str());

		ImGui::InsertNotification(toast);
	};

};

//}
//namespace ofxSurfing = surfNotify::surfNotify;
//  using namespace A::AA;