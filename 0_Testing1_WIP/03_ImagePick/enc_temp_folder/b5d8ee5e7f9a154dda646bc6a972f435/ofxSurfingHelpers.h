#pragma once

#include "ofMain.h"

/*

	TODO:

*/

//---------

// Include some classes by default. 
// Notice that there's other classes bundled on the add-on (/src or /libs) 
// that are not included here, then you have to include them manually.

#include "ofxSurfingConstants.h"

#include "surfingTimers.h"
#include "ofxSurfing_Widgets.h"
//#include "ofxAutosaveGroupTimer.h"

//--

//TODO: WIP
// test improve serialize performance..
// trying to load all the settings but not triggering each param.
// then trig all loaded params after file load.
//#define USE_FAST_SERIALIZER 

//--

namespace ofxSurfingHelpers
{
	// Monitors helpers

	// WARRNING! For my personal setup!
	// I have three FHD monitors: 
	// Left monitor is portrait. 
	// Central and Right monitor are landscape.
	//--------------------------------------------------------------
	inline void SurfSetMyMonitor(int layout = 0)
	{
		int h = 38; // window bar height on WIN_32
		int offset = 12;
		int hw = h - offset;
		if (layout == 0) { // left portrait
			ofSetWindowPosition(-1080, h);
			ofSetWindowShape(1080, 1920 - hw);
		}
		else if (layout == 1) { // landscape right
			ofSetWindowPosition(1920, h);
			ofSetWindowShape(1920, 1080 - hw);
		}
		else if (layout == 2) { // landscape left
			ofSetWindowPosition(-1920, h);
			ofSetWindowShape(1920, 1080 - hw);
		}
	}

	inline void SurfDrawImageFullScreenFit(ofFloatImage& imageFloat, ofScaleMode scaleMode = OF_SCALEMODE_FIT)
	{
		ofRectangle rr(0, 0, imageFloat.getWidth(), imageFloat.getHeight());
		rr.scaleTo(ofGetCurrentViewport(), scaleMode);
		imageFloat.draw(rr.x, rr.y, rr.width, rr.height);
	}

	//----

	// Serializers

	//----

	//--------------------------------------------------------------
	inline bool loadGroup(ofParameterGroup& g, string path = "", bool debug = true)
	{
		if (path == "")
		{
			path = g.getName() + "_Settings.json"; // a default filename
			ofLogWarning("ofxSurfingHelpers") << "loadGroup " << "Path is empty! Using a default instead!";
		}

		if (debug)
		{
			ofLogNotice("ofxSurfingHelpers") << "loadGroup `" << g.getName() << "` to `" << path << "`";
			ofLogNotice("ofxSurfingHelpers") << "ofParameters: \n\n  " << g.toString();
		}

		ofJson settings;
		settings = ofLoadJson(path);

#ifndef USE_FAST_SERIALIZER
		ofDeserialize(settings, g);
#endif
#ifdef USE_FAST_SERIALIZER
		ofDeserializeSilent(settings, g);
#endif

		// Returns false if no file preset yet.
		ofFile f;
		bool b = f.doesFileExist(path);
		if (b) ofLogNotice("ofxSurfingHelpers") << "loadGroup: `" << g.getName() << "` at `" << path << "`";
		else ofLogError("ofxSurfingHelpers") << "Error loading: `" << g.getName() << "` at `" << path << "` Not found!";

		return b; // Returns true if it's ok
	}

