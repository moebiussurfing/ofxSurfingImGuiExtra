#include "myAddon.h"

//--------------------------------------------------------------
void myAddon::setup(string _name, int _val, int _x, int _y) {
	name = _name;
	val = _val;
	x = _x;
	y = _y;

	ui.setup(IM_GUI_MODE_INSTANTIATED);
	//ui.setup(IM_GUI_MODE_NOT_INSTANTIATED);

	value1 = ofRandom(1);
	value2 = ofRandom(1);
}

//--------------------------------------------------------------
void myAddon::draw()
{
	ui.Begin();
	drawWindow(name.c_str(), val, x, y);
	ui.End();
}

//--------------------------------------------------------------
void myAddon::drawWindow(string _title, int& _value, int _x, int _y, ImGuiWindowFlags _flags)
{
	//ImGuiWindowFlags _flags = ImGuiWindowFlags_None;

	name = _title;
	ImGuiCond cond = ImGuiCond_FirstUseEver;

	ImGui::SetNextWindowSize(ImVec2(200, 200), cond);
	ImGui::SetNextWindowPos(ImVec2(_x + ofGetWindowPositionX(), _y + ofGetWindowPositionY()), cond);

	if (ui.bAutoResize) _flags |= ImGuiWindowFlags_AlwaysAutoResize;

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 255, 0, 128)); // This styles the special windows

	ui.BeginWindow(name.c_str(), NULL, _flags);
	{
		ImGui::Text("ui");
		ImGui::SliderFloat("value1", &value1, 0, 1);
		ImGui::SliderFloat("value2", &value2, 0, 1);

		ui.drawAdvanced();
	}
	ui.EndWindow();

	ImGui::PopStyleColor(1);
}

//--------------------------------------------------------------
void myAddon::exit() {
}