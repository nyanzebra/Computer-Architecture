#include "functionunit.h"
#include "generalpurposeregistermachine.h"
#include "functionInterface.h"

template <typename T>
void setOperands(T& opa, T& opb, const int& rs, const int& rt) {
	opa = 0;
	opb = 0;
	if (rs != -1) {
		opa = GPR_Machine::getReg(rs);
		
	}
	if (rt != -1) {
		opb = GPR_Machine::getReg(rt);
	}
}

void FunctionUnit::readOperands() { //TODO add float stuff
	if (!m_isBusy && m_instruction.opcode != -1) {
		if (isIType(m_instruction.opcode)) {
			setOperands(m_instruction.opA, m_instruction.opB, m_instruction.rs, m_instruction.rt);
		} else if (isRType(m_instruction.opcode)) {
			setOperands(m_instruction.opA, m_instruction.opB, m_instruction.rs, m_instruction.rt);
		}
		if (isFloatType(m_instruction.opcode)) {
			setOperands(m_instruction.fopA, m_instruction.fopB, m_instruction.rs, m_instruction.rt);
		}
		m_readoperand_instruction = m_instruction;
		m_instruction.opcode = -1;
		if (m_readoperand_instruction.opcode != 0) {
			Scoreboard::setFURegister(m_readoperand_instruction.rd, m_type);
		}
		m_isExecutable = true;
		if (!Base_Machine::isPipeScoreboard()) {
			m_isBusy = true;
		}
	}
}

void FunctionUnit::execute() {
	if (m_isExecutable) {
		executeFunction(m_readoperand_instruction);

		if (Base_Machine::isPipeScoreboard()) {
			m_isBusy = false;
		}

		// add to execution list
		if (m_readoperand_instruction.whenExecuted == 0) {
			m_readoperand_instruction.whenExecuted = Base_Machine::getCycles();
			m_execute_instructions.push_back(m_readoperand_instruction);
			Base_Machine::incrementInstructionCounter();
		}

		m_isWritable = true;
		m_isExecutable = false;
	}
}

void FunctionUnit::writeback() {
	if (m_execute_instructions.size() > 0) {
		Instruction temp = m_execute_instructions.front();
		if (temp.opcode == -1) {
			m_isBusy = false;
			m_isWritable = false;
			return;
		}
		if (Base_Machine::isPipeScoreboard() && m_execute_instructions.size() > 0) {
			m_isWritable = true;
		}
		if (m_isWritable && (temp.whenExecuted + m_nstages <= Base_Machine::getCycles())) {
			if (isRType(temp.opcode) || isIType(temp.opcode)) {
				if (isFloatType(temp.opcode)) {
					GPR_Machine::setReg(temp.rd, temp.faluout);
				} else {
					GPR_Machine::setReg(temp.rd, temp.aluout);
				}
			}

			m_isBusy = false;
			m_isWritable = false;
			m_execute_instructions.pop_front();
			if (temp.opcode != 31 && temp.opcode != 0) {
				Scoreboard::setFURegister(temp.rd, futype::isfree);
			}
		}
	}
}