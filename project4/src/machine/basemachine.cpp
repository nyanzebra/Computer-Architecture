#include <iostream>

#include "basemachine.h"

//init static variables
int Base_Machine::m_num_instructions = 1;
int Base_Machine::m_program_counter = 0;
bool Base_Machine::m_pipe_scoreboard = false;
int Base_Machine::m_num_cycles = 1;
int Base_Machine::m_nop_counter = 0;

void Base_Machine::begin() {
	m_program_counter = MIN_SEGMENT_INSTRUCTION;
	m_num_instructions = 1;
	m_num_cycles = 1;
	m_nop_counter = 0;

	while (m_program_counter < Memory::m_instruction_counter) {
		if (m_program_counter == 10) {
			int i = 0;
		}
 		getNextInstruction();
		processInstruction();
		m_num_cycles++;
	}
	processRemainingInstructions();

	std::cout << "Number of Instructions: " << m_num_instructions << std::endl;
	std::cout << "Number of Cycles: " << m_num_cycles << std::endl;
	std::cout << "Number of nop's in code: " << m_nop_counter << std::endl;
}

void Base_Machine::getNextInstruction() {
	m_current_instruction = Memory::loadInstruction(m_program_counter);
}