	//--------------------------------------------------------------
	inline bool saveGroup(ofParameterGroup& g, string path = "", bool debug = true)
	{
		if (path == "") {
			path = g.getName() + "_Settings.json";
			ofLogWarning("ofxSurfingHelpers") << "saveGroup " << "Path is empty! Using a default instead!";
		}

		if (debug) {
			ofLogNotice("ofxSurfingHelpers") << g.getName() << " to `" << path << "`";
			ofLogNotice("ofxSurfingHelpers") << "ofParameters: \n\n  " << g.toString();
		}

		// Create folder if folder do not exist!
		// From now, will not rerquire to call manually:
		//ofxSurfingHelpers::CheckFolder(path);

		if (!ofDirectory::doesDirectoryExist(ofFilePath::getEnclosingDirectory(path))) {
			ofFilePath::createEnclosingDirectory(path);
			ofLogWarning("ofxSurfingHelpers") << "Created enclosing folder for: " << path;
		}

		ofJson settings;
		ofSerialize(settings, g);
		bool b = ofSavePrettyJson(path, settings);

		if (b) ofLogVerbose("ofxSurfingHelpers") << "Save: `" << g.getName() << "` at " << path;
		else ofLogError("ofxSurfingHelpers") << "Error saving: `" << g.getName() << "` at " << path;

		return b;
	}

	//----

	// Shorten versions:
	// will use a default path
	//--------------------------------------------------------------
	inline bool load(ofParameterGroup& g)
	{
		return loadGroup(g);
	}

	//--------------------------------------------------------------
	inline bool save(ofParameterGroup& g)
	{
		return saveGroup(g);
	}

	//--

	// Files

	//--------------------------------------------------------------
	// Check if a folder path exist and creates one if not
	// why? many times when you try to save a file, 
	// this is not possible and do not happens 
	// bc the container folder do not exist
	//--------------------------------------------------------------
	inline void CheckFolder(string _path)
	{
		//ofLogNotice("ofxSurfingHelpers")<<(__FUNCTION__) << _path;

		//TODO: A clean alternative..
		/*
		///string jsonfilepath;
		if (!ofDirectory::doesDirectoryExist(ofFilePath::getEnclosingDirectory(jsonfilepath))) {
			ofFilePath::createEnclosingDirectory(jsonfilepath);
		}
		*/

		//if (ofFile::doesFileExist(_path)) {

		//// Workaround to avoid error when folders are folder/subfolder
		//auto _fullPath = ofSplitString(_path, "/");
		//for (int i = 0; i < _fullPath.size(); i++) {
		//	ofLogNotice("ofxSurfingHelpers")<<(__FUNCTION__) << ofToString(i) << " " << _fullPath[i];
		//}

		// /bin/data/
		ofDirectory dataDirectory(ofToDataPath(_path, true));

		// Check if folder path exist
		if (!dataDirectory.isDirectory())
		{
			ofLogError("ofxSurfingHelpers") << (__FUNCTION__) << "FOLDER NOT FOUND! TRYING TO CREATE...";

			// Try to create folder
			bool b = dataDirectory.createDirectory(ofToDataPath(_path, true), false, true);
			//bool b = dataDirectory.createDirectory(ofToDataPath(_path, true));
			// Added enable recursive to allow create nested subfolders if required

			// Debug if creation has been succeded
			if (b) ofLogNotice("ofxSurfingHelpers") << "CREATED '" << _path << "' SUCCESSFULLY!";
			else ofLogError("ofxSurfingHelpers") << "UNABLE TO CREATE '" << _path << "' FOLDER!";
		}
		else
		{
			ofLogVerbose("ofxSurfingHelpers") << _path << " Found!";// nothing to do
		}
	}

	//--

	//TODO:
	// Testing for improving performance
	// changing the mode we trig the loaded params...
	// load file without trigging. trig after all is loaded.

