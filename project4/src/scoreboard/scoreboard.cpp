#include "scoreboard.h"
#include "../machine/functionInterface.h"

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

void Scoreboard::resolveRAWHazard() {
	if (m_integer.isRSEqualToFURD(m_currentInstruction.rs) || m_integer.isRTEqualToFURD(m_currentInstruction.rt)) {
		m_integer.finish();
	} else if (m_floatAdd.isRSEqualToFURD(m_currentInstruction.rs) || m_floatAdd.isRTEqualToFURD(m_currentInstruction.rt)){
		m_floatAdd.finish();
	} else if (m_floatMult.isRSEqualToFURD(m_currentInstruction.rs) || m_floatMult.isRTEqualToFURD(m_currentInstruction.rt)) {
		m_floatMult.finish();
	} else if (m_loadStore.isRSEqualToFURD(m_currentInstruction.rs) || m_loadStore.isRTEqualToFURD(m_currentInstruction.rt)) {
		m_loadStore.finish();
	}
}

void Scoreboard::resolveWAWHazard() {
	if (m_integer.isRDEqualToFURD(m_currentInstruction.rd)) {
		m_integer.finish();
	} else if (m_floatAdd.isRDEqualToFURD(m_currentInstruction.rd)){
		m_floatAdd.finish();
	} else if (m_floatMult.isRDEqualToFURD(m_currentInstruction.rd)) {
		m_floatMult.finish();
	} else if (m_loadStore.isRDEqualToFURD(m_currentInstruction.rd)) {
		m_loadStore.finish();
	}
}

// war combinations:
// mult int
// mult ls
// mult fadd
void Scoreboard::resolveWARHazard() {
	if (!isFloatMultUnit(m_currentInstruction.opcode)) {
		if (m_floatMult.isRDEqualToFURS(m_currentInstruction.rd) || m_floatMult.isRDEqualToFURT(m_currentInstruction.rd)) {
			m_floatMult.finish();
		}
	}
}

void Scoreboard::resolveStructureHazard() {
	if (isIntegerUnit(m_currentInstruction.opcode) && m_integer.isBusy()) {
		m_integer.finish();
		m_integer.setInstruction(m_currentInstruction);
	} else if (isFloatAddUnit(m_currentInstruction.opcode) && m_floatAdd.isBusy()){
		m_floatAdd.finish();
		m_floatAdd.setInstruction(m_currentInstruction);
	} else if (isFloatMultUnit(m_currentInstruction.opcode) && m_floatMult.isBusy()) {
		m_floatMult.finish();
		m_floatMult.setInstruction(m_currentInstruction);
	} else if (isLoadStoreUnit(m_currentInstruction.opcode) && m_loadStore.isBusy()) {
		m_loadStore.finish();
		m_loadStore.setInstruction(m_currentInstruction);
	}
}

void Scoreboard::execute() {
	m_integer.execute();
	m_floatAdd.execute();
	m_floatMult.execute();
	m_loadStore.execute();
}

void Scoreboard::fetchAssign(const instruction_t& instr) {
	m_currentInstruction.opcode = instr >> 26;

	if (isIType(m_currentInstruction.opcode)) {
		if (isLoading(m_currentInstruction.opcode)) {// maybe needs to be changed
			m_currentInstruction.opB = getIType(instr)[1];
		}
		m_currentInstruction.rs = getIType(instr)[0];
		m_currentInstruction.rt = getIType(instr)[1];
		m_currentInstruction.rd = getIType(instr)[1];
		m_currentInstruction.aluout = (getIType(instr)[2]);
		m_currentInstruction.offset = m_currentInstruction.aluout;
	} else if (isRType(m_currentInstruction.opcode)) {
		m_currentInstruction.rs = getRType(instr)[0];
		m_currentInstruction.rt = getRType(instr)[1];
		m_currentInstruction.rd = getRType(instr)[2];
		m_currentInstruction.aluout = (getRType(instr)[3]);
	} else if (isJType(m_currentInstruction.opcode)) {
		m_currentInstruction.offset = instr & 0x03FFFFFF;
		executeFunction(m_currentInstruction);
	}

	// if structure or waw finish everything then move on
	resolveStructureHazard();
	resolveWAWHazard();
}

void Scoreboard::readOperands() {
	m_integer.readOperands();
	m_floatAdd.readOperands();
	m_floatMult.readOperands();
	m_loadStore.readOperands();
	resolveRAWHazard();
}

void Scoreboard::writeBack() {
	resolveWARHazard();
	m_floatAdd.writeback();
	m_floatMult.writeback();
	m_loadStore.writeback();
	m_integer.writeback();
}