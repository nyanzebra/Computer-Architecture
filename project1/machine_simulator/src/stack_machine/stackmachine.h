#pragma once

#include <list>

#include "../memory/memory.h"
#include "../utility/lambdas.h"
#include "../utility/types.h"

class Stack_Machine : public Memory {//TODO: need to fetch main from instructions
public:
	
	void getNextInstruction();
	void* getData(const byte& location);

	void push(const std::string& value) { m_stack.push_back(value); }
	void pop(const byte* location) { storeData(location, L_stringToList(m_stack.back())); m_stack.pop_back(); }

	void processInstruction();
	static std::list<std::string> getStack() { return m_stack; }
	static void removeTop() { m_stack.pop_back(); }

	void execute();
private:
	static stack m_stack;
	std::list<byte> m_current_instruction;
	int m_program_counter;
	int* m_stack_pointer;
};