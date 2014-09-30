#include "generalpurposeregistermachine.h"
#include "../utility/functionInterface.h"

std::array<reg_t, 32> GPR_Machine::m_registers = L_makeRegisters();

void GPR_Machine::processInstruction() {
	multicycle = true;
	//determine type of instruction
	m_num_cycles += opcodeFunction(m_current_instruction); 
}