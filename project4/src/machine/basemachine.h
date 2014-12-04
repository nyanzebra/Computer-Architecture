#pragma once

#include "../memory/memory.h"

class Base_Machine {
public:
	void begin();//goes through all instructions by checking to see if pc == ic
	static void setPC(const int& label) { m_program_counter = label; }
	static int getCycles() { return m_num_cycles; }
	static void incrementInstructionCounter() { m_num_instructions++; }
	static void incrementProgramCounter() { m_program_counter++; }
	static bool isPipeScoreboard() { return m_pipe_scoreboard; }
	static void incrementNopCount() { m_nop_counter++; }
	static void clear() { m_nop_counter = 0; }
	static void setPipeline() { m_pipe_scoreboard = !m_pipe_scoreboard; }
protected:
	virtual void processInstruction() = 0; //pure virtual as each machine processes different instructions
	virtual void processRemainingInstructions() = 0;
	void getNextInstruction(); //updates pc for you so no need to mess with program counter
	static bool m_pipe_scoreboard; //determine if piping scoreboard
	static int m_num_cycles; //number of cycles
	instruction_t m_current_instruction; //current machine instruction
private:
	static int m_num_instructions;
	static int m_program_counter;
	static int m_nop_counter;
};