#include "myClassA.h"

//--------------------------------------------------------------
myClassA::myClassA() {
	setup();
}

//--------------------------------------------------------------
myClassA::~myClassA() {
	if (ui != nullptr)
	{
		// Set to nullptr after deleting to avoid double deletes
		ui = nullptr;

		delete ui;
	}
}

////--------------------------------------------------------------
//void myClassA::setUiPtr(std::unique_ptr<ofxSurfingGui> _ui) {
//	ui = _ui;
//	ui = std::move(_ui);
//}

//--------------------------------------------------------------
void myClassA::setUiPtr(ofxSurfingGui* _ui) {
	ui = _ui;
}

//--------------------------------------------------------------
void myClassA::setup()
{
	// params
	params2.setName("paramsGroupA");
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));

	//--

	//ui = std::make_unique<ofxSurfingGui>();
	//ui = new ofxSurfingGui();
	//ui->setup();
}

//--------------------------------------------------------------
void myClassA::drawImGuiWidgets()
{
	ui->AddGroup(params2);
}

//--------------------------------------------------------------
void myClassA::drawImGuiWindow()
{
	if (!bGui) return;

	if (ui->BeginWindow(bGui))
	{
		ui->AddGroup(params2);

		ui->EndWindow();
	}
}

//--------------------------------------------------------------
void myClassA::drawImGui()
{
	if (!bGui) return;

	ui->Begin();
	{
		drawImGuiWindow();
	}
	ui->End();
}