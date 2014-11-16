#include "functionunit.h"
#include "generalpurposeregistermachine.h"
#include "functionInterface.h"

void FunctionUnit::readOperands() {
	if (!m_isBusy && m_instruction.opcode != -1) {
		if (isIType(m_instruction.opcode)) {
			m_instruction.opA = GPR_Machine::getReg(m_instruction.rs);
			m_instruction.opB = GPR_Machine::getReg(m_instruction.rt);
		} else if (isRType(m_instruction.opcode)) {
			m_instruction.opA = GPR_Machine::getReg(m_instruction.rs);
			m_instruction.opB = GPR_Machine::getReg(m_instruction.rt);
		}
		m_isExecutable = true;
		m_isBusy = true;
	}
}

void FunctionUnit::execute() {
	if (m_isExecutable) {
		if (m_instruction.opcode != -1) {
			if (m_instruction.opcode == 31) {
				Base_Machine::incrementNopCount();
			}
			executeFunction(m_instruction);
		}
		m_isWritable = true;
		m_isExecutable = false;
	}
}

void FunctionUnit::writeback() {
	if (m_isWritable) {
		if (isRType(m_instruction.opcode) || isIType(m_instruction.opcode)) {
			GPR_Machine::setReg(m_instruction.rd, m_instruction.mdr);
		}

		m_isBusy = false;
		m_isWritable = false;
	}
}