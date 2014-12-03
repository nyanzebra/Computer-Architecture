#pragma once
#ifndef FUNCTIONINTERFACE_H
#define FUNCTIONINTERFACE_H

#include <array>
#include <unordered_map>
#include <functional>
#include "../utility/types.h"

void executeFunction(Instruction& instruction);

//determine type
const bool isFloatType(const int& op);

const bool isRType(const int& op);

const bool isIType(const int& op);

const bool isJType(const int& op);

const bool isBranch(const int& opcode);

const bool isLoading(const int& opcode);

//r type add pipeline
void addR(Instruction& instruction);

void addI(Instruction& instruction);

//i type sub pipeline
void subI(Instruction& instruction);

void loadAscii(Instruction& instruction);

void loadByte(Instruction& instruction);

void loadDouble(Instruction& instruction);

void storeDouble(Instruction& instruction);

void insertNOP(Instruction& instruction);

//gets the immediate value from Jtype, then sets the pc to that address.
void branch(Instruction& instruction);

//breaks up the instruction into Itype values, then checks to see if the source register is equal to 0, then jumps if it is.
void branchEqualZero(Instruction& instruction);

//breaks up the instruction into Itype values, then checks to see if the dest register is >= source register 
//then jumps if it is.
void branchGreaterEqual(Instruction& instruction);

////breaks up the instruction into Itype values, then checks to see if the dest register is not equal to source register
//then jumps if it is.
void branchNotEqual(Instruction& instruction);

void fadd(Instruction& instruction);

void fmult(Instruction& instruction);

void fsub(Instruction& instruction);

// Syscall has multiple different internal functions.
// uses registers 29, 30, and 31. 29 is return value / parameter.
void syscall(Instruction& instruction);

//fills the map with <opcode, function>
void initUMapOpcodeGroup();

#endif
