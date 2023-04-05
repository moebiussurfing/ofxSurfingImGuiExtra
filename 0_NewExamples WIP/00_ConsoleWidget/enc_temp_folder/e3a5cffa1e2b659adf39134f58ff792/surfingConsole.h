
// Original code from @theKlanc:
// https://github.com/theKlanc/YAIC

/*
*
*
* myCustomConsole.hpp
*
	// EXAMPLE

	#pragma once
	#include <functional>
	#include "console.hpp"

	struct customType{
	  int someVar;
	};

	using namespace std::placeholders;
	#define BIND(name) _commandList.emplace(std::make_pair<std::string, std::function<void(std::stringstream args, customType data)>>(#name, std::bind(&myCustomConsole::name, this, _1, _2)))

	class myCustomConsole : public console<customType>{
		public:
			myCustomConsole(bool redir = false): console(redir){
				BIND(myCommand);
			}
		private:
			void myCommand(std::stringstream args, customType data){
				doWhatev(data->someVar);
			}
	};
*/


/*

	Header only C++ ImGui console,
	with support for stdout redirection into itself.

	Then just initialize an object myCustomConsole wherever you want,
	and call its myCustomConsoleObject.show(data) method inside an ImGui context.

*/


//--

#pragma once
#include "ofMain.h"
#include "ofxSurfingImGui.h"

#include <functional>
#include "console.hpp"

//--

struct customType
{
	ofColor color{ 0,0,0,0 };
	int someVar = 0;
	string someString = "";
};

using namespace std::placeholders;

#define BIND(name) _commandList.emplace(std::make_pair<std::string, std::function<void(std::stringstream args, customType* data)>>(#name, std::bind(&myCustomConsole::name, this, _1, _2)))

//--

class myCustomConsole : public console<customType*>
{
public:

	myCustomConsole(bool redir = false) : console(redir)
	{
		std::cout << "> myCustomConsole()" << " redir:" << redir << endl;

		addCommands();
	};

	void addCommands()
	{
		BIND(myCommand);
		BIND(help);
		BIND(colorToggle);
		BIND(setColor);
		BIND(clear);
		BIND(printArgs);

		std::cout << "> addCommands:" << endl;
		help_();
	};

private:
	void myCommand(std::stringstream args, customType* data)
	{
		std::cout << "--------------------------------------------------------------" << endl;
		std::cout << "> myCommand" << endl;
		std::cout << endl;

		//doWhatev(data);

		if (args.tellg() != -1) {
			std::string argument;
			args >> argument;
			unsigned id = std::strtol(argument.c_str(), nullptr, 10);

			if (argument == "reset") {
				data->someVar = 12345;
				data->someString = "just reseted";
				data->color = ofColor::yellow;
			}
			else if (argument == "default") {
				data->someVar = -1;
				data->someString = "just defaulted";
				data->color = ofColor::black;
			}

			std::cout << "> data" << endl;
			std::cout << "data->someVar:" << data->someVar << endl;
			std::cout << "data->someString:" << data->someString << endl;
			std::cout << "data->color:" << data->color << endl;
		}
	};

private:
	void help(std::stringstream args, customType* data)
	{
		std::cout << "--------------------------------------------------------------" << endl;
		std::cout << "> data" << endl;
		std::cout << "data->someVar:" << data->someVar << endl;
		std::cout << "data->someString:" << data->someString << endl;
		std::cout << "data->color:" << data->color << endl;
		std::cout << endl;
		help_();
	};

	void clear(std::stringstream args, customType* data)
	{
		std::cout << "--------------------------------------------------------------" << endl;

		clearLines(data);
	};

	void printArgs(std::stringstream args, customType* data)
	{
		std::cout << "--------------------------------------------------------------" << endl;
		std::cout << "args:" << args << endl;
		std::cout << endl;
	};

	void colorToggle(std::stringstream args, customType* data)
	{
		std::cout << "--------------------------------------------------------------" << endl;

		data->color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
		std::cout << "data->color:" << data->color << endl;
		std::cout << endl;
	};

	void setColor(std::stringstream args, customType* data)
	{
		std::cout << "--------------------------------------------------------------" << endl;

		//TODO: catch/filter args
		string s = args.str();

		ofColor c;
		if (s == "red") c = ofColor(ofColor::red);
		else if (s == "green") c = ofColor(ofColor::green);
		else if (s == "blue") c = ofColor(ofColor::blue);
		data->color = c;

		std::cout << "data->color:" << data->color << endl;
		std::cout << endl;
	};

public:
	void help_()
	{
		std::cout << "> added commands:" << endl;
		std::cout << "myCommand (reset or default)" << std::endl;
		std::cout << "help (list commands)" << std::endl;
		std::cout << "colorToggle (random color)" << std::endl;
		std::cout << "setColor (blue, green or red)" << std::endl;
		std::cout << "printArgs (print passed args)" << std::endl;
		std::cout << "clear (clear console)" << std::endl;
		std::cout << endl;
	};

	void clear_()
	{
		clearLines(NULL);
	};
};
