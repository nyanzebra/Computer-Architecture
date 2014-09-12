#include <iostream>

#include "logic.h"
#include "accummachine.h"
#include "stackmachine.h"

std::unordered_map<int, std::string>* Logic::m_hash_strings = new std::unordered_map<int, std::string>();

//stack machine add
const data_t Logic::add() {
	data_t i = Memory::topStack(); //get first value
	if (i < 48) { // make sure i is a number
		return NULL;
	}
	Memory::popStack(); //remove top of stack
	data_t j = Memory::topStack(); //get second value
	if (j < 48) { //make sure j is a number
		return NULL;
	}
	Memory::popStack(); //remove top of stack
	data_t answer = (i - 48) + (j - 48); //multiply
	return answer + 48; //return addition
}
//accum machine add
void Logic::add(const instruction_t& addr) {
	data_t i = Memory::loadData(addr); //get data at addr
	if (i < 48) { // make sure i is a number
		return;
	}
	data_t j = Accum_Machine::getReg(); //get accum data
	if (j < 48) { //make sure j is a number
		return;
	}
	data_t answer = (i - 48) + (j - 48); //multiply
	Accum_Machine::setReg((answer + 48)); //set register
}
//stack machine multiply
const data_t Logic::mult() {
	data_t i = Memory::topStack(); //get first value
	if (i < 48) { // make sure i is a number
		return NULL;
	}
	Memory::popStack(); //remove top of stack
	data_t j = Memory::topStack(); //get second value
	if (j < 48) { //make sure j is a number
		return NULL;
	}
	Memory::popStack(); //remove top of stack
	data_t answer = (i - 48) * (j - 48); //multiply

	return answer + 48; //return multiplication
}
//accum machine multiply
void Logic::mult(const instruction_t& addr) {
	data_t i = Memory::loadData(addr); //get data at addr
	if (i < 48) { // make sure i is a number
		return;
	}
	data_t j = Accum_Machine::getReg(); //get accum data
	if (j < 48) { //make sure j is a number
		return;
	}
	data_t answer = (i - 48) * (j - 48); //multiply
	Accum_Machine::setReg((answer + 48)); //set register
}
void Logic::stack_print() {
	if (m_hash_strings->find(Memory::topStack()) != m_hash_strings->end()) {
		std::string s = m_hash_strings->find(Memory::topStack())->second;
		if (!s.empty()) {
			Memory::popStack();
			std::cout << s;
		}
	} else {
		char c = (char)Memory::topStack();
		if (c >= 0 && c < 20) { //check and see if it is most likely a char
			Memory::popStack();
			std::cout << c;
		} else {
			int i = Memory::topStack();
			Memory::popStack();
			i = i - 48; //convert from decimal to ascii
			std::cout << i;
		}
	}
}
void Logic::accum_print() {
	if (m_hash_strings->find(Accum_Machine::getReg()) != m_hash_strings->end()) {
		std::string s = m_hash_strings->find(Accum_Machine::getReg())->second;
		if (!s.empty()) {
			std::cout << s;
		}
	} else {
		char c = (char)Accum_Machine::getReg();
		if (c >= 0 && c < 20) {
			std::cout << c;
		} else {
			std::cout << Accum_Machine::getReg() - 48;
		}
	}
}
int Logic::end() {
	return 0;
}