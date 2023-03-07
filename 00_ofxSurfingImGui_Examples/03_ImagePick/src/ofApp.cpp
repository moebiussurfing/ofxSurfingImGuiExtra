#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowPosition(1920, 25);

	path = path1;
	initTexture();

	event = index.newListener([&](int& value)
		{
			switch (value)
			{
			case 0: path = path1; break;
			case 1: path = path2; break;
			case 2: path = path3; break;
			}

	ofLogNotice() << "path: " << path;

	initTexture();

		});
}

//--------------------------------------------------------------
void ofApp::initTexture()
{
	ofLogNotice() << "initTexture()";

	bool bLoaded = image.load(path);
	if (bLoaded) ofLogNotice() << "Loaded image on path: " << path;
	else ofLogError() << "Not found image on path: " << path;

	// push
	bool b = ofGetUsingArbTex();
	ofDisableArbTex();

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
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			float _w100 = ui.getWidgetsWidth(1);
			float _spcx = ui.getWidgetsSpacingX();
			float _hb = ui.getWidgetsHeightUnit();

			ui.AddAutoResizeToggle();
			ui.AddMinimizerToggle();
			ui.AddDebugToggle();
			ui.AddLabelBig("Shift click to imgInspect");
			ui.AddSpacingBigSeparated();

			ui.Add(index);
			ui.AddLabelBig(path);
			ui.AddSpacing();

			static bool bEnable = false;

			//--

			float w = texture.getWidth();
			float h = texture.getHeight();
			float ratio = h / w;

			float ww;
			float hh;

			ww = _w100;
			hh = ww * ratio;

			if (ui.AddButton("Reset"))
			{
				ww = image.getWidth();
				hh = image.getHeight();
			}

			if (ui.AddToggle("Show", bEnable))
			{
			}

			//pixels.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR_ALPHA);
			//pixels.setImageType(OF_IMAGE_COLOR_ALPHA);

			//TODO:
			// raw data

			texture.readToPixels(pixels);

			auto nBits = pixels.getBitsPerPixel();//24 for RGB, 32 for RGBA

			const unsigned char* data = pixels.getData();

			if (ui.isDebug()) {
				//size_t dsz = sizeof(((uint32_t*)data)) / sizeof(((uint32_t*)data)[0]);
				size_t dsz = sizeof(((unsigned char*)data)) / sizeof(((unsigned char*)data)[0]);
				ui.AddLabel("Data size: " + ofToString(dsz));
				ui.AddLabel("nBits: " + ofToString(nBits) + " bits");
				ui.AddSpacing();

				ui.BeginColumns(2, "##cols", true);
				ui.AddLabelBig("FILE:");
				ui.AddLabel(ofToString(w) + "," + ofToString(h));
				ui.NextColumn();
				ui.AddLabelBig("DRAWN:");
				ui.AddLabel(ofToString(ww, 0) + "," + ofToString(hh, 0));
				ui.EndColumns();
			}

			ui.AddSpacingBigSeparated();

			//--

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

			ImGuiIO& io = ImGui::GetIO();
			ImRect rc = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
			ImVec2 mouseUVCoord = (io.MousePos - rc.Min) / rc.GetSize();
			mouseUVCoord.y = 1.f - mouseUVCoord.y;

			ImVec2 displayedTextureSize = ImVec2(ww, hh);

			if (io.KeyShift && io.MouseDown[1])
			{
				static bool bEnable_ = !bEnable;
				if (bEnable != bEnable_) {
					bEnable_ = bEnable;
					bEnable = !bEnable;
				}
			}

			if (bEnable && mouseUVCoord.x >= 0.f && mouseUVCoord.y >= 0.f)
			{
				//ui.AddTooltip("Hello");

				ImageInspect::inspect(w, h, data, mouseUVCoord, displayedTextureSize);

				//--

				if (ui.isMaximized())
				{
					ui.AddSpacingBigSeparated();

					ImVec2 sz = ImVec2(image.getWidth(), image.getHeight());

					// 2. Texture
					ImGui::Image((ImTextureID)(uintptr_t)textureID, sz);

					// 3. Pixels
					//ImGui::Image(GetImTextureID(pixelsButtonID), sz);
				}
			}

			ui.EndWindow();
		}
		ui.End();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bGui = !bGui;
}
