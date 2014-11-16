#pragma once
#include <array>
#include "basemachine.h"
#include "../scoreboard/scoreboard.h"

class GPR_Machine : public Base_Machine {
public:
	void processInstruction();

	static reg_t getReg(const int& reg) { return m_registers[reg]; }
	static void setReg(const int& reg, const data_t& data) { m_registers[reg] = data; }

private:
	static std::array<reg_t, 48> m_registers;
	Scoreboard m_scoreboard;
};