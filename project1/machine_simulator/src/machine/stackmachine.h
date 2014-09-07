#pragma once

#include "../memory/memory.h"

class Stack_Machine {//TODO: need to fetch main from instructions
public:
	void processInstruction();
	void getNextInstruction(); //updates pc for you so no need to mess with program counter

	//push and pop these will work on static stack
	void push(const std::string& value) { m_stack.push_back(value); }
	void pop(const byte_t* location) { Memory::storeData(location, L_stringToList(m_stack.back())); m_stack.pop_back(); }

	//get stack
	static std::list<std::string> getStack() { return m_stack; }
	//static remover as doing it non-static will not work!
	static void removeTop() { m_stack.pop_back(); }

	void execute();//goes through all instructions by checking to see if pc == ic
private:
	int m_program_counter;
	std::list<byte_t> m_current_instruction;
	static stack_t m_stack; // is static!!
};