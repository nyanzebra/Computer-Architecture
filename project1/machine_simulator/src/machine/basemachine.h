#pragma once

#include "memory.h"

class Base_Machine {
public:
	void execute();//goes through all instructions by checking to see if pc == ic
protected:
	virtual void processInstruction() = 0; //pure virtual as each machine processes different instructions
	void getNextInstruction(); //updates pc for you so no need to mess with program counter

	int m_program_counter;
	instruction_t m_current_instruction;
};