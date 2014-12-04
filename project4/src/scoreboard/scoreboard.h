#pragma once

#include <array>

#include "../machine/functionunit.h"
#include "../utility/types.h"
#include "../machine/basemachine.h"

class Scoreboard {
public:
	Scoreboard() {}
	~Scoreboard() {}

	const bool isRAWHazard();
	const bool isWAWHazard();
	const bool isWARHazard();
	const bool isControlHazard();
	const bool isStructureHazard();

	const bool isIntegerUnit(const int& opcode);
	const bool isFloatAddUnit(const int& opcode);
	const bool isFloatMultUnit(const int& opcode);
	const bool isLoadStoreUnit(const int& opcode);

	void setFunctionUnitInteger(const Instruction& instruction) { m_integer.setInstruction(instruction); Base_Machine::incrementProgramCounter(); }
	void setFunctionUnitLoadStore(const Instruction& instruction) { m_loadStore.setInstruction(instruction); Base_Machine::incrementProgramCounter(); }
	void setFunctionUnitFloatAdd(const Instruction& instruction) { m_floatAdd.setInstruction(instruction); Base_Machine::incrementProgramCounter(); }
	void setFunctionUnitFloatMult(const Instruction& instruction) { m_floatMult.setInstruction(instruction); Base_Machine::incrementProgramCounter(); }

	FunctionUnit& getFUInteger() { return m_integer; }
	FunctionUnit& getFUFloatAdd() { return m_floatAdd; }
	FunctionUnit& getFUFloatMult() { return m_floatMult; }
	FunctionUnit& getFULoadStore() { return m_loadStore; }

	static void clearExecution() { m_shouldClear = true; }
	void emptyFUs() { m_integer.empty(); m_floatAdd.empty(); m_floatMult.empty(); m_loadStore.empty(); }

	static const futype& getFURegister(const unsigned& place) { return m_furegisters[place]; }
	static void setFURegister(const unsigned& place, const futype& fu) { m_furegisters[place] = fu; }

	void fetchAssign(const instruction_t& instruction);
	void readOperands();
	void execute();
	void writeBack();
private:

	FunctionUnit m_integer = FunctionUnit(2,futype::integer);
	FunctionUnit m_floatAdd = FunctionUnit(2,futype::add);
	FunctionUnit m_floatMult = FunctionUnit(6, futype::mult);
	FunctionUnit m_loadStore = FunctionUnit(2, futype::loadstore);
	Instruction m_currentInstruction;
	static std::array<futype, 48> m_furegisters;
	static bool m_shouldClear;
};