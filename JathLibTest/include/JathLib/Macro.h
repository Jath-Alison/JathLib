#pragma once

#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <functional>

namespace Jath{

	struct Macro
	{
		Macro(const char* sssname){
			name = new char[20];
			strcpy(name, sssname);

		};

		Macro(){
			name = new char[20];
			strcpy(name, "none");
		}

		Macro(const Macro& macro) {
			name = new char[20];
			strcpy(name, macro.name);
		}

		char* name;

	};

	struct MacroFunc{
	template <class Fn>
	MacroFunc(const char* sssname, Fn fn){
		func = fn;
		name = new char[20];
			strcpy(name, sssname);
	}

	std::function<void(void)> func;

	void run(){
		func();
	}

	char* name;
	};

}