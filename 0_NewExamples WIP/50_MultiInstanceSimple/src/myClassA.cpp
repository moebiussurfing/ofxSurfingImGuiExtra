#include "myClassA.h"

//--------------------------------------------------------------
myClassA::myClassA() 
{
	//setup();
}

//--------------------------------------------------------------
myClassA::~myClassA()
{
	//#ifdef SURFING_USE_REFERENCED
	//if (ui != nullptr)
	//{
	//	// Set to nullptr after deleting to avoid double deletes
	//	ui = nullptr;
	//	delete ui;
	//}
	//#endif
}

//#ifdef SURFING_USE_REFERENCED2
////--------------------------------------------------------------
//void myClassA::setUiPtr(std::unique_ptr<ofxSurfingGui> _ui) 
// {
//	ui = _ui;
//	ui = std::move(_ui);
//}
//#endif

#ifdef SURFING_USE_REFERENCED
//--------------------------------------------------------------
void myClassA::setUiPtr(ofxSurfingGui* _ui)
{
	ui = _ui;
}
#endif

//--------------------------------------------------------------
void myClassA::setup()
{
	parameters.setName("paramsGroupA");
	parameters.add(shapeType2.set("shapeType2", 0, -50, 50));
	parameters.add(size2.set("size2", 100, 0, 100));
	parameters.add(amount2.set("amount2", 10, 0, 25));

	//--

#ifdef SURFING_USE_INSTANCE2
#if 0
	// Can be omitted in many scenarios..
	ui_.setup();
	ui_.startup();
#endif
#endif

#ifdef SURFING_USE_REFERENCED2
	//ui = std::make_unique<ofxSurfingGui>();
	//ui = new ofxSurfingGui();
	//ui->setup();
#endif
}

#ifdef SURFING_USE_INSTANCE2
//--------------------------------------------------------------
void myClassA::drawImGui()
{
	if (!bGui) return;

	ui_.Begin();
	{
		if (ui_.BeginWindow(bGui))
		{
			ui_.AddGroup(parameters);

			ui_.EndWindow();
		}
	}
	ui_.End();
}
#endif

#ifdef SURFING_USE_REFERENCED
//--------------------------------------------------------------
void myClassA::drawImGuiWidgets()
{
	ui->AddGroup(parameters);
}

//--------------------------------------------------------------
void myClassA::drawImGuiWindow()
{
	if (!bGui) return;

	if (ui->BeginWindow(bGui))
	{
		ui->AddGroup(parameters);

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
#endif