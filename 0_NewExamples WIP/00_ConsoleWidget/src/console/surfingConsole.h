
// Original code from:
// https://github.com/theKlanc/YAIC

/*
*
*
* myCustomConsole.hpp
*

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

Header only C++ Imgui console,
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

struct customType {
	int someVar;
	//string someString;
};

using namespace std::placeholders;

#define BIND(name) _commandList.emplace(std::make_pair<std::string, std::function<void(std::stringstream args, customType data)>>(#name, std::bind(&myCustomConsole::name, this, _1, _2)))

#define CONSOLE_REDIRECT false

class myCustomConsole : public console<customType> {
public:
	myCustomConsole(bool redir = CONSOLE_REDIRECT) : console(redir) {
		cout << "myCustomConsole()" << endl;
		cout << "redir:" << redir << endl;

		//BIND(customCommand1);

		_commandList.emplace(
			std::make_pair<
			std::string, 
			std::function<void(std::stringstream args, customType data)>>("customCommand1", std::bind(&myCustomConsole::customCommand1, this, _1, _2)));
	}

private:
	void customCommand1(std::stringstream args, customType data) {
		ofLog() << "customCommand1()";

		cout << "customCommand1" << endl;
		cout << args;

		//doWhatev(data.someVar);

		//cout << __FUNCTION__ << endl;
		//cout << "t:" << data.someString << " : " << data.someVar;
	}

};
