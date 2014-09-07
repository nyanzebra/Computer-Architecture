#pragma once 

//robert baldwin
//general typing is done here
//if make a type it should be type_t
//main reason for this is so we know what is a manufactured type
//structs need to be struct_s

#ifndef TYPES_H
#define TYPES_H
#include <list>
#include <string>

//data types in memory
typedef char byte_t;
typedef short halfword_t;
typedef int word_t;
typedef char* asciiz_t;

//stack
typedef std::list<std::string> stack_t;

//registers
typedef std::string reg_t;

//what memory is address and alias as could have X as the address alias
struct memoryAddress_s {
	unsigned int address;
	std::string alias;
};

#endif