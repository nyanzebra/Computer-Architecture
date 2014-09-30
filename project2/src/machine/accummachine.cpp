#include "accummachine.h"

reg_t Accum_Machine::m_accumulator = 0;

void Accum_Machine::processInstruction() {

	instruction_t instruction = m_current_instruction;
	data_t opcode = instruction >> 24;
	instruction = instruction & 0x00ffffff;

	if (opcode == 0x02) {
		Memory::storeData(instruction, m_accumulator);
	} else if (opcode == 0x01) {
		m_accumulator = Memory::loadData(instruction);
	} else if (opcode == 0x03) {
		Logic::add(instruction);
	} else if (opcode == 0x04) {
		Logic::mult(instruction);
	} else if (opcode == 0x05) {
		Logic::accum_print();
	} else if (opcode == 0x06) {
		Logic::end();
	}
}