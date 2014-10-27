#include <iostream>

#include "basemachine.h"

//init static variables
int Base_Machine::m_num_instructions = 0;
int Base_Machine::m_program_counter = 0;
bool Base_Machine::multicycle = false;
int Base_Machine::m_num_cycles = 0;
int Base_Machine::m_nop_counter = 0;

void Base_Machine::execute() {
	m_program_counter = MIN_SEGMENT_INSTRUCTION;
	m_num_instructions = 0;
	m_num_cycles = 0;

	while (m_program_counter != Memory::m_instruction_counter) {
		getNextInstruction();
		processInstruction();
		m_num_instructions++;
		m_num_cycles++;
	}
	std::cout << "Number of Instructions: " << m_num_instructions << std::endl;
	std::cout << "Number of Cycles: " << m_num_cycles << std::endl;
	std::cout << "Speed up: " << ((8 * m_num_instructions) / (float)m_num_cycles) << std::endl;
	std::cout << "Number of nop's in code: " << m_nop_counter << std::endl;
}

void Base_Machine::getNextInstruction() {
	m_current_instruction = Memory::loadInstruction(m_program_counter);
	m_program_counter++;
}