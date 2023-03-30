#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofLogNotice("ofApp") << "setup()";

	ofxSurfingHelpers::SurfSetMyMonitor(1);

	ui.setName("ofApp");
	ui.setup();

	eventIndex = index.newListener([&](int& value)
		{
			switch (value)
			{
			case 0: path = pathImages + "/" + path1; break;
			case 1: path = pathImages + "/" + path2; break;
			case 2: path = pathImages + "/" + path3; break;
			}
	ofLogNotice("ofApp") << "path: " << path;

	loadImage(path);

		});

	g.add(bGui);
	g.add(bDrawImg);
	g.add(index);

	//--

	imageInspect.setUiPtr(&ui);
	imageInspect.setup();
	imageInspect.colorPtr.makeReferenceTo(colorPtr);//link color to be auto updated!

	//--

	if (!ofxSurfingHelpers::load(g)) {
		index = 0;
	}
}

//--------------------------------------------------------------
void ofApp::loadImage(string _path)
{
	if (path != _path) path = _path;

	ofLogNotice("ofApp") << "loadImage";

	bLoaded = imageFloat.load(path);
	if (bLoaded) ofLogNotice("ofApp") << "Loaded image on path: " << path;
	else ofLogError() << "Not found image on path: " << path;

	imageInspect.loadTexture(path);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(colorPtr.get());

	if (bDrawImg && imageFloat.isAllocated())
	{
		if (1) // maintain ratio
		{
			ofRectangle rr(0, 0, imageFloat.getWidth(), imageFloat.getHeight());
			rr.scaleTo(ofGetCurrentViewport(), OF_SCALEMODE_FIT);
			imageFloat.draw(rr.x, rr.y, rr.width, rr.height);
		}
		else // expand
		{
			int p = 50;
			imageFloat.draw(p, p, ofGetWidth() - p * 2, ofGetHeight() - p * 2);
		}
	}

	//--

	drawImGui();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	if (!bGui) return;

	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.Add(index);
			ui.AddLabel(path);
			ui.AddSpacing();

			if (bLoaded)
			{
				ui.Add(bDrawImg, OFX_IM_TOGGLE_ROUNDED);
				ui.AddSpacingBigSeparated();

				ui.Add(imageInspect.bGui, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(colorPtr, OFX_IM_COLOR_BOX_FULL_WIDTH_BIG);
			}

			ui.EndWindow();
		}

		//--

		if (imageInspect.bGui) imageInspect.drawImGui();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bGui = !bGui;
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ofLogNotice("ofApp") << "exit()";
	ofxSurfingHelpers::save(g);
}
