#include <string>

#ifndef TYPES_H
#define TYPES_H

//data types in memory
typedef char byte;
typedef short halfword;
typedef int word;
typedef char* asciiz;

//what memory is address and pointer value
struct memory_address
{
	int address;
	char* value;
};

#endif