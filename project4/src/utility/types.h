#pragma once 

//robert baldwin
//general typing is done here
//if make a type it should be type_t
//main reason for this is so we know what is a manufactured type
//structs need to be struct_s

#ifndef TYPES_H
#define TYPES_H

#define MIN_SEGMENT_INSTRUCTION 0 // begin
#define MAX_SEGMENT_INSTRUCTION 128 // end
#define MIN_SEGMENT_DATA 0 //begin 
#define MAX_SEGMENT_DATA 128// end
#define MIN_SEGMENT_FLOAT 0  // begin
#define MAX_SEGMENT_FLOAT 128// end

//data types in memory
typedef int word_t;
typedef char* asciiz_t;

//mem
typedef struct instruction_t {
		int opcode : 6;
		int rs : 8;
		int rt : 8;
		int rd : 8;
		int offset : 16;
		int target : 26;
		int shiftamount : 8;
		int function : 10;
} instrution_t;

typedef int data_t; // [address] = [0000 0000 0000 0000 0000 0000 0000 0000] we can check for null to get full stuff

typedef unsigned int mem_t; // what an address is

//registers
typedef int reg_t;

typedef struct Instruction {
	int opcode = -1, function = -1;
	int rs = -1, rt = -1, rd = -1;
	int aluout = -1;
	int opA = -1, opB = -1;
	float faluout = -1;
	float fopA = -1, fopB = -1;
	int offset = -1, shift = -1;
	int whenExecuted = 0;
} Instruction;

enum futype {
	isfree,
	integer,
	loadstore,
	mult,
	add,
};

#endif