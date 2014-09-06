#include "basemachine.h"

void Base_Machine::execute() {
	m_program_counter = 0;

	while (m_program_counter != Memory::getMemoryInstructionSize()) {
		getNextInstruction();
		processInstruction();
	}
}

void Base_Machine::getNextInstruction() {
	memoryAddress_s addr;
	addr.address = m_program_counter;
	m_current_instruction = Memory::loadInstruction(addr.address);
	m_program_counter = addr.address;
}