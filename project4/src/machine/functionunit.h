#pragma once

#include "../utility/types.h"

class FunctionUnit {
public:
	FunctionUnit() {}
	~FunctionUnit() {}

	const bool& isBusy() const { return m_isBusy; }
	const bool& isWritable() const { return m_isWritable; }
	const bool& isExecutable() const { return m_isExecutable; }

	const Instruction& getInstruction() const { return m_instruction; }
	void setInstruction(const Instruction& instruction) { m_instruction = instruction; m_isBusy = true; }

	const int& getOpcode() const { return m_opcode; }

	const reg_t& getRS() const { return m_instruction.rs; }
	const reg_t& getRT() const { return m_instruction.rt; }
	const reg_t& getRD() const { return m_instruction.rd; }

	const bool isRSEqualToFURD(const int& rs) const { return (rs == m_instruction.rd) ? true : false; }
	const bool isRTEqualToFURD(const int& rt) const { return (rt == m_instruction.rd) ? true : false; }
	const bool isRDEqualToFURD(const int& rd) const { return (rd == m_instruction.rd) ? true : false; }
	const bool isRDEqualToFURS(const int& rd) const { return (rd == m_instruction.rs) ? true : false; }
	const bool isRDEqualToFURT(const int& rd) const { return (rd == m_instruction.rt) ? true : false; }

	void readOperands();

	//gets the opcode and then checks to see if it is in the map, then exectues the function if it is in the map.
	void execute();

	void writeback();

	void finish() {
		readOperands();
		execute();
		writeback();
	}

private:
	// instruction knowledge
	bool m_isBusy = false;
	bool m_isWritable = false;
	bool m_isExecutable = false;

	int m_opcode = 0;
	Instruction m_instruction;
};