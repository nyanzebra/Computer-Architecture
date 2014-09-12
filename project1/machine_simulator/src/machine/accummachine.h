#pragma once

#include "basemachine.h"

class Accum_Machine  : public Base_Machine {
public:
	void processInstruction();	

	static reg_t getReg() { return m_accumulator; }
	static void setReg(const reg_t& reg) { m_accumulator = reg; }
private:
	static reg_t m_accumulator;
};