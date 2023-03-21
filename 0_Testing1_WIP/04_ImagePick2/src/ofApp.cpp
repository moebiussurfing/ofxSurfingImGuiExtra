#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//ui.setup();
	//ui.startup();

	initTexture();
}

//--------------------------------------------------------------
void ofApp::initTexture()
{
	ofLogNotice() << "initTexture()";

	image.load(path1);

	ofLogNotice() << "image path1: " << path1;

	// push
	bool b = ofGetUsingArbTex();
	ofDisableArbTex();

	//if (image.isAllocated()) tex = image.getTexture();
	//else ofLoadImage(tex, path);

	ofLoadImage(textureSource, path1);
	//ofLoadImage(tex, path1);

	//float w = tex.getWidth();
	//float h = tex.getHeight();
	float w = textureSource.getWidth();
	float h = textureSource.getHeight();

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
	textureSource.draw(0, 0);
	//tex.draw(0, 0);
	fbo.end();

	//--

	textureSourceID = ui.getGuiPtr()->loadTexture(textureSource, path1);

	buffer.allocate(textureSource.getWidth() * textureSource.getHeight() * 3, GL_DYNAMIC_READ);


	ImGuiTexInspect::ImplOpenGL3_Init(); // Or DirectX 11 equivalent (check your chosen backend header file)
	ImGuiTexInspect::Init();
	ImGuiTexInspect::CreateContext();

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
			float hb = ui.getWidgetsHeightUnit();

			ui.AddAutoResizeToggle();
			ui.AddMinimizerToggle();
			ui.AddLabelBig("Shift click to imgInspect");
			ui.AddSpacingBigSeparated();


			//ui.AddLabelBig("HELLO WORLD");
			//ui.Add(bEnable, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			//ui.Add(speed, OFX_IM_HSLIDER);
			//ui.AddSpacingSeparated();
			//ui.AddGroup(params, SurfingGuiGroupStyle_Collapsed);

			//--

			//float w = tex.getWidth();
			//float h = tex.getHeight();
			float w = textureSource.getWidth();
			float h = textureSource.getHeight();

			float ratio = h / w;

			float ww;
			float hh;
			float offset = 0;

			ww = _w100 - (2 * _spcx) - offset;
			hh = ww * ratio;

			//--


			// copy the fbo texture to a buffer
			fbo.getTexture().copyTo(buffer);


			//// 1. Fbo
			//if (ImGui::ImageButton(
			//	(ImTextureID)(uintptr_t)fbo.getTexture(0).getTextureData().textureID,
			//	ImVec2(ww, hh)))
			//{
			//	ofLogNotice() << "Image clicked";
			//}


			// 2. Texture
			ImGui::Image((ImTextureID)(uintptr_t)textureSourceID, ImVec2(ww, hh));

			//--

			ImTextureID textureHandle = (ImTextureID)(uintptr_t)textureSourceID;
			ImVec2 textureSize = ImVec2(ww, hh);

			ImGui::Begin("Simple Texture Inspector");
			ImGuiTexInspect::BeginInspectorPanel("Inspector", textureHandle, textureSize);
			ImGuiTexInspect::EndInspectorPanel();
			ImGui::End();



			//--

			ImGuiIO& io = ImGui::GetIO();
			ImRect rc = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
			ImVec2 mouseUVCoord = (io.MousePos - rc.Min) / rc.GetSize();
			mouseUVCoord.y = 1.f - mouseUVCoord.y;

			ImVec2 displayedTextureSize = ImVec2(ww, hh);

			if (io.KeyShift && io.MouseDown[0] && mouseUVCoord.x >= 0.f && mouseUVCoord.y >= 0.f)
			{
				ui.AddTooltip("Hello");

				//int width = ww;
				//int height = hh;

				//int w = tex.getWidth();
				//int h = tex.getHeight();

				int w = textureSource.getWidth();
				int h = textureSource.getHeight();

				//ofBuffer b = buffer;
				//const unsigned char* data = b;

				//ImageInspect::inspect(w, h, (const unsigned char*)buffer, mouseUVCoord, displayedTextureSize);



				/*
				// Assume you have an ofTexture object named tex
				// Bind the texture so that we can access its pixel data
				tex.bind();

				// Create an ofPixels object and read the texture data into it
				ofPixels pixels;
				tex.readToPixels(pixels);

				// Get a pointer to the pixel data
				const unsigned char* texPixels = pixels.getData();

				// Create an ofBuffer object and copy the pixel data into it
				ofBuffer buffer;
				auto sz = tex.getWidth() * tex.getHeight() * 8;
				//auto sz = tex.getWidth() * tex.getHeight() * ofGetBytesPerPixel(tex.getTextureData().glInternalFormat);
				buffer.set(texPixels, sz);

				// Get a pointer to the buffer's data as a const unsigned char*
				const unsigned char* data = buffer.getData();


				// Unbind the texture when we're done
				tex.unbind();

				const unsigned char* data = (const unsigned char*)tex.getTextureData();
				*/



				//ofBufferObject bufferCopy;
				//fbo.getTexture().copyTo(bufferCopy);
				//ImageInspect::inspect(w, h, (const unsigned char*)bufferCopy, mouseUVCoord, displayedTextureSize);




				//ofBuffer buffer(tex.getTextureData(), 1024);


				//ofBufferObject buffer_Graph;

				//buffer_Graph.allocate();
				//buffer_Graph.bind(GL_SAMPLER_2D_RECT);
				//buffer_Graph.setData(tex.getTextureData().textureID(), GL_DYNAMIC_DRAW);
				//tex_Graph.allocateAsBufferTexture(buffer_Graph, GL_RGBA32F);

				//textureSource.bind();
				//const unsigned char* data = tex.readToPixels();
				//textureSource.unbind();




				//ofBuffer buffer;
				//buffer.set(tex.getTextureData(), tex.getWidth() * tex.getHeight() * 4); // Lee los datos de la textura en un ofBuffer

				//const unsigned char* data = tex.getTextureData().textureID;




				// Get a pointer to the texture pixel data
				//const unsigned char* data = (const unsigned char*)textureSource.getTextureData();
				//const unsigned char* data = (const unsigned char*)ImGui::GetIO().Fonts->TexPixelsAlpha8;
				//const unsigned char* data = (const unsigned char*)(uintptr_t)textureSourceID;
				//const unsigned char* data = (const unsigned char*)textureSourceID;


				//ImageInspect::inspect(w, h, data, mouseUVCoord, displayedTextureSize);
				//ImageInspect::inspect(w, h, (const unsigned char*)(ImTextureID)textureSourceID, mouseUVCoord, displayedTextureSize);
				//ImageInspect::inspect(w, h, (const unsigned char*)(ImTextureID)(uintptr_t)textureSourceID, mouseUVCoord, displayedTextureSize);


				//ImageInspect::inspect(width, height, data, mouseUVCoord, displayedTextureSize);
				//ImageInspect::inspect(width, height, (void*)data, mouseUVCoord, displayedTextureSize);
				//ImageInspect::inspect(width, height, pickerImage.GetBits(), mouseUVCoord, displayedTextureSize);
				//ImageInspect::inspect(width, height, bits, mouseUVCoord, displayedTextureSize);
			}

			//--

			if (ui.isMaximized())
			{
				ui.AddSpacingBigSeparated();

				//--

				// 2. Texture

				ImGui::Image((ImTextureID)(uintptr_t)textureSourceID, ImVec2(200, 200));

				//--

				// 3. Pixels

				//ImGui::Image(GetImTextureID(pixelsButtonID), ImVec2(200, 200));

				//--

				ui.AddSpacingBigSeparated();

				////GetImTextureID is a static function define in Helpers.h that accepts ofTexture, ofImage, or GLuint
				//ImGui::Dummy(ImVec2(10, 10));
				//if (ImGui::ImageButton(GetImTextureID(imageButtonID), ImVec2(200, 200))) {
				//	ofLog() << "PRESSED";
				//}
				////or do it manually
				////ImGui::SameLine();
				//ImGui::Image(GetImTextureID(pixelsButtonID), ImVec2(200, 200));

				//ImGui::Image((ImTextureID)(uintptr_t)textureSourceID, ImVec2(200, 200));
			}

			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bGui = !bGui;
}
