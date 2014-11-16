#pragma once

#include "../machine/functionunit.h"
#include "../utility/types.h"

class Scoreboard {
public:
	Scoreboard() {}
	~Scoreboard() {}

	void resolveRAWHazard();
	void resolveWAWHazard();
	void resolveWARHazard();
	const bool isControlHazard();
	void resolveStructureHazard();

	const bool isIntegerUnit(const int& opcode);
	const bool isFloatAddUnit(const int& opcode);
	const bool isFloatMultUnit(const int& opcode);
	const bool isLoadStoreUnit(const int& opcode);

	void setFunctionUnitInteger(const Instruction& instruction) { m_integer.setInstruction(instruction); }
	void setFunctionUnitLoadStore(const Instruction& instruction) { m_loadStore.setInstruction(instruction); }
	void setFunctionUnitFloatAdd(const Instruction& instruction) { m_floatAdd.setInstruction(instruction); }
	void setFunctionUnitFloatMult(const Instruction& instruction) { m_floatMult.setInstruction(instruction); }

	FunctionUnit& getFUInteger() { return m_integer; }
	FunctionUnit& getFUFloatAdd() { return m_floatAdd; }
	FunctionUnit& getFUFloatMult() { return m_floatMult; }
	FunctionUnit& getFULoadStore() { return m_loadStore; }

	void fetchAssign(const instruction_t& instruction);
	void readOperands();
	void execute();
	void writeBack();
private:
	FunctionUnit m_integer;
	FunctionUnit m_floatAdd;
	FunctionUnit m_floatMult;
	FunctionUnit m_loadStore;
	Instruction m_currentInstruction;
};