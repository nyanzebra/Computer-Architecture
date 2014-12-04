#include "generalpurposeregistermachine.h"
#include "functionInterface.h"
#include "../scoreboard/scoreboard.h"

std::array<reg_t, 48> GPR_Machine::m_registers = { 0 };

// we fetch instruction every time
// we decode the instruction
// check and see if it can be put in function unit
// if so then good 
// if not it must stall
// so what is stalling here?
// if stall we cannot go forward (we follow in order instructions)
// therefore if we stall we should execute and writeback everything
// so if we do not stall we pipe

//
void GPR_Machine::processInstruction() {
	//fetch decode
	m_registers[2];
	m_scoreboard.writeBack();
	m_scoreboard.execute();
	m_scoreboard.readOperands();
	m_scoreboard.fetchAssign(m_current_instruction);
}

void GPR_Machine::processRemainingInstructions() {
	m_scoreboard.fetchAssign(m_current_instruction);
	m_scoreboard.readOperands();
	while (!m_scoreboard.getFUFloatAdd().isBufferEmpty() || !m_scoreboard.getFUFloatMult().isBufferEmpty()
		|| !m_scoreboard.getFUInteger().isBufferEmpty() || !m_scoreboard.getFULoadStore().isBufferEmpty()) {
		m_scoreboard.writeBack();
		m_scoreboard.execute();
		m_num_cycles++;
	}
}