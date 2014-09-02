#include <list>

#include "../memory/memory.h"
#include "../utility/types.h"

class Stack_Machine {//TODO: need to fetch main from instructions
public:
	Stack_Machine();
	~Stack_Machine();
	
	byte* getNextInstruction();
	void* getData(const byte& location);

	void push(const memory_address& value) { m_stack.push_back(value); }
	void pop(const memory_address& location) { Memory::store(m_stack.back(), location); m_stack.pop_back(); }

	void processInstruction();

	void execute();
private:
	std::list<memory_address> m_stack;
	int* m_stack_pointer;
};