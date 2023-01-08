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

#include "ofxSurfingImGui.h"
//#include "ofxImGui.h"
//#include "imgui_internal.h"
//#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui_notify.h"
#include "tahoma.h"

namespace surfNotify
{
	inline void init()
	{
		ImGuiIO* io = &ImGui::GetIO();

		// We must load a font before loading notify, because we cannot merge font-awesome with default font
		// FontDataOwnedByAtlas = false is required (also in ImGui::MergeIconsWithLatestFont())
		// because otherwise ImGui will call free() while freeing resources which will lead into a crash
		// since tahoma is defined as readonly and wasn't allocated with malloc()
		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;
		//io->Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);

		//// Initialize notify
		//ImGui::MergeIconsWithLatestFont(16.f, false);
	}

	inline void render()
	{
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

		// Render toasts on top of everything, at the end of your code!
		// You should push style vars here
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
		ImGui::RenderNotifications();
		ImGui::PopStyleVar(1); // Don't forget to Pop()
		ImGui::PopStyleColor(1);
	}
}
