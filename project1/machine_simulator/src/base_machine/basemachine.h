#pragma once

#ifndef PCH_H
#include "../pch.h"
#endif

//this is a base machine and it holds all the common functions between machines

class Base_Machine :public Memory {
public:
	void getNextInstruction(); //updates pc for you so no need to mess with program counter
	virtual void processInstruction() = 0;

	void execute();//goes through all instructions by checking to see if pc == ic
protected:
	int m_program_counter;
	std::list<byte_t> m_current_instruction;
};
