#pragma once

#ifndef ALL_IMGUITWEAKS
#define ALL_IMGUITWEAKS

#include <imgui.h>
#include <imgui_internal.h>

#include <algorithm>
#include <unordered_map>

#include <functional>
using callback_t = std::function<void()>;

#ifndef PI_IMGUITWEAKS
#define PI_IMGUITWEAKS 3.1415926545
#endif

namespace ImEasings {
    static float InSine(float t) {
        return sin(1.5707963 * t);
    }

    static float OutSine(float t) {
        return 1 + sin(1.5707963 * (--t));
    }

    static float InOutSine(float t) {
        return 0.5 * (1 + sin(3.1415926 * (t - 0.5)));
    }

    static float InQuad(float t) {
        return t * t;
    }

    static float OutQuad(float t) {
        return t * (2 - t);
    }

    static float InOutQuad(float t) {
        return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
    }

    static float InCubic(float t) {
        return t * t * t;
    }

    static float OutCubic(float t) {
        return 1 + (--t) * t * t;
    }

    static float InOutCubic(float t) {
        return t < 0.5 ? 4 * t * t * t : 1 + (--t) * (2 * (--t)) * (2 * t);
    }

    static float InQuart(float t) {
        t *= t;
        return t * t;
    }

    static float OutQuart(float t) {
        t = (--t) * t;
        return 1 - t * t;
    }

    static float InOutQuart(float t) {
        if (t < 0.5) {
            t *= t;
            return 8 * t * t;
        }
        else {
            t = (--t) * t;
            return 1 - 8 * t * t;
        }
    }

    static float InQuint(float t) {
        float t2 = t * t;
        return t * t2 * t2;
    }

    static float OutQuint(float t) {
        float t2 = (--t) * t;
        return 1 + t * t2 * t2;
    }

    static float InOutQuint(float t) {
        float t2;
        if (t < 0.5) {
            t2 = t * t;
            return 16 * t * t2 * t2;
        }
        else {
            t2 = (--t) * t;
            return 1 + 16 * t * t2 * t2;
        }
    }

    static float InExpo(float t) {
        return (pow(2, 8 * t) - 1) / 255;
    }

    static float OutExpo(float t) {
        return 1 - pow(2, -8 * t);
    }

    static float InOutExpo(float t) {
        if (t < 0.5) {
            return (pow(2, 16 * t) - 1) / 510;
        }
        else {
            return 1 - 0.5 * pow(2, -16 * (t - 0.5));
        }
    }

    static float InCirc(float t) {
        return 1 - sqrt(1 - t);
    }

    static float OutCirc(float t) {
        return sqrt(t);
    }

    static float InOutCirc(float t) {
        if (t < 0.5) {
            return (1 - sqrt(1 - 2 * t)) * 0.5;
        }
        else {
            return (1 + sqrt(2 * t - 1)) * 0.5;
        }
    }

    static float InBack(float t) {
        return t * t * (2.70158 * t - 1.70158);
    }

    static float OutBack(float t) {
        return 1 + (--t) * t * (2.70158 * t + 1.70158);
    }

    static float InOutBack(float t) {
        if (t < 0.5) {
            return t * t * (7 * t - 2.5) * 2;
        }
        else {
            return 1 + (--t) * t * 2 * (7 * t + 2.5);
        }
    }

    static float InElastic(float t) {
        float t2 = t * t;
        return t2 * t2 * sin(t * PI_IMGUITWEAKS * 4.5);
    }

    static float OutElastic(float t) {
        float t2 = (t - 1) * (t - 1);
        return 1 - t2 * t2 * cos(t * PI_IMGUITWEAKS * 4.5);
    }

    static float InOutElastic(float t) {
        float t2;
        if (t < 0.45) {
            t2 = t * t;
            return 8 * t2 * t2 * sin(t * PI_IMGUITWEAKS * 9);
        }
        else if (t < 0.55) {
            return 0.5 + 0.75 * sin(t * PI_IMGUITWEAKS * 4);
        }
        else {
            t2 = (t - 1) * (t - 1);
            return 1 - 8 * t2 * t2 * sin(t * PI_IMGUITWEAKS * 9);
        }
    }

    static float InBounce(float t) {
        return pow(2, 6 * (t - 1)) * abs(sin(t * PI_IMGUITWEAKS * 3.5));
    }

    static float OutBounce(float t) {
        return 1 - pow(2, -6 * t) * abs(cos(t * PI_IMGUITWEAKS * 3.5));
    }

    static float InOutBounce(float t) {
        if (t < 0.5) {
            return 8 * pow(2, 8 * (t - 1)) * abs(sin(t * PI_IMGUITWEAKS * 7));
        }
        else {
            return 1 - 8 * pow(2, -8 * t) * abs(sin(t * PI_IMGUITWEAKS * 7));
        }
    }
}