	//--------------------------------------------------------------
	inline void ofDeserializeSilent(const ofJson& json, ofAbstractParameter& parameter) {
		ofLogNotice("ofxSurfingHelpers") << (__FUNCTION__) << parameter.getName();

		if (!parameter.isSerializable()) {
			return;
		}
		std::string name = parameter.getEscapedName();
		if (json.find(name) != json.end()) {
			if (parameter.type() == typeid(ofParameterGroup).name()) {
				ofParameterGroup& group = static_cast <ofParameterGroup&>(parameter);
				for (auto& p : group) {
					ofDeserializeSilent(json[name], *p);
				}
			}
			else {
				if (parameter.type() == typeid(ofParameter <int>).name() && json[name].is_number_integer()) {
					parameter.cast <int>().setWithoutEventNotifications(json[name].get<int>());
					//parameter.cast <int>() = json[name].get<int>();
				}
				else if (parameter.type() == typeid(ofParameter <float>).name() && json[name].is_number_float()) {
					parameter.cast <float>().setWithoutEventNotifications(json[name].get<float>());
					//parameter.cast <float>() = json[name].get<float>();
				}
				else if (parameter.type() == typeid(ofParameter <bool>).name() && json[name].is_boolean()) {
					parameter.cast <bool>().setWithoutEventNotifications(json[name].get<bool>());
					//parameter.cast <bool>() = json[name].get<bool>();
				}
				else if (parameter.type() == typeid(ofParameter <int64_t>).name() && json[name].is_number_integer()) {
					parameter.cast <int64_t>().setWithoutEventNotifications(json[name].get<int64_t>());
					//parameter.cast <int64_t>() = json[name].get<int64_t>();
				}
				else if (parameter.type() == typeid(ofParameter <std::string>).name()) {
					parameter.cast <std::string>().setWithoutEventNotifications(json[name].get<std::string>());
					//parameter.cast <std::string>() = json[name].get<std::string>();
				}
				else {
					parameter.fromString(json[name]);
				}
			}
		}
	}


	//----


	//TODO: add to API
	/*
	// Return file extension

	inline string getFileName(string _str, bool _trimExt = false) {
		string name = "";
		int slashPos = _str.rfind('/');

		if (slashPos != string::npos) {
			name = _str.substr(slashPos + 1);

			if (_trimExt)
				name = getFilePathTrimExtension(name);
		}

		return name;
	}

	inline string getFileFolderPath(string _str) {
		string name = "";
		int slashPos = _str.rfind('/');

		if (slashPos != string::npos) {
			name = _str.substr(0, slashPos);
		}

		return name;
	}

	inline string getFileExtension(string _str) {
		string ext = "";
		int extPos = _str.rfind('.');

		if (extPos != string::npos) {
			ext = _str.substr(extPos + 1);
		}

		return ext;
	}

	inline string getFilePathTrimExtension(string _str) {
		string ext = "";
		int extPos = _str.rfind('.');

		if (extPos != string::npos) {
			ext = _str.substr(0, extPos);
		}

		return ext;
	}

	inline int getNumWords(std::string str)
	{
		int word_count(0);
		std::stringstream ss(str);
		std::string word;
		while (ss >> word) ++word_count;
		return word_count;
	}
	*/


	//----


	// Time in seconds to string min::sec
	// Original code taken from ofxFilikaUtils.h

#define SECS_PER_MIN 60
#define SECS_PER_HOUR 3600

	//--------------------------------------------------------------
	inline std::string calculateTime(float _time) {

		int seconds;
		int minutes;
		int mins_left;
		int secs_left;

		seconds = (/*gameTimeSeconds - */int(_time));
		minutes = (/*gameTimeSeconds - */int(_time)) / SECS_PER_MIN;
		mins_left = minutes % SECS_PER_MIN;
		secs_left = seconds % SECS_PER_MIN;

		std::string mins;
		std::string secs;

		if (mins_left < 10) {
			mins = "0" + ofToString(mins_left);
		}
		else {
			mins = ofToString(mins_left);
		}

		if (secs_left < 10) {
			secs = "0" + ofToString(secs_left);
		}
		else {
			secs = ofToString(secs_left);
		}

		//cout << ofGetElapsedTimeMillis() / 1000 << endl;
		//cout << "remaining time : " << mins_left << " : " <<  secs_left << endl;
		//cout << "remaining time : " << mins << " : " <<  secs << endl;

		if (mins_left < 0 || secs_left < 0)
			return "00:00";
		else
			return (mins + ":" + secs);
	}


	//----


	// Debug Helpers

	//--------------------------------------------------------------
	inline void DebugCoutParam(ofAbstractParameter& ap)
	{
		cout << ap.getName() << ": " << ap << endl;
	}

}; // namespace ofxSurfingHelpers 
