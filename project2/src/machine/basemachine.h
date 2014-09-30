#pragma once

#include "../memory/memory.h"

class Base_Machine {
public:
	void execute();//goes through all instructions by checking to see if pc == ic
	static const bool& isMulticycle() { return multicycle; }

	static const void setPC(const int& label) { m_program_counter = label; };
protected:
	virtual void processInstruction() = 0; //pure virtual as each machine processes different instructions
	void getNextInstruction(); //updates pc for you so no need to mess with program counter
	static bool multicycle;
	static int m_num_cycles;
	instruction_t m_current_instruction;
private:
	static int m_num_instructions;
	static int m_program_counter;
};