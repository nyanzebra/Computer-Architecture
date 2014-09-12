#include "basemachine.h"

void Base_Machine::execute() {
	m_program_counter = MIN_SEGMENT_INSTRUCTION;

	while (m_program_counter != Memory::m_instruction_counter) {
		getNextInstruction();
		processInstruction();
	}
}

void Base_Machine::getNextInstruction() {
	m_current_instruction = Memory::loadInstruction(m_program_counter);
	m_program_counter++;
}