#pragma once

#include "../memory/memory.h"

class Base_Machine {
public:
	void execute();//goes through all instructions by checking to see if pc == ic
	static const bool& isMulticycle() { return multicycle; }
	static void setMulticyle(const bool& b) { multicycle = b; }
	static void setPC(const int& label) { m_program_counter = label; };
	static void incrementNopCount() { m_nop_counter++; };
	static void clear() { m_nop_counter = 0; }
protected:
	virtual void processInstruction() = 0; //pure virtual as each machine processes different instructions
	void getNextInstruction(); //updates pc for you so no need to mess with program counter
	static bool multicycle; //determine if multicycle
	static int m_num_cycles; //number of cycles
	instruction_t m_current_instruction; //current machine instruction
private:
	static int m_num_instructions;
	static int m_program_counter;
	static int m_nop_counter;
};