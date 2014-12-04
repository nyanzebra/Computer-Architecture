#include "scoreboard.h"
#include "../machine/functionInterface.h"

std::array<futype, 48> Scoreboard::m_furegisters = { futype::isfree };
bool Scoreboard::m_shouldClear = false;

const bool Scoreboard::isIntegerUnit(const int& opcode) {
	return (!isFloatAddUnit(opcode) && !isFloatMultUnit(opcode) && !isLoadStoreUnit(opcode)) ? true : false;
}

const bool Scoreboard::isFloatAddUnit(const int& opcode) {
	return (opcode == 3 || opcode == 4) ? true : false;
}

const bool Scoreboard::isFloatMultUnit(const int& opcode) {
	return (opcode == 5 || opcode == 6) ? true : false;
}

const bool Scoreboard::isLoadStoreUnit(const int& opcode) {
	return (opcode <= 17 && opcode >= 12) ? true : false;
}

const bool Scoreboard::isRAWHazard() {
	if (m_currentInstruction.rs != -1 && m_currentInstruction.rt != -1) {
		if (m_furegisters[m_currentInstruction.rs] != futype::isfree && m_furegisters[m_currentInstruction.rt] != futype::isfree){
			return true;
		}
	}
	return false;
}

const bool Scoreboard::isWAWHazard() {
	if (m_currentInstruction.rd != -1) {
		if (m_furegisters[m_currentInstruction.rd] != futype::isfree) {
			return true;
		}
	}
	return false;
}

// war combinations:
// mult int
// mult ls
// mult fadd
const bool Scoreboard::isWARHazard() {
	if (!isFloatMultUnit(m_currentInstruction.opcode)) {
		if (!m_floatMult.isExecutable()) {
			if (m_integer.isWritable()) {
				if (m_integer.getWritableInstruction().opcode == 31) {
					return false;
				}
				if (m_integer.getWritableInstruction().rd == m_floatMult.getInstruction().rs
					|| m_integer.getWritableInstruction().rd == m_floatMult.getInstruction().rt) {
					return true;
				}
			}
			if (m_loadStore.isWritable()) {
				if (m_loadStore.getWritableInstruction().rd == m_floatMult.getInstruction().rs
					|| m_loadStore.getWritableInstruction().rd == m_floatMult.getInstruction().rt) {
					return true;
				}
			}
			if (m_floatAdd.isWritable()) {
				if (m_floatAdd.getWritableInstruction().rd == m_floatMult.getInstruction().rs
					|| m_floatAdd.getWritableInstruction().rd == m_floatMult.getInstruction().rt) {
					return true;
				}
			}
		}
	}
	return false;
}

const bool Scoreboard::isStructureHazard() {
	if (isIntegerUnit(m_currentInstruction.opcode) && m_integer.isBusy()) {
		return true;
	} else if (isFloatAddUnit(m_currentInstruction.opcode) && m_floatAdd.isBusy()){
		return true;
	} else if (isFloatMultUnit(m_currentInstruction.opcode) && m_floatMult.isBusy()) {
		return true;
	} else if (isLoadStoreUnit(m_currentInstruction.opcode) && m_loadStore.isBusy()) {
		return true;
	}
	return false;
}

void Scoreboard::execute() {
	m_integer.execute();
	m_floatAdd.execute();
	m_floatMult.execute();
	m_loadStore.execute();
}

void Scoreboard::fetchAssign(const instruction_t& instr) {
	m_currentInstruction.opcode = instr.opcode;

	if (isIType(m_currentInstruction.opcode)) {
		if (isLoading(m_currentInstruction.opcode)) {// maybe needs to be changed
			m_currentInstruction.opB = instr.rs;
		}
		m_currentInstruction.rs = instr.rs;
		m_currentInstruction.rt = instr.rt;
		m_currentInstruction.rd = instr.rt;
		m_currentInstruction.aluout = instr.offset;
		m_currentInstruction.offset = m_currentInstruction.aluout;
	} else if (isRType(m_currentInstruction.opcode)) {
		m_currentInstruction.rs = instr.rs;
		m_currentInstruction.rt = instr.rt;
		m_currentInstruction.rd = instr.rd;
		m_currentInstruction.aluout = instr.shiftamount;
	} else if (isJType(m_currentInstruction.opcode)) {
		m_currentInstruction.offset = instr.target;
		executeFunction(m_currentInstruction);
	}
	if (m_currentInstruction.opcode == 31) {
		Base_Machine::incrementNopCount();
		Base_Machine::incrementInstructionCounter();
		Base_Machine::incrementProgramCounter();
		return;
	}
	// if structure or waw finish everything then move on
	if (!isStructureHazard() && !isWAWHazard()) {
		if (isIntegerUnit(m_currentInstruction.opcode)) {
			setFunctionUnitInteger(m_currentInstruction);
		} else if (isFloatAddUnit(m_currentInstruction.opcode)){
			setFunctionUnitFloatAdd(m_currentInstruction);
		} else if (isFloatMultUnit(m_currentInstruction.opcode)) {
			setFunctionUnitFloatMult(m_currentInstruction);
		} else if (isLoadStoreUnit(m_currentInstruction.opcode)) {
			setFunctionUnitLoadStore(m_currentInstruction);
		}
	}
	if (m_shouldClear) {
		emptyFUs();
		m_shouldClear = false;
	}
}

void Scoreboard::readOperands() {
	if (!isRAWHazard()) {
		m_integer.readOperands();
		m_floatAdd.readOperands();
		m_floatMult.readOperands();
		m_loadStore.readOperands();
	}
}

void Scoreboard::writeBack() {
	if (!isWARHazard()) {
		m_floatAdd.writeback();
		m_floatMult.writeback();
		m_loadStore.writeback();
		m_integer.writeback();
	}
}