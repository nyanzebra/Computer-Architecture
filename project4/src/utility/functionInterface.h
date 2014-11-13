#pragma once
#ifndef FUNCTIONINTERFACE_H
#define FUNCTIONINTERFACE_H

#include <array>
#include <unordered_map>
#include <functional>

#include "../machine/generalpurposeregistermachine.h"
#include "../logic/logic.h"
#include "latches.h"

//variable that holds the current instruction, set by opcodeFunction
static int instr = 0;

//determine type
const bool& isRType(const int& op) {
	return (op >= 0 && op < 10 ? true : false);
}

const bool& isIType(const int& op) {
	return ((op >= 10 && op < 30) ? true : false);
}

const bool& isJType(const int& op) {
	return (op >= 30 && op != 31 ? true : false);
}

const bool& isBranch(const int& opcode) {
	return (opcode == 0x1E ? true : false);
}

const bool& isLoading(const int& opcode) {
	return ((opcode >= 0xC && opcode < 0xF) ? true : false);
}

//Breaks up the instruction into 4 different values and returns them in an array.
const std::array<int, 4> getRType(const instruction_t& instr) {
	std::array<int, 4> values;
	values[0] = (instr & 0x03E00000) >> 21; //source reg1
	values[1] = (instr & 0x001F0000) >> 16; //source reg2
	values[2] = (instr & 0x0000F800) >> 11; //dest reg
	values[3] = (instr & 0x000007C0) >> 6;  //shift value
	return values;
};

//Breaks up the instruction into 3 different values and returns them in an array.
const std::array<int, 3> getIType(const instruction_t& instr) {
	std::array<int, 3> values;
	values[0] = (instr & 0x03E00000) >> 21; //source reg
	values[1] = (instr & 0x001F0000) >> 16; //dest reg
	values[2] = (instr & 0x0000FFFF);       //imm value
	return values;
};

//returns the immediate value that is stored in J type instructions
const int getJType(const instruction_t& instr) {
	int value = (instr & 0x03FFFFFF);       //immediate value
	return value;
};

//map that stores functions with an opcode as their key
std::unordered_map<int, std::function<void()>> umap_opcodeGroups;

//r type add pipeline
void add() {
	latch_decode_execute_old.alu_out = Logic::add(latch_decode_execute_old.op_A, latch_decode_execute_old.op_B);
}

//i type sub pipeline
void executeSubtract() {
	latch_decode_execute_old.alu_out = Logic::sub(latch_decode_execute_old.op_A, latch_decode_execute_old.offset);
}

//breaks up the instruction to get Itype values
//Then sets the dest reg to the immediate value.
void executeAdd() {
	latch_decode_execute_old.alu_out = Logic::add(latch_decode_execute_old.op_A, latch_decode_execute_old.offset); //load
}

void loadAscii() {
	latch_decode_execute_old.alu_out =  latch_decode_execute_old.offset;
}

void loadByte() {
	latch_decode_execute_old.alu_out = Memory::loadData(Logic::add(latch_decode_execute_old.op_A, latch_decode_execute_old.offset));
}

void insertNOP() {
	latch_decode_execute_new.alu_out = -1;
	latch_decode_execute_new.opcode = -1;
	latch_decode_execute_new.offset = -1;
	latch_decode_execute_new.op_A = -1;
	latch_decode_execute_new.op_B = -1;
	latch_decode_execute_new.rd = -1;
	latch_decode_execute_new.rs = -1;
	latch_decode_execute_new.rt = -1;
}

void insertNOP1() {
	latch_decode_execute_old.alu_out = -1;
	latch_decode_execute_old.opcode = -1;
	latch_decode_execute_old.offset = -1;
	latch_decode_execute_old.op_A = -1;
	latch_decode_execute_old.op_B = -1;
	latch_decode_execute_old.rd = -1;
	latch_decode_execute_old.rs = -1;
	latch_decode_execute_old.rt = -1;
}

//gets the immediate value from Jtype, then sets the pc to that address.
void branch() {
	Base_Machine::setPC(getJType(instr));   //set pc to value(memory location)
	latch_fetch_decode_new.current_instruction = -1;
}

//breaks up the instruction into Itype values, then checks to see if the source register is equal to 0, then jumps if it is.
void branchEqualZero() {
	if (latch_decode_execute_old.op_B == 0) { //checks to see if it is equal to 0
		Base_Machine::setPC(latch_decode_execute_old.offset); // sets pc to the immediate value
	}
	insertNOP1();
}

//breaks up the instruction into Itype values, then checks to see if the dest register is >= source register 
//then jumps if it is.
void branchGreaterEqual() {
	if (latch_decode_execute_old.op_B >= latch_decode_execute_old.op_A) // checks if dest reg is greater or equal to source reg
		Base_Machine::setPC(latch_decode_execute_old.offset); //sets pc to immediate
	insertNOP1();
}
////breaks up the instruction into Itype values, then checks to see if the dest register is not equal to source register
//then jumps if it is.
void branchNotEqual() {
	if (latch_decode_execute_old.op_A != latch_decode_execute_old.op_B) //checks to see if dest reg != source reg
		Base_Machine::setPC(latch_decode_execute_old.offset); //set pc to the immediate
	insertNOP1();
}

// Syscall has multiple different internal functions.
// uses registers 29, 30, and 31. 29 is return value / parameter.
void syscall() {
	if (latch_execute_memory_new.alu_out == 1) { //print out reg 30
		std::cout << GPR_Machine::getReg(30);
	} else if (latch_execute_memory_new.alu_out == 8) { //get user input string
		std::string input;
		std::cout << "> ";
		std::getline(std::cin, input);
		int address = GPR_Machine::getReg(30);
		int size = GPR_Machine::getReg(31);
		int counter = 0;
		input.substr(0, size);

		for (char c : input) {
			Memory::storeData(address, c);
			address++;
		}
	} else if (latch_execute_memory_new.alu_out == 4) { //print string that is located in register 30
		if (Logic::m_hash_strings->find(Memory::loadData(GPR_Machine::getReg(30))) != Logic::m_hash_strings->end()) {
			std::string s = Logic::m_hash_strings->find(Memory::loadData(GPR_Machine::getReg(30)))->second;
			if (!s.empty()) {
				std::cout << s;
			}
		}
	} else if (latch_execute_memory_new.alu_out == 10) {//exit
		// exit is handled already due to logic check in basemachine.cpp
		bufferClear();
	}
	insertNOP1();
}

//fills the map with <opcode, function>
void initUMapOpcodeGroup() {
	//r
	umap_opcodeGroups.insert({ 0x0, syscall });
	
	umap_opcodeGroups.insert({ 0x2, add });
	//umap_opcodeGroups.insert({ 0x3, sub });

	//i
	umap_opcodeGroups.insert({ 0xA, executeAdd });
	umap_opcodeGroups.insert({ 0xB, executeSubtract });
	umap_opcodeGroups.insert({ 0xC, executeAdd });
	umap_opcodeGroups.insert({ 0xD, executeAdd });
	umap_opcodeGroups.insert({ 0xE, loadAscii });
	umap_opcodeGroups.insert({ 0xF, loadByte });

	umap_opcodeGroups.insert({ 0x1B, branchEqualZero });
	umap_opcodeGroups.insert({ 0x1C, branchGreaterEqual });
	umap_opcodeGroups.insert({ 0x1D, branchNotEqual });

	//j
	umap_opcodeGroups.insert({ 0x1E, branch });

	//1F is nop
	umap_opcodeGroups.insert({ 0x1F, insertNOP1 });
}

#endif
