#include "stackmachine.h"

#include "../logic/logic.h"

void Stack_Machine::execute() {
	m_program_counter = 0;

	while (m_program_counter != Memory::getMemoryInstructionSize()) {
		getNextInstruction();
		processInstruction();
	}
}

void Stack_Machine::getNextInstruction() {
	memory_address addr;
	addr.data_or_instruction = false;
	addr.address = m_program_counter;
	m_current_instruction = Memory::load(addr);
	m_program_counter = addr.address;
}

void Stack_Machine::processInstruction() {
	std::string temp = m_current_instruction;
	memory_address mem;

	if (temp.find("push")) {
		mem.alias = const_cast<char*>(temp.substr(temp.find("push"),temp.find("_")).c_str());
		m_stack.push_back(mem);
	} else if (temp.find("pop")) {
		mem = m_stack.back();
		m_stack.pop_back();
		Memory::store(mem);
	} else if (temp.find("add")) {
		Logic::add(m_stack);
	} else if (temp.find("mult")) {
		Logic::mult(m_stack);
	} else if (temp.find("prnt")) {
		Logic::print(m_stack);
	} else if (temp.find("end")) {
		Logic::end();
	}
}