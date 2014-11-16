#pragma once 

//robert baldwin
//general typing is done here
//if make a type it should be type_t
//main reason for this is so we know what is a manufactured type
//structs need to be struct_s

#ifndef TYPES_H
#define TYPES_H

#define MIN_SEGMENT_INSTRUCTION 0 // begin
#define MAX_SEGMENT_INSTRUCTION 4095 // end
#define MIN_SEGMENT_DATA 4096 //begin 
#define MAX_SEGMENT_DATA 4096 + 1023// end
#define MIN_SEGMENT_STACK 4096 + 1024  // begin
#define MAX_SEGMENT_STACK 4096 + 1024 + 256// end

//data types in memory
typedef int word_t;
typedef char* asciiz_t;

//mem
typedef unsigned int instruction_t; // [op][address] = [0000 0000][0000 0000 0000 0000 0000 0000]
typedef int data_t; // [address] = [0000 0000 0000 0000 0000 0000 0000 0000] we can check for null to get full stuff

typedef unsigned int mem_t; // what an address is

//registers
typedef int reg_t;

typedef struct Instruction {
	int opcode = -1, function = -1;
	int rs = -1, rt = -1, rd = -1;
	int aluout = -1, mdr = -1;
	int opA = -1, opB = -1;
	float faluout = -1, fmdr = -1;
	float fopA = -1, fopB = -1;
	int offset = -1, shift = -1;
} Instruction;

#endif