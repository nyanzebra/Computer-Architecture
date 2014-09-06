#pragma once

#include "../pch.h"

class Stack_Machine : public Base_Machine {//TODO: need to fetch main from instructions
public:
	//non virtual process
	void processInstruction();

	//push and pop these will work on static stack
	void push(const std::string& value) { m_stack.push_back(value); }
	void pop(const byte_t* location) { storeData(location, L_stringToList(m_stack.back())); m_stack.pop_back(); }

	//get stack
	static std::list<std::string> getStack() { return m_stack; }
	//static remover as doing it non-static will not work!
	static void removeTop() { m_stack.pop_back(); }

private:
	static stack_t m_stack; // is static!!
};