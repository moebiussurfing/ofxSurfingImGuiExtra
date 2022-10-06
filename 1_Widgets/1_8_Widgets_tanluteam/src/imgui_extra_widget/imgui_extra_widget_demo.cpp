#include <imgui.h>
#undef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <imgui_helper.h>
//-----------------------------------------------------------------------------------------------------------------
#include <imgui_extra_widget.h>
#include <implot.h>

namespace ImGui
{
void ShowKnobDemoWindow()
{
    static float val = 0.5, val_default = 0.5;
    float t = (float)ImGui::GetTime();
    float h = abs(sin(t * 0.2));
    float s = abs(sin(t * 0.1)) * 0.5 + 0.4;
    ImVec4 base_color = ImVec4(0.f, 0.f, 0.f, 1.f), active_color = ImVec4(0.f, 0.f, 0.f, 1.f), hovered_color = ImVec4(0.f, 0.f, 0.f, 1.f);
    ImGui::ColorConvertHSVtoRGB(h, s, 0.5f, base_color.x, base_color.y, base_color.z);
    ImGui::ColorConvertHSVtoRGB(h, s, 0.6f, active_color.x, active_color.y, active_color.z);
    ImGui::ColorConvertHSVtoRGB(h, s, 0.7f, hovered_color.x, hovered_color.y, hovered_color.z);
    ImVec4 highlight_base_color = ImVec4(0.f, 0.f, 0.f, 1.f), highlight_active_color = ImVec4(0.f, 0.f, 0.f, 1.f), highlight_hovered_color = ImVec4(0.f, 0.f, 0.f, 1.f);
    ImGui::ColorConvertHSVtoRGB(h, s, 0.75f, highlight_base_color.x, highlight_base_color.y, highlight_base_color.z);
    ImGui::ColorConvertHSVtoRGB(h, s, 0.95f, highlight_active_color.x, highlight_active_color.y, highlight_active_color.z);
    ImGui::ColorConvertHSVtoRGB(h, s, 1.0f, highlight_hovered_color.x, highlight_hovered_color.y, highlight_hovered_color.z);
    ImVec4 lowlight_base_color = ImVec4(0.f, 0.f, 0.f, 1.f), lowlight_active_color = ImVec4(0.f, 0.f, 0.f, 1.f), lowlight_hovered_color = ImVec4(0.f, 0.f, 0.f, 1.f);
    ImGui::ColorConvertHSVtoRGB(h, s, 0.2f, lowlight_base_color.x, lowlight_base_color.y, lowlight_base_color.z);
    ImGui::ColorConvertHSVtoRGB(h, s, 0.3f, lowlight_active_color.x, lowlight_active_color.y, lowlight_active_color.z);
    ImGui::ColorConvertHSVtoRGB(h, s, 0.4f, lowlight_hovered_color.x, lowlight_hovered_color.y, lowlight_hovered_color.z);
    ImVec4 tick_base_color = ImVec4(0.8f, 0.8f, 0.8f, 1.f), tick_active_color = ImVec4(1.f, 1.f, 1.f, 1.f), tick_hovered_color = ImVec4(1.f, 1.f, 1.f, 1.f);
    ColorSet circle_color = {base_color, active_color, hovered_color};
    ColorSet wiper_color = {highlight_base_color, highlight_active_color, highlight_hovered_color};
    ColorSet track_color = {lowlight_base_color, lowlight_active_color, lowlight_hovered_color};
    ColorSet tick_color = {tick_base_color, tick_active_color, tick_hovered_color};

    float knob_size = 80.f;
    float knob_step = NAN; // (max - min) / 200.f
    ImGui::Knob("##Tick", &val, 0.0f, 1.0f, knob_step, val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_TICK, "%.03fdB");
    ImGui::SameLine();
    ImGui::Knob("TickDot", &val, 0.0f, 1.0f, knob_step, val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_TICK_DOT, "%.03fdB");
    ImGui::SameLine();
    ImGui::Knob("TickWiper", &val, 0.0f, 1.0f, knob_step, val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_TICK_WIPER, "%.03fdB");
    ImGui::SameLine();
    ImGui::Knob("Wiper", &val, 0.0f, 1.0f, knob_step, val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_WIPER, "%.03fdB");
    ImGui::SameLine();
    ImGui::Knob("WiperTick", &val, 0.0f, 1.0f, knob_step, val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_WIPER_TICK, "%.03fdB");
    ImGui::SameLine();
    ImGui::Knob("WiperDot", &val, 0.0f, 1.0f, knob_step, val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_WIPER_DOT, "%.03fdB");
    ImGui::SameLine();
    ImGui::Knob("WiperOnly", &val, 0.0f, 1.0f, knob_step, val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_WIPER_ONLY, "%.03fdB");
    ImGui::SameLine();
    ImGui::Knob("SteppedTick", &val, 0.0f, 1.0f, knob_step, val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_STEPPED_TICK, "%.03fdB", 10);
    ImGui::SameLine();
    ImGui::Knob("SteppedDot", &val, 0.0f, 1.0f, knob_step, val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_STEPPED_DOT, "%.03fdB", 10);
    ImGui::SameLine();
    ImGui::Knob("Space", &val, 0.0f, 1.0f, knob_step, val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_SPACE, "%.03fdB");

    // no limit knob
    static float no_limit_val = 0.5, no_limit_val_default = 0.5;
    float no_limit_knob_step = 0.01; // (max - min) / 200.f
    ImGui::Knob("##TickNL", &no_limit_val, NAN, NAN, no_limit_knob_step, no_limit_val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_TICK, "%.03f");
    ImGui::SameLine();
    ImGui::Knob("TickDotNL", &no_limit_val, NAN, NAN, no_limit_knob_step, no_limit_val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_TICK_DOT, "%.03f");
    ImGui::SameLine();
    ImGui::Knob("TickWiperNL", &no_limit_val, NAN, NAN, no_limit_knob_step, no_limit_val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_TICK_WIPER, "%.03f");
    ImGui::SameLine();
    ImGui::Knob("WiperNL", &no_limit_val, NAN, NAN, no_limit_knob_step, no_limit_val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_WIPER, "%.03f");
    ImGui::SameLine();
    ImGui::Knob("WiperTickNL", &no_limit_val, NAN, NAN, no_limit_knob_step, no_limit_val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_WIPER_TICK, "%.03f");
    ImGui::SameLine();
    ImGui::Knob("WiperDotNL", &no_limit_val, NAN, NAN, no_limit_knob_step, no_limit_val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_WIPER_DOT, "%.03f");
    ImGui::SameLine();
    ImGui::Knob("WiperOnlyNL", &no_limit_val, NAN, NAN, no_limit_knob_step, no_limit_val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_WIPER_ONLY, "%.03f");
    ImGui::SameLine();
    ImGui::Knob("SteppedTickNL", &no_limit_val, NAN, NAN, no_limit_knob_step, no_limit_val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_STEPPED_TICK, "%.03f", 10);
    ImGui::SameLine();
    ImGui::Knob("SteppedDotNL", &no_limit_val, NAN, NAN, no_limit_knob_step, no_limit_val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_STEPPED_DOT, "%.03f", 10);
    ImGui::SameLine();
    ImGui::Knob("SpaceNL", &no_limit_val, NAN, NAN, no_limit_knob_step, no_limit_val_default, knob_size, circle_color,  wiper_color, track_color, tick_color, ImGui::ImGuiKnobType::IMKNOB_SPACE, "%.03f");

    int idb = val * 80;
    ImGui::Fader("##mastervol", ImVec2(20, 80), &idb, 0, 80, "%d", 1.0f); ImGui::ShowTooltipOnHover("Slide.");
    ImGui::SameLine();
    static int stack = 0;
    static int count = 0;
    ImGui::UvMeter("##vuvr", ImVec2(10, 80), &idb, 0, 80, 20); ImGui::ShowTooltipOnHover("Vertical Uv meters.");
    ImGui::UvMeter("##huvr", ImVec2(80, 10), &idb, 0, 80, 20, &stack, &count); ImGui::ShowTooltipOnHover("Horizon Uv meters width stack effect.");

    //ProgressBar
    static float progress = 0.f;
    progress += 0.1; if (progress > 100.f) progress = 0.f;
    ImGui::RoundProgressBar(knob_size, &progress, 0.f, 100.f, circle_color, wiper_color, tick_color);
}

void ShowExtraWidgetDemoWindow()
{
    if (ImGui::TreeNode("Knob Widget"))
    {
        ShowKnobDemoWindow();
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Extended Buttons"))
    {
        // Check Buttons
        ImGui::Spacing();
        ImGui::AlignTextToFramePadding();ImGui::Text("Check Buttons:");
        ImGui::SameLine();
        static bool checkButtonState1=false;
        if (ImGui::CheckButton("CheckButton",&checkButtonState1)) {}
        ImGui::SameLine();
        static bool checkButtonState2=false;
        if (ImGui::CheckButton("SmallCheckButton",&checkButtonState2, true)) {}
        
        ImGui::Spacing();
        ImGui::TextUnformatted("ToggleButton:");ImGui::SameLine();
        ImGui::ToggleButton("ToggleButtonDemo",&checkButtonState1);

        ImGui::Spacing();
        ImGui::Text("ColorButton (by @ocornut)");
        if (ImGui::IsItemHovered()) ImGui::SetTooltip("%s","Code posted by @ocornut here:\nhttps://github.com/ocornut/imgui/issues/4722");
        // [Button rounding depends on the FrameRounding Style property (but can be overridden with the last argument)]
        const float cbv1width = ImGui::GetContentRegionAvail().x*0.45f;
        ImGui::ColoredButton("Hello##ColoredButtonV1Hello", ImVec2(cbv1width, 0.0f), IM_COL32(255, 255, 255, 255), IM_COL32(200, 60, 60, 255), IM_COL32(180, 40, 90, 255));
        ImGui::SameLine();
        ImGui::ColoredButton("You##ColoredButtonV1You", ImVec2(cbv1width, 0.0f), IM_COL32(255, 255, 255, 255), IM_COL32(50, 220, 60, 255), IM_COL32(69, 150, 70, 255),10.0f); // FrameRounding in [0.0,12.0]

        // ColorComboTest
        ImGui::Spacing();
        static ImVec4 chosenColor(1,1,1,1);
        if (ImGui::ColorCombo("ColorCombo",&chosenColor))
        {
            // choice OK here
        }

        ImGui::SameLine();
        static bool color_choose = false;
        ImGui::CheckButton("+",&color_choose);
        if (ImGui::ColorChooser(&color_choose, &chosenColor))
        {
            // choice OK here
        }


        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Line leader"))
    {
        ImGui::Circle(false); ImGui::TextUnformatted("Circle");
        ImGui::Circle(true); ImGui::TextUnformatted("Circle filled");
        ImGui::Circle(false, true); ImGui::TextUnformatted("Circle arrow");
        ImGui::Circle(true, true); ImGui::TextUnformatted("Circle filled arrow");
        ImGui::Separator();
        ImGui::Square(false); ImGui::TextUnformatted("Square");
        ImGui::Square(true); ImGui::TextUnformatted("Square filled");
        ImGui::Square(false, true); ImGui::TextUnformatted("Square arrow");
        ImGui::Square(true, true); ImGui::TextUnformatted("Square filled arrow");
        ImGui::Separator();
        ImGui::BracketSquare(false); ImGui::TextUnformatted("Bracket Square");
        ImGui::BracketSquare(true); ImGui::TextUnformatted("Bracket Square filled");
        ImGui::BracketSquare(false, true); ImGui::TextUnformatted("Bracket Square arrow");
        ImGui::BracketSquare(true, true); ImGui::TextUnformatted("Bracket Square filled arrow");
        ImGui::Separator();
        ImGui::RoundSquare(false); ImGui::TextUnformatted("Round Square");
        ImGui::RoundSquare(true); ImGui::TextUnformatted("Round Square filled");
        ImGui::RoundSquare(false, true); ImGui::TextUnformatted("Round Square arrow");
        ImGui::RoundSquare(true, true); ImGui::TextUnformatted("Round Square filled arrow");
        ImGui::Separator();
        ImGui::GridSquare(false); ImGui::TextUnformatted("Grid Square");
        ImGui::GridSquare(true); ImGui::TextUnformatted("Grid Square filled");
        ImGui::GridSquare(false, true); ImGui::TextUnformatted("Grid Square arrow");
        ImGui::GridSquare(true, true); ImGui::TextUnformatted("Grid Square filled arrow");
        ImGui::Separator();
        ImGui::Diamond(false); ImGui::TextUnformatted("Diamond");
        ImGui::Diamond(true); ImGui::TextUnformatted("Diamond filled");
        ImGui::Diamond(false, true); ImGui::TextUnformatted("Diamond arrow");
        ImGui::Diamond(true, true); ImGui::TextUnformatted("Diamond filled arrow");
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Custom badge button"))
    {
        ImGui::CircleButton("Circle", false); ImGui::SameLine();
        ImGui::CircleButton("Circle filled", true); ImGui::SameLine();
        ImGui::CircleButton("Circle arrow", false, true); ImGui::SameLine();
        ImGui::CircleButton("Circle filled arrow", true, true);

        ImGui::SquareButton("Square", false); ImGui::SameLine();
        ImGui::SquareButton("Square filled", true); ImGui::SameLine();
        ImGui::SquareButton("Square arrow", false, true); ImGui::SameLine();
        ImGui::SquareButton("Square filled arrow", true, true);

        ImGui::BracketSquareButton("Bracket Square", false); ImGui::SameLine();
        ImGui::BracketSquareButton("Bracket Square filled", true); ImGui::SameLine();
        ImGui::BracketSquareButton("Bracket Square arrow", false, true); ImGui::SameLine();
        ImGui::BracketSquareButton("Bracket Square filled arrow", true, true);

        ImGui::RoundSquareButton("Round Square", false); ImGui::SameLine();
        ImGui::RoundSquareButton("Round Square filled", true); ImGui::SameLine();
        ImGui::RoundSquareButton("Round Square arrow", false, true); ImGui::SameLine();
        ImGui::RoundSquareButton("Round Square filled arrow", true, true);

        ImGui::GridSquareButton("Grid Square", false); ImGui::SameLine();
        ImGui::GridSquareButton("Grid Square filled", true); ImGui::SameLine();
        ImGui::GridSquareButton("Grid Square arrow", false, true); ImGui::SameLine();
        ImGui::GridSquareButton("Grid Square filled arrow", true, true);

        ImGui::DiamondButton("Diamond", false); ImGui::SameLine();
        ImGui::DiamondButton("Diamond filled", true); ImGui::SameLine();
        ImGui::DiamondButton("Diamond arrow", false, true); ImGui::SameLine();
        ImGui::DiamondButton("Diamond filled arrow", true, true);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Extended ProgressBar and Indicator"))
    {
        const float time = ((float)(((unsigned int) (ImGui::GetTime() * 1000.f)) % 50000) - 25000.f) / 25000.f;
        float progress=(time > 0 ? time : -time);
        // No IDs needed for ProgressBars:
        ImGui::ProgressBar("ProgressBar", progress);
        ImGui::ProgressBar("ProgressBar", 1.f - progress);
        ImGui::ProgressBar("", 500 + progress * 1000, 500, 1500, "%4.0f (absolute value in [500,1500] and fixed bar size)", ImVec2(150, -1));
        ImGui::ProgressBar("", 500 + progress * 1000, 500, 1500, "%3.0f%% (same as above, but with percentage and new colors)", ImVec2(150, -1), ImVec4(0.7, 0.7, 1, 1),ImVec4(0.05, 0.15, 0.5, 0.8),ImVec4(0.8, 0.8, 0,1));
        
        // LoadingIndicatorCircle
        ImGui::Separator();
        ImGui::Text("LoadingIndicatorCircle(...) from https://github.com/ocornut/imgui/issues/1901");
        ImGui::Separator();
        ImGui::TextUnformatted("Test 1:");ImGui::SameLine();
        ImGui::LoadingIndicatorCircle("MyLIC1");ImGui::SameLine();
        ImGui::TextUnformatted("Test 2:");ImGui::SameLine();
        ImGui::LoadingIndicatorCircle("MyLIC2",1.f,&ImGui::GetStyle().Colors[ImGuiCol_Header],&ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered]);
        ImGui::AlignTextToFramePadding();ImGui::TextUnformatted("Test 3:");ImGui::SameLine();ImGui::LoadingIndicatorCircle("MyLIC3",2.0f);
        ImGui::AlignTextToFramePadding();ImGui::TextUnformatted("Test 4:");ImGui::SameLine();ImGui::LoadingIndicatorCircle("MyLIC4",4.0f,&ImGui::GetStyle().Colors[ImGuiCol_Header],&ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered],12,2.f);
        ImGui::Separator();

        // LoadingIndicatorCircle2
        ImGui::Separator();
        ImGui::Text("LoadingIndicatorCircle2(...) from https://github.com/ocornut/imgui/issues/1901");
        ImGui::Separator();
        ImGui::TextUnformatted("Test 1:");ImGui::SameLine();
        ImGui::LoadingIndicatorCircle2("MyLIC21");ImGui::SameLine();
        ImGui::TextUnformatted("Test 2:");ImGui::SameLine();
        ImGui::LoadingIndicatorCircle2("MyLIC22",1.f,1.5f,&ImGui::GetStyle().Colors[ImGuiCol_Header]);
        ImGui::AlignTextToFramePadding();ImGui::TextUnformatted("Test 3:");ImGui::SameLine();ImGui::LoadingIndicatorCircle2("MyLIC23",2.0f);
        ImGui::AlignTextToFramePadding();ImGui::TextUnformatted("Test 4:");ImGui::SameLine();ImGui::LoadingIndicatorCircle2("MyLIC24",4.0f,1.f,&ImGui::GetStyle().Colors[ImGuiCol_Header]);

        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Extra Spinners"))
    {
        static int hue = 0;
        static float nextdot = 0, nextdot2;
        nextdot -= 0.07f;
        static float velocity = 1.f;
        ImGui::SliderFloat("Speed", &velocity, 0.0f, 10.0f, "velocity = %.3f");

        ImGui::Spinner<e_st_rainbow>("Spinner", Radius{16.f}, Thickness{2.f}, Color{ImColor::HSV(++hue * 0.005f, 0.8f, 0.8f)}, Speed{8 * velocity}); ImGui::SameLine();
        ImGui::Spinner<e_st_angle>("SpinnerAng", Radius{16.f}, Thickness{2.f}, Color{ImColor(255, 255, 255)}, BgColor{ImColor(255, 255, 255, 128)}, Speed{8 * velocity}, Angle{IM_PI}); ImGui::SameLine();
        ImGui::Spinner<e_st_dots>("SpinnerDots", FloatPtr{&nextdot}, Radius{16}, Thickness{4}, Color{ImColor(255, 255, 255)}, Speed{1 * velocity}, Dots{12}, MiddleDots{6}, MinThickness{-1.f}); ImGui::SameLine();
        ImGui::Spinner<e_st_ang>("SpinnerAngNoBg", Radius{16.f}, Thickness{2.f}, Color{ImColor(255, 255, 255)}, BgColor{ImColor(255, 255, 255, 0)}, Speed{6 * velocity}, Angle{IM_PI}); ImGui::SameLine();
        ImGui::Spinner<e_st_ang>("SpinnerAng270", Radius{16.f}, Thickness{2.f}, Color{ImColor(255, 255, 255)}, BgColor{ImColor(255, 255, 255, 128)}, Speed{6 * velocity}, Angle{270.f / 360.f * 2 * IM_PI});

        ImGui::SameLine();
        ImGui::SpinnerAng("SpinnerAng270NoBg", 16, 6, ImColor(255, 255, 255), ImColor(255, 255, 255, 0), 6 * velocity, 270.f / 360.f * 2 * IM_PI );

        ImGui::SameLine();
        ImGui::SpinnerVDots("SpinnerVDots", 16, 4, ImColor(255, 255, 255), 2.7f * velocity);

        ImGui::SameLine(); ImGui::Dummy({10, 0}); ImGui::SameLine();
        ImGui::SpinnerBounceBall("SpinnerBounceBall", 16, 6, ImColor(255, 255, 255), 4 * velocity);

        ImGui::SameLine();
        ImGui::SpinnerAngEclipse("SpinnerAng", 16, 5, ImColor(255, 255, 255), 6 * velocity);

        ImGui::SameLine();
        ImGui::SpinnerIngYang("SpinnerIngYang", 16, 5, false, 0, ImColor(255, 255, 255), ImColor(255, 0, 0), 4 * velocity, IM_PI * 0.8f);

        // Next Line
        ImGui::SpinnerBounceDots("SpinnerBounceDots", 6, ImColor(255, 255, 255), 6 * velocity, 3);

        ImGui::SameLine();
        ImGui::SpinnerFadeDots("SpinnerFadeDots", 6, ImColor(255, 255, 255), 8 * velocity, 3);

        ImGui::SameLine();
        ImGui::SpinnerScaleDots("SpinnerMovingDots", 6, ImColor(255, 255, 255), 7 * velocity, 3);

        ImGui::SameLine();
        ImGui::SpinnerMovingDots("SpinnerMovingDots", 6, ImColor(255, 255, 255), 30 * velocity, 3);

        ImGui::SameLine(); ImGui::Dummy({10, 0}); ImGui::SameLine();
        ImGui::SpinnerRotateDots("SpinnerRotateDots", 16, 6, ImColor(255, 255, 255), 4 * velocity, 2);

        ImGui::SameLine(); ImGui::Dummy({10, 0}); ImGui::SameLine();
        ImGui::SpinnerTwinAng("SpinnerTwinAng", 16, 16, 6, ImColor(255, 255, 255), ImColor(255, 0, 0), 4 * velocity);

        ImGui::SameLine();
        ImGui::SpinnerClock("SpinnerClock", 16, 2, ImColor(255, 0, 0), ImColor(255, 255, 255), 4 * velocity);

        ImGui::SameLine();
        ImGui::SpinnerIngYang("SpinnerIngYangR", 16, 5, true, 0.1f, ImColor(255, 255, 255), ImColor(255, 0, 0), 4 * velocity, IM_PI * 0.8f);

        // next line
        ImGui::SpinnerTwinAng180("SpinnerTwinAng", 16, 12, 4, ImColor(255, 255, 255), ImColor(255, 0, 0), 4 * velocity);

        ImGui::SameLine();
        ImGui::SpinnerTwinAng360("SpinnerTwinAng360", 16, 11, 4, ImColor(255, 255, 255), ImColor(255, 0, 0), 4 * velocity);

        ImGui::SameLine();
        ImGui::SpinnerIncDots("SpinnerIncDots", 16, 4, ImColor(255, 255, 255), 5.6f, 6);

        ImGui::SameLine();
        nextdot2 -= 0.2f * velocity;
        ImGui::SpinnerDots("SpinnerDots", &nextdot2, 16, 4, ImColor(255, 255, 255), 0.3f, 12, 6, 0.f);

        ImGui::SameLine();
        ImGui::SpinnerIncScaleDots("SpinnerIncScaleDots", 16, 4, ImColor(255, 255, 255), 6.6f, 6);

        ImGui::SameLine();
        ImGui::SpinnerAng("SpinnerAng90", 16, 6, ImColor(255, 255, 255), ImColor(255, 255, 255, 128), 8.f * velocity, IM_PI / 2.f);

        ImGui::SameLine();
        ImGui::SpinnerAng("SpinnerAng90", 16, 6, ImColor(255, 255, 255), ImColor(255, 255, 255, 0), 8.5f * velocity, IM_PI / 2.f);

        ImGui::SameLine();
        ImGui::SpinnerFadeBars("SpinnerFadeBars", 10, ImColor(255, 255, 255), 4.8f * velocity, 3);

        ImGui::SameLine(); ImGui::Dummy({10, 0}); ImGui::SameLine();
        ImGui::SpinnerPulsar("SpinnerPulsar", 16, 2, ImColor(255, 255, 255), 1 * velocity);

        ImGui::SameLine();
        ImGui::SpinnerIngYang("SpinnerIngYangR2", 16, 5, true, 3.f, ImColor(255, 255, 255), ImColor(255, 0, 0), 4 * velocity, IM_PI * 0.8f);

        // Next line
        ImGui::SpinnerBarsRotateFade("SpinnerBarsRotateFade", 8, 18, 4, ImColor(255, 255, 255), 7.6f, 6);

        ImGui::SameLine();
        ImGui::SpinnerFadeBars("SpinnerFadeScaleBars", 10, ImColor(255, 255, 255), 6.8f, 3, true);

        ImGui::SameLine(); ImGui::Dummy({10, 0}); ImGui::SameLine();
        ImGui::SpinnerBarsScaleMiddle("SpinnerBarsScaleMiddle", 6, ImColor(255, 255, 255), 8.8f, 3);

        ImGui::SameLine(); ImGui::Dummy({10, 0}); ImGui::SameLine();
        ImGui::SpinnerAngTwin("SpinnerAngTwin1", 16, 13, 2, ImColor(255, 0, 0), ImColor(255, 255, 255), 6 * velocity, IM_PI / 2.f);

        ImGui::SameLine();
        ImGui::SpinnerAngTwin("SpinnerAngTwin2", 13, 16, 2, ImColor(255, 0, 0), ImColor(255, 255, 255), 6 * velocity, IM_PI / 2.f);

        ImGui::SameLine();
        ImGui::SpinnerAngTwin("SpinnerAngTwin3", 13, 16, 2, ImColor(255, 0, 0), ImColor(255, 255, 255), 6 * velocity, IM_PI / 2.f, 2);

        ImGui::SameLine();
        ImGui::SpinnerAngTwin("SpinnerAngTwin4", 16, 13, 2, ImColor(255, 0, 0), ImColor(255, 255, 255), 6 * velocity, IM_PI / 2.f, 2);

        ImGui::SameLine(); 
        ImGui::SpinnerTwinPulsar("SpinnerTwinPulsar", 16, 2, ImColor(255, 255, 255), 0.5f * velocity, 2);

        ImGui::SameLine();
        ImGui::SpinnerAngTwin("SpinnerAngTwin4", 14, 13, 3, ImColor(255, 0, 0), ImColor(0, 0, 0, 0), 5 * velocity, IM_PI / 1.5f, 2);

        // next line
        ImGui::SpinnerTwinBall("SpinnerTwinBall", 16, 11, 2, 2.5f, ImColor(255, 0, 0), ImColor(255, 255, 255), 6 * velocity, 2);

        ImGui::SameLine();
        ImGui::SpinnerTwinBall("SpinnerTwinBall2", 15, 19, 2, 2.f, ImColor(255, 0, 0), ImColor(255, 255, 255), 6 * velocity, 3);

        ImGui::SameLine();
        ImGui::SpinnerTwinBall("SpinnerTwinBall2", 16, 16, 2, 5.f, ImColor(255, 0, 0), ImColor(255, 255, 255), 5 * velocity, 1);

        ImGui::SameLine();
        ImGui::SpinnerAngTriple("SpinnerAngTriple", 16, 13, 10, 1.3f, ImColor(255, 255, 255), ImColor(255, 0, 0), ImColor(255, 255, 255), 5 * velocity, 1.5f * IM_PI);

        ImGui::SameLine();
        ImGui::SpinnerIncFullDots("SpinnerIncFullDots", 16, 4, ImColor(255, 255, 255), 5.6f, 4);

        ImGui::SameLine();
        ImGui::SpinnerGooeyBalls("SpinnerGooeyBalls", 16, ImColor(255, 255, 255), 2.f);

        ImGui::SameLine();
        ImGui::SpinnerRotateGooeyBalls("SpinnerRotateGooeyBalls2", 16, 5, ImColor(255, 255, 255), 6.f, 2);

        ImGui::SameLine();
        ImGui::SpinnerRotateGooeyBalls("SpinnerRotateGooeyBalls3", 16, 5, ImColor(255, 255, 255), 6.f, 3);

        ImGui::SameLine();
        ImGui::SpinnerMoonLine("SpinnerMoonLine", 16, 3, ImColor(200, 80, 0), ImColor(80, 80, 80), 5 * velocity);

        ImGui::SameLine();
        ImGui::SpinnerArcRotation("SpinnerArcRotation", 13, 5, ImColor(255, 255, 255), 3 * velocity, 4);


        // Next line
        ImGui::SpinnerArcFade("SpinnerArcFade", 13, 5, ImColor(255, 255, 255), 3 * velocity, 4);

        ImGui::SameLine();
        ImGui::SpinnerFilling("SpinnerFilling", 16, 6, ImColor(255, 255, 255), ImColor(255, 0, 0), 4 * velocity);

        ImGui::SameLine();
        ImGui::SpinnerTopup("SpinnerTopup", 16, 12, ImColor(255, 0, 0), ImColor(80, 80, 80), ImColor(255, 255, 255), 1 * velocity);


        ImGui::SameLine(); 
        ImGui::SpinnerFadePulsar("SpinnerFadePulsar", 16, ImColor(255, 255, 255), 1.5f * velocity, 1);

        ImGui::SameLine(); 
        ImGui::SpinnerFadePulsar("SpinnerFadePulsar2", 16, ImColor(255, 255, 255), 0.9f * velocity, 2);


        ImGui::SameLine(); 
        ImGui::SpinnerPulsar("SpinnerPulsar", 16, 2, ImColor(255, 255, 255), 1 * velocity, false);

        ImGui::SameLine(); 
        ImGui::SpinnerDoubleFadePulsar("SpinnerDoubleFadePulsar", 16, 2, ImColor(255, 255, 255), 2 * velocity);


        ImGui::SameLine(); 
        ImGui::SpinnerFilledArcFade("SpinnerFilledArcFade", 16, ImColor(255, 255, 255), 4 * velocity, 4);

        ImGui::SameLine(); 
        ImGui::SpinnerFilledArcFade("SpinnerFilledArcFade6", 16, ImColor(255, 255, 255), 6 * velocity, 6);

        ImGui::SameLine(); 
        ImGui::SpinnerFilledArcFade("SpinnerFilledArcFade6", 16, ImColor(255, 255, 255), 8 * velocity, 12);


        ImGui::SameLine(); 
        ImGui::SpinnerFilledArcColor("SpinnerFilledArcColor", 16, ImColor(255, 0, 0), ImColor(255, 255, 255), 2.8f, 4);

        // End
        ImGui::TreePop();
    }
	if (ImGui::TreeNode("Color Bands"))
	{
        ImGui::PushItemWidth(300);
		static float col[4] = { 1, 1, 1, 1 };
		ImGui::ColorEdit4("Color", col);
		float const width = 300;
		float const height = 32.0f;
		static float gamma = 1.0f;
		ImGui::DragFloat("Gamma##Color", &gamma, 0.01f, 0.1f, 10.0f);
		static int division = 32;
		ImGui::DragInt("Division", &division, 1, 1, 128);

		ImGui::Text("HueBand");
		ImGui::DrawHueBand(ImGui::GetCursorScreenPos(), ImVec2(width, height), division, col, col[3], gamma);
		ImGui::InvisibleButton("##Zone", ImVec2(width, height), 0);

		ImGui::Text("LuminanceBand");
		ImGui::DrawLumianceBand(ImGui::GetCursorScreenPos(), ImVec2(width, height), division, ImVec4(col[0], col[1], col[2], col[3]), gamma);
		ImGui::InvisibleButton("##Zone", ImVec2(width, height), 0);

		ImGui::Text("SaturationBand");
		ImGui::DrawSaturationBand(ImGui::GetCursorScreenPos(), ImVec2(width, height), division, ImVec4(col[0], col[1], col[2], col[3]), gamma);
		ImGui::InvisibleButton("##Zone", ImVec2(width, height), 0);

        ImGui::Text("ContrastBand");
		ImGui::DrawContrastBand(ImGui::GetCursorScreenPos(), ImVec2(width, height), ImVec4(col[0], col[1], col[2], col[3]));
		ImGui::InvisibleButton("##Zone", ImVec2(width, height), 0);

		ImGui::Separator();
		ImGui::Text("Custom Color Band");
		static int frequency = 6;
		ImGui::SliderInt("Frequency", &frequency, 1, 32);
		static float alpha = 1.0f;
		ImGui::SliderFloat("alpha", &alpha, 0.0f, 1.0f);

		float const fFrequency = frequency;
		float const fAlpha = alpha;
		ImGui::DrawColorBandEx< true >(ImGui::GetWindowDrawList(), ImGui::GetCursorScreenPos(), ImVec2(width, height),
			[fFrequency, fAlpha](float const t)
			{
				float r = ImSign(ImSin(fFrequency * 2.0f * IM_PI * t + 2.0f * IM_PI * 0.0f / fFrequency)) * 0.5f + 0.5f;
				float g = ImSign(ImSin(fFrequency * 2.0f * IM_PI * t + 2.0f * IM_PI * 2.0f / fFrequency)) * 0.5f + 0.5f;
				float b = ImSign(ImSin(fFrequency * 2.0f * IM_PI * t + 2.0f * IM_PI * 4.0f / fFrequency)) * 0.5f + 0.5f;

				return IM_COL32(r * 255, g * 255, b * 255, fAlpha * 255);
			},
			division, gamma);
		ImGui::InvisibleButton("##Zone", ImVec2(width, height), 0);

        ImGui::PopItemWidth();
		ImGui::TreePop();
	}
    if (ImGui::TreeNode("Color Ring"))
	{
        ImGui::PushItemWidth(300);
		static int division = 32;
		float const width = 300;
		ImGui::SliderInt("Division", &division, 3, 128);
		static float colorOffset = 0;
		ImGui::SliderFloat("Color Offset", &colorOffset, 0.0f, 2.0f);
		static float thickness = 0.5f;
		ImGui::SliderFloat("Thickness", &thickness, 1.0f / width, 1.0f);

		ImDrawList* pDrawList = ImGui::GetWindowDrawList();
		{
			ImVec2 curPos = ImGui::GetCursorScreenPos();
			ImGui::InvisibleButton("##Zone", ImVec2(width, width), 0);

			ImGui::DrawColorRingEx< true >(pDrawList, curPos, ImVec2(width, width), thickness,
				[](float t)
				{
					float r, g, b;
					ImGui::ColorConvertHSVtoRGB(t, 1.0f, 1.0f, r, g, b);

					return IM_COL32(r * 255, g * 255, b * 255, 255);
				}, division, colorOffset);
		}
		static float center = 0.5f;
		ImGui::DragFloat("Center", &center, 0.01f, 0.0f, 1.0f);
		static float colorDotBound = 0.5f;
		ImGui::SliderFloat("Alpha Pow", &colorDotBound, -1.0f, 1.0f);
		static int frequency = 6;
		ImGui::SliderInt("Frequency", &frequency, 1, 32);
		{
			ImGui::Text("Nearest");
			ImVec2 curPos = ImGui::GetCursorScreenPos();
			ImGui::InvisibleButton("##Zone", ImVec2(width, width) * 0.5f, 0);

			float fCenter = center;
			float fColorDotBound = colorDotBound;
			ImGui::DrawColorRingEx< false >(pDrawList, curPos, ImVec2(width, width * 0.5f), thickness,
				[fCenter, fColorDotBound](float t)
				{
					float r, g, b;
					ImGui::ColorConvertHSVtoRGB(t, 1.0f, 1.0f, r, g, b);

					ImVec2 const v0(ImCos(t * 2.0f * IM_PI), ImSin(t * 2.0f * IM_PI));
					ImVec2 const v1(ImCos(fCenter * 2.0f * IM_PI), ImSin(fCenter * 2.0f * IM_PI));

					float const dot = ImDot(v0, v1);
					float const angle = ImAcos(dot) / IM_PI;// / width;

					return IM_COL32(r * 255, g * 255, b * 255, (dot > fColorDotBound ? 1.0f : 0.0f) * 255);
				}, division, colorOffset);
		}
		{
			ImGui::Text("Custom");
			ImVec2 curPos = ImGui::GetCursorScreenPos();
			ImGui::InvisibleButton("##Zone", ImVec2(width, width) * 0.5f, 0);

			float const fFreq = (float)frequency;
			ImGui::DrawColorRingEx< true >(pDrawList, curPos, ImVec2(width, width) * 0.5f, thickness,
				[fFreq](float t)
				{
					float v = ImSign(ImCos(fFreq * 2.0f * IM_PI * t)) * 0.5f + 0.5f;

					return IM_COL32(v * 255, v * 255, v * 255, 255);
				}, division, colorOffset);
		}
        ImGui::PopItemWidth();
		ImGui::TreePop();
	}
    if (ImGui::TreeNode("Color Selector"))
	{
        ImGui::PushItemWidth(300);
		float const width = 300;
		float const height = 32.0f;
		static float offset = 0.0f;
		static int division = 32;
        static float gamma = 1.0f;
		ImGui::DragInt("Division", &division, 1.0f, 2, 256);
        ImGui::DragFloat("Gamma##Color", &gamma, 0.01f, 0.1f, 10.0f);
		static float alphaHue = 1.0f;
		static float alphaHideHue = 0.125f;
		ImGui::DragFloat("Offset##ColorSelector", &offset, 0.0f, 0.0f, 1.0f);
		ImGui::DragFloat("Alpha Hue", &alphaHue, 0.0f, 0.0f, 1.0f);
		ImGui::DragFloat("Alpha Hue Hide", &alphaHideHue, 0.0f, 0.0f, 1.0f);
		static float hueCenter = 0.5f;
		static float hueWidth = 0.1f;
		static float featherLeft = 0.125f;
		static float featherRight = 0.125f;
		ImGui::DragFloat("featherLeft", &featherLeft, 0.0f, 0.0f, 0.5f);
		ImGui::DragFloat("featherRight", &featherRight, 0.0f, 0.0f, 0.5f);
		
        ImGui::Spacing();
        ImGui::TextUnformatted("Hue:"); ImGui::SameLine();
        ImGui::HueSelector("Hue Selector", ImVec2(width, height), &hueCenter, &hueWidth, &featherLeft, &featherRight, 0.5f, 1.0f, division, alphaHue, alphaHideHue, offset);
		
        static bool rgb_color = false;
        ImGui::Checkbox("RGB Color Bar", &rgb_color);
        ImGui::Spacing();
        static float lumianceCenter = 0.0f;
        ImGui::TextUnformatted("Lum:"); ImGui::SameLine();
        ImGui::LumianceSelector("Lumiance Selector", ImVec2(width, height), &lumianceCenter, 0.0f, -1.f, 1.f, 1.0f, division, gamma, rgb_color);

        ImGui::Spacing();
        static float saturationCenter = 0.0f;
        ImGui::TextUnformatted("Sat:"); ImGui::SameLine();
        ImGui::SaturationSelector("Saturation Selector", ImVec2(width, height), &saturationCenter, 0.0f, -1.f, 1.f, 1.0f, division, gamma, rgb_color);
        
        ImGui::Spacing();
        static float contrastCenter = 1.0f;
        ImGui::TextUnformatted("Con:"); ImGui::SameLine();
        ImGui::ContrastSelector("Contrast Selector", ImVec2(width, height), &contrastCenter, 1.0f, 1.0f, rgb_color);

        ImGui::Spacing();
        static float gammaCenter = 1.0f;
        ImGui::TextUnformatted("Gma:"); ImGui::SameLine();
        ImGui::GammaSelector("Gamma Selector", ImVec2(width, height), &gammaCenter, 1.0f, 0.f, 4.f, 1.0f);

        ImGui::Spacing();
        static float temperatureCenter = 5000.0f;
        ImGui::TextUnformatted("Tmp:"); ImGui::SameLine();
        ImGui::TemperatureSelector("TemperatureSelector Selector", ImVec2(width, height), &temperatureCenter, 5000.0f, 2000.f, 8000.f, 1.0f);

        ImGui::Spacing();
        static ImVec4 rgba = ImVec4(0.0, 0.0, 0.0, 0.0);
        ImGui::BalanceSelector("Balance Selector", ImVec2(width / 2, height), &rgba, ImVec4(0, 0, 0, 0));

        ImGui::PopItemWidth();
        ImGui::TreePop();
	}
    if (ImGui::TreeNode("Slider Select"))
    {
        ImGui::PushItemWidth(300);

        static ImVec2 val2d(0.f, 0.f);
        static ImVec4 val3d(0.f, 0.f, 0.f, 0.f);
        ImGui::InputVec2("Vec2D", &val2d, ImVec2(-1.f, -1.f), ImVec2(1.f, 1.f));
        ImGui::SameLine();
        ImGui::InputVec3("Vec3D", &val3d, ImVec4(-1.f, -1.f, -1.f, -1.f), ImVec4(1.f, 1.f, 1.f, 1.f));
        ImGui::SameLine();
        static ImVec2 min(-0.5f, -0.5f);
		static ImVec2 max(0.5f, 0.5f);
		ImGui::RangeSelect2D("Range Select 2D", &min.x, &min.y, &max.x, &max.y, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f);

        ImGui::PopItemWidth();
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Bezier Select"))
    { 
        static float v[5] = { 0.950f, 0.050f, 0.795f, 0.035f }; 
        ImGui::BezierSelect("##easeInExpo", ImVec2(200, 200), v);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Bezier View"))
    {
        ImGuiIO& io = ImGui::GetIO();
        bool reset = false;
        static bool value_limited = true;
        static bool scroll_v = true;
        static bool move_curve = true;
        static bool keep_begin_end = false;
        static bool dock_begin_end = false;
        static ImGui::KeyPointEditor rampEdit(IM_COL32(0, 0, 0, 255), IM_COL32(32, 32, 32, 128));
        char ** curve_type_list = nullptr;
        auto curve_type_count = ImCurveEdit::GetCurveTypeName(curve_type_list);
        float table_width = 300;
        auto size_x = ImGui::GetWindowSize().x - table_width - 60;
        if (rampEdit.GetCurveCount() <= 0)
        {
            rampEdit.AddCurve("key1", ImCurveEdit::Smooth, IM_COL32(255, 0, 0, 255), true, -1, 1, 0);
            rampEdit.AddPoint(0, ImVec2(size_x * 0.f, 0), ImCurveEdit::Smooth);
            rampEdit.AddPoint(0, ImVec2(size_x * 0.25f, 0.610f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(0, ImVec2(size_x * 0.5f, 1.0f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(0, ImVec2(size_x * 0.75f, 0.610f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(0, ImVec2(size_x * 1.f, 0.f), ImCurveEdit::Smooth);

            rampEdit.AddCurve("key2", ImCurveEdit::Smooth, IM_COL32(0, 255, 0, 255), true, 0, 1, 0);
            rampEdit.AddPoint(1, ImVec2(size_x * 0.f, 1.f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(1, ImVec2(size_x * 0.25f, 0.75f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(1, ImVec2(size_x * 0.5f, 0.5f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(1, ImVec2(size_x * 0.75f, 0.75f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(1, ImVec2(size_x * 1.f, 1.f), ImCurveEdit::Smooth);

            rampEdit.AddCurve("key3", ImCurveEdit::Smooth, IM_COL32(0, 0, 255, 255), true, 0, 100, 50);
            rampEdit.AddPoint(2, ImVec2(size_x * 0.f, 0.f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(2, ImVec2(size_x * 0.25f, 0.05f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(2, ImVec2(size_x * 0.5f, 0.25f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(2, ImVec2(size_x * 0.75f, 0.75f), ImCurveEdit::Smooth);
            rampEdit.AddPoint(2, ImVec2(size_x * 1.f, 1.f), ImCurveEdit::Smooth);
        }
        if (ImGui::Button("Reset##curve_reset"))
            reset = true;
        if (rampEdit.GetMax().x <= 0 || reset)
        {
            rampEdit.SetMax(ImVec2(size_x, 1.f));
            rampEdit.SetMin(ImVec2(0.f, 0.f));
        }
        ImGui::Checkbox("Value limited", &value_limited); ImGui::SameLine();
        ImGui::Checkbox("Scroll V", &scroll_v); ImGui::SameLine();
        ImGui::Checkbox("Move Curve", &move_curve); ImGui::SameLine();
        ImGui::Checkbox("Keep Begin End", &keep_begin_end); ImGui::SameLine();
        ImGui::Checkbox("Dock Begin End", &dock_begin_end);
        uint32_t curvs_flags = CURVE_EDIT_FLAG_NONE;
        if (value_limited) curvs_flags |= CURVE_EDIT_FLAG_VALUE_LIMITED;
        if (scroll_v) curvs_flags |= CURVE_EDIT_FLAG_SCROLL_V;
        if (move_curve) curvs_flags |= CURVE_EDIT_FLAG_MOVE_CURVE;
        if (keep_begin_end) curvs_flags |= CURVE_EDIT_FLAG_KEEP_BEGIN_END;
        if (dock_begin_end) curvs_flags |= CURVE_EDIT_FLAG_DOCK_BEGIN_END;

        ImVec2 item_pos = ImGui::GetCursorScreenPos();
        ImVector<ImCurveEdit::editPoint> edit_points;
        ImCurveEdit::Edit(rampEdit, ImVec2(size_x, 300), ImGui::GetID("##bezier_view"), curvs_flags, nullptr, nullptr, &edit_points);
        if (ImGui::IsItemHovered())
        {
            float pos = io.MousePos.x - item_pos.x;
            ImGui::BeginTooltip();
            for (int i = 0; i < rampEdit.GetCurveCount(); i++)
            {
                auto value = rampEdit.GetValue(i, pos);
                ImGui::Text("pos=%.0f val=%f", pos, value);
            }
            ImGui::EndTooltip();
        }

        ImGui::SameLine();
        static ImGuiTableFlags flags = ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;
        if (ImGui::BeginTable("table_selected", 5, flags, ImVec2(table_width, 300.f)))
        {
            ImGui::TableSetupScrollFreeze(2, 1);
            ImGui::TableSetupColumn("C", ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_WidthFixed, 20); // Make the first column not hideable to match our use of TableSetupScrollFreeze()
            ImGui::TableSetupColumn("P", ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_WidthFixed, 20);
            ImGui::TableSetupColumn("X", ImGuiTableColumnFlags_WidthFixed, 80);
            ImGui::TableSetupColumn("Y", ImGuiTableColumnFlags_WidthFixed, 80);
            ImGui::TableSetupColumn("T", ImGuiTableColumnFlags_WidthFixed, 100);
            ImGui::TableHeadersRow();
            for (int row = 0; row < edit_points.size(); row++)
            {
                ImGui::TableNextRow(ImGuiTableRowFlags_None);
                for (int column = 0; column < 5; column++)
                {
                    if (!ImGui::TableSetColumnIndex(column) && column > 0)
                        continue;
                    auto point = rampEdit.GetPoint(edit_points[row].curveIndex, edit_points[row].pointIndex);
                    std::string column_id = std::to_string(edit_points[row].curveIndex) + "@" + std::to_string(edit_points[row].pointIndex);
                    switch (column)
                    {
                        case 0 : ImGui::Text("%u", edit_points[row].curveIndex); break;
                        case 1 : ImGui::Text("%u", edit_points[row].pointIndex); break;
                        case 2 :
                            ImGui::PushItemWidth(80);
                            if (ImGui::SliderFloat(("##x_pos@" + column_id).c_str(), &point.point.x, 0.f, size_x, "%.0f"))
                            {
                                rampEdit.EditPoint(edit_points[row].curveIndex, edit_points[row].pointIndex, point.point, point.type);
                            }
                            ImGui::PopItemWidth();
                        break;
                        case 3 :
                            ImGui::PushItemWidth(80);
                            if (ImGui::SliderFloat(("##y_pos" + column_id).c_str(), &point.point.y, 0.f, 1.f, "%.1f"))
                            {
                                rampEdit.EditPoint(edit_points[row].curveIndex, edit_points[row].pointIndex, point.point, point.type);
                            }
                            ImGui::PopItemWidth();
                        break;
                        case 4 :
                            ImGui::PushItemWidth(100);
                            if (ImGui::Combo(("##type" + column_id).c_str(), (int*)&point.type, curve_type_list, curve_type_count))
                            {
                                rampEdit.EditPoint(edit_points[row].curveIndex, edit_points[row].pointIndex, point.point, point.type);
                            }
                            ImGui::PopItemWidth();
                        break;
                        default : break;
                    }
                    
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Splitter windows"))
    {
        float h = 200;
        static float hsz1 = 300;
        static float hsz2 = 300;
        static float vsz1 = 100;
        static float vsz2 = 100;
        ImGui::Splitter(true, 8.0f, &hsz1, &hsz2, 8, 8, h);
        ImGui::BeginChild("1", ImVec2(hsz1, h), true);
            ImGui::Text("Window 1");
        ImGui::EndChild();
        ImGui::SameLine();

        ImGui::BeginChild("2", ImVec2(hsz2, h), true);
            ImGui::Splitter(false, 8.0f, &vsz1, &vsz2, 8, 8, hsz2);
            ImGui::BeginChild("3", ImVec2(hsz2, vsz1), false);
                ImGui::Text("Window 2");
            ImGui::EndChild();
            ImGui::BeginChild("4", ImVec2(hsz2, vsz2), false);
                ImGui::Text("Window 3");
            ImGui::EndChild();
        ImGui::EndChild();

        ImGui::TreePop();
    }
}

void ShowImKalmanDemoWindow()
{
    ImGuiIO& io = ImGui::GetIO();
    int64_t t1, t2, predicted_time, update_time;
    int state_size = 4;
    int measurement_size   = 2;
    static int noise_covariance_pow = 5;
    static int measurement_noise_covariance_pow = 1;
    static ImKalman kalman(state_size, measurement_size);
    static ImMat measurement;
    measurement.create_type(1, measurement_size, IM_DT_FLOAT32);

    //1.kalman previous state
    ImVec2 statePt = ImVec2(kalman.statePre.at<float>(0, 0), kalman.statePre.at<float>(0, 1));
    //2.kalman prediction
    t1 = ImGui::get_current_time_usec();
    ImMat prediction  = kalman.predicted();
    t2 = ImGui::get_current_time_usec();
    predicted_time = t2 - t1;
    ImVec2 predictPt = ImVec2(prediction.at<float>(0, 0), prediction.at<float>(0, 1));
    //3. kalman update
    measurement.at<float>(0, 0) = io.MousePos.x;
    measurement.at<float>(0, 1) = io.MousePos.y;
    t1 = ImGui::get_current_time_usec();
    kalman.update(measurement);
    t2 = ImGui::get_current_time_usec();
    update_time = t2 - t1;

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->AddCircle(statePt, 3, IM_COL32(255,0,0,255));
    drawList->AddCircle(predictPt, 3, IM_COL32(0,255,0,255));
    drawList->AddCircle(io.MousePos, 3, IM_COL32(255,255,255,255));

    ImGui::Text("Predicted time: %lldus", predicted_time);
    ImGui::Text("   Update time: %lldus", update_time);
    if (ImGui::SliderInt("noise covariance pow", &noise_covariance_pow, 1, 5))
    {
        kalman.covariance(1.f / (pow(10, noise_covariance_pow)), 1.f / (pow(10, measurement_noise_covariance_pow)));
    }
    if (ImGui::SliderInt("measurement noise covariance pow", &measurement_noise_covariance_pow, 1, 5))
    {
        kalman.covariance(1.f / (pow(10, noise_covariance_pow)), 1.f / (pow(10, measurement_noise_covariance_pow)));
    }
}

void ShowImFFTDemoWindow()
{
#define FFT_DATA_LENGTH 1024
#define SUB_LENGTH (FFT_DATA_LENGTH / 4)
    ImGuiIO &io = ImGui::GetIO();
    static float wave_scale = 1.0f;
    static float fft_scale = 1.0f;
    static float x_scale = 1.0f;
    ImMat time_domain;
    time_domain.create_type(FFT_DATA_LENGTH, IM_DT_FLOAT32);
    static int signal_type = 0;
    static const char * signal_item[] = {"Sine", "Composition", "Square wave", "Triangular Wave", "Sawtooth wave"};
    static int view_type = 0;
    static const char * view_item[] = {"FFT", "Amplitude", "Phase", "DB"};
    static ImGui::ImMat spectrogram;
    static ImTextureID spectrogram_texture = nullptr;
    ImGui::PushItemWidth(200);
    if (ImGui::Combo("Signal Type", &signal_type, signal_item, IM_ARRAYSIZE(signal_item)))
    {
        spectrogram.release();
    }
    ImGui::SameLine();
    ImGui::Combo("View Type", &view_type, view_item, IM_ARRAYSIZE(view_item));
    ImGui::PopItemWidth();
    // init time domain data
    switch (signal_type)
    {
        case 0: // Sine
        {
            for (int i = 0; i < FFT_DATA_LENGTH; i++)
            {
                float t = (float)i / (float)FFT_DATA_LENGTH;
                time_domain.at<float>(i) = 0.5 * sin(2 * M_PI * 100 * t);
            }
        }
        break;
        case 1: // Composition
        {
            for (int i = 0; i < FFT_DATA_LENGTH; i++)
            {
                float t = (float)i / (float)FFT_DATA_LENGTH;
                time_domain.at<float>(i) = 0.2 * sin(2 * M_PI * 100 * t) + 0.3 * sin(2 * M_PI * 200 * t) + 0.4 * sin(2 * M_PI * 300 * t);
            }
        }
        break;
        case 2: // Square wave
        {
            int sign = 1;
            float step = 0;
            float t = (float)FFT_DATA_LENGTH / 50.f;
            for (int i = 0; i < FFT_DATA_LENGTH; i++)
            {
                step ++; if (step >= t) { step = 0; sign = -sign; }
                time_domain.at<float>(i) = 0.5 * sign;
            }
        }
        break;
        case 3: // Triangular Wave
        {
            int sign = 1;
            float step = -1;
            float t = 50.f / (float)FFT_DATA_LENGTH;
            for (int i = 0; i < FFT_DATA_LENGTH; i++)
            {
                step += t * sign; if (step >= 1.0 || step <= -1.0) sign = -sign;
                time_domain.at<float>(i) = 0.5 * step;
            }
        }
        break;
        case 4: // Sawtooth wave
        {
            float step = -1;
            float t = 50.f / (float)FFT_DATA_LENGTH;
            for (int i = 0; i < FFT_DATA_LENGTH; i++)
            {
                step += t; if (step >= 1.0) step = -1;
                time_domain.at<float>(i) = 0.5 * step;
            }
        }
        break;
        default: break;
    }

    // spectrogram
    if (spectrogram.empty())
    {
        ImGui::ImSpectrogram(time_domain, spectrogram, 128);
        if (spectrogram_texture) { ImGui::ImDestroyTexture(spectrogram_texture); spectrogram_texture = nullptr; }
        ImGui::ImMatToTexture(spectrogram, spectrogram_texture);
    }
    // init frequency domain data
    ImGui::ImMat frequency_domain;
    frequency_domain.clone_from(time_domain);

    // do fft
    ImRFFT((float *)frequency_domain.data, frequency_domain.w, true);

    ImGui::ImMat amplitude;
    amplitude.create_type((FFT_DATA_LENGTH >> 1) + 1, IM_DT_FLOAT32);
    ImGui::ImReComposeAmplitude((float*)frequency_domain.data, (float *)amplitude.data, FFT_DATA_LENGTH);

    ImGui::ImMat phase;
    phase.create_type((FFT_DATA_LENGTH >> 1) + 1, IM_DT_FLOAT32);
    ImGui::ImReComposePhase((float*)frequency_domain.data, (float *)phase.data, FFT_DATA_LENGTH);

    ImGui::ImMat db;
    db.create_type((FFT_DATA_LENGTH >> 1) + 1, IM_DT_FLOAT32);
    ImGui::ImReComposeDB((float*)frequency_domain.data, (float *)db.data, FFT_DATA_LENGTH, false);

    // do ifft
    ImMat time_domain_out;
    time_domain_out.clone_from(frequency_domain);
    ImRFFT((float *)time_domain_out.data, time_domain_out.w, false);

    ImGui::BeginChild("FFT Result");
    // draw result
    ImVec2 channel_view_size = ImVec2(1024 * x_scale, 128);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 1.f));

    // draw time domain
    if (ImPlot::BeginPlot("##time_domain", channel_view_size, ImPlotFlags_CanvasOnly | ImPlotFlags_NoFrame | ImPlotFlags_NoChild | ImPlotFlags_NoInputs))
    {
        ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
        ImPlot::SetupAxesLimits(0, time_domain.w, -1.0 * wave_scale, 1.0 * wave_scale, ImGuiCond_Always);
        ImPlot::PlotLine("##TimeDomain", (float *)time_domain.data, time_domain.w);
        ImPlot::EndPlot();
    }
    if (ImGui::IsItemHovered())
    {
        if (io.MouseWheel < -FLT_EPSILON) { wave_scale *= 0.9f; if (wave_scale < 0.1f) wave_scale = 0.1f; }
        if (io.MouseWheel >  FLT_EPSILON) { wave_scale *= 1.1f; if (wave_scale > 4.0f) wave_scale = 4.0f; }
        if (io.MouseWheelH < -FLT_EPSILON) { x_scale *= 0.9f; if (x_scale < 1.0f) x_scale = 1.0f; }
        if (io.MouseWheelH >  FLT_EPSILON) { x_scale *= 1.1f; if (x_scale > 16.0f) x_scale = 16.0f; }
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) { wave_scale = 1.0; x_scale = 1.0; }
    }

    // draw spectrogram
    if (spectrogram_texture)
    {
        ImGui::Image(spectrogram_texture, channel_view_size);
    }

    // draw frequency domain data
    float * fft_data = nullptr;
    int data_count = 0;
    double f_min = 0.f;
    double f_max = 1.f;
    switch (view_type)
    {
        case 0:
            fft_data = (float *)frequency_domain.data; data_count = frequency_domain.w;
            f_min = -8.f; f_max = 8.f;
        break;
        case 1:
            fft_data = (float *)amplitude.data; data_count = amplitude.w;
            f_min = 0.f; f_max = 32.f;
        break;
        case 2:
            fft_data = (float *)phase.data; data_count = phase.w;
            f_min = -180.f; f_max = 180.f;
        break;
        case 3:
            fft_data = (float *)db.data; data_count = db.w;
            f_min = 0.f; f_max = 32.f;
        break;
        default: break;
    }

    if (ImPlot::BeginPlot("##fft_domain", channel_view_size, ImPlotFlags_CanvasOnly | ImPlotFlags_NoFrame | ImPlotFlags_NoChild | ImPlotFlags_NoInputs))
    {
        ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
        ImPlot::SetupAxesLimits(0, data_count, f_min * fft_scale, f_max * fft_scale, ImGuiCond_Always);
        ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.75f);
        ImPlot::PlotShaded("##FFTDomainAMP", (float *)fft_data, data_count);
        ImPlot::PopStyleVar();
        ImPlot::PlotLine("##FFTDomain", (float *)fft_data, data_count);
        ImPlot::EndPlot();
    }
    if (ImGui::IsItemHovered())
    {
        if (io.MouseWheel < -FLT_EPSILON) { fft_scale *= 0.9f; if (fft_scale < 0.1f) fft_scale = 0.1f; }
        if (io.MouseWheel >  FLT_EPSILON) { fft_scale *= 1.1f; if (fft_scale > 4.0f) fft_scale = 4.0f; }
        if (io.MouseWheelH < -FLT_EPSILON) { x_scale *= 0.9f; if (x_scale < 1.0f) x_scale = 1.0f; }
        if (io.MouseWheelH >  FLT_EPSILON) { x_scale *= 1.1f; if (x_scale > 16.0f) x_scale = 16.0f; }
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) { fft_scale = 1.0; x_scale = 1.0f; }
    }

    // draw time domain out(ifft)
    if (ImPlot::BeginPlot("##time_domain_out", channel_view_size, ImPlotFlags_CanvasOnly | ImPlotFlags_NoFrame | ImPlotFlags_NoChild | ImPlotFlags_NoInputs))
    {
        ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
        ImPlot::SetupAxesLimits(0, time_domain_out.w, -1.0 * wave_scale, 1.0 * wave_scale, ImGuiCond_Always);
        ImPlot::PlotLine("##TimeDomainOut", (float *)time_domain_out.data, time_domain_out.w);
        ImPlot::EndPlot();
    }
    if (ImGui::IsItemHovered())
    {
        if (io.MouseWheel < -FLT_EPSILON) { wave_scale *= 0.9f; if (wave_scale < 0.1f) wave_scale = 0.1f; }
        if (io.MouseWheel >  FLT_EPSILON) { wave_scale *= 1.1f; if (wave_scale > 4.0f) wave_scale = 4.0f; }
        if (io.MouseWheelH < -FLT_EPSILON) { x_scale *= 0.9f; if (x_scale < 1.0f) x_scale = 1.0f; }
        if (io.MouseWheelH >  FLT_EPSILON) { x_scale *= 1.1f; if (x_scale > 16.0f) x_scale = 16.0f; }
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) { wave_scale = 1.0; x_scale = 1.0; }
    }

    ImGui::PopStyleColor();
    ImGui::EndChild();
}

void ShowImSTFTDemoWindow()
{
#define STFT_DATA_LENGTH (512*128)
#define STFT_SUB_LENGTH (STFT_DATA_LENGTH / 4)
    ImGuiIO &io = ImGui::GetIO();
    static float wave_scale = 1.0f;
    static float fft_scale = 16.0f;
    static float x_scale = 1.0f;
    const float rate = 44100.f;
    ImMat time_domain;
    time_domain.create_type(STFT_DATA_LENGTH, IM_DT_FLOAT32);
    static int signal_type = 0;
    static const char * signal_item[] = { "Sine", "Sweep", "Inverse Sweep", "Segmentation", "Inverse Segmentation", "High-Frequency Disturbing" };
    static int fft_type = 0;
    static const char * fft_item[] = { "FFT", "STFT" };
    static ImGui::ImMat spectrogram;
    static ImTextureID spectrogram_texture = nullptr;
    ImGui::PushItemWidth(200);
    if (ImGui::Combo("Signal Type", &signal_type, signal_item, IM_ARRAYSIZE(signal_item)))
    {
        spectrogram.release();
    }
    ImGui::SameLine();
    if (ImGui::Combo("Spectrogram Type", &fft_type, fft_item, IM_ARRAYSIZE(fft_item)))
    {
        spectrogram.release();
    }
    ImGui::PopItemWidth();
    // init time domain data
    switch (signal_type)
    {
        case 0: // Sine
        {
            for (int i = 0; i < STFT_DATA_LENGTH; i++)
            {
                float t = (float)i / rate;
                time_domain.at<float>(i) = 0.5 * sin(2 * M_PI * 1000 * t);
            }
        }
        break;
        case 1: // Sweep
        {
            float f = 0.f;
            float fstep = 10000.f / (float)STFT_DATA_LENGTH;
            for (int i = 0; i < STFT_DATA_LENGTH; i++)
            {
                float t = (float)i / rate;
                time_domain.at<float>(i) = 0.5 * sin(2 * M_PI * f * t);
                f += fstep;
            }
        }
        break;
        case 2: // Inverse Sweep
        {
            float f = 0.f;
            float step = 10000.f / (float)STFT_DATA_LENGTH;
            for (int i = 0; i < STFT_DATA_LENGTH; i++)
            {
                float t = (float)i / rate;
                time_domain.at<float>(STFT_DATA_LENGTH - i - 1) = 0.5 * sin(2 * M_PI * f * t);
                f += step;
            }
        }
        break;
        case 3: // Segmentation
        {
            for (int i = 0; i < STFT_SUB_LENGTH; i++)
            {
                float t = (float)i / rate;
                time_domain.at<float>(i + STFT_SUB_LENGTH * 0) = 0.1 * sin(2 * M_PI * 1000 * t);
                time_domain.at<float>(i + STFT_SUB_LENGTH * 1) = 0.2 * sin(2 * M_PI * 2000 * t);
                time_domain.at<float>(i + STFT_SUB_LENGTH * 2) = 0.3 * sin(2 * M_PI * 3000 * t);
                time_domain.at<float>(i + STFT_SUB_LENGTH * 3) = 0.4 * sin(2 * M_PI * 4000 * t);
            }
        }
        break;
        case 4: // Inverse Segmentation
        {
            for (int i = 0; i < STFT_SUB_LENGTH; i++)
            {
                float t = (float)i / rate;
                time_domain.at<float>(i + STFT_SUB_LENGTH * 0) = 0.4 * sin(2 * M_PI * 4000 * t);
                time_domain.at<float>(i + STFT_SUB_LENGTH * 1) = 0.3 * sin(2 * M_PI * 3000 * t);
                time_domain.at<float>(i + STFT_SUB_LENGTH * 2) = 0.2 * sin(2 * M_PI * 2000 * t);
                time_domain.at<float>(i + STFT_SUB_LENGTH * 3) = 0.1 * sin(2 * M_PI * 1000 * t);
            }
        }
        break;
        case 5: // High-Frequency Disturbing
        {
            for (int i = 0; i < STFT_DATA_LENGTH; i++)
            {
                float t = (float)i / rate;
                if (i > STFT_DATA_LENGTH / 2 - 40 && i < STFT_DATA_LENGTH / 2 + 40)
                {
                    time_domain.at<float>(i) = 0.2 * sin(2 * M_PI * 40 * t) + 0.4 * sin(2 * M_PI * 80 * t) + 0.3 * sin(2 * M_PI * 800 * t);
                }
                else
                {
                    time_domain.at<float>(i) = 0.2 * sin(2 * M_PI * 40 * t) + 0.4 * sin(2 * M_PI * 80 * t);
                }
            }
        }
        default: break;
    }

    // spectrogram
    if (spectrogram.empty())
    {
        if (fft_type == 0)
            ImGui::ImSpectrogram(time_domain, spectrogram, 2048);
        else
            ImGui::ImSpectrogram(time_domain, spectrogram, 512, true, 128);
        if (spectrogram_texture) { ImGui::ImDestroyTexture(spectrogram_texture); spectrogram_texture = nullptr; }
        ImGui::ImMatToTexture(spectrogram, spectrogram_texture);
    }
    
    // init STFT
    const int window = STFT_DATA_LENGTH / 4;
    const int hope = window / 4;
    const int overlap = window - hope;
    ImGui::ImSTFT process(window, hope);
    ImGui::ImMat short_time_domain, padding_data;
    short_time_domain.create_type(window + 2, IM_DT_FLOAT32);
    padding_data.create_type(window, IM_DT_FLOAT32);
    ImGui::ImMat short_time_domain_out;
    short_time_domain_out.create_type(STFT_DATA_LENGTH, IM_DT_FLOAT32);
    ImGui::ImMat short_time_amplitude;
    short_time_amplitude.create_type((window >> 1) + 1, IM_DT_FLOAT32);
    int length = 0;
    // stft/istft/analyzer with slipping window
    while (length < STFT_DATA_LENGTH + overlap)
    {
        ImMat amplitude;
        amplitude.create_like(short_time_amplitude);
        float * in_data, *out_data;
        if (length < STFT_DATA_LENGTH)
            in_data = (float *)time_domain.data + length;
        else
            in_data = (float *)padding_data.data;
        process.stft(in_data, (float *)short_time_domain.data);

        // do analyzer
        ImGui::ImReComposeAmplitude((float *)short_time_domain.data, (float *)amplitude.data, window);
        for (int i = 0; i < amplitude.w; i++) short_time_amplitude.at<float>(i) += amplitude.at<float>(i);
        // analyzer end

        if (length >= overlap)
            out_data = (float *)short_time_domain_out.data + length - overlap;
        else
            out_data = (float *)padding_data.data;
        process.istft((float *)short_time_domain.data, out_data);
        length += hope;
    }

    ImGui::BeginChild("STFT Result");
    // draw result
    ImVec2 channel_view_size = ImVec2(1024 * x_scale, 128);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 1.f));

    // draw time domain
    if (ImPlot::BeginPlot("##time_domain", channel_view_size, ImPlotFlags_CanvasOnly | ImPlotFlags_NoFrame | ImPlotFlags_NoChild | ImPlotFlags_NoInputs))
    {
        ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
        ImPlot::SetupAxesLimits(0, time_domain.w, -1.0 * wave_scale, 1.0 * wave_scale, ImGuiCond_Always);
        ImPlot::PlotLine("##TimeDomain", (float *)time_domain.data, time_domain.w);
        ImPlot::EndPlot();
    }
    if (ImGui::IsItemHovered())
    {
        if (io.MouseWheel < -FLT_EPSILON) { wave_scale *= 0.9f; if (wave_scale < 0.1f) wave_scale = 0.1f; }
        if (io.MouseWheel >  FLT_EPSILON) { wave_scale *= 1.1f; if (wave_scale > 4.0f) wave_scale = 4.0f; }
        if (io.MouseWheelH < -FLT_EPSILON) { x_scale *= 0.9f; if (x_scale < 1.0f) x_scale = 1.0f; }
        if (io.MouseWheelH >  FLT_EPSILON) { x_scale *= 1.1f; if (x_scale > 16.0f) x_scale = 16.0f; }
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) { wave_scale = 1.0; x_scale = 1.0; }
    }

    // draw spectrogram
    if (spectrogram_texture)
    {
        ImGui::Image(spectrogram_texture, channel_view_size);
    }

    // draw stft domain (amplitude)
    if (ImPlot::BeginPlot("##stft_domain", channel_view_size, ImPlotFlags_CanvasOnly | ImPlotFlags_NoFrame | ImPlotFlags_NoChild | ImPlotFlags_NoInputs))
    {
        ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
        ImPlot::SetupAxesLimits(0, short_time_amplitude.w, 0.0 * fft_scale, 1.0 * fft_scale, ImGuiCond_Always);
        ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.75f);
        ImPlot::PlotShaded("##STFTDomainAMP", (float *)short_time_amplitude, short_time_amplitude.w);
        ImPlot::PopStyleVar();
        ImPlot::PlotLine("##STFTDomain", (float *)short_time_amplitude.data, short_time_amplitude.w);
        ImPlot::EndPlot();
    }
    if (ImGui::IsItemHovered())
    {
        if (io.MouseWheel < -FLT_EPSILON) { fft_scale *= 0.9f; if (fft_scale < 0.1f) fft_scale = 0.1f; }
        if (io.MouseWheel >  FLT_EPSILON) { fft_scale *= 1.1f; if (fft_scale > 32.0f) fft_scale = 32.0f; }
        if (io.MouseWheelH < -FLT_EPSILON) { x_scale *= 0.9f; if (x_scale < 1.0f) x_scale = 1.0f; }
        if (io.MouseWheelH >  FLT_EPSILON) { x_scale *= 1.1f; if (x_scale > 16.0f) x_scale = 16.0f; }
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) { fft_scale = 1.0; x_scale = 1.0; }
    }

    // draw time domain out(istft)
    if (ImPlot::BeginPlot("##time_domain_out", channel_view_size, ImPlotFlags_CanvasOnly | ImPlotFlags_NoFrame | ImPlotFlags_NoChild | ImPlotFlags_NoInputs))
    {
        ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
        ImPlot::SetupAxesLimits(0, short_time_domain_out.w, -1.0 * wave_scale, 1.0 * wave_scale, ImGuiCond_Always);
        ImPlot::PlotLine("##TimeDomainOut", (float *)short_time_domain_out.data, short_time_domain_out.w);
        ImPlot::EndPlot();
    }
    if (ImGui::IsItemHovered())
    {
        if (io.MouseWheel < -FLT_EPSILON) { wave_scale *= 0.9f; if (wave_scale < 0.1f) wave_scale = 0.1f; }
        if (io.MouseWheel >  FLT_EPSILON) { wave_scale *= 1.1f; if (wave_scale > 4.0f) wave_scale = 4.0f; }
        if (io.MouseWheelH < -FLT_EPSILON) { x_scale *= 0.9f; if (x_scale < 1.0f) x_scale = 1.0f; }
        if (io.MouseWheelH >  FLT_EPSILON) { x_scale *= 1.1f; if (x_scale > 16.0f) x_scale = 16.0f; }
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) { wave_scale = 1.0; x_scale = 1.0; }
    }
    ImGui::PopStyleColor();
    ImGui::EndChild();
}

} // namespace ImGui
