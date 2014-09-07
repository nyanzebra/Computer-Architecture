#pragma once

#include <list>

#include "../memory/memory.h"

class Accum_Machine {
public:

	void processInstruction();
	void getNextInstruction(); //updates pc for you so no need to mess with program counter

	void store(const byte_t* location) { 
		Memory::storeData(location, L_stringToList(m_accumulator));
		m_accumulator = ""; 
	}
	void load(const std::string& value) { m_accumulator = value; }

	static reg_t getReg() { return m_accumulator; }
	static void setReg(const reg_t& reg) { m_accumulator = reg; }
	
	void execute();//goes through all instructions by checking to see if pc == ic
private:
	int m_program_counter;
	std::list<byte_t> m_current_instruction;
	static reg_t m_accumulator;
};