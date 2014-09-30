#include "stackmachine.h"

void Stack_Machine::processInstruction() {

	instruction_t instruction = m_current_instruction; 
	data_t opcode = instruction >> 24;
	instruction = instruction & 0x00ffffff; 

	if (opcode == 0x01) {
		pushAddress(instruction);
	} else if (opcode == 0x02) {
		pop(instruction);
	} else if (opcode == 0x03) {
		data_t i = Logic::add();
		pushData(i);
	} else if (opcode == 0x04) {
		data_t i = Logic::mult();
		pushData(i);
	} else if (opcode == 0x05) {
		Logic::stack_print();
	} else if (opcode == 0x06) {
		Memory::clear();
		Logic::end();
	}
}