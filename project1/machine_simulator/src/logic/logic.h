#include <list>
#include <iostream>
#include <stdlib.h>

#include "../memory/memory.h"
#include "../utility/types.h"

typedef std::list<memory_address> stack;

class Logic {//TODO fix for memory address
public:
	static const int add(stack& s) {
		int i = atoi(Memory::load(s.back()));
		s.pop_back();
		int j = atoi(Memory::load(s.back()));
		s.pop_back();
		return i + j;
	}
	static const int mult(stack& s) {
		int i = atoi(Memory::load(s.back()));
		s.pop_back();
		int j = atoi(Memory::load(s.back()));
		s.pop_back();
		return i * j;
	}	
	static int end() {
		return 0;
	}
	static void print(stack& s) { 
		byte* statement = Memory::load(s.back());
		std::cout << statement << std::endl;
		s.pop_back();
	}
};

