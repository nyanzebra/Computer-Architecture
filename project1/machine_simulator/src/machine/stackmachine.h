#pragma once

#include "basemachine.h"

class Stack_Machine  : public Base_Machine {//TODO: need to fetch main from instructions
public:
	void processInstruction(); // defined processInstruction

private:
	void pushAddress(const mem_t& addr) { Memory::pushStackAddr(addr); } // call memory push
	void pushData(const data_t& data) { Memory::pushStackData(data); } // call memory push
	void pop(const mem_t& addr) { Memory::popStack(addr); } // call memory pop
};