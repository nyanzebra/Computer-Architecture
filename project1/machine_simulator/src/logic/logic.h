#include <list>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "../memory/memory.h"
#include "../utility/types.h"
#include "../utility/lambdas.h"

class Logic {//TODO fix for memory address
public:
	static const int add() {
		std::string temp = Stack_Machine::getStack().back();
		int i = atoi(temp.c_str());
		Stack_Machine::removeTop();
		temp = Stack_Machine::getStack().back();
		int j = atoi(temp.c_str());
		Stack_Machine::removeTop();
		return i + j;
	}
	static const int mult() {
		std::string temp = Stack_Machine::getStack().back();
		int i = atoi(temp.c_str());
		stack s = Stack_Machine::getStack();
		Stack_Machine::removeTop();
		temp = Stack_Machine::getStack().back();
		int j = atoi(temp.c_str());
		Stack_Machine::removeTop();
		return i * j;
	}	
	static int end() {
		return 0;
	}
	static void print() { 
		stack s = Stack_Machine::getStack();
		std::string statement = Stack_Machine::getStack().back();
		if (statement != "\\n") {
			for (char c : statement) {
				std::cout << c;
			}
		} else{
			std::cout << std::endl;
		}
		Stack_Machine::removeTop();
	}
};

