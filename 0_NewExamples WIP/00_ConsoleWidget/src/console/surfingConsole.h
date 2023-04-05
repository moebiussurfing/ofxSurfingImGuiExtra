
// Original code from @theKlanc:
// https://github.com/theKlanc/YAIC
// 
// https://gitea.ledgedash.com/klanc/Spaceworks/src/branch/master/source/gameConsole.cpp
// https://gitea.ledgedash.com/klanc/Spaceworks/src/branch/master

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

struct dataCustom
{
	ofColor color{ 0,0,0,0 };
	int someVar = 0;
	string someString = "";
};

using namespace std::placeholders;

#define BIND(name) _commandList.emplace(std::make_pair<std::string, std::function<void(std::stringstream args, dataCustom* data)>>(#name, std::bind(&surfingConsole::name, this, _1, _2)))

//--

class surfingConsole : public console<dataCustom*>
{
public:
	surfingConsole(bool redir = false) : console(redir)
	{
		std::cout << "> surfingConsole()" << " redir:" << redir << endl;

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
	void myCommand(std::stringstream args, dataCustom* data)
	{
		std::cout << "> myCommand" << endl;
		std::cout << endl;

		//doWhatev(data);

		if (args.tellg() != -1) {
			std::string argument;
			args >> argument;

			// Example some catchers
			//unsigned id = std::strtol(argument.c_str(), nullptr, 10);
			//config::zoom = std::stoi(argument);
			//unsigned childID = std::stoi(argument);
			/*
			if (args.tellg() != -1) {
					args >> argument;
					if(argument == "_")
					{}
					else if(argument[0] == '-'){
						pos.pos.z -= std::strtol(&argument.c_str()[1], nullptr, 10);
					}
					else if(argument[0] == '+'){
						pos.pos.z += std::strtol(&argument.c_str()[1], nullptr, 10);
					}
					else{
						pos.pos.z = std::strtol(&argument.c_str()[1], nullptr, 10);
					}
				}
			*/

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
	void help(std::stringstream args, dataCustom* data)
	{
		std::cout << "> help" << endl;
		std::cout << "> data" << endl;
		std::cout << "data->someVar:" << data->someVar << endl;
		std::cout << "data->someString:" << data->someString << endl;
		std::cout << "data->color:" << data->color << endl;
		std::cout << endl;
		help_();
	};

	void clear(std::stringstream args, dataCustom* data)
	{
		clearLines(data);
	};

	void printArgs(std::stringstream args, dataCustom* data)
	{
		std::cout << "args:" << args << endl;
		std::cout << endl;
	};

	void colorToggle(std::stringstream args, dataCustom* data)
	{
		data->color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
		std::cout << "data->color:" << data->color << endl;
		std::cout << endl;
	};

	void setColor(std::stringstream args, dataCustom* data)
	{
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
		std::cout << "> help" << endl;
		std::cout << endl;
		std::cout << "myCommand   \t (reset or default)" << std::endl;
		std::cout << "help        \t (list commands)" << std::endl;
		std::cout << "colorToggle \t (random color)" << std::endl;
		std::cout << "setColor    \t (blue, green or red)" << std::endl;
		std::cout << "printArgs   \t (print passed args)" << std::endl;
		std::cout << "clear       \t (clear console)" << std::endl;
		std::cout << endl;
	};

	void clear_()
	{
		clearLines(NULL);
	};
};
