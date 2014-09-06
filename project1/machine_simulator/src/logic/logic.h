#pragma once

#include "../pch.h"

class Logic {//TODO fix for memory address
public:
	//stack machine add
	static const int add() {
		std::string temp = Stack_Machine::getStack().back(); //get first value
		int i = atoi(temp.c_str()); //convert to int
		Stack_Machine::removeTop(); //remove top of stack
		temp = Stack_Machine::getStack().back(); //get second value
		int j = atoi(temp.c_str()); //convert to int
		Stack_Machine::removeTop(); //remove top of stack
		return i + j; //return addition
	}
	//accum machine add
	static void add(const std::string& s) {
		int i = atoi(s.c_str()); //convert to int
		int j = atoi(Accum_Machine::getReg().c_str()); //convert to int
		std::string t = std::to_string(i + j);//get string value
		Accum_Machine::setReg(t); //set register
	}
	//stack machine multiply
	static const int mult() {
		std::string temp = Stack_Machine::getStack().back(); //get first value
		int i = atoi(temp.c_str()); //convert to int
		Stack_Machine::removeTop(); //remove top of stack
		temp = Stack_Machine::getStack().back(); //get second value
		int j = atoi(temp.c_str()); //convert to int
		Stack_Machine::removeTop(); //remove top of stack
		return i * j; //return multiplication
	}	
	//stack machine multiply
	static void mult(const std::string& s) {
		int i = atoi(s.c_str()); //convert to int
		int j = atoi(Accum_Machine::getReg().c_str()); //convert to int
		std::string t = std::to_string(i * j);//get string value
		Accum_Machine::setReg(t); //set register
	}
	static int end() { //good exit
		return 0;
	}
	static void stack_print() { 
		std::string statement = Stack_Machine::getStack().back(); //get message
		if (statement != "\\n") { //make sure it does not equal new line
			std::cout << statement; //print out message
		} else{
			std::cout << std::endl; //print new line
		}
		Stack_Machine::removeTop();
	}
	static void accum_print() {
		std::cout << Accum_Machine::getReg() << std::endl; //print message
	}
};