namespace ImAnimations 
{
	/*
	* Easing functions are only available when the value type is float. 
	* Also, to use Easing, the minimum and maximum values must be 0.f and 1.f, respectively.
	*/
	template <class T = const char*, class B = float>
	class Animator {
	public:
		B Value(T indentifier, bool state, B min, B max, B speed) {
			auto value = storage.find(indentifier);

			if (value == storage.end()) {
				storage.insert({ indentifier, min });
				value = storage.find(indentifier);
			}

			const float frameRateSpeed = speed * (1.f - ImGui::GetIO().DeltaTime);

			state ? value->second += frameRateSpeed : value->second -= frameRateSpeed;

			value->second = std::clamp(value->second, min, max);

			return value->second;
		}

		B ValueInSine(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InSine(Value(indentifier, state, min, max, speed));
		}
		B ValueOutSine(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::OutSine(Value(indentifier, state, min, max, speed));
		}
		B ValueInOutSine(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InOutSine(Value(indentifier, state, min, max, speed));
		}
		B ValueInQuad(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InQuad(Value(indentifier, state, min, max, speed));
		}
		B ValueOutQuad(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::OutQuad(Value(indentifier, state, min, max, speed));
		}
		B ValueInOutQuad(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InOutQuad(Value(indentifier, state, min, max, speed));
		}
		B ValueInCubic(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InCubic(Value(indentifier, state, min, max, speed));
		}
		B ValueOutCubic(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::OutCubic(Value(indentifier, state, min, max, speed));
		}
		B ValueInOutCubic(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InOutCubic(Value(indentifier, state, min, max, speed));
		}
		B ValueInQuart(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InQuart(Value(indentifier, state, min, max, speed));
		}
		B ValueOutQuart(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::OutQuart(Value(indentifier, state, min, max, speed));
		}
		B ValueInOutQuart(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InOutQuart(Value(indentifier, state, min, max, speed));
		}
		B ValueInQuint(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InQuint(Value(indentifier, state, min, max, speed));
		}
		B ValueOutQuint(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::OutQuint(Value(indentifier, state, min, max, speed));
		}
		B ValueInOutQuint(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InOutQuint(Value(indentifier, state, min, max, speed));
		}
		B ValueInExpo(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InExpo(Value(indentifier, state, min, max, speed));
		}
		B ValueOutExpo(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::OutExpo(Value(indentifier, state, min, max, speed));
		}
		B ValueInOutExpo(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InOutExpo(Value(indentifier, state, min, max, speed));
		}
		B ValueInCirc(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InCirc(Value(indentifier, state, min, max, speed));
		}
		B ValueOutCirc(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::OutCirc(Value(indentifier, state, min, max, speed));
		}
		B ValueInOutCirc(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InOutCirc(Value(indentifier, state, min, max, speed));
		}
		B ValueInBack(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InBack(Value(indentifier, state, min, max, speed));
		}
		B ValueOutBack(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::OutBack(Value(indentifier, state, min, max, speed));
		}
		B ValueInElastic(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InElastic(Value(indentifier, state, min, max, speed));
		}
		B ValueOutElastic(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::OutElastic(Value(indentifier, state, min, max, speed));
		}
		B ValueInOutElastic(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InOutElastic(Value(indentifier, state, min, max, speed));
		}
		B ValueInBounce(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InBounce(Value(indentifier, state, min, max, speed));
		}
		B ValueOutBounce(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::OutBounce(Value(indentifier, state, min, max, speed));
		}
		B ValueInOutBounce(T indentifier, bool state, B min, B max, B speed) {
			return ImEasings::InOutBounce(Value(indentifier, state, min, max, speed));
		}
	private:
		std::unordered_map<T, B> storage;
	};

	__forceinline ImColor LerpColor(ImColor start, ImColor end, float interpolation) {
		return ImLerp(
			ImVec4(start.Value.x, start.Value.y, start.Value.z, start.Value.w), 
			ImVec4(end.Value.x, end.Value.y, end.Value.z, end.Value.w),
			interpolation
		);
	}
}

namespace ImSugar
{
	//__forceinline bool Button(const char* label, ImVec2 size, callback_t callback = nullptr)
	//{
	//	if (ImGui::Button(label, size))
	//		callback();
	//}
	__forceinline bool Button(const char* label, ImVec2 size, callback_t callback = nullptr)
	{
		if (ImGui::Button(label, size)) {
			if (callback != nullptr) callback();
			return true;;
		}

		return false;
	}

	__forceinline void Font(ImFont* font, callback_t callback = nullptr)
	{
		ImGui::PushFont(font);
		{
			callback();
		}
		ImGui::PopFont();
	}

	__forceinline void Group(callback_t callback = nullptr)
	{
		ImGui::BeginGroup();
		{
			callback();
		}
		ImGui::EndGroup();
	}

	__forceinline void Child(const char* label, ImVec2 size, callback_t callback, bool border = false, ImGuiWindowFlags flags = 0)
	{
		ImGui::BeginChild(label, size, border, flags);
		{
			callback();
		}
		ImGui::EndChild();
	}

	__forceinline void Window(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0, callback_t callback = nullptr)
	{
		ImGui::Begin(name, p_open, flags);
		{
			callback();
		}
		ImGui::End();
	}
}

#endif