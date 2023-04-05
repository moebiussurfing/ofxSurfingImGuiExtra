
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
				BIND(customCommand1);
			}
		private:
			void customCommand1(std::stringstream args, customType data){
				doWhatev(data.someVar);
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
	ofColor color{ 0,0,0,255 };
	int someVar = 0;
	string someString = "hello";
};

using namespace std::placeholders;

#define BIND(name) _commandList.emplace(std::make_pair<std::string, std::function<void(std::stringstream args, customType data)>>(#name, std::bind(&myCustomConsole::name, this, _1, _2)))

//--

class myCustomConsole : public console<customType>
{
public:

	myCustomConsole(bool redir = false) : console(redir)
	{
		std::cout << "> myCustomConsole()" << " redir:" << redir << endl;

		addCommands();
	}

	void addCommands()
	{
		BIND(customCommand1);
		BIND(help);
		BIND(reload);
		BIND(stop);
		BIND(clear);
		BIND(printArgs);
		BIND(colorToggle);

		std::cout << "-----------------------------" << endl;
		std::cout << "> addCommands:" << endl;
		std::cout << "customCommand1" << std::endl;
		std::cout << "help" << std::endl;
		std::cout << "reload" << std::endl;
		std::cout << "stop" << std::endl;
		std::cout << "clear" << std::endl;
		std::cout << "printArgs" << std::endl;
		std::cout << "colorToggle" << std::endl;
	}

private:

	void customCommand1(std::stringstream args, customType data)
	{
		std::cout << "-----------------------------" << endl;
		std::cout << "> customCommand1" << endl;

		//doWhatev(data.someVar);
	}

	void help(std::stringstream args, customType data)
	{
		std::cout << "-----------------------------" << endl;
		std::cout << "> help" << endl;
		std::cout << "> data" << endl;
		std::cout << "data.someVar:" << data.someVar << endl;
		std::cout << "data.someString:" << data.someString << endl;
		std::cout << "data.color:" << data.color << endl;
		std::cout << "> Added commands:" << endl;
		std::cout << "customCommand1" << std::endl;
		std::cout << "help" << std::endl;
		std::cout << "reload" << std::endl;
		std::cout << "stop" << std::endl;
		std::cout << "clear" << std::endl;
		std::cout << "printArgs" << std::endl;
		std::cout << "colorToggle" << std::endl;
	}

	void reload(std::stringstream args, customType data)
	{
		std::cout << "-----------------------------" << endl;
		std::cout << "> reload" << endl;
		std::cout << "data.someVar:" << data.someVar << endl;
	}

	void stop(std::stringstream args, customType data) {
		std::cout << "-----------------------------" << endl;
		std::cout << "> stop" << endl;
		std::cout << "data.someVar:" << data.someVar << endl;
	}

	void clear(std::stringstream args, customType data) {
		std::cout << "-----------------------------" << endl;
		std::cout << "> clear" << endl;
		std::cout << "data.someVar:" << data.someVar << endl;

		clearLines(data);
	}

	void printArgs(std::stringstream args, customType data) {
		std::cout << "-----------------------------" << endl;
		std::cout << "> printArgs" << endl;
		std::cout << "args:" << args << endl;
		std::cout << "data.someVar:" << data.someVar << endl;
	}

	void colorToggle(std::stringstream args, customType data) {
		std::cout << "-----------------------------" << endl;
		std::cout << "> colorToggle" << endl;
		data.color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
		std::cout << "data.color:" << data.color << endl;
	}
};
