#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::exit()
{
	ofLogNotice() << "exit()";

	ofxSurfingHelpers::save(g);
}

//--------------------------------------------------------------
void ofApp::setup()
{
	ofLogNotice() << "setup()";

	ofSetWindowPosition(1920, 25);

	ui.setup();
	ui.bNotifier = false;
	ui.bDebug = true;

	//path = path1;
	//loadTexture();

	event = index.newListener([&](int& value)
		{
			switch (value)
			{
			case 0: path = pathImages + "/" + path1; break;
			case 1: path = pathImages + "/" + path2; break;
			case 2: path = pathImages + "/" + path3; break;
			}

	ofLogNotice() << "path: " << path;

	loadTexture();

		});

	//startup
	//index = 0;

	g.add(bGui);
	g.add(bDrawImg);
	g.add(bDrawImg2);
	g.add(index);
	ofxSurfingHelpers::load(g);

	// inspector
	params_ImageInspector.add(bEnableInspector);
	params_ImageInspector.add(bEnablePicker);
	params_ImageInspector.add(zoomSize);
	params_ImageInspector.add(zoomRectangleWidth);
}

//--------------------------------------------------------------
void ofApp::loadTexture()
{
	ofLogNotice() << "loadTexture()";

	bLoaded = image.load(path);
	if (bLoaded) ofLogNotice() << "Loaded image on path: " << path;
	else {
		ofLogError() << "Not found image on path: " << path;
		return;
	}

	imageFloat.load(path);

	//-

	// push
	bool b = ofGetUsingArbTex();
	ofDisableArbTex();

	//ofImageLoadSettings s = ;

	ofLoadImage(texture, path);

	float w = texture.getWidth();
	float h = texture.getHeight();
	fbo.allocate(w, h);

	fbo.createAndAttachTexture(GL_RGB, 0); //position
	fbo.createAndAttachTexture(GL_RGBA32F, 1); //velocity
	fbo.createAndAttachRenderbuffer(GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT);
	fbo.checkStatus();

	fbo.begin();
	ofClear(0);
	fbo.end();

	// pop/restore
	if (b) ofEnableArbTex();

	// draw texture once
	fbo.begin();
	ofClear(0, 0, 0, 0);
	texture.draw(0, 0);
	fbo.end();

	//--

	// "preload" on ui
	textureID = ui.getGuiPtr()->loadTexture(texture, path);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(cBg);

	if (bDrawImg && imageFloat.isAllocated())
	{
		if (1) {//maintain ration
			ofRectangle rr(0, 0, imageFloat.getWidth(), imageFloat.getHeight());
			rr.scaleTo(ofGetCurrentViewport(), OF_SCALEMODE_FIT);
			imageFloat.draw(rr.x, rr.y, rr.width, rr.height);
		}
		else {//expand
			int p = 50;
			imageFloat.draw(p, p, ofGetWidth() - p * 2, ofGetHeight() - p * 2);
		}
	}

	//-

	drawImGui();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	ui.Begin();

	{
		//if (bGui) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;

		if (ui.BeginWindow(bGui))
		{
			bool bDebug = ui.bDebug;

			//--

			float _w100 = ui.getWidgetsWidth(1);
			float _spcx = ui.getWidgetsSpacingX();
			float _hb = ui.getWidgetsHeightUnit();

			//--

			float wsrc = texture.getWidth();
			float hsrc = texture.getHeight();
			float ratio = hsrc / wsrc;

			float ww;
			float hh;

			ww = _w100;
			hh = ww * ratio;

			ui.AddMinimizerToggle();
			ui.AddDebugToggle();

			ui.AddSpacing();

			if (ui.isMaximized())
			{
				ui.AddNotifierToggle();
				ui.AddLogToggle();
				ui.AddAutoResizeToggle();
				ui.AddSpacingBigSeparated();
				ui.AddSpacing();

				ui.Add(index);
				ui.AddLabelBig(path);
				ui.AddSpacing();

				if (bLoaded) {
					ui.Add(bDrawImg, OFX_IM_TOGGLE_ROUNDED);
					ui.Add(bDrawImg2, OFX_IM_TOGGLE_ROUNDED);
				}

				ui.AddSpacingBigSeparated();
			}

			//TODO:
			// raw data
			if (bLoaded)
			{
				texture.readToPixels(pixels);
			}
			const unsigned char* data = pixels.getData();
			auto nBits = pixels.getBitsPerPixel();

			if (bLoaded)
			{
				// mode
				//pixels.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR_ALPHA);
				//pixels.setImageType(OF_IMAGE_COLOR_ALPHA);

				if (ui.isDebug() && ui.isMaximized())
				{
					//size_t dsz = sizeof(((unsigned char*)data)) / sizeof(((unsigned char*)data)[0]);
					//ui.AddLabel("nData: " + ofToString(dsz));
					ui.AddLabel("nBits: " + ofToString(nBits));
					ui.AddSpacing();
					ui.BeginColumns(2, "##cols", true);
					ui.AddLabelBig("FILE:");
					ui.AddLabel(ofToString(wsrc) + "," + ofToString(hsrc));
					ui.AddLabel("nPixels: " + ofToString(wsrc * hsrc));
					ui.NextColumn();
					ui.AddLabelBig("DRAWN:");
					ui.AddLabel(ofToString(ww, 0) + "," + ofToString(hh, 0));
					ui.AddLabel("nPixels: " + ofToString(ww * hh));
					ui.EndColumns();
					ui.AddSpacingBigSeparated();
					
					ui.AddLabelBig("MOUSE App:");
					ui.AddLabel("x,y: " + ofToString(ofGetMouseX()) + "," + ofToString(ofGetMouseY()));

					auto pm = ImGui::GetMousePos();
					auto pw = ImGui::GetWindowPos();
					ImVec2 p = pm - pw;
					ui.AddLabelBig("MOUSE Window:");
					ofRectangle r(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
					bool bInside = r.inside(ofGetMouseX(), ofGetMouseY());
					string s = " ";
					if (bInside)
					{
						s = "x,y: " + ofToString(p.x) + "," + ofToString(p.y);
					}
					ui.AddLabel(s);

					ui.AddSpacingBigSeparated();
				}
			}

			//--

			if (bLoaded)
			{
				//// 1. Fbo
				//if (ImGui::ImageButton(
				//	(ImTextureID)(uintptr_t)fbo.getTexture(0).getTextureData().textureID,
				//	ImVec2(ww, hh)))
				//{
				//	ofLogNotice() << "Image clicked";
				//}

				// 2. Texture
				ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(ww, hh));

				//--
		
				// Catch from previous widget
				ImGuiIO& io = ImGui::GetIO();
				bool bOver = ImGui::IsItemHovered();
				bool bMouseLeft = io.MouseClicked[0];
				bool bMouseRight = io.MouseClicked[1];
				bool bShift = io.KeyShift;

				ImRect rc = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
				ImVec2 mouseUVCoord_ = (io.MousePos - rc.Min) / rc.GetSize();
				//mouseUVCoord_.y = 1.f - mouseUVCoord_.y; // flip y

				// clamp
				ImVec2 mouseUVCoord = ImVec2(
					ofClamp(mouseUVCoord_.x, 0, 1),
					ofClamp(mouseUVCoord_.y, 0, 1));

				ImVec2 displayedTextureSize_ = ImVec2(ww, hh);
				ImVec2 displayedTextureSize = ImVec2(
					ofClamp(displayedTextureSize_.x, 0, wsrc),
					ofClamp(displayedTextureSize_.y, 0, hsrc));

				//--

				bool b24bits = (nBits == 24);

				//--

				if (bOver)
				{
					if (bEnableInspector) {
						ImageInspect::inspect(wsrc, hsrc, data, mouseUVCoord, displayedTextureSize, zoomSize, zoomRectangleWidth, b24bits, bDebug, bDebugAdvanced, &c);
					}
					if (bEnablePicker && bMouseLeft) {
						c = ImageInspect::getColor(wsrc, hsrc, data, mouseUVCoord, displayedTextureSize, b24bits, &c);
						ofLogNotice("ofApp") << "Click color: " << c;
						cBg.set(c);
					}
				}

				if (bEnableInspector && bOver && bMouseLeft)
				{
					ofLogNotice("ofApp") << "Click color: " << c;
					cBg.set(c);
				}

				//--

				ui.AddSpacing();
				ui.AddSpacing();
				ui.Add(bEnableInspector, OFX_IM_TOGGLE_BIG, 2, true);
				ui.Add(bEnablePicker, OFX_IM_TOGGLE_BIG, 2);
				ui.AddSpacing();

				//--

				if (bEnableInspector) {
					//TODO: make ofParams
					ui.Add(zoomSize);
					ui.Add(zoomRectangleWidth);

					if (ImGui::Button("Mini")) {
						zoomSize = 1;
						zoomRectangleWidth = 60;
					}
					ImGui::SameLine();
					if (ImGui::Button("Small")) {
						zoomSize = 50;
						zoomRectangleWidth = 100;
					}
					ImGui::SameLine();
					if (ImGui::Button("Medium")) {
						zoomSize = 3;
						zoomRectangleWidth = 160;
					}
					ImGui::SameLine();
					if (ImGui::Button("Big")) {
						zoomSize = 30;
						zoomRectangleWidth = 500;
					}
					ImGui::SameLine();
					if (ImGui::Button("Huge")) {
						zoomSize = 50;
						zoomRectangleWidth = 1000;
					}

					ui.Add(bDebugAdvanced, OFX_IM_TOGGLE_ROUNDED_MINI);
				}

				/*
				if (ui.AddButton("Reset Original"))
				{
					ww = image.getWidth();
					hh = image.getHeight();
				}
				*/
			}

			ui.EndWindow();
		}

		//--

		if (bLoaded)
		{
			if (ui.BeginWindow(bDrawImg2, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImVec2 sz = ImVec2(image.getWidth(), image.getHeight());

				// 2. Texture
				ImGui::Image((ImTextureID)(uintptr_t)textureID, sz);

				// 3. Pixels
				//ImGui::Image(GetImTextureID(pixelsButtonID), sz);

				ui.EndWindow();
			}
		}
	}

	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bGui = !bGui;
}
