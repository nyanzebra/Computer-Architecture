#include "generalpurposeregistermachine.h"
#include "../utility/functionInterface.h"
#include "../utility/pipelineInterface.h"

std::array<reg_t, 32> GPR_Machine::m_registers = L_makeRegisters();

void GPR_Machine::processInstruction() {
	multicycle = true;
	//determine type of instruction
	instr = m_current_instruction;

	//backups
	latch_fetch_decode_old = latch_fetch_decode_new;
	latch_fetch_decode_new.current_instruction = instr; //set instruction

	latch_decode_execute_old = latch_decode_execute_new;
	latch_decode_execute_new = decode(); //decode

	latch_execute_memory_old = latch_execute_memory_new;
	latch_execute_memory_new = executeInstruction(); //execute

	latch_memory_writeback_old = latch_memory_writeback_new;
	latch_memory_writeback_new = pipelineMemory(); //memory

	//writeback
	int result = writeback(); 
}