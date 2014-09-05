#include <string>

#ifndef TYPES_H
#include <string>

#define TYPES_H

//data types in memory
typedef char byte;
typedef short halfword;
typedef int word;
typedef char* asciiz;

//stack
typedef std::list<std::string> stack;

//what memory is address and pointer value
struct memory_address {
	bool data_or_instruction;
	int address;
	std::string alias;
};

#endif