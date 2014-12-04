#pragma once

#include <list>

#include "../utility/types.h"
#include "../fileio/fileparser.h"

class FunctionUnit {
public:
	FunctionUnit(const int& nstages, const futype& type) : m_nstages(nstages), m_type(type) {}
	~FunctionUnit() {}

	const bool& isBusy() const { return m_isBusy; }
	const bool& isWritable() const { return m_isWritable; }
	const bool& isExecutable() const { return m_isExecutable; }
	const bool& isBufferEmpty() const { return (m_execute_instructions.size() > 0) ? false : true; }

	const Instruction& getInstruction() const { return m_instruction; }
	void setInstruction(const Instruction& instruction) { m_instruction = instruction; }

	const Instruction& getWritableInstruction() const { return m_execute_instructions.front(); }

	const futype& getType() const { return m_type; }

	void empty() { 
		if (FileParser::getFilename() == "lab4a.s") {
			m_instruction = Instruction();
		}
		m_readoperand_instruction = Instruction();
	}

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

	//type
	futype m_type;

	int m_nstages = 0; //for execute or mem whatever
	Instruction m_instruction;
	Instruction m_readoperand_instruction;
	std::list<Instruction> m_execute_instructions;
	Instruction m_writeback_instruction;
};