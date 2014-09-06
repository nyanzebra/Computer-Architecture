#pragma once

#include "../pch.h"

class Accum_Machine : public Base_Machine {
public:

	void processInstruction();

	void store(const byte_t* location) { storeData(location, L_stringToList(m_accumulator)); m_accumulator = ""; }
	void load(const std::string& value) { m_accumulator = value; }

	static register_t getReg() { return m_accumulator; }
	static void setReg(const register_t& reg) { m_accumulator = reg; }
	
private:
	static register_t m_accumulator;
};