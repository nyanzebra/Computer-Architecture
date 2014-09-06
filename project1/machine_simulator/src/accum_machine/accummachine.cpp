#include "accummachine.h"

register_t Accum_Machine::m_accumulator = "";

void Accum_Machine::processInstruction() {
	memoryAddress_s mem;

	std::vector<std::string> iando = L_instructionAndOperand(L_listToString(m_current_instruction));

	if (iando[0] == "stor") {
		store(iando[1].c_str());
	}
	else if (iando[0] == "load") {
		std::string x = L_listToString(Memory::loadData(const_cast<char*>(iando[1].c_str()))); //get value of from address
		load(x.c_str());
	}
	else if (iando[0] == "add") {
		std::string x = L_listToString(Memory::loadData(const_cast<char*>(iando[1].c_str()))); //get value of from address
		Logic::add(x);
	}
	else if (iando[0] == "mult") {
		std::string x = L_listToString(Memory::loadData(const_cast<char*>(iando[1].c_str()))); //get value of from address
		Logic::mult(x);
	}
	else if (iando[0] == "prnt") {
		Logic::accum_print();
	}
	else if (iando[0] == "end") {
		Logic::end();
	}
}