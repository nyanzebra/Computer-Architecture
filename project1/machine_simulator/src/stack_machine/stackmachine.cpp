#include "stackmachine.h"

stack_t Stack_Machine::m_stack = L_initStack(0);

void Stack_Machine::processInstruction() {
	memoryAddress_s mem;

	std::vector<std::string> iando = L_instructionAndOperand(L_listToString(m_current_instruction));

	if (iando[0] == "push") {
		std::string x = L_listToString(Memory::loadData(const_cast<char*>(iando[1].c_str())));
		push(x);
	} else if (iando[0] == "pop") {
		pop(iando[1].c_str());
	} else if (iando[0] == "add") {
		int i = Logic::add();
		push(std::to_string(i));
	} else if (iando[0] == "mult") {
		int i = Logic::mult();
		push(std::to_string(i));
	} else if (iando[0] == "prnt") {
		Logic::stack_print();
	} else if (iando[0] == "end") {
		Logic::end();
	}
}