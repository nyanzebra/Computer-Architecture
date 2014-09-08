#include <iostream>
#include <stdlib.h>

#include "logic.h"
#include "../machines/accummachine.h"
#include "../machines/stackmachine.h"

//stack machine add
const int Logic::add() {
	std::string temp = Stack_Machine::getStack().back(); //get first value
	int i = atoi(temp.c_str()); //convert to int
	Stack_Machine::removeTop(); //remove top of stack
	temp = Stack_Machine::getStack().back(); //get second value
	int j = atoi(temp.c_str()); //convert to int
	Stack_Machine::removeTop(); //remove top of stack
	return i + j; //return addition
}
//accum machine add
void Logic::add(const std::string& s) {
	int i = atoi(s.c_str()); //convert to int
	int j = std::stoi(Accum_Machine::getReg()); //convert to int
	Accum_Machine::setReg(std::to_string(i + j)); //set register
}
//stack machine multiply
const int Logic::mult() {
	std::string temp = Stack_Machine::getStack().back(); //get first value
	int i = atoi(temp.c_str()); //convert to int
	Stack_Machine::removeTop(); //remove top of stack
	temp = Stack_Machine::getStack().back(); //get second value
	int j = atoi(temp.c_str()); //convert to int
	Stack_Machine::removeTop(); //remove top of stack
	return i * j; //return multiplication
}
//accum machine multiply
void Logic::mult(const std::string& s) {
	int i = atoi(s.c_str()); //convert to int
	int j = std::stoi(Accum_Machine::getReg()); //convert to int
	Accum_Machine::setReg(std::to_string(i * j)); //set register
}
void Logic::stack_print() {
	std::string statement = Stack_Machine::getStack().back(); //get message
	if (statement != "\\n") { //make sure it does not equal new line
		std::cout << statement; //print out message
	}
	else{
		std::cout << std::endl; //print new line
	}
	Stack_Machine::removeTop();
}
void Logic::accum_print() {
	std::string statement = Accum_Machine::getReg(); //get message
	if (statement != "\\n") { //make sure it does not equal new line
		std::cout << statement; //print out message
	}
	else{
		std::cout << std::endl; //print new line
	}
}
int Logic::end() {
	return 0;
}